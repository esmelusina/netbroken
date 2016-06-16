#pragma once

#define KEY_ESCAPE    256
#define KEY_ENTER	  257
#define KEY_TAB		  258
#define KEY_BACKSPACE 259

#define KEY_RIGHT     262
#define KEY_LEFT	  263
#define KEY_DOWN	  264
#define KEY_UP		  265

#define WHITE	 0xffffffff
#define BLACK    0x000000ff
#define CYAN	 0x00ffffff
#define MAGENTA  0xff00ffff
#define YELLOW	 0xffff00ff
#define RED		 0xff0000ff
#define GREEN    0x00ff00ff
#define BLUE	 0x0000ffff
#define NONE     0x00000000

#define PI 3.14159265359

namespace sfwl
{
    const float identity[9] = {1,0,0,0,1,0,0,0,1};


    bool initContext(unsigned width = 800, unsigned height = 600, const char *title = "SFW Draw", unsigned max_lines = 32000);

    void termContext();

    bool stepContext();

    void drawLineGradient(float x1, float y1, float x2, float y2, unsigned c1 = WHITE, unsigned c2 = WHITE, const float transform[9] = identity);

    void drawLine(float x1, float y1, float x2, float y2, unsigned c = WHITE, const float transform[9] = identity);

    void drawBox(float x, float y, float s, unsigned c = WHITE, const float transform[9] = identity);

    // Real application time
    float getTime();

    // Calculated time between the last frame and the current
    float getDeltaTime();

    bool getKey(unsigned keycode);
}