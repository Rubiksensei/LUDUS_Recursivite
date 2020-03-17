#include <SDL/SDL.h>

#define MAX(a, b) (((a)>(b))?(a):(b))
#define ABS(a) (((a)<0)?-(a):(a))

#define SQRT_3  1.732

void dot(int x, int y, Uint32 color)
{
    SDL_Rect r = {x, y, 1, 1};
    SDL_FillRect(SDL_GetVideoSurface(), &r, color);
}

void drawLine(int x1, int y1, int x2, int y2, Uint32 color)
{
    double x = x1, y = y1;
    double inc_x = x2 - x1, inc_y = y2 - y1;
    int m = MAX(ABS(inc_x), ABS(inc_y));
    inc_x /= m;
    inc_y /= m;

    for(; m >= 0; m--)
    {
        dot((unsigned int)x, (unsigned int)y, color);
        x += inc_x;
        y += inc_y;
    }
}

void fractale(int x1, int y1, int x2, int y2, int level)
{
    if(level > 0)
    {
        int x3 = (2*x1 + x2)/3;
        int y3 = (2*y1 + y2)/3;
        int x5 = (x1 + 2*x2)/3;
        int y5 = (y1 + 2*y2)/3;
        int x4 = x3 + (x5 - x3)/2 + (y5 - y3)*SQRT_3/2;
        int y4 = y3 - (x5 - x3)*SQRT_3/2 + (y5 - y3)/2;
        fractale(x1, y1, x3, y3, level-1);
        fractale(x3, y3, x4, y4, level-1);
        fractale(x4, y4, x5, y5, level-1);
        fractale(x5, y5, x2, y2, level-1);
    }
    else
    {
        drawLine(x1, y1, x2, y2,
            SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 255, 255));
    }
}

#define LEVEL 6

int main(int argc, char **argv)
{
    SDL_Surface *video = NULL;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    video = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
    SDL_FillRect(video, NULL, SDL_MapRGB(video->format, 0, 0, 0));

    fractale(320, 60, 520, 340, LEVEL);
    fractale(520, 340, 120, 340, LEVEL);
    fractale(120, 340, 320, 60, LEVEL);

    SDL_Flip(video);
    while(SDL_WaitEvent(&event))
        if(event.type == SDL_QUIT)
            break;
    SDL_Quit();
    return 0;
}
