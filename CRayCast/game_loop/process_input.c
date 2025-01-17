#include "process_input.h"

#include "raylib.h"


void ProcessInput() {
    if (IsKeyDown(KEY_A)) {
        TraceLog(LOG_INFO, "ProcessInput: Key A pressed");
    }
}
