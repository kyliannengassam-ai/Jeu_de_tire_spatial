
  // ...existing code...
/**
 * Game.h - Logique du jeu de tire spatial
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL3/SDL.h>

/* Données du joueur */
struct Vaisseau {
    float mPosX = 0.0f;
    float mPosY = 0.0f;
    float mW = 32.0f, mH = 32.0f;
    float mVitesse = 300.0f;
    int mPointsDeVie = 3;
};

/* Projectile */
struct Projectile {
    float mPosX = 0.0f;
    float mPosY = 0.0f;
    float mW = 8.0f, mH = 16.0f;
    float mVitesse = 500.0f;
    bool bIsActive = false;
};

/* Asteroide */
struct Asteroide {
    float mPosX = 0.0f;
    float mPosY = 0.0f;
    float mW = 32.0f, mH = 32.0f;
    float mVitesse = 100.0f;
    int mType = 0;
};

class Game {
public:
    Game();

    void InitialiserJeu();
    void Update(float deltaTime);
    void GererEntrees(const bool* keys);
    void Tirer();
    void GenererAsteroide();
    void ResetGame(); // Réinitialiser le jeu

    // Accesseurs pour le rendu et l'UI (utilisés par UI.cpp)
    int GetScore() const { return mScore; }
    int GetLives() const { return mLives; }
    bool IsGameOver() const { return mIsGameOver; }

    const Vaisseau& ObtenirVaisseau() const { return mJoueur; }
    const std::vector<Projectile>& ObtenirProjectiles() const { return mProjectiles; }
    const std::vector<Asteroide>& ObtenirAsteroides() const { return mListeAsteroides; }

    // Modificateurs utiles
    void AjouterScore(int pts) { mScore += pts; }
    void PerdreVie(int n = 1) { mLives = (mLives - n >= 0) ? mLives - n : 0; }

private:
    Vaisseau mJoueur;
    bool mIsGameOver = false;
    std::vector<Projectile> mProjectiles;
    std::vector<Asteroide> mListeAsteroides;

    // Valeurs pour l'UI
    int mScore = 0;
    int mLives = 3;
};

#endif // GAME_H
