
 #include <iostream>
 #include "../include/Game.h"
 #include "../include/Utils.h"
  #include "../include/Renderer.h"
 #include <SDL3/SDL_main.h>
 #include <SDL3/SDL.h>

 int main(int argc, char* argv[]) {
  // Initialisation 
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Erreur : %s", SDL_GetError());
    return -1;
  }
  // Creation de la fenetre
  SDL_Window* window = SDL_CreateWindow("Jeu de tire spatial", 800, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
  
  if(!window || !renderer) {
    SDL_Log("Erreur de creation de la fenetre ou du renderer : %s", SDL_GetError());
    SDL_Quit();
    return -1;
  }
  // Initialisation du jeu
  Game monJeu;
  Renderer monAfficheur;
  if(!monAfficheur.Initialiser(renderer)){
      SDL_Log("Erreur d'initialisation du renderer");
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return -1;
  }
  
  bool running = true;
  SDL_Event event;
  Uint64 lastTime = SDL_GetTicks();//pour le delta time
  // Boucle principale
  while (running) {
    // Gestion des evenements
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }
    // Calcul du delta time
    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    //--- LOGIQUE DU JEU ---
    const bool* keys = SDL_GetKeyboardState(NULL);
    monJeu.GererEntrees(keys);
    monJeu.Update(deltaTime);
    //--- RENDU DU JEU ---
    monAfficheur.AfficherScene(renderer, monJeu);
    SDL_Delay(1); // Evite de saturer le CPU
    // On affiche le resultat a l'ecran
    SDL_RenderPresent(renderer);
  }
  // Nettoyage
  monAfficheur.Nettoyer();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
 


   
  return 0; 

}