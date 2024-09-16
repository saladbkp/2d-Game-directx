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

    int topBorderMargin = 30;      // Top border margin
    int rightBorderMargin = 70;    // Right border margin (decreased)
    int extendedLineOffset = 80;   // Extend the top and bottom lines by 20 pixels on both sides

    // Top border (extended by 20 pixels on both sides)
    drawLine(gr, 10 - extendedLineOffset, topBorderMargin, screenWidth - 10 + extendedLineOffset, topBorderMargin, 255, 255, 255);
    // Left border (remains the same)
    drawLine(gr, 10, topBorderMargin, 10, screenHeight - 10, 255, 255, 255);
    // Bottom border (extended by 20 pixels on both sides)
    drawLine(gr, 10 - extendedLineOffset, screenHeight - 10, screenWidth - 10 + extendedLineOffset, screenHeight - 10, 255, 255, 255);
    // Right border (moved left by 50 pixels)
    drawLine(gr, screenWidth + rightBorderMargin, topBorderMargin, screenWidth + rightBorderMargin, screenHeight - 10, 255, 255, 255);
}


