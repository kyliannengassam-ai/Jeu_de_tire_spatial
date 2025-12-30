
 #include <iostream>
 #include "../include/Game.h"
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
  Game monJeu;
  bool bIsRunning = true;
  SDL_Event event;
  // variable de temps
  Uint64 lastTime = SDL_GetTicks();
  float deltaTime = 0;

  // Boucle du jeu
  while (bIsRunning) {
    // Gestion des evenements
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        bIsRunning = false;
      }
    }
    // Lecture du clavier
    const bool* keys = SDL_GetKeyboardState(NULL);
    monJeu.GererEntrees(keys);
    // Calcul du delta time
    Uint64 currentTime = SDL_GetTicks();
    deltaTime = (float)(currentTime-lastTime)/1000.0f;
    lastTime = currentTime;
    // Mise a jour de la logique du jeu
   monJeu.Update( deltaTime);

   // Generation aleatoire d'asteroides
    if (rand() % 100 < 2) { // Toutes les secondes
        monJeu.GenererAsteroide();
    }



    // Rendu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Dessiner le vaisseau
    const Vaisseau& v = monJeu.ObtenirVaisseau();
    SDL_FRect rectVaisseau = { v.mPosX, v.mPosY, v.mW, v.mH}; 
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectVaisseau);

    // Dessiner les projectiles
     SDL_SetRenderDrawColor(renderer, 255,255, 0, 255);
    for(const auto& p : monJeu.ObtenirProjectiles()){
            SDL_FRect rectProj = {p.mPosX, p.mPosY, p.mW, p.mH};
            SDL_RenderFillRect(renderer, &rectProj);
        
    }
    // Dessiner les asteroides
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    for(const auto& a : monJeu.ObtenirAsteroides()){
        SDL_FRect rectAst = {a.mPosX, a.mPosY, a.mW,a.mH}; 
        
        SDL_RenderFillRect(renderer, &rectAst);
    
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
   }  
    //Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0; 

}