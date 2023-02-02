#include "raylib.h"

int main()
{
    // Window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;
    InitWindow(windowDimensions[0], windowDimensions[1], "Phil's Top Down");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        Vector2 mapPos{0.0,0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}