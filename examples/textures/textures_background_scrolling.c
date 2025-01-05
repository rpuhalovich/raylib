#include "raylib.h"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "raylib [textures] example - background scrolling");

    // NOTE: Be careful, background width must be equal or bigger than screen width
    // if not, texture should be draw more than two times for scrolling effect
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

    float scrolloff = 0.0f;

    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(GetColor(0x052c46ff));
            // DrawTextureEx(foreground, (Vector2){ 100, 100 }, 0.0f, 1.0f, WHITE);
            // DrawTextureRec(foreground, (Rectangle){ scrolloff, 100, 100, 100 }, (Vector2){ 200, 200 }, WHITE);
            DrawTexturePro(foreground, (Rectangle){ scrolloff, 100, 50, 50 }, (Rectangle){ 100, 100, 400, 400 }, (Vector2){0,0}, 0.0f, WHITE);
        EndDrawing();

        scrolloff += 0.2f;
    }

    UnloadTexture(foreground);
    CloseWindow();
    return 0;
}
