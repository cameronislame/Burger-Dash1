//This is Conner's individual source file.




#include <GL/glx.h>
#include "fonts.h"
void display_border(int xres, int yres)
{
    //draw border around window
    int b = 50;
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(1.0f,1.0f,0.0f,0.5f);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2i(0,0);
        glVertex2i(0+b,0+b);
        glVertex2i(0,0+yres);
        glVertex2i(0+b,0+yres-b);
        glVertex2i(xres,0+yres);
        glVertex2i(xres-b,0+yres-b);
        glVertex2i(xres, 0);
        glVertex2i(xres-b,b);
        glVertex2i(0,0);
        glVertex2i(0+b,0+b);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);


}


void display_name (int x , int y){


    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r,0, 0x00000000, "Conner");

}


