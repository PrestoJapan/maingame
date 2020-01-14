#include <stdio.h>
#include <stdlib.h>
#include "game1.h"

int printrow(int rownumber, char *row) {
    printf("%2d %s\n", rownumber, row);
}

int printHeader(){
    printf("   00000000011111111112\n");
    printf("   12345678901234567890\n");
}

char sitoa(int i) {
    switch (i)
    {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        default: break;
    }
    return 'x';
}

void sellCountup(int x, int y, int jirai[][20], int jiraiCount[][20]) {
    //printf("sellCountup %d %d\n",x,y);
    for(int i = -1;i<2;i++) {
        for(int j = -1;j<2;j++) {
            if ( (x + i) < 0 | (x + i) > 19 | (y + j) < 0 | (y + j) > 19) {

            } else {
                if (jirai[y][x] == 1)  jiraiCount[y+j][x+i]++;
            }
        }
    }
}

