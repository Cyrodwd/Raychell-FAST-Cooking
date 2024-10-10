#include "raylib.h"
#include "draggable.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Raychell's Fast Cooking"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    draggable my_draggable = create_draggable((Vector2){0, 0, }, (Vector2){ 50.0f, 50.0f});

    while (!WindowShouldClose())
    {
        update_draggable(&my_draggable);
        BeginDrawing();

        ClearBackground(RAYWHITE);

        draw_draggable(&my_draggable);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
