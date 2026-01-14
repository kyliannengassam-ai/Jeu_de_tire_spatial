/**
 * Utils.h - fichier d'en tete pour les fonctions utilitaires
 */
#ifndef UTILS_H
#define UTILS_H
#include <SDL3/SDL.h>
/**
 * class Utils - boite a outils statique
 */
class Utils {
public:
  // verifie les collisions entre deux rectangles
    static bool VerifierCollision(const SDL_FRect& rectA, const SDL_FRect& rectB); 
    // Genere un nombre aleatoire entre min et max
    static float GenererNombreAleatoire(float min, float max);
    // Empeche le vaisseau de sortir de l'ecran
    static void LimiterPosition(float& pos, float min, float max);
};

#endif 