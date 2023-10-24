/***************************************************
 * Copyright    : 2023 Cameron McDaniel
 * File Name    : cmcdaniel.cpp
 * Description   : individual project source file
***************************************************/


#include "fonts.h"
#include "cmcdaniel.h"
#include <GL/glx.h>
#include <time.h>

/*
void display_name(int x, int y) 
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 0, 0x00ffff00, "Cameron");

}

void display_border(int xres, int yres)
{
    int b = 50;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2i(0,      0);
        glVertex2i(0+b,    0+b);
        glVertex2i(0,      0+yres);
        glVertex2i(0+b,    0+yres-b);
        glVertex2i(xres,   0+yres);
        glVertex2i(xres-b, 0+yres-b);
        glVertex2i(xres,   0);
        glVertex2i(xres-b, b);
	
        glVertex2i(0, 0);

        glVertex2i(0+b,     0+b);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);

}
*/
void display_credits(int xres, int yres) 
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex2i(0,      0);
        glVertex2i(0,      0+yres);
        glVertex2i(xres,   0+yres);
        glVertex2i(xres,   0);
	

    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);

  Rect r;
  r.bot = yres * 2 / 3;
  r.left = xres / 2;
  r.center = 100;
  ggprint16(&r, 16, 0x00ffff00, "CREDITS:");
  ggprint8b(&r, 16, 0x00ffff00, "Cameron McDaniel");
  ggprint8b(&r, 16, 0x00ffff00, "Conner Estes");
  ggprint8b(&r, 16, 0x00ffff00, "Jesus Baltazar");
  ggprint8b(&r, 16, 0x00ffff00, "Mario Jimenez");

}

int total_running_time(time_t begin)
{
    return time(NULL) - begin;    
}

int time_since_mouse_move(time_t mouse_timer)
{
    return time(NULL) - mouse_timer;
}
