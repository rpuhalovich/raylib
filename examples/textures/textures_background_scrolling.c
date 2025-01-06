#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "texture scrolling");

    // NOTE: Be careful, background width must be equal or bigger than screen width
    // if not, texture should be draw more than two times for scrolling effect
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

    float maxSpeed = 10.0f;
    float curspeedx = 0.0f;

    float scrolloffx = 0.0f;
    float scrolloffy = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // core
        {
            float dt = GetFrameTime();
            float scrollAmount = 3.0f;
            float acceleration = 9.8f;

            if (IsKeyDown(KEY_RIGHT))
                curspeedx = fmin(maxSpeed, curspeedx + acceleration * dt);
            if (!IsKeyDown(KEY_RIGHT))
                curspeedx = fmax(0.0f, curspeedx - acceleration * dt);

            scrolloffx += GetMouseWheelMove();

            printf("%f\n", curspeedx);
            scrolloffx += curspeedx;

            if (IsKeyDown(KEY_UP))
                scrolloffy -= scrollAmount;
            if (IsKeyDown(KEY_DOWN))
                scrolloffy += scrollAmount;
        }

        // draw
        {
            BeginDrawing();
                ClearBackground(GetColor(0x052c46ff));
                // DrawTextureEx(foreground, (Vector2){ 100, 100 }, 0.0f, 1.0f, WHITE);
                // DrawTextureRec(foreground, (Rectangle){ scrolloff, 100, 100, 100 }, (Vector2){ 200, 200 }, WHITE);
                DrawTexturePro(foreground, (Rectangle){ scrolloffx, scrolloffy, 200, 100 }, (Rectangle){ 100, 100, 800, 400 }, (Vector2){0,0}, 0.0f, WHITE);
            EndDrawing();
        }
    }

    UnloadTexture(foreground);
    CloseWindow();
    return 0;
}
