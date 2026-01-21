 #include "../include/UI.h"
 #include "../include/Game.h"
 #include "../external/imgui/imgui.h"
 #include "../external/imgui/backends/imgui_impl_sdl3.h"
 #include "../external/imgui/backends/imgui_impl_sdlrenderer3.h"

UI::UI()
    : m_showWindow(true), m_window(nullptr), m_renderer(nullptr), m_score(0), m_lives(0)
{}

UI::~UI()
{
    Nettoyer();
}

bool UI::Initialiser(SDL_Window* window, SDL_Renderer* renderer, const std::string& /*fontPath*/, int /*fontSize*/)
{
    m_window = window;
    m_renderer = renderer;
    // Pas de SDL_ttf utilisé ici ; ImGui gère le rendu du texte.
    return true;
}

void UI::AfficherInterface(const Game& game)
{
    if (!m_showWindow) return;

    // Récupère les valeurs depuis Game
    // Adapte ces appels si les noms de méthodes dans Game diffèrent
    m_score = game.GetScore();
    m_lives = game.GetLives();

    // Affichage simple avec ImGui (le contexte ImGui doit être initialisé et frame commencé dans le main)
    ImGui::SetNextWindowBgAlpha(0.0f); // transparent
    ImGui::Begin("HUD", nullptr,
                 ImGuiWindowFlags_NoDecoration |
                 ImGuiWindowFlags_AlwaysAutoResize |
                 ImGuiWindowFlags_NoFocusOnAppearing |
                 ImGuiWindowFlags_NoNav);
    ImGui::SetWindowPos(ImVec2(8, 8), ImGuiCond_Always);
    ImGui::Text("Score: %d", m_score);
    ImGui::Text("Vies: %d", m_lives);
    ImGui::End();

    // Affichage du Game Over
    if (game.IsGameOver()) {
        ImGui::SetNextWindowPos(ImVec2(400, 300), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
        ImGui::Begin("Game Over", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("GAME OVER!");
        ImGui::Separator();
        ImGui::Text("Score Final: %d", m_score);
        ImGui::Text("Vies Restantes: %d", m_lives);
        ImGui::End();
    }
}

void UI::Nettoyer()
{
    m_window = nullptr;
    m_renderer = nullptr;
    // aucune ressource SDL_ttf à libérer ici
}

void UI::RenderText(const std::string& /*text*/, int /*x*/, int /*y*/, SDL_Color /*color*/)
{
    // Fallback vide : le rendu texte est assuré par ImGui dans AfficherInterface.
    // Si besoin d'un rendu SDL natif sans SDL_ttf, implémenter ici une solution basée sur textures/images.
}
