#include"../include/Game.h"
#include<algorithm> // Pour std::remove_if
#include <iostream>

Game::Game(): mIsGameOver(false){
    InitialiserJeu();
}
void Game::InitialiserJeu(){
    // Initialisation du vaisseau joueur
    mJoueur.mPosX = 400.0f;
    mJoueur.mPosY = 500.0f;
    mJoueur.mW = 50.0f;
    mJoueur.mH = 50.0f;
    mJoueur.mVitesse = 300.0f; // Pixels par seconde
    mJoueur.mPointsDeVie = 3;
    // vider les listes pour recommencer à zéro
    mProjectiles.clear();
    mListeAsteroides.clear();
}
void Game::GererEntrees(const bool* keys){
    // Deplacement du vaisseau joueur
    if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
        mJoueur.mPosX -= mJoueur.mVitesse * 0.016f; // Supposant 60 FPS
        if(mJoueur.mPosX < 0) mJoueur.mPosX = 0;
    }
    if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        mJoueur.mPosX += mJoueur.mVitesse * 0.016f; // Supposant 60 FPS
        if(mJoueur.mPosX + mJoueur.mW > 800) mJoueur.mPosX = 800 - mJoueur.mW;
    }
    static bool bSpacePressed = false;
    // Tirer un projectile
    if(keys[SDL_SCANCODE_SPACE]){
        if(!bSpacePressed){
        Tirer();
        bSpacePressed = true;
        }
      }else{
        bSpacePressed = false;
        }
    }
void Game::Tirer(){
    Projectile projectile;
    projectile.mPosX = mJoueur.mPosX + mJoueur.mW / 2 - 5;
    projectile.mPosY = mJoueur.mPosY;
    projectile.mVitesse = 400.0f; // Pixels par seconde
    projectile.mW = 10.0f;
    projectile.mH = 20.0f;
    projectile.bIsActive = true;

    mProjectiles.push_back(projectile);
}
void Game::GenererAsteroide(){
    Asteroide asteroide;
    asteroide.mW = 40.0f;
    asteroide.mH = 40.0f;
    asteroide.mPosX = static_cast<float>(rand() % (800 - static_cast<int>(asteroide.mW)));
    asteroide.mPosY = -asteroide.mH; // Commence au-dessus de l'écran
    asteroide.mVitesse = 100.0f + static_cast<float>(rand() % 100); // Vitesse aléatoire entre 100 et 200 pixels par seconde
    asteroide.mType = rand() % 3; // Trois types d'asteroides
    mListeAsteroides.push_back(asteroide);
}
void Game::Update(float deltaTime){
    // Mettre à jour les projectiles
    for(auto& projectile : mProjectiles){
        if(projectile.bIsActive){
            projectile.mPosY -= projectile.mVitesse * deltaTime;
            if(projectile.mPosY + projectile.mH < 0){
                projectile.bIsActive = false; // Désactiver le projectile s'il sort de l'ecran
            }
        }
    }
    // Mettre a jour les asteroides
    for(auto& asteroide : mListeAsteroides){
        asteroide.mPosY += asteroide.mVitesse * deltaTime;
    }
    // Supprimer les objects inactifs ou hors ecran
    mProjectiles.erase(std::remove_if(mProjectiles.begin(), mProjectiles.end(),
        [](const Projectile& p){ return !p.bIsActive; }), mProjectiles.end());
        mListeAsteroides.erase(std::remove_if(mListeAsteroides.begin(), mListeAsteroides.end(),
        [](const Asteroide& a){ return a.mPosY > 600; }), mListeAsteroides.end());
}

        