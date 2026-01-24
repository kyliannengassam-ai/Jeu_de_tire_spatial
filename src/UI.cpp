 #include "../include/UI.h"
 #include "../include/Game.h"
 #include "../external/imgui/imgui.h"
 #include "../external/imgui/backends/imgui_impl_sdl3.h"
 #include "../external/imgui/backends/imgui_impl_sdlrenderer3.h"

UI::UI()
    : m_showWindow(true), m_window(nullptr), m_renderer(nullptr), m_score(0), m_lives(0), 
      m_menuAction(MenuAction::None), m_gameOverAction(GameOverAction::None), 
      m_selectedDifficulty(Difficulty::Easy)
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

void UI::AfficherMenuDifficulte()
{
    ImGui::SetNextWindowPos(ImVec2(400, 300), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowBgAlpha(0.95f);
    ImGui::Begin("Menu Principal", nullptr, 
                 ImGuiWindowFlags_AlwaysAutoResize | 
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse);
    
    ImGui::SetWindowFontScale(2.0f);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Selectionnez le niveau");
    ImGui::SetWindowFontScale(1.0f);
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Boutons pour sélectionner la difficulté
    bool easySelected = (m_selectedDifficulty == Difficulty::Easy);
    bool mediumSelected = (m_selectedDifficulty == Difficulty::Medium);
    bool hardSelected = (m_selectedDifficulty == Difficulty::Hard);
    
    if(easySelected) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.8f, 0.0f, 1.0f));
    if (ImGui::Button("Facile", ImVec2(200, 50))) {
        m_selectedDifficulty = Difficulty::Easy;
        m_menuAction = MenuAction::SelectEasy;
    }
    if(easySelected) ImGui::PopStyleColor();
    
    ImGui::Spacing();
    
    if(mediumSelected) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.8f, 0.0f, 1.0f));
    if (ImGui::Button("Moyen", ImVec2(200, 50))) {
        m_selectedDifficulty = Difficulty::Medium;
        m_menuAction = MenuAction::SelectMedium;
    }
    if(mediumSelected) ImGui::PopStyleColor();
    
    ImGui::Spacing();
    
    if(hardSelected) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    if (ImGui::Button("Difficile", ImVec2(200, 50))) {
        m_selectedDifficulty = Difficulty::Hard;
        m_menuAction = MenuAction::SelectHard;
    }
    if(hardSelected) ImGui::PopStyleColor();
    
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Bouton pour lancer le jeu
    if (ImGui::Button("Lancer", ImVec2(200, 50))) {
        m_menuAction = MenuAction::StartGame;
    }
    
    ImGui::End();
}

void UI::AfficherInterface(const Game& game)
{
    if (!m_showWindow) return;

    // Afficher le menu de sélection de difficulté si en état Menu
    if (game.GetGameState() == GameState::Menu) {
        AfficherMenuDifficulte();
        return;  // Ne pas afficher le HUD en arrière-plan
    }

    // Récupère les valeurs depuis Game
    m_score = game.GetScore();
    m_lives = game.GetLives();

    // ===== AFFICHAGE HUD (Score et Vies en haut à gauche) =====
    ImGui::SetNextWindowBgAlpha(0.3f); // semi-transparent
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::Begin("HUD", nullptr,
                 ImGuiWindowFlags_NoDecoration |
                 ImGuiWindowFlags_AlwaysAutoResize |
                 ImGuiWindowFlags_NoFocusOnAppearing |
                 ImGuiWindowFlags_NoNav |
                 ImGuiWindowFlags_NoInputs);
    
    // Affichage grand format du score et des vies
    ImGui::SetWindowFontScale(1.5f);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Score: %d", m_score);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Vies: %d", m_lives);
    ImGui::SetWindowFontScale(1.0f);
    
    ImGui::End();

    // ===== AFFICHAGE GAME OVER =====
    if (game.IsGameOver()) {
        ImGui::SetNextWindowPos(ImVec2(400, 300), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowBgAlpha(0.95f); // Opaque pour le dialog de fin
        ImGui::Begin("Game Over", nullptr, 
                     ImGuiWindowFlags_AlwaysAutoResize | 
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse);
        
        ImGui::SetWindowFontScale(2.0f);
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "GAME OVER");
        ImGui::SetWindowFontScale(1.0f);
        
        ImGui::Separator();
        
        ImGui::Text("Score Final: %d", m_score);
        ImGui::Text("Vies Restantes: %d", m_lives);
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // Boutons pour les actions
        if (ImGui::Button("Recommencer", ImVec2(150, 40))) {
            m_gameOverAction = GameOverAction::Restart;
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Accueil", ImVec2(150, 40))) {
            m_gameOverAction = GameOverAction::Menu;
        }
        
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
