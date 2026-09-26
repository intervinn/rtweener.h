#ifndef TWEENER_H
#define TWEENER_H

#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float (*Easer)(float t, float b, float c, float d);

typedef struct Tween {
    float *current;
    float destination;
    float start;

    float (*GetTime)();
    void (*Finish)(struct Tween t);
    Easer Ease;
    
    float clock;
    float duration;

    bool going;
} Tween;

typedef struct {
    uint64_t len;
    Tween *raw;
} Tweener;

Tween MakeTween(float *out, float start, float destination, float duration, float (*GetTime)(), Easer Ease);
void AddTweenVec2(Tweener *tr, Vector2 *out, Vector2 start, Vector2 destination, float duration, float (*GetTime)(), Easer Ease);
void AddTween(Tweener *tr, Tween t);
void UpdateTweens(Tweener *tr);
void NothingFinish(Tween t);

#ifdef __cplusplus
}
#endif

#define TWEENER_IMPLEMENTATION
#ifdef TWEENER_IMPLEMENTATION

Tween MakeTween(float *out, float start, float destination, float duration, float (*GetTime)(), Easer Ease) {
    Tween t = {0};
    t.current = out;
    t.start = start;
    t.destination = destination;
    t.duration = duration;
    t.GetTime = GetTime;
    t.Ease = Ease;
    t.going = true;
    t.Finish = NothingFinish;

    return t;
}

void NothingFinish(Tween t) {
    return;
}

void AddTween(Tweener *tr, Tween t) {
    for (int i = 0; i < tr->len; i++) {
        if (!tr->raw[i].going) {
            tr->raw[i] = t;
            return;
        }
    }
}

void UpdateTweens(Tweener *tr) {
    int i = 0;
    float c = 0;

    for (int i = 0; i < tr->len; i++) {
        if (!tr->raw[i].going) continue;

        tr->raw[i].clock += tr->raw[i].GetTime();
        if (tr->raw[i].clock > tr->raw[i].duration) {
            tr->raw[i].going = false;
            tr->raw[i].Finish(tr->raw[i]);
        }

        c = tr->raw[i].destination - tr->raw[i].start;
        *(tr->raw[i].current) = tr->raw[i].Ease(
            tr->raw[i].clock,
            tr->raw[i].start,
            c,
            tr->raw[i].duration
        );
    }
}

void AddTweenVec2(Tweener *tr, Vector2 *out, Vector2 start, Vector2 destination, float duration, float (*GetTime)(), Easer Ease) {
    Tween a = MakeTween(&(out->x), start.x, destination.x, duration, GetTime, Ease);
    Tween b = MakeTween(&(out->y), start.y, destination.y, duration, GetTime, Ease);

    AddTween(tr, a);
    AddTween(tr, b);
}

#endif  
#endif // TWEENER_H