#include "Paddle.h"

void Paddle::drawPaddle(Graphics& gr, int y, int size)
{
    int thickness = 10;
    for (int a = x - thickness; a <= x; a++)
    {
        for (int b = y - (size / 2); b < y + (size / 2); b++)
        {
            gr.PutPixel(a, b, 255, 0, 0); // Red paddle
        }
    }

}
