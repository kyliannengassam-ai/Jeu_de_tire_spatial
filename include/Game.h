/**
 * Game.h - Logique du jeu de tire spatial
 * Description : Fusion de la logique du vaisseau, des projectiles et des asteroides.
 */

  #ifndef GAME_H
  #define GAME_H
  
  #include <vector> // Necessaire pour stocker les listes de tirs et d'ennemis
  #include <SDL3/SDL.h>

  /**
   * struct Vaisseau - Donnees du joueur
   */
  struct Vaisseau {
    float mPosX;
    float mPosY;
    float mW, mH; // Dimensions du vaisseau
    float mVitesse;      // Vitesse de deplacement du vaisseau
    int mPointsDeVie;           // Points de vie du vaisseau
  };
  /**
   * struct projectile - Une munition tiree
   */
  struct Projectile {
    float mPosX;
    float mPosY;
    float mW, mH; //Dimensions du projectile
    float mVitesse; // Vitesse du projectile
    bool bIsActive; // Indique si le projectile est actif
  };
  /**
   * struct Asteroide - un ennemi
   */
  struct Asteroide {
    float mPosX;
    float mPosY;
    float mW, mH; // Dimensions de l'asteroide
    float mVitesse; // Vitesse de l'asteroide
    int mType;
  };
  /**
   * class Game - Gestion de la logique du jeu
   */
  class Game{
    public:
        Game();
        void InitialiserJeu();
        void Update(float deltaTime);
        void GererEntrees(const bool* keys);
        // Nouvelles fonctionnalites du combat
        void Tirer();
        void GenererAsteroide();
        // Accesseurs pour le rendu
        const  Vaisseau& ObtenirVaisseau() const{return mJoueur;}
        // Accesseurs pour voir les tirs et asteroides
        const std::vector<Projectile>& ObtenirProjectiles() const {return mProjectiles;}
        const std::vector<Asteroide>& ObtenirAsteroides() const {return mListeAsteroides;}
        private:
        Vaisseau mJoueur;
        bool mIsGameOver;
        // Listes dynamiques 
        std::vector<Projectile> mProjectiles;
        std::vector<Asteroide> mListeAsteroides;
  };

  #endif