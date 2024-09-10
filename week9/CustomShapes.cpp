#include "CustomShapes.h"
#include <cmath>

void CustomShapes::drawLine(Graphics& gr, int x1, int y1, int x2, int y2, int r, int g, int b)
{
    int x_len = x2 - x1;
    int y_len = y2 - y1;

    if (x_len == 0)
    {
        // Vertical line
        for (int i = y1; i < y2; i++)
        {
            gr.PutPixel(x1, i, r, g, b);
        }
    }
    else if (y_len == 0)
    {
        // Horizontal line
        for (int i = x1; i < x2; i++)
        {
            gr.PutPixel(i, y1, r, g, b);
        }
    }
}

void CustomShapes::drawCircle(Graphics& gr, int ox, int oy, int rad, int r, int g, int b)
{
    for (int x = -rad; x < rad; x++)
    {
        int height = (int)sqrt(rad * rad - x * x);
        for (int y = -height; y < height; y++)
        {
            gr.PutPixel(x + ox, y + oy, r, g, b);
        }
    }
}

void CustomShapes::drawCourt(Graphics& gr)
{
    int screenWidth = gr.ScreenWidth;
    int screenHeight = gr.ScreenHeight;

    // Top border
    drawLine(gr, 10, 10, screenWidth - 10, 10, 255, 255, 255);
    // Left border
    drawLine(gr, 10, 10, 10, screenHeight - 10, 255, 255, 255);
    // Bottom border
    drawLine(gr, 10, screenHeight - 10, screenWidth - 10, screenHeight - 10, 255, 255, 255);
    // Right border
    drawLine(gr, screenWidth - 10, 10, screenWidth - 10, screenHeight - 10, 255, 255, 255);
}
