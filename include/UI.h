// ...existing code...
/*
* UI.h - Module d'Interface utilisateur
*/
#ifndef UI_H
#define UI_H

#include <SDL3/SDL.h>
#include <string>
#include "../include/Game.h"

class UI {
public:
    UI();
    ~UI();

    // Initialiser l'interface utilisateur (charge la police si fournie)
    bool Initialiser(SDL_Window* window, SDL_Renderer* renderer, const std::string& fontPath = "", int fontSize = 16);

    // Afficher l'interface (score, vies, etc.) par dessus le jeu
    void AfficherInterface(const Game& game);

    // Nettoyer les ressources de l'interface
    void Nettoyer();

    // Contrôles utilitaires
    void SetVisible(bool visible) { m_showWindow = visible; }
    bool IsVisible() const { return m_showWindow; }

private:
    // Rend du texte simple à l'écran 
    void RenderText(const std::string& text, int x, int y, SDL_Color color);

    bool m_showWindow;           // État de la fenêtre UI
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    

    // Valeurs affichées (peuvent être synchronisées depuis Game dans AfficherInterface)
    int m_score;
    int m_lives;
};

#endif // UI_H
// ...existing code...