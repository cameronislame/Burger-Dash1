#ifndef _Cameron_M_
#define _Cameron_M_
#include <time.h>
#include <math.h>
#include "jbaltazarrob.h"
//Cameron's project files

extern class Global {
    public:
        int xres, yres;
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
} gl; 


//extern void display_name(int, int);
//extern void display_border(int xres, int yres);
extern void display_credits(int xres, int yres);
extern int total_running_time(time_t begin);
extern int time_since_mouse_move(const bool get);
extern void renderLevel(Level lev, Global gl, double* camera);

class cameron{
	int abc;
};

#endif
