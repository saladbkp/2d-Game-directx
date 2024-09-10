#pragma once

class Graphics {
public:
    static const int ScreenWidth = 800;
    static const int ScreenHeight = 600;
    void PutPixel(int x, int y, int r, int g, int b);
};
