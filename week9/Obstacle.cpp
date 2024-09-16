#include "Obstacle.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

Obstacle::Obstacle()
{

};

void Obstacle::drawObstacle(Graphics& gr, int _x, int _y)
{
    // Seed the random number generator (you can do this once in your game initialization)
    srand(static_cast<unsigned int>(time(0)));

    // Generate random RGB values
    int r = rand() % 256; // Red: 0-255
    int g = rand() % 256; // Green: 0-255
    int b = rand() % 256; // Blue: 0-255

    for (int x = _x; x <= _x + x_size; x++)
    {
        for (int y = _y; y < _y + y_size; y++)
        {
            gr.PutPixel(x, y, r, g, b);  // Use random color for each obstacle
        }
    }
}

void Obstacle::drawObstacle(Graphics& gr, int _x, int _y, int y_size)
{
	for (int x = _x; x <= _x + x_size; x++)
	{
		for (int y = _y; y < _y + y_size; y++)
		{
			gr.PutPixel(x, y, 0, 255, 0);
		}
	}

}