#pragma once
#include "raylib.h"


extern Texture2D wallTexture;
extern bool renderTextured;

void Render();
void RenderFPSCount();
void DrawMap();
void DrawRays();
void DrawPlayer();
void RenderWorld();
