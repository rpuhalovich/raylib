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
char* lorem2 = "incididunt ut labore et";
char* lorem3 = "nostrud exercitation ullamco laboris ut aliquip";
char* lorem4 = "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu";
char* lorem5 = "fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in";
char* lorem6 = "culpa qui officia deserunt mollit anim id est laborum";
char* lorem7 = "foo bar baz";

float clamp(float v, float min, float max)
{
    return fmin(max, fmax(min, v));
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "texture scrolling");
    SetTargetFPS(60);

    int rows = 7;
    float fontsize = 64.0f;
    Font font = LoadFontEx("resources/JetBrainsMono.ttf", (int)fontsize, 0, 0);
    Vector2 sizing = MeasureTextEx(font, lorem1, fontsize, 1.0f);

    float textRecWidth = sizing.x;
    float textRecHeight = sizing.y * rows;
    float imageRecWidth = textRecWidth + 1000.0f;
    float imageRecHeight = textRecHeight + 800.0f;
    float displayRecWidth = 1000.0f;
    float displayRecHeight = 400.0f;

    Image img = GenImageColor(imageRecWidth, imageRecHeight, GRAY);
    ImageDrawRectangleRec(&img, (Rectangle) { 0.0f, 0.0f, textRecWidth, textRecHeight }, RED);
    ImageDrawTextEx(&img, font, lorem1, (Vector2){ 0.0f, 0.0f }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, lorem2, (Vector2){ 0.0f, sizing.y }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, lorem3, (Vector2){ 0.0f, sizing.y * 2 }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, lorem4, (Vector2){ 0.0f, sizing.y * 3 }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, lorem5, (Vector2){ 0.0f, sizing.y * 4 }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, lorem6, (Vector2){ 0.0f, sizing.y * 5 }, (float)font.baseSize, 0.0f, BLACK);
    ImageDrawTextEx(&img, font, lorem7, (Vector2){ 0.0f, sizing.y * 6 }, (float)font.baseSize, 0.0f, BLACK);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    float scrollAmount = 10.0f;
    float scrolloffx = 0.0f;
    float scrolloffy = 0.0f;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // core
        {
            if (IsKeyDown(KEY_UP))
                scrolloffy += scrollAmount;
            if (IsKeyDown(KEY_DOWN))
                scrolloffy -= scrollAmount;
            // scrolloffy = fmin(0.0f, scrolloffy);
            scrolloffy = clamp(scrolloffy, 0.0f, textRecHeight);

            if (IsKeyDown(KEY_LEFT))
                scrolloffx -= scrollAmount;
            if (IsKeyDown(KEY_RIGHT))
                scrolloffx += scrollAmount;
            scrolloffx = clamp(scrolloffx, 0.0f, textRecWidth);

            printf("scrolloffx: %f, scrolloffy: %f\n", scrolloffx, scrolloffy);
        }

        // draw
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // source - the actual screen layout of the texture
            Rectangle source = (Rectangle){
                screenWidth / 2 - displayRecWidth / 2,
                screenHeight / 2 - displayRecHeight / 2,
                displayRecWidth,
                displayRecHeight };

            // dest - the offset and scaling of the texture
            Rectangle dest = (Rectangle){
                scrolloffx,
                scrolloffy,
                displayRecWidth,
                displayRecHeight };

            // e.g. from core_smooth_pixelperfect.c
            // Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
            // Rectangle destRec = { -virtualRatio, -virtualRatio, screenWidth + (virtualRatio*2), screenHeight + (virtualRatio*2) };

            DrawTexturePro(
                texture,
                dest,
                source,
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
