#ifndef _JESUS_H_
#define _JESUS_H_
/**
 * Author:    Jesus Baltazar Robles
 * Created:   9/29/2023
 * 
 **/
/*Header files that will define level design and objects implementation*/
typedef double Flt;
extern float render_val_count;
class Level {
    public:
    unsigned char arr[52][304];
    int nrows, ncols;
    int tilesize[2];
    Flt ftsz[2];
    Flt tile_base;
    Level();
    void removeCrLf(char *str);
};
void render_calls();
float total_render_function_calls();
#endif
