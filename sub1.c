#include <stdio.h>
#include <stdlib.h>
#include "game1.h"

int drawbattlefield(int visible[][20],char marks[][21],int jiraiCount[][20],int possible[][20])
{
    // marksを書き直す
    for (int y=0;y<20;y++) {
        for (int x=0;x<20;x++) {
            
            if (visible[y][x] == true) {
                marks[y][x] = sitoa(jiraiCount[y][x]);
                if (jiraiCount[y][x] == 0) marks[y][x] = ' ';
                else if (jiraiCount[y][x] == 9) marks[y][x] = 'x';
            } else {
                marks[y][x] = '-';
            }
            //　possible
            if (possible[y][x] == true) {
                marks[y][x] = 'F';
            }
        } 
    } 

    printHeader();
    for (int i=1;i<21;i++) {
        printrow(i, marks[i-1]);
    } 
};

// 選択されvisibleになった場所に隣接する0の場所をvisibleとする
int expandZero(int x, int y, int jiraiCount[][20], int visible[][20])
{
    // 0がつながる場所を拡張する
    int changes = 0;
    while (1) {
        changes = 0;
        for (int y=0;y<20;y++) {
            for (int x=0;x<20;x++) {
                // visibleがtrueの場合、その上下左右が0ならば、その場所もvisibleにする
                if (visible[y][x] == true) {
                    if (y > 0 & jiraiCount[y - 1][x] == 0 & visible[y - 1][x] == false) {visible[y - 1][x] = true;changes++;}
                    if (y < 19 & jiraiCount[y + 1][x] == 0 & visible[y + 1][x] == false) {visible[y + 1][x] = true;changes++;}
                    if (x > 0 & jiraiCount[y][x - 1] == 0 & visible[y][x - 1] == false) {visible[y][x - 1] = true;changes++;}
                    if (x < 19 & jiraiCount[y][x + 1] == 0 & visible[y][x + 1] == false) {visible[y][x + 1] = true;changes++;}
                }
            }
        }
        if ( changes == 0) break;
    }

    // 0でvisibleな場所の上下左右に位置して、かつ地雷でない場所もvisibleにする
    while (1) {
        changes = 0;
        for (int y=0;y<20;y++) {
            for (int x=0;x<20;x++) {
                // visibleがtrueの場合、その上下左右が0ならば、その場所もvisibleにする
                if (visible[y][x] == true & jiraiCount[y][x] == 0) {
                    if (y > 0 & jiraiCount[y - 1][x] != 9 & visible[y - 1][x] == false) {visible[y - 1][x] = true;changes++;}
                    if (y < 19 & jiraiCount[y + 1][x] != 9 & visible[y + 1][x] == false) {visible[y + 1][x] = true;changes++;}
                    if (x > 0 & jiraiCount[y][x - 1] != 9 & visible[y][x - 1] == false) {visible[y][x - 1] = true;changes++;}
                    if (x < 19 & jiraiCount[y][x + 1] != 9 & visible[y][x + 1] == false) {visible[y][x + 1] = true;changes++;}
                }
            }
        }
        if ( changes == 0) break;
    }

    return true;
}


// DEGUG用
int printmap(int fieldsmap[][20]){
    return 0;
    for(int y=0;y<20;y++) {
        for(int x=0;x<20;x++) {
            printf("%d,", fieldsmap[y][x]);            
        }
        printf("\n");
    }
}
// DEGUG

