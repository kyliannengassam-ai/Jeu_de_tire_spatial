# 🚀 Jeu de Tiré Spatial

Un jeu arcade classique de tiré vertical développé en C++ avec SDL3 et ImGui. Détruisez les astéroïdes, survivez aussi longtemps que possible et battez votre record!

## 📋 Table des matières

- [Aperçu du Projet](#aperçu-du-projet)
- [Architecture](#architecture)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Compilation](#compilation)
- [Guide de Jeu](#guide-de-jeu)
- [Documentation du Code](#documentation-du-code)
- [Dépendances](#dépendances)
- [Structure du Projet](#structure-du-projet)

---

## 🎮 Aperçu du Projet

**Jeu de Tiré Spatial** est un jeu d'action arcade où vous pilotez un vaisseau spatial et devez éliminer des astéroïdes qui descendent de haut en bas de l'écran.

### Caractéristiques principales:
- ✅ Trois niveaux de difficulté (Facile, Moyen, Difficile)
- ✅ Système de collision avec invulnérabilité temporaire
- ✅ Génération progressive d'astéroïdes
- ✅ Système de scoring
- ✅ Interface graphique avec ImGui
- ✅ Gestion des états du jeu (Menu, Jeu, Game Over)
- ✅ Effets visuels (clignotement du vaisseau lors des collisions)

---

## 🏗️ Architecture

Le projet suit une architecture **modulaire et orientée objet** avec une séparation nette des responsabilités:

```
Jeu de Tiré Spatial
├── Game (Logique du jeu)
├── Renderer (Affichage graphique)
├── UI (Interface utilisateur)
├── Utils (Fonctions utilitaires)
└── main.cpp (Point d'entrée)
```

### Diagramme d'architecture simplifié:

```
┌─────────────────┐
│   main.cpp      │ ◄─── Point d'entrée principal
└────────┬────────┘
         │
    ┌────┴──────────────────────────────┐
    │                                   │
    ▼                                   ▼
┌─────────────┐                  ┌──────────────┐
│   Game      │◄─────────────────┤  Renderer    │
│ (Logique)   │                  │(Affichage)   │
└─────────────┘                  └──────────────┘
    │                                   │
    │         ┌───────────────────────────┐
    │         │       UI (Interface)      │
    │         └───────────────────────────┘
    │                   │
    └───────────────────┘
         │
    ┌────▼─────────┐
    │  Utils       │
    │(Utilitaires) │
    └──────────────┘
```

---

## 🎯 Fonctionnalités

### Gameplay
- **Mouvements du vaisseau**: Naviguez librement sur l'écran avec les touches fléchées ou ZQSD
- **Système de tir**: Appuyez sur ESPACE pour tirer des projectiles
- **Collisions**: Détection précise AABB entre vaisseau, astéroïdes et projectiles
- **Invulnérabilité**: 2 secondes de protection après une collision avec clignotement visuel
- **Génération d'astéroïdes**: Augmentation progressive et aléatoire basée sur la difficulté

### Difficultés
| Niveau | Vies initiales | Max astéroïdes | Chance spawn | Progression |
|--------|---|---|---|---|
| **Facile** | 5 | 3 | 5% | Lente (+0.03%/s) |
| **Moyen** | 3 | 6 | 10% | Moyenne (+0.05%/s) |
| **Difficile** | 2 | 10 | 15% | Rapide (+0.08%/s) |

### Système de Score
- **Astéroïde détruit**: +100 points
- **Bonus progressif**: La chance de spawn d'astéroïdes diminue avec le temps (offrant une respiration)

---

## 📦 Installation

### Prérequis
- **Compilateur**: MSVC (Visual Studio 2019+) ou MinGW
- **CMake**: 3.10 ou supérieur
- **Windows**: Windows 10/11

### Étapes d'installation

1. **Cloner ou télécharger le projet**
   ```bash
   cd Jeu_de_tire_spatial
   ```

2. **Vérifier les dépendances externes**
   ```
   Le projet inclut déjà:
   - SDL3
   - SDL3_image
   - ImGui (avec backends SDL3)
   ```

3. **Créer les répertoires nécessaires**
   ```bash
   mkdir build
   cd build
   ```

---

## 🔨 Compilation

### Méthode 1: Script batch (Windows)
```bash
build.bat
```

Le script `build.bat` compile et lance automatiquement le jeu.

### Méthode 2: CMake manuel
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

### Méthode 3: PowerShell
```powershell
.\build.bat
```

### Après compilation
L'exécutable se trouvera dans le répertoire `build/`.

---

## 🎮 Guide de Jeu

### Contrôles

| Action | Touche(s) |
|--------|-----------|
| **Gauche** | `←` ou `A` |
| **Droite** | `→` ou `D` |
| **Haut** | `↑` ou `W` |
| **Bas** | `↓` ou `S` |
| **Tirer** | `ESPACE` |
| **Quitter** | `ALT+F4` ou Fermer fenêtre |

### Règles du jeu

1. **Menu Principal**: Sélectionnez la difficulté (Facile, Moyen, Difficile)
2. **Pendant le jeu**:
   - Déplacez votre vaisseau pour éviter les astéroïdes
   - Tirez pour détruire les astéroïdes (100 points par astéroïde)
   - Chaque collision sans invulnérabilité vous coûte **1 vie**
   - Pendant 2 secondes après une collision, vous êtes invulnérable (vaisseau clignote)

3. **Fin du jeu**: Quand vous avez 0 vies, l'écran **Game Over** apparaît
   - Sélectionnez **Recommencer** pour rejouer
   - Sélectionnez **Menu** pour revenir au menu principal

### Conseils stratégiques
- 📍 Restez au centre de l'écran pour plus de réactivité
- ⏱️ Utilisez l'invulnérabilité pour passer à travers les zones dangereuses
- 🎯 Tirez en priorité sur les astéroïdes qui descendent vers vous
- 🔄 La difficulté augmente progressivement, soyez prudent en fin de partie

---

## 📚 Documentation du Code

### Game.h / Game.cpp
**Responsabilité**: Logique complète du jeu

#### Structures principales

##### `Vaisseau`
Représente le vaisseau du joueur.
```cpp
struct Vaisseau {
    float mPosX, mPosY;           // Position (pixels)
    float mW, mH;                 // Dimensions
    float mVitesse;               // Vitesse de déplacement
    int mPointsDeVie;             // Points de vie (inutilisé, utiliser mLives dans Game)
    float mInvulnerabilityTime;   // Temps d'invulnérabilité restant
};
```

##### `Projectile`
Représente un projectile tiré par le vaisseau.
```cpp
struct Projectile {
    float mPosX, mPosY;           // Position
    float mW, mH;                 // Dimensions
    float mVitesse;               // Vitesse de déplacement (vers le haut)
    bool bIsActive;               // Le projectile est-il actif?
};
```

##### `Asteroide`
Représente un astéroïde ennemi.
```cpp
struct Asteroide {
    float mPosX, mPosY;           // Position
    float mW, mH;                 // Dimensions
    float mVitesse;               // Vitesse de déplacement (vers le bas)
    int mType;                    // Type d'astéroïde (0-2) ou -1 si marqué pour suppression
};
```

#### Énumérations

##### `Difficulty`
```cpp
enum class Difficulty {
    Easy,    // Facile: 5 vies, 3 astéroïdes max, progression lente
    Medium,  // Moyen: 3 vies, 6 astéroïdes max, progression moyenne
    Hard     // Difficile: 2 vies, 10 astéroïdes max, progression rapide
};
```

##### `GameState`
```cpp
enum class GameState {
    Menu,      // Écran de sélection de difficulté
    Playing,   // Jeu en cours
    GameOver   // Écran de fin de jeu
};
```

#### Méthodes clés

| Méthode | Description |
|---------|-------------|
| `InitialiserJeu()` | Initialise toutes les variables du jeu selon la difficulté |
| `Update(float deltaTime)` | Met à jour la logique du jeu (mouvements, collisions, spawns) |
| `GererEntrees(const bool* keys)` | Traite les entrées clavier |
| `Tirer()` | Crée un nouveau projectile au centre du vaisseau |
| `GenererAsteroide()` | Crée un nouvel astéroïde en haut de l'écran |
| `ResetGame()` | Réinitialise le jeu pour une nouvelle partie |

#### Système de collision

**Fonction**: `RectsIntersect()` (locale dans Update)
```cpp
static bool RectsIntersect(float ax, float ay, float aw, float ah,
                          float bx, float by, float bw, float bh)
```
Utilise une détection AABB (Axis-Aligned Bounding Box) simple et efficace.

**Collisions détectées**:
1. **Projectile ↔ Astéroïde**: Projectile détruit, astéroïde supprimé, +100 points
2. **Vaisseau ↔ Astéroïde**: -1 vie, invulnérabilité 2s, astéroïde supprimé

---

### Renderer.h / Renderer.cpp
**Responsabilité**: Affichage graphique du jeu

#### Méthodes principales

| Méthode | Description |
|---------|-------------|
| `Initialiser(SDL_Renderer*)` | Charge les textures depuis les fichiers |
| `AfficherScene(SDL_Renderer*, const Game&)` | Affiche tous les éléments du jeu |
| `Nettoyer()` | Libère les ressources graphiques |

#### Système de rendu

- **Fond**: Image statique depuis `assets/sprites/fond.png`
- **Vaisseau**: Texture avec effet de clignotement pendant l'invulnérabilité
  - Visible/invisible alternant 4 fois par seconde
  - Affichage semi-transparent si texture manquante
- **Astéroïdes**: Texture avec fallback en rectangle gris
- **Projectiles**: Rectangles jaunes

#### Clignotement (Blink)
```cpp
bool shouldDrawShip = (static_cast<int>(v.mInvulnerabilityTime * 4) % 2) == 0;
```
- Calcul basé sur le temps d'invulnérabilité restant
- 4 cycles par seconde = fréquence facilement perceptible

---

### UI.h / UI.cpp
**Responsabilité**: Interface utilisateur et menus

#### Enums

##### `MenuAction`
Actions disponibles dans le menu de sélection:
```cpp
enum class MenuAction {
    None,           // Aucune action
    SelectEasy,     // Sélection difficulté Facile
    SelectMedium,   // Sélection difficulté Moyen
    SelectHard,     // Sélection difficulté Difficile
    StartGame       // Démarrer la partie
};
```

##### `GameOverAction`
Actions disponibles à l'écran Game Over:
```cpp
enum class GameOverAction {
    None,      // Aucune action
    Restart,   // Recommencer une partie
    Menu       // Retour au menu principal
};
```

#### Méthodes principales

| Méthode | Description |
|---------|-------------|
| `Initialiser(SDL_Window*, SDL_Renderer*, const std::string&, int)` | Initialise ImGui et charge les ressources |
| `AfficherInterface(const Game&)` | Affiche le score, les vies et autres infos HUD |
| `AfficherMenuDifficulte()` | Affiche le menu de sélection de difficulté |
| `Nettoyer()` | Nettoie les ressources ImGui |

#### Écrans ImGui

1. **Menu Principal**: Choix de la difficulté avec boutons ImGui
2. **HUD In-Game**: Affichage du score et des vies en temps réel
3. **Game Over**: Résumé du score et options (Recommencer/Menu)

---

### Utils.h / Utils.cpp
**Responsabilité**: Fonctions utilitaires globales

#### Constantes
```cpp
namespace Constants {
    constexpr float WINDOW_WIDTH = 800.0f;
    constexpr float WINDOW_HEIGHT = 600.0f;
};
```

#### Méthodes statiques

| Méthode | Description |
|---------|-------------|
| `VerifierCollision(const SDL_FRect&, const SDL_FRect&)` | Détection AABB |
| `GenererNombreAleatoire(float min, float max)` | Génère nombre aléatoire |
| `LimiterPosition(float&, float min, float max)` | Clamp une position |
| `CalculerDistance(float, float, float, float)` | Distance euclidienne |

---

### main.cpp
**Responsabilité**: Point d'entrée et boucle principale

#### Initialisation
1. **SDL3**: Création fenêtre et renderer
2. **ImGui**: Contexte et backends
3. **Game**: Initialisation logique du jeu
4. **Renderer**: Chargement des textures
5. **UI**: Configuration menus

#### Boucle principale
```
Chaque frame:
1. Calcul deltaTime
2. Traitement événements SDL
3. Logique du jeu (Update)
4. Gestion états (Menu/Playing/GameOver)
5. Rendu (Renderer)
6. Rendu UI (ImGui)
7. Swap buffers SDL
```

#### États du jeu

```
Menu
  ├─ Sélection Facile ──┐
  ├─ Sélection Moyen  ──┼──► Playing
  ├─ Sélection Hard  ───┤
  │                      │
  └──────────────────────┘
                 │
                 ▼
            GameOver
                 │
          ┌──────┴──────┐
          │              │
    Restart       Retour Menu
          │              │
          └──────┬───────┘
                 ▼
              Menu
```

---

## 🔗 Dépendances

### Bibliothèques externes (incluses dans le projet)

| Dépendance | Version | Utilisation |
|---|---|---|
| **SDL3** | 3.x | Fenêtrage, rendu, gestion événements |
| **SDL3_image** | 3.x | Chargement textures PNG/JPG |
| **ImGui** | Latest | Interface utilisateur et menus |

### Compilateurs supportés
- Visual Studio 2019+ (MSVC)
- Visual Studio 2022 (MSVC)
- MinGW (g++) sur Windows

### Standards C++
- **C++17** minimum
- **C++20** recommandé

---

## 📁 Structure du Projet

```
Jeu_de_tire_spatial/
├── build.bat                          # Script de compilation
├── README.md                          # Ce fichier
├── imgui.ini                          # Configuration ImGui
│
├── include/                           # En-têtes
│   ├── Game.h                         # Logique du jeu
│   ├── Renderer.h                     # Affichage graphique
│   ├── UI.h                           # Interface utilisateur
│   └── Utils.h                        # Utilitaires
│
├── src/                               # Sources
│   ├── main.cpp                       # Point d'entrée
│   ├── Game.cpp                       # Implémentation Game
│   ├── Renderer.cpp                   # Implémentation Renderer
│   ├── UI.cpp                         # Implémentation UI
│   └── Utils.cpp                      # Implémentation Utils
│
├── assets/                            # Ressources du jeu
│   ├── sprites/
│   │   ├── vaisseau.png               # Texture du vaisseau
│   │   ├── asteroide.png              # Texture astéroïde
│   │   └── fond.png                   # Image de fond
│   └── sons/                          # Répertoire sons (actuellement vide)
│
├── external/                          # Dépendances externes
│   ├── SDL3/                          # SDL3 (window, renderer)
│   ├── SDL3_image/                    # SDL3_image (chargement textures)
│   └── imgui/                         # ImGui (interface utilisateur)
│       ├── backends/                  # Implémentations SDL3
│       ├── docs/                      # Documentation ImGui
│       └── examples/                  # Exemples ImGui
│
└── build/                             # Répertoire de compilation (généré)
    └── Jeu_de_tire_spatial.exe        # Exécutable final
```

---

## 🔄 Flux de jeu détaillé

### Démarrage
```
main.cpp
  ↓
Initialiser SDL3
  ↓
Créer fenêtre (800x600)
  ↓
Initialiser ImGui + backends
  ↓
Charger ressources (Game, Renderer, UI)
  ↓
Boucle principale
```

### En jeu (Playing)
```
Frame N:
  1. Calculer deltaTime
  2. Traiter entrées utilisateur
  3. Update Game (logique, collisions, mouvements)
  4. Update positions astéroïdes/projectiles
  5. Détecter collisions
  6. Générer nouveaux astéroïdes
  7. Renderer::AfficherScene() → Rendu SDL
  8. UI::AfficherInterface() → Rendu ImGui HUD
  9. Afficher résultat SDL_RenderPresent()
  10. Si Game Over → changeState(GameOver)
```

### Collision avec astéroïde
```
Collision vaisseau ↔ astéroïde
  ↓
Est invulnérable?
  ├─ Oui → Ignorer
  └─ Non ↓
    Réduire vies (-1)
    ↓
    Activer invulnérabilité (2s)
    ↓
    Marquer astéroïde pour suppression
    ↓
    Afficher message console
    ↓
    Vies ≤ 0? → GameState = GameOver
```

---

## 🚀 Optimisations futures possibles

- [ ] **Effets sonores**: Ajouter sons tir, collision, fond sonore
- [ ] **Particules**: Explosion astéroïde, traînée vaisseau
- [ ] **Power-ups**: Multiplicateur score, protection, tir rapide
- [ ] **Niveaux**: Vagues d'astéroïdes thématiques
- [ ] **Leaderboard**: Sauvegarde scores locaux
- [ ] **Mobile**: Contrôles tactiles pour Android/iOS
- [ ] **Multijoueur**: Mode co-op local

---

## 📝 Notes de développement

### Système de timing
- **Deltatime**: Utilisé pour tous les mouvements (indépendant de la FPS)
- **Limite**: Max 33ms (33 FPS) pour éviter sauts de physique
- **Précision**: Nanoseconde avec `SDL_GetTicksNS()`

### Détection collision
- **Algorithme**: AABB (boîtes de collision alignées aux axes)
- **Performance**: O(n²) pour projectiles × astéroïdes
- **Optimisation possible**: Spatial partitioning (Quadtree)

### Gestion mémoire
- **Conteneurs**: `std::vector` avec `erase-remove` idiom
- **Textures**: Gérées par SDL, libérées à l'arrêt
- **ImGui**: Context détruit en fin d'exécution

---

## 🤝 Contribution

Pour améliorer le jeu, vous pouvez:
1. Ajouter des visuels (animations, particules)
2. Implémenter des sons
3. Ajouter des power-ups
4. Optimiser la détection collision
5. Améliorer l'interface ImGui

---

## 📄 Licence

Ce projet utilise:
- **SDL3**: Licence Zlib
- **ImGui**: Licence MIT
- **SDL3_image**: Licence Zlib

---

## 👨‍💻 Auteur

Développé en C++ avec passion pour les jeux arcade rétro!

---

## ❓ FAQ

**Q: Comment augmenter la difficulté du jeu?**
R: Modifiez les paramètres dans `Game::InitialiserJeu()`. Pour Difficile:
- Réduisez `mLives`
- Augmentez `mMaxAsteroids`
- Augmentez `mAsteroidSpawnChance`

**Q: Le vaisseau clignote constamment, comment le corriger?**
R: Vérifiez que `INVULNERABILITY_DURATION` n'est pas trop court (actuellement 2 secondes).

**Q: Comment ajouter de nouvelles textures?**
R: Placez les fichiers PNG dans `assets/sprites/` et modifiez les chemins dans `Renderer.h`.

**Q: Pourquoi le jeu lag?**
R: Vérifiez que `deltaTime` est limité à 33ms. Si GPU slow, réduisez la résolution ou la qualité des textures.

---

**Bon jeu! 🎮✨**
