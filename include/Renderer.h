#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "../include/Game.h"
#include <string>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialiser(SDL_Renderer* renderer); // charge textures
    void AfficherScene(SDL_Renderer* renderer, const Game& game);
    void Nettoyer();

private:
    SDL_Texture* mTextureVaisseau = nullptr;
    SDL_Texture* mTextureAsteroide = nullptr;
    SDL_Texture* mTextureFond = nullptr;

    const std::string mPathVaisseau  = "assets/sprites/vaisseau.png";
    const std::string mPathAsteroide = "assets/sprites/asteroide.png";
    const std::string mPathFond      = "assets/sprites/fond.png";

    SDL_Texture* ChargerTexture(const std::string& chemin, SDL_Renderer* renderer);
    void LibererTexture(SDL_Texture*& tex);
};

#endif // RENDERER_H
