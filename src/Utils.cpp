/**
 * Utils.cpp - Implémentation des fonctions utilitaires
 */
#include "../include/Utils.h"
#include <cstdlib>
#include <ctime>
#include <random>

// Initialisation du générateur aléatoire (statique pour éviter les réinitialisations)
static std::random_device rd;
static std::mt19937 gen(rd());

/**
 * VerifierCollision - Détecte les collisions entre deux rectangles (AABB)
 * Algorithme AABB (Axis-Aligned Bounding Box)
 * Retourne true si les deux rectangles se chevauchent
 */
bool Utils::VerifierCollision(const SDL_FRect& rectA, const SDL_FRect& rectB) {
    return (rectA.x < rectB.x + rectB.w &&
            rectA.x + rectA.w > rectB.x &&
            rectA.y < rectB.y + rectB.h &&
            rectA.y + rectA.h > rectB.y);
}

/**
 * GenererNombreAleatoire - Génère un nombre aléatoire entre min et max
 * Utilise le Mersenne Twister pour une meilleure qualité aléatoire
 */
float Utils::GenererNombreAleatoire(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

/**
 * LimiterPosition - Empêche une position de sortir des limites données
 * Clamp la valeur entre min et max
 */
void Utils::LimiterPosition(float& pos, float min, float max) {
    if (pos < min) {
        pos = min;
    } else if (pos > max) {
        pos = max;
    }
}

/**
 * CalculerDistance - Calcule la distance euclidienne entre deux points
 * @return Distance euclidienne sqrt((x2-x1)² + (y2-y1)²)
 */
float Utils::CalculerDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * EstDansLesLimites - Vérifie si un point est dans les limites de l'écran
 * @return true si le point est à l'écran, false sinon
 */
bool Utils::EstDansLesLimites(float x, float y) {
    return (x >= 0.0f && x <= Constants::WINDOW_WIDTH &&
            y >= 0.0f && y <= Constants::WINDOW_HEIGHT);
}