/*******************************************************************************************
*
*   raylib [textures] example - Text Scrolling
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2025 Ryan Puhalovich
*
********************************************************************************************/

#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

char* lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum";
char* tqbf = "The quick brown fox jumps over the lazy dog.";

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "texture scrolling");
    SetTargetFPS(60);

    char* text = tqbf;

    float fontsize = 64.0f;
    Font font = LoadFontEx("resources/JetBrainsMono.ttf", (int)fontsize, 0, 0);
    Vector2 sizing = MeasureTextEx(font, text, fontsize, 1.0f);

    Image img = GenImageColor(sizing.x, sizing.y, GRAY);
    ImageDrawTextEx(&img, font, text, (Vector2){ 0.0f, 0.0f }, (float)font.baseSize, 0.0f, BLACK);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    float scrolloffx = 0.0f;
    while (!WindowShouldClose()) {
        float recwidth = 1000.0f;
        float recheight = sizing.y;

        // core
        {
            float dt = GetFrameTime();

            scrolloffx = fmax(0.0f, scrolloffx + GetMouseWheelMove() * 256.0f * dt);
            scrolloffx = fmin(sizing.x - recwidth, scrolloffx);
        }

        // draw
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            Rectangle bgrec = (Rectangle){ 0, 0, recwidth, recheight };

            Rectangle centeredrec = (Rectangle){
                screenWidth / 2 - recwidth / 2,
                screenHeight / 2 - recheight / 2,
                recwidth,
                recheight };

            DrawRectangleRec(centeredrec, GRAY);
            DrawTexturePro(
                texture,
                (Rectangle){ scrolloffx, 0, recwidth, recheight },
                centeredrec,
                (Vector2){ 0, 0 },
                0.0f,
                WHITE);

            EndDrawing();
        }
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}
