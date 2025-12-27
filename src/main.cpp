/**
 * main.cpp -point d'entree du jeu de tire spatial
 * @state: pointeur vers la fenetre principale du jeu
 * @argc: nombre d'arguments
 * @argv: Tableau des arguments
 * 
 * return: SDL_APP_CONTINUE pour continuer, SDL_APP_SUCCESS pour quitter.
 */

 #include <SDL3/SDL.h>
 #include <SDL3/SDL_main.h>
 #include <iostream>
 
 /*Structure pour l'etat de l'application*/
 struct AppContext {
     SDL_Window* window;
     SDL_Renderer* renderer;
     bool bIsRunning;
 };
 /**
  * SDL_AppInit - Initilialistion de l'application SDL
  * @state: Donnees d'etat partagees entre les fonctions
  */
 SDL_AppResult SDL_AppInit(void** state,int argc,char* argv[]) {
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_Log ("Erreur SDL_Init: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // allocation de notre structure d'etat
      AppContext* app = new AppContext();
      app->bIsRunning = true;
      // creation de la fenetre
      app->window = SDL_CreateWindow("Jeu de tire spatial", 800, 600, 0);
      if(!app->window) {
        return SDL_APP_FAILURE;
      }
      app->renderer = SDL_CreateRenderer(app->window, NULL);
      if (!app->renderer) {
        return SDL_APP_FAILURE;
      }
      *state = app;
      return SDL_APP_CONTINUE;
 }
 /**
  * SDL_AppIterate - boucle de rendu
  */
  SDL_AppResult SDL_AppIterate(void* state) {
    AppContext* app = (AppContext*)state;
    //fonds noir pour l'espace (R,G,B,A)
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    // Ici : le code  de dessin des objets du jeu irait ici
    SDL_RenderPresent(app->renderer);
    return SDL_APP_CONTINUE;

  }
  /**
   *  SDL_AppQuit - Nettoyage final de la memoire
   */
  void SDL_AppQuit(void* state) {
    if (state) { 
    AppContext* app = (AppContext*)state;
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    delete app;
    }
    SDL_Quit();
    SDL_Log("Application fermee proprement");
}