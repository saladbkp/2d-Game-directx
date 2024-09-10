#pragma once
#include "Graphics.h"

class CustomShapes {
public:
    static void drawLine(Graphics& gr, int x1, int y1, int x2, int y2, int r, int g, int b);
    static void drawCircle(Graphics& gr, int ox, int oy, int rad, int r, int g, int b);
    static void drawCourt(Graphics& gr);
};
