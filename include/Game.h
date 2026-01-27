
  
/**
 * Game.h - Logique du jeu de tire spatial
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL3/SDL.h>

/* Énumération pour les niveaux de difficulté */
enum class Difficulty {
    Easy,
    Medium,
    Hard
};

/* Énumération pour l'état du jeu */
enum class GameState {
    Menu,           // Affiche le menu de sélection de difficulté
    Playing,        // Jeu en cours
    GameOver        // Écran de fin de jeu
};

/* Données du joueur */
struct Vaisseau {
    float mPosX = 0.0f;
    float mPosY = 0.0f;
    float mW = 32.0f, mH = 32.0f;
    float mVitesse = 100.0f;
    int mPointsDeVie = 3;
    float mInvulnerabilityTime = 0.0f;  // Temps restant d'invulnérabilité
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

    void InitialiserJeu(); // Initialiser les variables du jeu
    void Update(float deltaTime); // Mettre à jour l'état du jeu
    void GererEntrees(const bool* keys); // Gerer les entrees de clavier
    void Tirer(); // Créer un nouveau projectile
    void GenererAsteroide(); // Générer un nouvel astéroïde
    void ResetGame(); // Réinitialiser le jeu
    
    // Gestion de la difficulté et l'état du jeu
    void SetDifficulty(Difficulty difficulty) { mDifficulty = difficulty; }
    Difficulty GetDifficulty() const { return mDifficulty; }
    
    void SetGameState(GameState state) { mGameState = state; }
    GameState GetGameState() const { return mGameState; }

    // Accesseurs pour le rendu et l'UI (utilisés par UI.cpp)
    int GetScore() const { return mScore; }
    int GetLives() const { return mLives; }
    bool IsGameOver() const { return mIsGameOver; }
    bool IsShipInvulnerable() const { return mJoueur.mInvulnerabilityTime > 0.0f; }
    bool ShouldShipBlink() const { return mJoueur.mInvulnerabilityTime > 0.0f; }

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
    
    // Gestion de la difficulté et progression
    Difficulty mDifficulty = Difficulty::Easy;
    GameState mGameState = GameState::Menu;
    float mElapsedTime = 0.0f;
    
    // Contrôle du spawn d'astéroïdes selon la difficulté
    float mAsteroidSpawnChance = 10.0f;  // % de chance par frame
    int mMaxAsteroids = 5;                // Nombre max d'astéroïdes simultanés
    float mAsteroidSpawnDecreasePerSecond = 0.05f; // Réduction progressive
    
    // Durée de l'invulnérabilité et de l'effet après collision (en secondes)
    static constexpr float INVULNERABILITY_DURATION = 2.0f;
};
#endif // GAME_H