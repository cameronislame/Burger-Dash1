#include "jbaltazarrob.h"
#include <GL/glx.h>
#include "cmcdaniel.h"
#include "cestes.h"
#include <iostream>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <string>
/**
 * Auhtor: Jesus Baltazar Robles
 * Date: 9/29/2023
 */
/*LEVEL CLASS INITIALIZATION
 * CODE COMES FROM GORDON WALK2*/
float render_val_count = 0;
Square hp_pack;
//Knife obj 
Square knife1;
Square knife2;
Square knife3;
Level::Level() {
    //Log("Level constructor\n");
    tilesize[0] = 8;
    tilesize[1] = 8;
    ftsz[0] = (Flt)tilesize[0];
    ftsz[1] = (Flt)tilesize[1];
    tile_base = 0.0;
    imageName = "final-kitchen.xpm";
    //read level
    FILE *fpi = fopen(imageName.c_str(), "r");
    if (fpi) {
        nrows=0;
        char line[1000];
        while (fgets(line, 1000, fpi) != NULL) {
            removeCrLf(line);
            int slen = strlen(line);
            ncols = slen;
            //Log("line: %s\n", line);
            for (int j=0; j<slen; j++) {
                arr[nrows][j] = line[j];
            }
            ++nrows;
        }
        fclose(fpi);
        //printf("nrows of background data: %i\n", nrows);
    }
    /*
    for (int i=0; i<nrows; i++) {
        for (int j=0; j<ncols; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    } */
}

Level::Level(int tileSizeX, int tileSizeY, std::string fileName) {
    
    tilesize[0] = tileSizeX;
    tilesize[1] = tileSizeY;
    ftsz[0] = (Flt)tilesize[0];
    ftsz[1] = (Flt)tilesize[1];
    tile_base = 0.0;
    imageName = fileName;
    //read level
    FILE *fpi = fopen(imageName.c_str(), "r");
    if (fpi) {
        nrows=0;
        char line[20];
        while (fgets(line, 20, fpi) != NULL) {
            removeCrLf(line);
            int slen = strlen(line);
            ncols = slen;
            //Log("line: %s\n", line);
            for (int j=0; j<slen; j++) {
                burgerArr[nrows][j] = line[j];
            }
            ++nrows;
        }
        fclose(fpi);
        //printf("nrows of background data: %i\n", nrows);
    }
}

void Level::removeCrLf(char *str) {
    //remove carriage return and linefeed from a Cstring
    char *p = str;
    while (*p) {
        if (*p == 10 || *p == 13) {
            *p = '\0';
            break;
        }
        ++p;
    }
}
void render_calls(){
    render_val_count = render_val_count + 1;
}
float total_render_function_calls(){
    return render_val_count;
}
void init_hpPack()
{
    //hp_pack.pos[0] = gl.xres + 300.0;
    hp_pack.pos[0] = burger.pos[0] + (float)gl.xres  + 300.0; 
    hp_pack.pos[1] = gl.yres / 3.0;
    hp_pack.width = 20.0;
    hp_pack.vel[0] = -30;
    hp_pack.height = 20.0;

}
void initKnives()
{
    //initialize knives in the air
    knife1.pos[0] = gl.xres + knife1.width;
    knife1.pos[1] = gl.yres / 4.0;
    knife1.width = 20.0;
    knife1.vel[0] = -40;
    knife1.height = 4.0;


    knife2.pos[0] = gl.xres + knife2.width + 20.0;
    knife2.pos[1] = (gl.yres / 4.0) + 40.0;
    knife2.width = 20.0;
    knife2.vel[0] = -40;
    knife2.height = 4.0;

    knife3.pos[0] = gl.xres + knife3.width + 20;
    knife3.pos[1] = (gl.yres / 4.0) - 40.0;
    knife3.width = 20.0;
    knife3.vel[0] = -40;
    knife3.height = 4.0;
}
void render_knives()
{
    //Knives in the air
    glPushMatrix();
    glColor3ub(160,32,240);
    glTranslatef(knife1.pos[0], knife1.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-knife1.width, -knife1.height);
    glVertex2f(-knife1.width,  knife1.height);
    glVertex2f( knife1.width,  knife1.height);
    glVertex2f( knife1.width, -knife1.height);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glColor3ub(160,32,240);
    glTranslatef(knife2.pos[0], knife2.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-knife2.width, -knife2.height);
    glVertex2f(-knife2.width,  knife2.height);
    glVertex2f( knife2.width,  knife2.height);
    glVertex2f( knife2.width, -knife2.height);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(160,32,240);
    glTranslatef(knife3.pos[0], knife3.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-knife3.width, -knife3.height);
    glVertex2f(-knife3.width,  knife3.height);
    glVertex2f( knife3.width,  knife3.height);
    glVertex2f( knife3.width, -knife3.height);
    glEnd();
    glPopMatrix();
}
void render_hp_pack()
{
    //render hp pack in the air
    if(healthbar.health < 170) {
        glPushMatrix();
        glColor3ub(0,255,0);
        glTranslatef(hp_pack.pos[0], hp_pack.pos[1], 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-hp_pack.width, -hp_pack.height);
        glVertex2f(-hp_pack.width,  hp_pack.height);
        glVertex2f( hp_pack.width,  hp_pack.height);
        glVertex2f( hp_pack.width, -hp_pack.height);
        glEnd();
        glPopMatrix();
    }
}
