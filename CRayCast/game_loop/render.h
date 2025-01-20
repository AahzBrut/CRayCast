#pragma once
#include "constants.h"
#include "raylib.h"


extern Texture2D wallTextures[NUM_TEXTURES];
extern bool renderTextured;

void Render();
void RenderFPSCount();
void DrawMap();
void DrawRays();
void DrawPlayer();
void RenderWorld();
