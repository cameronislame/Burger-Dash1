/**
 * Author: Cameron McDaniel, Mario Jimenez, Conner Estes, Jesus Baltazar Robles
 * Created: 09/27/2023
 * File: burger_dash.cpp
 * Description: Main Game Source File 
 **/
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
//#include "log.h"
#include "fonts.h"
#include "X11_wrapper.h"
#include "cmcdaniel.h"
#include "cestes.h"
#include "mjimenez.h"
#include "jbaltazarrob.h"
#include <sys/stat.h>
#include </usr/include/AL/alut.h>
#include <thread>
#include <string>


//# Need to work on modified burger_dash on odin but don't want to make
// changes to main yet, until discussed.



using namespace std;
bool loopMusic = true;
bool startScreenActive = true;
bool gameOver = false;
bool restart = false;
//floating point random numbers
#define rnd() (float)rand() / (float)RAND_MAX

const float GRAVITY = 1.0f;
//Camer for level render
double camera[2] = {0.0,0.0};

//set up timers
extern void startScreenMusic();
const double physicsRate = 1.0/10.0;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);


/*
class Global {
    public:
        int xres, yres;
        double physicsCountdown;
        double timeSpan;
        unsigned int keys[65536];
        int score;
        bool show_border;
        bool display_credits;
        bool CheckCollision2;
        double delay;
        bool display_statistics;
        time_t begin;
        time_t key_checker;
        Global() {
            show_border = false;
            display_credits = false;
            display_statistics = false;
            xres = 1200;
            yres = 600;
            score = 0;
            delay = 0.1;
            time(&begin);
            time(&key_checker);
        }
} gl; */
Global gl;

class Obstacle {
    public:
        float pos[2];
        float vel[2];
        float verts[4][2];
        float width;
        float height;
        bool pointClaimed;
        Obstacle() {
            init();
        }
        void init() {
            pointClaimed = false;
            vel[0] = -5.0f;
            vel[1] = 0.0f;
            width =  30.0f;
            height = 20.0f;
            pos[0] = 900.0f;
            pos[1] = 0.0f + height;
        }
} spike;

// Render knives
int ST = 1;
int hp_ST = 1;
//Square burger;

//Declare global Level class
Level lev;
Level burgerSprite(5.0f, 5.0f, "burger.xpm");
ShieldPowerUp shieldPowerUp;
//Function prototypes
void init_opengl(void);
void physics(void);
void render(void);






void waitForEnterKey(X11_wrapper &x11) {
    // XEvent e;
    if (!playOpenALSound("./607276__bloodpixelhero__retro-arcade-music-2.wav")) {
        printf("Failed to play sound.\n");
    }
    while (startScreenActive) { 
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            if (e.type == KeyPress) {
                int key = XLookupKeysym(&e.xkey, 0);
                if (key == XK_Return) {
                    startScreenActive = false;
		    stopOpenALSound();
                    break;
                }
            }
        }
    }
}
//extern bool CheckCollision2(Square burger, Enemy enemy) ;

//=====================================
// MAIN FUNCTION IS HERE
//=====================================

int main() {
    X11_wrapper x11;
    init_opengl();
    //playLoopingSound();
    renderStartScreen(gl.xres, gl.yres, x11, gl);   // Display start screen
    waitForEnterKey(x11);;   // Wait for Enter Key
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);
    // Render knife and hp pack
    init_hpPack();
    initKnives();
    //Main loop
    int done = 0;
    while (!done) {
        //Process external events.
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.check_resize(&e);
            x11.check_mouse(&e);
	    //startScreenMusic();
            done = x11.check_keys(&e);
        }
        clock_gettime(CLOCK_REALTIME, &timeCurrent);
        timeSpan = timeDiff(&timeStart, &timeCurrent);
        timeCopy(&timeStart, &timeCurrent);
        physicsCountdown += timeSpan;
        x11.swapBuffers();
        //usleep(1000);

	if (startScreenActive) {
		cout <<"active" << endl;
	
	}

        if (!startScreenActive) {
            if (!gameOver){
             while (physicsCountdown >= physicsRate) {
            physics();
            physicsCountdown -= physicsRate;

        }
            render();
            }
            if (gameOver) {
                renderGameOver(gl.xres,gl.yres,x11,gl);
                usleep(1000000); 
                gameOver = false;
                burger.init();
                spike.init();
                enemy.init();
                healthbar.init();
                oil.init();
                initKnives();//knife initializer
                init_hpPack();
                shieldPowerUp.init();// Initialize shield power-up


            }

           

            
            
            
            x11.swapBuffers();
            usleep(400);
            }
        }
        
       


        
    
    return 0;
}

X11_wrapper::~X11_wrapper()
{
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}

X11_wrapper::X11_wrapper()
{
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    int w = gl.xres, h = gl.yres;
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        cout << "\n\tcannot connect to X server\n" << endl;
        exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(dpy);
    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
    if (vi == NULL) {
        cout << "\n\tno appropriate visual found\n" << endl;
        exit(EXIT_FAILURE);
    } 
    Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask =
        ExposureMask | KeyPressMask | KeyReleaseMask |
        ButtonPress | ButtonReleaseMask |
        PointerMotionMask |
        StructureNotifyMask | SubstructureNotifyMask;
    win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
            InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    set_title();
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
}

void X11_wrapper::set_title()
{
    //Set the window title bar.
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Burger-Dash");
}

bool X11_wrapper::getXPending()
{
    //See if there are pending events.
    return XPending(dpy);
}

XEvent X11_wrapper::getXNextEvent()
{
    //Get a pending event.
    XEvent e;
    XNextEvent(dpy, &e);
    return e;
}

void X11_wrapper::swapBuffers()
{
    glXSwapBuffers(dpy, win);
}

void X11_wrapper::reshape_window(int width, int height)
{
    //window has been resized.
    gl.xres = width;
    gl.yres = height;
    //
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
}

void X11_wrapper::check_resize(XEvent *e)
{
    //The ConfigureNotify is sent by the
    //server if the window is resized.
    if (e->type != ConfigureNotify)
        return;
    XConfigureEvent xce = e->xconfigure;
    if (xce.width != gl.xres || xce.height != gl.yres) {
        //Window size did change.
        reshape_window(xce.width, xce.height);
    }
}
//-----------------------------------------------------------------------------

void X11_wrapper::check_mouse(XEvent *e)
{
    static int savex = 0;
    static int savey = 0;

    //Weed out non-mouse events
    if (e->type != ButtonRelease &&
            e->type != ButtonPress &&
            e->type != MotionNotify) {
        //This is not a mouse event that we care about.
        return;
    }
    //
    if (e->type == ButtonRelease) {
        return;
    }
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button was pressed.
            //int y = g.yres - e->xbutton.y;
            return;
        }
        if (e->xbutton.button==3) {
            //Right button was pressed.
            return;
        }
    }
    if (e->type == MotionNotify) {
        //The mouse moved!
        if (savex != e->xbutton.x || savey != e->xbutton.y) {
            savex = e->xbutton.x;
            savey = e->xbutton.y;
            //Code placed here will execute whenever the mouse moves.
            time_since_mouse_move(true);

        }
    }
}

int X11_wrapper::check_keys(XEvent *e)
{
    if (e->type != KeyPress && e->type != KeyRelease)
        return 0;
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyPress) {
        gl.keys[key] = 1;
        time(&gl.key_checker);
    }

    if (e->type == KeyRelease)
        gl.keys[key] = 0;
    if (e->type == KeyPress) {
        switch (key) {
            case XK_r:
                //Key R was pressed
                burger.init();
                spike.init();
                enemy.init();
                healthbar.init();
                oil.init();
                initKnives();//knife intializer
                init_hpPack();
                break;
            case XK_Escape:
                //Escape key was pressed
                return 1;
            case XK_g:
                gl.show_border = !gl.show_border;
                break;
            case XK_c:
                gl.display_credits = !gl.display_credits;
                break;
            case XK_s:
                gl.display_statistics = !gl.display_statistics;
                break;
        }
    }
    return 0;
}



void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, gl.xres, gl.yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //Set 2D mode (no perspective)
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    //Set the screen background color
    glClearColor(0.1, 0.1, 0.1, 1.0);
    //Enable fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
}

bool checkCollision(Square burger, Obstacle spike) {
    


    // Calculate the coordinates of the bounding boxes
    int leftBurger = burger.pos[0] - burger.width;
    int rightBurger = burger.pos[0] + burger.width;
    int topBurger = burger.pos[1] - burger.height;
    int bottomBurger = burger.pos[1] + burger.height;

    int leftSpike = spike.pos[0] - spike.width;
    int rightSpike = spike.pos[0] + spike.width;
    int topSpike = spike.pos[1] - spike.height;
    int bottomSpike = spike.pos[1] + spike.height;

    // If one shape is on the left side of the other
    if (rightBurger < leftSpike || rightSpike < leftBurger)
        return false;

    // If one shape is above the other
    if (bottomBurger < topSpike || bottomSpike < topBurger)
        return false;

    return true;

}
bool checkCollision(Square burger, Square spike) {



    // Calculate the coordinates of the bounding boxes
    int leftBurger = burger.pos[0] - burger.width;
    int rightBurger = burger.pos[0] + burger.width;
    int topBurger = burger.pos[1] - burger.height;
    int bottomBurger = burger.pos[1] + burger.height;

    int leftSpike = spike.pos[0] - spike.width;
    int rightSpike = spike.pos[0] + spike.width;
    int topSpike = spike.pos[1] - spike.height;
    int bottomSpike = spike.pos[1] + spike.height;

    // If one shape is on the left side of the other
    if (rightBurger < leftSpike || rightSpike < leftBurger)
        return false;

    // If one shape is above the other
    if (bottomBurger < topSpike || bottomSpike < topBurger)
        return false;

    return true;

}

void physics()
{
    bool enemyCollisionOccurred = false;
    //int tries;

    // shield power-up physics
    shieldPowerUp.pos[0] += shieldPowerUp.vel[0];

    // spike physics
    spike.pos[0] += spike.vel[0];

    enemy.pos[0] += enemy.vel[0];
    oil.pos[0] += oil.vel[0];

    // Check collision with shield power-up
    if (Check4(burger, shieldPowerUp)) {
        shieldPowerUp.activate();
    }

     //hp pack physics
    hp_pack.pos[0] += hp_pack.vel[0];
    if (hp_pack.pos[0] + hp_pack.width < 0.0) {
        init_hpPack();
    }
    // knife physics
    knife1.pos[0] += knife1.vel[0];
    knife2.pos[0] += knife2.vel[0];
    knife3.pos[0] += knife3.vel[0];
    //knife collision
    if (!shieldPowerUp.isActivated()) {
        // Only apply damage if the shield is not active
        if (checkCollision(burger, knife1) || checkCollision(burger, knife2) || 
                checkCollision(burger, knife3)) {
            healthbar.health -= 20;
            hp_ST = 0;
            gl.score += 1;
        }
    }
    if (knife1.pos[0] + knife1.width < 0.0) {
        ST = 0;
        initKnives(); 
    }
    // burger physics
    // If burger is off the ground, it is subject to gravity
    if(burger.pos[1] > 0 + burger.height && !checkCollision(burger, spike)) {
        burger.vel[1] += GRAVITY;
        burger.pos[1] -= burger.vel[1];
    }

    // Update burger position based on its velocity
    burger.pos[0] += burger.vel[0]; 
    burger.pos[1] -= burger.vel[1];

    // When burger hits ground, set velocity to 0
    if (burger.pos[1] <= 0 + burger.height) {
        burger.pos[1] = 0 + burger.height;
        burger.vel[1] = 0;
        //burger.vel[0] = 10;
    }

    if (gl.keys[XK_space]) {
        if (burger.pos[1] == 0 + burger.height)
            burger.vel[1] -= 13.0f; 
    }

    // if they collide, send burger back a bit
    if(checkCollision(burger, spike)) {
        //spike.vel[0] = 10;
        
        //burger.vel[0] = -10;
        burger.vel[1] = 0;


        
       
    }

    /*if (enemy.pos[0] <= 400.0f){
        enemy.vel[0] = 8.0;

    }*/

    if (enemy.pos[0] + enemy.width < 0) {
        enemy.init();

    }

     if (spike.pos[0] + spike.width < 0) {
        spike.init();

    }
 


    if(Check2(burger,enemy)){
        burger.vel[0] = enemy.vel[0];
        

    }




    for(int i = 0; i<50; i++){
        //render the level while burger is in motion
        if(burger.vel[0] >= 0.0){
            camera[0] += 2.0/lev.tilesize[0] * (0.05 / gl.delay);
            if (camera[0] < 0.0) {
                camera[0] = 0.0;
            }
        }
    }

    

    //if we clear the obstacle we get a point
    if (burger.pos[0] - burger.width > spike.pos[0] + spike.width && !spike.pointClaimed) {
        spike.pointClaimed = true;
        gl.score += 1;
        //re-Render knives when the user has an even amount of points
        if(gl.score % 2 == 0)
            ST = 1;
    }




    if ((checkCollision(burger, spike)) || ((Check2(burger, enemy))) && !enemyCollisionOccurred ) {
        healthbar.health = healthbar.health - 20;  // Adjust the amount based on your game's design
        enemyCollisionOccurred  = 1;
        if (healthbar.health <= 0) {
            healthbar.health = 0;
            gameOver = true;
            
        }

      }


    if (Check3(burger,oil)) {
        burger.vel[1] = -20.0;
    }
}




void render()
{
    //startScreenMusic();
    render_calls();
    
    glClear(GL_COLOR_BUFFER_BIT);
    //Draw burger
    
    renderHealth();
    renderLevel(lev, gl, camera);
    renderBurger(burger, burgerSprite, gl);
    
    renderEnemy();    
    renderOil();

    // Render shield power-up
    if (!shieldPowerUp.isActivated()) {
        glColor3ub(50, 100, 200);
        glPushMatrix();
        glTranslatef(shieldPowerUp.pos[0], shieldPowerUp.pos[1], 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-shieldPowerUp.width, -shieldPowerUp.height);
        glVertex2f(-shieldPowerUp.width, shieldPowerUp.height);
        glVertex2f(shieldPowerUp.width, shieldPowerUp.height);
        glVertex2f(shieldPowerUp.width, -shieldPowerUp.height);
        glEnd();
        glPopMatrix();
    }

    //draw spike
    glPushMatrix();
    glColor3ub(250,0,0);
    glTranslatef(spike.pos[0], spike.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-spike.width, -spike.height);
    glVertex2f(-spike.width,  spike.height);
    glVertex2f( spike.width,  spike.height);
    glVertex2f( spike.width, -spike.height);
    glEnd();
    glPopMatrix();
    //Render knives
    render_knives(ST);
    
    //render hp pack in the air
    if(healthbar.health < 170) {
        render_hp_pack(hp_ST);
        hp_ST = 1;
    }
    
    unsigned int c = 0x00ffff44;
    Rect r;
    r.bot = gl.yres - 20;
    r.left = 10;
    r.center = 0;

    ggprint8b(&r, 16, c, "Press SPACE to jump");
    ggprint8b(&r, 16, c, "Press R to reset obstacle");
    ggprint8b(&r, 16, c, "Press G for border");
    ggprint8b(&r, 16, c, "Press C for credits");
    ggprint8b(&r, 16, c, "Press S for statistics");
    ggprint8b(&r, 16, c, "score: %i", gl.score);

    if (gameOver) {
        

    }


    if (gl.show_border) {
        display_border(gl.xres, gl.yres);
    }

    if (gl.display_credits) {
        display_credits(gl.xres, gl.yres);
    }

    if (gl.display_statistics) {
        Rect r1;
        r1.bot = 90;
        r1.left = 10;
        r1.center = 0;

        ggprint8b(&r1, 16, c, "STATISTICS");
        
        // uncomment once yours works :D
        ggprint8b(&r1, 16, c, "n physics calls: %i", total_physics_function_calls());
        ggprint8b(&r1, 16, c, "n render calls: %f", total_render_function_calls());
        ggprint8b(&r1, 16, c, "time since last key press: %i seconds", time_since_key_press(gl.key_checker));
        
        ggprint8b(&r1, 16, c, "time elapsed: %i seconds", total_running_time(gl.begin));
        ggprint8b(&r1, 16, c, "time since last mouse move: %i seconds", time_since_mouse_move(false));
        }


}
