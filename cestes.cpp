//Author: Conner Estes
// Created: 09/27/2023
// Description: My individual source file for my CMPS 3350 project.
// (c) Copyright by Conner Estes

//#include "burger_dash.cpp"
#include "cestes.h"
#include <GL/glx.h>
#include "fonts.h"
/*
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
*/


Square burger;



void display_name (int x , int y)
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 0, 0x00000000, "Conner");
}




Enemy enemy;  // Definition of the enemy variable

// Definition of the collision detection function
bool Check2(Square burger, Enemy enemy) {
    int leftBurger = burger.pos[0] - burger.width;
    int rightBurger = burger.pos[0] + burger.width;
    int topBurger = burger.pos[1] - burger.height;
    int bottomBurger = burger.pos[1] + burger.height;

    int leftEnemy = enemy.pos[0] - enemy.width;
    int rightEnemy = enemy.pos[0] + enemy.width;
    int topEnemy = enemy.pos[1] - enemy.height;
    int bottomEnemy = enemy.pos[1] + enemy.height;

    if (rightBurger < leftEnemy || rightEnemy < leftBurger)
        return false;

    if (bottomBurger < topEnemy || bottomEnemy < topBurger)
        return false;

    // If there is a collision, set burger's velocity to 0
    
    return true;
}

// Implement the Enemy class as needed
// For example, rendering the enemy
void renderEnemy() {
    glPushMatrix();
    glColor3ub(0, 0, 255);  // Blue color
    glTranslatef(enemy.pos[0], enemy.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-enemy.width, -enemy.height);
    glVertex2f(-enemy.width, enemy.height);
    glVertex2f(enemy.width, enemy.height);
    glVertex2f(enemy.width, -enemy.height);
    glEnd();
    glPopMatrix();
}

// ... other definitions ...

