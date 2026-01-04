/**
 * Renderer.h -Module d'affichage
 */
#ifndef RENDERER_H
#define RENDERER_H
#include<SDL3/SDL.h>
#include"Game.h"
#include<SDL3_image/SDL_image.h>

class Renderer{
    public:
        Renderer();
        //Initialisation du moteur de rendu
        bool Initialiser(SDL_Renderer* renderer);
        //Dessine l'integralite de la scene du jeu
        void AfficherScene(SDL_Renderer*renderer, const Game& game);
        //Nettoyage des textures
        void Nettoyer();
    private:
     //Ici on stockera plus tard les textures
     SDL_Texture* mTextureVaisseau;
     SDL_Texture* mTextureAsteroide;
     // fonctions utilitaires pour charger l'image
     //SDL_Texture* ChargerTexture(const char* filePath, SDL_Renderer* renderer);
};

#endif