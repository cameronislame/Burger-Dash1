/**
 * Author: Mario Jimenez
 * Created: 09/27/2023
 * File: mjimenez.cpp
 * Description: Mario Jimenez Source File 
 **/

#include "mjimenez.h"
#include "fonts.h"
#include <GL/glx.h>
#include <time.h>
/*
int time_since_key_press(const bool get) {
    static int check_keys = 1;
    static int start_time;
    if (check_keys) {
        start_time = time(NULL);
        check_keys = 0;
    }
    if (get) {
        return time(NULL) - start_time;
    }
    return 0;
}
*/

int time_since_key_press(time_t begin) {
        return time(NULL) - begin;
}

void display_border(int xres, int yres)
{
    // draw a border around the window

    int b = 50;
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(0.0f, 1.0f, 1.0f, 0.5f);
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
        glVertex2i(0,      0);
        glVertex2i(0+b,      0+b);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}
/*
void display_name(int x, int y)
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 0, 0x00000000, "Mario");

}
*/
