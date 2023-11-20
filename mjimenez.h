#ifndef _MJIMENEZ_H_
#define _MJIMENEZ_H_
/**
 * Author: Mario Jimenez
 * Created: 09/27/2023
 * File: mjimenez.h
 * Description: Mario Jimenez Header File 
 **/
#include <time.h>
#include "X11_wrapper.h"
class Global;
// called from main program
//extern void display_name(int, int);
extern void renderStartScreen(int xres, int yres, X11_wrapper& x11, Global& gl);
extern int time_since_key_press(time_t key_checker);
extern void display_border(int xres, int yres);

#endif
