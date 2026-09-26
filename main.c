#include "raylib.h"

#define TWEENER_IMPLEMENTATION
#include "rtweener.h"

#include "reasings.h"

#define RECS 5

static void UpdateRecs(float dt);

int main() {
    InitWindow(500, 500, "");
    SetTargetFPS(60);

    Tween raw[128] = {0};
    Tweener t = {
        .len = 128,
        .raw = raw
    };

    Vector2 recs[RECS] = {
        {100, 100},
        {200, 200},
         {300, 0},
         {0, 300},
         {500, 500}
    };

    for (int i = 0; i < RECS; i++) {
        AddTweenVec2(&t, &(recs[i]), (Vector2){recs[i].x, recs[i].y}, (Vector2){0, 0}, 3, GetFrameTime, EaseCubicOut);
    }

    while (!WindowShouldClose()) {
        UpdateTweens(&t);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < RECS; i++) {
            DrawRectangleRec((Rectangle){recs[i].x, recs[i].y, 50, 50}, RED);
        }
        EndDrawing();
    }
    return 0;
}