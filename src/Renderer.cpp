// ...existing code...
#include "../include/Renderer.h"
#include <SDL3/SDL.h>
#include "../include/Game.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

Renderer::Renderer() = default;
Renderer::~Renderer() { Nettoyer(); }

SDL_Texture* Renderer::ChargerTexture(const std::string& chemin, SDL_Renderer* renderer) {
    if (chemin.empty() || !renderer) return nullptr;
    SDL_Texture* tex = IMG_LoadTexture(renderer, chemin.c_str());
    if (!tex) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_LoadTexture failed for %s: %s", chemin.c_str(), SDL_GetError());
    }
    return tex;
}

void Renderer::LibererTexture(SDL_Texture*& tex) {
    if (tex) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}

bool Renderer::Initialiser(SDL_Renderer* renderer) {
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer::Initialiser - renderer is null");
        return false;
    }

    mTextureVaisseau = ChargerTexture(mPathVaisseau, renderer);
    mTextureAsteroide = ChargerTexture(mPathAsteroide, renderer);
    mTextureFond = ChargerTexture(mPathFond, renderer);

    // Retourne true même si certaines textures manquent.
    return true;
}

void Renderer::AfficherScene(SDL_Renderer* renderer, const Game& game) {
    if (!renderer) return;

    // Fond
    if (mTextureFond) {
        SDL_FRect dst = { 0, 0, 800, 600 };
        SDL_RenderTexture(renderer, mTextureFond, nullptr, &dst);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    // Vaisseau avec effet de clignotement si invulnérable
    const auto& v = game.ObtenirVaisseau();
    SDL_FRect dstV = { static_cast<float>(v.mPosX), static_cast<float>(v.mPosY),
                      static_cast<float>(v.mW), static_cast<float>(v.mH) };
    
    // Clignotement: alterner la visibilité du vaisseau
    bool shouldDrawShip = true;
    if (game.ShouldShipBlink()) {
        // Clignotement 4 fois par seconde (période de 0.25s)
        shouldDrawShip = (static_cast<int>(v.mInvulnerabilityTime * 4) % 2) == 0;
    }
    
    if (shouldDrawShip) {
        if (mTextureVaisseau) {
            SDL_RenderTexture(renderer, mTextureVaisseau, nullptr, &dstV);
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &dstV);
        }
    } else if (game.ShouldShipBlink()) {
        // Afficher une version semi-transparente quand le vaisseau "disparaît"
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 100);
        SDL_RenderFillRect(renderer, &dstV);
    }

    // Projectiles
    for (const auto& p : game.ObtenirProjectiles()) {
        if (!p.bIsActive) continue;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_FRect dstP = { static_cast<float>(p.mPosX), static_cast<float>(p.mPosY),
                          static_cast<float>(p.mW), static_cast<float>(p.mH) };
        SDL_RenderFillRect(renderer, &dstP);
    }

    // Asteroides
    for (const auto& a : game.ObtenirAsteroides()) {
        SDL_FRect dstA = { static_cast<float>(a.mPosX), static_cast<float>(a.mPosY),
                          static_cast<float>(a.mW), static_cast<float>(a.mH) };
        if (mTextureAsteroide) {
            SDL_RenderTexture(renderer, mTextureAsteroide, nullptr, &dstA);
        } else {
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            SDL_RenderFillRect(renderer, &dstA);
        }
    }
}

void Renderer::Nettoyer() {
    LibererTexture(mTextureVaisseau);
    LibererTexture(mTextureAsteroide);
    LibererTexture(mTextureFond);
}
