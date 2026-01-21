@echo off
cls
REM nettoyage des anciens fichiers
if exist jeu.exe del /f /q jeu.exe

echo ================================
echo compilation en cours...
echo ================================

g++ src\*.cpp ^
external\imgui\imgui.cpp ^
external\imgui\imgui_draw.cpp ^
external\imgui\imgui_tables.cpp ^
external\imgui\imgui_widgets.cpp ^
external\imgui\backends\imgui_impl_sdl3.cpp ^
external\imgui\backends\imgui_impl_sdlrenderer3.cpp ^
-Iexternal\imgui ^
-Iexternal\imgui\backends ^
-Iexternal\SDL3\include ^
-Iexternal\SDL3_image\include ^
-Lexternal\SDL3\lib ^
-Lexternal\SDL3_image\lib ^
-lSDL3 -lSDL3_image -o jeu.exe

if %errorlevel% equ 0 (
    echo SUCCESS: Compilation reussie.
    echo lancement du jeu...
    jeu.exe
) else (
    echo ERROR: La compilation a echoue.
    pause
)