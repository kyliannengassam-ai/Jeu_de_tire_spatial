
 #include <iostream>
 #include "../include/Game.h"
 #include "../include/Utils.h"
 #include "../include/Renderer.h"
 #include "../include/UI.h"
 #include <SDL3/SDL_main.h>
 #include <SDL3/SDL.h>
 #include "../external/imgui/imgui.h"
 #include "../external/imgui/backends/imgui_impl_sdl3.h"
 #include "../external/imgui/backends/imgui_impl_sdlrenderer3.h"

 int main(int argc, char* argv[]) {
     // Initialisation SDL
     if (!SDL_Init(SDL_INIT_VIDEO)) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL: %s", SDL_GetError());
         return 1;
     }

     // Création de la fenêtre principale
     SDL_Window* window = SDL_CreateWindow(
         "Jeu de Tire Spatial",
         800, 600,
         SDL_WINDOW_RESIZABLE
     );
     if (!window) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur création fenêtre: %s", SDL_GetError());
         SDL_Quit();
         return 1;
     }

     // Création du renderer
     SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
     if (!renderer) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur création renderer: %s", SDL_GetError());
         SDL_DestroyWindow(window);
         SDL_Quit();
         return 1;
     }

     // Initialisation ImGui
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO& io = ImGui::GetIO();

     ImGui::StyleColorsDark();

     // Initialisation backends ImGui
     if (!ImGui_ImplSDL3_InitForSDLRenderer(window,renderer)) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation ImGui SDL3");
         SDL_DestroyRenderer(renderer);
         SDL_DestroyWindow(window);
         SDL_Quit();
         return 1;
     }

     if (!ImGui_ImplSDLRenderer3_Init(renderer)) {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation ImGui Renderer3");
         ImGui_ImplSDL3_Shutdown();
         SDL_DestroyRenderer(renderer);
         SDL_DestroyWindow(window);
         SDL_Quit();
         return 1;
     }

     // Initialisation du jeu et du rendu
     Game game;
     Renderer gameRenderer;
     gameRenderer.Initialiser(renderer);

     UI ui;
     ui.Initialiser(window, renderer);

     // Boucle principale
     bool running = true;
     float deltaTime = 0.0f;
     Uint64 lastTime = SDL_GetTicksNS();

     while (running) {
         Uint64 currentTime = SDL_GetTicksNS();
         deltaTime = static_cast<float>(currentTime - lastTime) / 1000000000.0f; // Convertir en secondes
         lastTime = currentTime;

         // Limiter deltaTime pour éviter les saut de physique
         if (deltaTime > 0.033f) deltaTime = 0.033f; // Max ~30ms (~33 FPS)

         // Gestion des événements
         SDL_Event event;
         while (SDL_PollEvent(&event)) {
             ImGui_ImplSDL3_ProcessEvent(&event);

             switch (event.type) {
                 case SDL_EVENT_QUIT:
                     running = false;
                     break;
                 default:
                     break;
             }
         }

         // Récupérer l'état du clavier
         int numKeys = 0;
         const bool* keys = SDL_GetKeyboardState(&numKeys);

         // Mettre à jour le jeu
         game.GererEntrees(keys);
         game.Update(deltaTime);

         // Rendu SDL
         gameRenderer.AfficherScene(renderer, game);

         // Début frame ImGui
         ImGui_ImplSDLRenderer3_NewFrame();
         ImGui_ImplSDL3_NewFrame();
         ImGui::NewFrame();

         // Affichage de l'interface (HUD + Game Over)
         ui.AfficherInterface(game);

         // Gestion des actions du menu Game Over
         GameOverAction action = ui.GetGameOverAction();
         if (action == GameOverAction::Restart) {
             game.ResetGame();
             ui.ResetGameOverAction();
         } else if (action == GameOverAction::Quit) {
             running = false;
         }

         // Rendu ImGui
         ImGui::Render();
         ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

         // Affichage final
         SDL_RenderPresent(renderer);
     }

     // Nettoyage ImGui
     ImGui_ImplSDLRenderer3_Shutdown();
     ImGui_ImplSDL3_Shutdown();
     ImGui::DestroyContext();

     // Nettoyage SDL
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();

     std::cout << "Fermeture du jeu\n";
     return 0;
 }