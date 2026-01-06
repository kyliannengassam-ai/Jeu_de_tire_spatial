#include ".../include/Renderer.h"
#include <iostream>
#include<SDL3_image/SDL_image.h>

Renderer::Renderer()
    : mTextureVaisseau(nullptr), mTextureAsteroide(nullptr) {
}

bool Renderer::Initialiser(SDL_Renderer* renderer) {
    // Charger les textures
    mTextureVaisseau = IMG_LoadTexture(renderer, "assets/sprites/vaisseau.png");
    mTextureAsteroide = IMG_LoadTexture(renderer, "assets/sprites/asteroide.png");
    if (!mTextureVaisseau || !mTextureAsteroide) {
        SDL_Log("Erreur de chargement des textures: %s", SDL_GetError());
        return false;
    }
    return true;
}
SDL_Texture* Renderer::ChargerTexture(const char* chemin, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, chemin);
    if (!texture) {
        SDL_Log("Erreur de chargement de la texture %s: %s", chemin, SDL_GetError());
    }
    return texture;
}
//Afficher la scene du jeu
void Renderer::AfficherScene(SDL_Renderer* renderer, const Game& game) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Dessiner le vaisseau
    const Vaisseau& vaisseau = game.ObtenirVaisseau();
    SDL_FRect rectVaisseau = { vaisseau.mPosX, vaisseau.mPosY, vaisseau.mW, vaisseau.mH };
    SDL_RenderTexture(renderer, mTextureVaisseau, nullptr, &rectVaisseau);
    // Dessiner les asteroides
    for(const auto& a: game.ObtenirAsteroides()){
        SDL_FRect rectAsteroide = { a.mPosX, a.mPosY, a.mW, a.mH };
        
        SDL_RenderTexture(renderer, mTextureAsteroide, nullptr, &rectAsteroide);
    }
    //Dessiner les projectiles
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune pour les projectiles
    for(const auto& p: game.ObtenirProjectiles()){
        SDL_FRect rectProjectile = { p.mPosX, p.mPosY, p.mW, p.mH };
        SDL_RenderFillRect(renderer, &rectProjectile);
    }
    // Affichage final
    SDL_RenderPresent(renderer);
}
// Nettoyage - libere la memoire des textures
void Renderer::Nettoyer() {
    if (mTextureVaisseau) {
        SDL_DestroyTexture(mTextureVaisseau);
        mTextureVaisseau = nullptr;
    }
    if (mTextureAsteroide) {
        SDL_DestroyTexture(mTextureAsteroide);
    }
}