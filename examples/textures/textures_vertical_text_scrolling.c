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

/*
TODO:
    - [ ] use a RenderTexture2D to render text to a texture as it's more effecient?
        - [ ] see textures_fog_of_war.c for an example of this

```c
BeginTextureMode(fogOfWar);
    ClearBackground(BLANK);

    // use regular draw commands...
EndTextureMode();
```
*/

#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

int rows = 7;
char* lorem[] = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor",
    "incididunt ut labore et",
    "nostrud exercitation ullamco laboris ut aliquip",
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu",
    "fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in",
    "culpa qui officia deserunt mollit anim id est laborum",
    "foo bar baz"
};

int shakeRows = 14;
char* shake[] = {
    "Over hill, over dale,",
    "Thorough bush, thorough brier,",
    "Over park, over pale,",
    "Thorough flood, thorough fire!",
    "I do wander everywhere,",
    "Swifter than the moon's sphere;",
    "And I serve the Fairy Queen,",
    "To dew her orbs upon the green;",
    "The cowslips tall her pensioners be;",
    "In their gold coats spots you see;",
    "Those be rubies, fairy favours;",
    "In those freckles live their savours;",
    "I must go seek some dewdrops here,",
    "And hang a pearl in every cowslip's ear."
};

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

    float fontsize = 64.0f;
    Font font = LoadFontEx("resources/JetBrainsMono.ttf", (int)fontsize, 0, 0);
    Vector2 sizing = MeasureTextEx(font, shake[13], fontsize, 1.0f);

    float textRecWidth = sizing.x;
    float textRecHeight = sizing.y * shakeRows;
    float imageRecWidth = textRecWidth + 1000.0f;
    float imageRecHeight = textRecHeight + 800.0f;
    float displayRecWidth = 1000.0f;
    float displayRecHeight = 400.0f;

    Image img = GenImageColor(imageRecWidth, imageRecHeight, GRAY);
    ImageDrawRectangleRec(&img, (Rectangle) { 0.0f, 0.0f, imageRecWidth, imageRecHeight }, RED);

    for (int i = 0; i < shakeRows; i++)
        ImageDrawTextEx(&img, font, shake[i], (Vector2){ 0.0f, sizing.y * i }, (float)font.baseSize, 0.0f, BLACK);

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
                scrolloffy -= scrollAmount;
            if (IsKeyDown(KEY_DOWN))
                scrolloffy += scrollAmount;
            scrolloffy = clamp(scrolloffy, 0.0f, textRecHeight);

            if (IsKeyDown(KEY_LEFT))
                scrolloffx -= scrollAmount;
            if (IsKeyDown(KEY_RIGHT))
                scrolloffx += scrollAmount;
            scrolloffx = clamp(scrolloffx, 0.0f, textRecWidth);

            // printf("scrolloffx: %f, scrolloffy: %f\n", scrolloffx, scrolloffy);
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

            char str[128];
            sprintf(str, "scrolloffx: %.2f, scrolloffy: %.2f", scrolloffx, scrolloffy);
            DrawText(str, 16.0f, 16.0f, 32.0f, BLACK);

            EndDrawing();
        }
    }

    UnloadTexture(texture);
    UnloadFont(font);
    CloseWindow();
    return 0;
}
