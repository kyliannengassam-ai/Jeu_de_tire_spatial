#include "../include/Game.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructeur
Game::Game()
    : mIsGameOver(false), mScore(0), mLives(3), mDifficulty(Difficulty::Easy), 
      mGameState(GameState::Menu), mElapsedTime(0.0f)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::InitialiserJeu(){
    mJoueur.mPosX = 400.0f;
    mJoueur.mPosY = 500.0f;
    mJoueur.mW = 50.0f;
    mJoueur.mH = 50.0f;
    mJoueur.mVitesse = 50.0f; // pixels / seconde
    mJoueur.mPointsDeVie = 3;

    mProjectiles.clear();
    mListeAsteroides.clear();

    mScore = 0;
    mElapsedTime = 0.0f;
    
    // Définir les paramètres selon la difficulté
    switch(mDifficulty) {
        case Difficulty::Easy:
            mLives = 5;
            mMaxAsteroids = 3;
            mAsteroidSpawnChance = 5.0f;
            mAsteroidSpawnDecreasePerSecond = 0.03f;
            break;
        case Difficulty::Medium:
            mLives = 3;
            mMaxAsteroids = 6;
            mAsteroidSpawnChance = 10.0f;
            mAsteroidSpawnDecreasePerSecond = 0.05f;
            break;
        case Difficulty::Hard:
            mLives = 2;
            mMaxAsteroids = 10;
            mAsteroidSpawnChance = 15.0f;
            mAsteroidSpawnDecreasePerSecond = 0.08f;
            break;
    }
    
    mGameState = GameState::Playing;
    mIsGameOver = false;
}

void Game::GererEntrees(const bool* keys){
    // On utilise un pas temporel fixe pour le déplacement clavier (si tu veux précision, passe deltaTime)
    const float frameTime = 1.0f / 60.0f;
    if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
        mJoueur.mPosX -= mJoueur.mVitesse * frameTime;
        if(mJoueur.mPosX < 0.0f) mJoueur.mPosX = 0.0f;
    }
    if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        mJoueur.mPosX += mJoueur.mVitesse * frameTime;
        if(mJoueur.mPosX + mJoueur.mW > 800.0f) mJoueur.mPosX = 800.0f - mJoueur.mW;
    }
    if(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]){
        mJoueur.mPosY -= mJoueur.mVitesse * frameTime;
        if(mJoueur.mPosY < 0.0f) mJoueur.mPosY = 0.0f;
    }
    if(keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]){
        mJoueur.mPosY += mJoueur.mVitesse * frameTime;
        if(mJoueur.mPosY + mJoueur.mH > 600.0f) mJoueur.mPosY = 600.0f - mJoueur.mH;
    }

    // Tirer sur appui (détecte la transition d'état pour éviter tirs continus)
    static bool prevSpace = false;
    bool space = keys[SDL_SCANCODE_SPACE] != 0;
    if(space && !prevSpace){
        Tirer();
    }
    prevSpace = space;
}

void Game::Tirer(){
    Projectile projectile;
    projectile.mPosX = mJoueur.mPosX + mJoueur.mW / 2.0f - 7.5f;
    projectile.mPosY = mJoueur.mPosY;
    projectile.mVitesse = 700.0f;
    projectile.mW = 5.0f;
    projectile.mH = 20.0f;
    projectile.bIsActive = true;
    mProjectiles.push_back(projectile);
}

void Game::GenererAsteroide(){
    Asteroide asteroide;
    asteroide.mW = 40.0f;
    asteroide.mH = 40.0f;
    asteroide.mPosX = static_cast<float>(std::rand() % (800 - static_cast<int>(asteroide.mW)));
    asteroide.mPosY = -asteroide.mH;
    asteroide.mVitesse = 50.0f + static_cast<float>(std::rand() % 150);
    asteroide.mType = std::rand() % 3;
    mListeAsteroides.push_back(asteroide);
}

static bool RectsIntersect(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh){
    return !(ax + aw < bx || bx + bw < ax || ay + ah < by || by + bh < ay);
}

void Game::Update(float deltaTime){
    if(mGameState != GameState::Playing) return;

    // Accumulate elapsed time and decrease asteroid spawn chance
    mElapsedTime += deltaTime;
    float currentSpawnChance = mAsteroidSpawnChance - (mElapsedTime * mAsteroidSpawnDecreasePerSecond);
    if(currentSpawnChance < 1.0f) currentSpawnChance = 1.0f;  // Spawn minimum d'1%

    // Déplacer projectiles
    for(auto& p : mProjectiles){
        if(p.bIsActive){
            p.mPosY -= p.mVitesse * deltaTime;
            if(p.mPosY + p.mH < 0.0f){
                p.bIsActive = false;
            }
        }
    }

    // Déplacer astéroïdes
    for(auto& a : mListeAsteroides){
        a.mPosY += a.mVitesse * deltaTime;
    }

    // Collision entre projectiles et astéroïdes
    for(auto& a : mListeAsteroides){
        for(auto& p : mProjectiles){
            if(!p.bIsActive) continue;
            if(RectsIntersect(p.mPosX, p.mPosY, p.mW, p.mH, a.mPosX, a.mPosY, a.mW, a.mH)){
                p.bIsActive = false;
                // Marquer l'asteroide pour suppression en le déplaçant hors-écran et en changeant type
                a.mPosY = 10000.0f;
                a.mType = -1;
                mScore += 100;
                break;
            }
        }
    }

    // Collision entre astéroïdes et vaisseau
    for(auto& a : mListeAsteroides){
        if(a.mType != -1 && RectsIntersect(mJoueur.mPosX, mJoueur.mPosY, mJoueur.mW, mJoueur.mH,
                                          a.mPosX, a.mPosY, a.mW, a.mH)){
            // Perte de vie sans arrêter le jeu immédiatement
            mLives = (mLives - 1 >= 0) ? mLives - 1 : 0;
            a.mPosY = 10000.0f;
            a.mType = -1; // marquer pour suppression
            std::cout << "Collision! Vies: " << mLives << "\n";
        }
    }

    // Gestion astéroïdes arrivés en bas -> perte de vie
    for(auto& a : mListeAsteroides){
        if(a.mPosY > 600.0f && a.mType != -1){
            mLives = (mLives - 1 >= 0) ? mLives - 1 : 0;
            a.mType = -1; // marquer pour suppression
        }
    }

    // Supprimer projectiles inactifs
    mProjectiles.erase(std::remove_if(mProjectiles.begin(), mProjectiles.end(),
        [](const Projectile& p){ return !p.bIsActive; }), mProjectiles.end());

    // Supprimer astéroïdes marqués ou hors écran
    mListeAsteroides.erase(std::remove_if(mListeAsteroides.begin(), mListeAsteroides.end(),
        [](const Asteroide& a){ return a.mType == -1 || a.mPosY > 1000.0f; }), mListeAsteroides.end());

    // Génération aléatoire d'astéroïdes avec chance décroissante
    if(static_cast<int>(mListeAsteroides.size()) < mMaxAsteroids) {
        if((std::rand() % 1000) < currentSpawnChance) {
            GenererAsteroide();
        }
    }

    // Vérifier game over
    if(mLives <= 0){
        mIsGameOver = true;
        mGameState = GameState::GameOver;
        std::cout << "Game Over\n";
    }
}

void Game::ResetGame(){
    InitialiserJeu();
}
