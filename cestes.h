// Conner Estes header file


// cestes.h
#ifndef CESTES_H
#define CESTES_H





#endif


#ifndef _CESTES_H_
#define _CESTES_H_

class Stove {
    public:
        float pos[2];
        float vel[2];
        float width;
        float height;
        Stove(){
            init();
        }
        void init(){
            width = 30.0f;
            height = 3.0f;
        }
};




class Enemy {
public:
    float pos[2];
    float vel[2];
    float width;
    float height;
    Enemy() {
        init();
    }
    void init() {
        width = 30.0f;
        height = 30.0f;
        pos[0] = 600.0f;
        pos[1] = 0.0f + height;
        vel[0] = -12.0f;
    }
};

extern Enemy enemy;

// ... other declarations ...

#endif // _CESTES_H_









class Square {
    public:
        float pos[2];
        float vel[2];
        float verts[4][2];
        float width;
        float height;
        Square() {
            init();

        }
        void init() {
            vel[0] = 5.0f;
            vel[1] = 0;
            width =  15.0f;
            height = 15.0f;
            pos[0] = 50.f;
            pos[1] = 0.0f + height;
        }
};

extern Square burger;


int total_physics_function_calls();
void renderEnemy();

// cestes.h



//extern void display_border(int xres, int yres);
extern void display_name(int, int);
bool Check2(Square burger, Enemy enemy);
