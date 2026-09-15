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

    Rectangle recs[RECS] = {
        {100,100,50,50},
        {0,0,50,50},
        {25, 25, 50, 50},
        {0, 100, 50, 50},
        {10, 25, 50, 50}
    };

    for (int i = 0; i < RECS; i++) {
        AddTween(&t, MakeTween(&(recs[i].x), recs[i].x, 0, 5, GetFrameTime, EaseCubicIn));
        AddTween(&t, MakeTween(&(recs[i].y), recs[i].y, 0, 5, GetFrameTime, EaseCubicIn));
    }

    while (!WindowShouldClose()) {
        UpdateTweens(&t);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < RECS; i++) {
            DrawRectangleRec(recs[i], RED);
        }
        EndDrawing();
    }
    return 0;
}