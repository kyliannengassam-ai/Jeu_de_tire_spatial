/**
 * Utils.h - Fichier d'en-tête pour les fonctions utilitaires
 * Contient des fonctions statiques pour les collisions, nombres aléatoires et limites de position
 */
#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>
#include <cmath>

/**
 * Constantes globales
 */
namespace Constants {
    constexpr float WINDOW_WIDTH = 800.0f;
    constexpr float WINDOW_HEIGHT = 600.0f;
}

/**
 * class Utils - Boîte à outils statique pour les opérations courantes
 */
class Utils {
public:
    /**
     * VerifierCollision - Détecte les collisions entre deux rectangles (AABB)
     * @param rectA : Premier rectangle
     * @param rectB : Deuxième rectangle
     * @return true si les rectangles se chevauchent, false sinon
     */
    static bool VerifierCollision(const SDL_FRect& rectA, const SDL_FRect& rectB);
    
    /**
     * GenererNombreAleatoire - Génère un nombre aléatoire dans une plage
     * @param min : Valeur minimale
     * @param max : Valeur maximale
     * @return Nombre aléatoire entre min et max
     */
    static float GenererNombreAleatoire(float min, float max);
    
    /**
     * LimiterPosition - Empêche une position de sortir des limites
     * @param pos : Position à vérifier (modifiée si hors limites)
     * @param min : Limite minimale
     * @param max : Limite maximale
     */
    static void LimiterPosition(float& pos, float min, float max);
    
    /**
     * CalculerDistance - Calcule la distance euclidienne entre deux points
     * @param x1, y1 : Coordonnées du premier point
     * @param x2, y2 : Coordonnées du deuxième point
     * @return Distance euclidienne
     */
    static float CalculerDistance(float x1, float y1, float x2, float y2);
    
    /**
     * EstDansLesLimites - Vérifie si un point est dans les limites de l'écran
     * @param x, y : Coordonnées du point
     * @return true si le point est à l'écran, false sinon
     */
    static bool EstDansLesLimites(float x, float y);
};

#endif // UTILS_H 