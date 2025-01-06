/*******************************************************************************************
*
*   raylib [textures] example - Vertical Text Scrolling
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

char* lorem1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor";
char* lorem2 = "incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis";
char* lorem3 = "nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.";
char* lorem4 = "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu";
char* lorem5 = "fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in";
char* lorem6 = "culpa qui officia deserunt mollit anim id est laborum";

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "texture scrolling");
    SetTargetFPS(60);

    int rows = 8;
    int cols = 16;

    float fontsize = 64.0f;
    Font font = LoadFontEx("resources/JetBrainsMono.ttf", (int)fontsize, 0, 0);
    Vector2 sizing = MeasureTextEx(font, lorem1, fontsize, 1.0f);

    float recwidth = 1000.0f;
    float recheight = sizing.y * rows;

    Image img = GenImageColor(recwidth, recheight, GRAY);
    ImageDrawTextEx(&img, font, "Hello there", (Vector2){ 0.0f, 0.0f }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, "Foo bar", (Vector2){ 0.0f, sizing.y }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, "This is a test", (Vector2){ 0.0f, sizing.y * 2 }, (float)font.baseSize, 0.0f, BLACK);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    float scrollAmount = 10.0f;

    float scrolloffx = 0.0f;
    float scrolloffy = 0.0f;
    while (!WindowShouldClose()) {
        float recwidth = 1000.0f;
        float recheight = sizing.y * rows;
        float dt = GetFrameTime();

        // core
        {
            // scrolloffy = fmax(0.0f, scrolloffy + GetMouseWheelMove() * 256.0f * dt);
            // scrolloffy = fmin(sizing.y - recwidth, scrolloffy);

            if (IsKeyDown(KEY_UP))
                scrolloffy -= scrollAmount;
            if (IsKeyDown(KEY_DOWN))
                scrolloffy += scrollAmount;

            if (IsKeyDown(KEY_LEFT))
                scrolloffx -= scrollAmount;
            if (IsKeyDown(KEY_RIGHT))
                scrolloffx += scrollAmount;
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
                (Rectangle){ scrolloffx, scrolloffy, recwidth, recheight },
                centeredrec,
                (Vector2){ 0, 0 },
                0.0f,
                WHITE);

            EndDrawing();
        }
    }

    UnloadTexture(texture);
    UnloadFont(font);
    CloseWindow();
    return 0;
}
