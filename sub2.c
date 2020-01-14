#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game1.h"

//　周辺場所の地雷数をカウントする
int setjiraicount(int jirai[][20],int jiraiCount[][20]) {
    // jiraicount配列を計算する
    for (int i =0;i<20;i++) { // y:縦軸
        for (int j =0;j<20;j++) { // x:横軸
            //　場所が地雷の時
            if (jirai[i][j] == 1) {
                // 周辺の８ブロックのカウントを加算する
                sellCountup(j, i, jirai, jiraiCount);
            }
        } 
    } 
    // 地雷の場所を9にする
    for (int i =0;i<20;i++) { 
        for (int j =0;j<20;j++) { 
        if (jirai[i][j] == 1) jiraiCount[i][j] = 9;
        }
    }
}

// jirai[20][20]に指定された数(count)の地雷を埋める
int setjirai(int count, int jirairetu[], int jirai[][20]){
    // jirai[20][20]に指定された数(count)の地雷を埋める
    // 0から19までの乱数を発生
    int cc = 0;
    srand(time(NULL));
    while(1) {
        int pos = rand() % 400;
        if (jirairetu[pos] != 1) {
            jirairetu[pos] = 1;
            cc++;
        }
        if (cc == count) break;
    }
    for (int i=0;i<400;i++) {
        int x = i % 20;
        int y = i / 20;
        if (jirairetu[i] == 1) jirai[y][x] = 1;
    }
}