#include "jbaltazarrob.h"
#include <iostream>
#include <cstddef>
#include <cstring>
#include <cstdio>
/**
* Auhtor: Jesus Baltazar Robles
* Date: 9/29/2023
*/
/*LEVEL CLASS INITIALIZATION
 * CODE COMES FROM GORDON WALK2*/
float render_val_count = 0;
Level::Level() {
        //Log("Level constructor\n");
        tilesize[0] = 16;
        tilesize[1] = 16;
        ftsz[0] = (Flt)tilesize[0];
        ftsz[1] = (Flt)tilesize[1];
        tile_base = 220.0;
        //read level
        FILE *fpi = fopen("lvl.txt","r");
        if (fpi) {
        nrows=0;
        char line[100];
        while (fgets(line, 100, fpi) != NULL) {
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
        for (int i=0; i<nrows; i++) {
        for (int j=0; j<ncols; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
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
