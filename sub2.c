#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game1.h"

/*
**
**　jiraiCCount配列を設定する
**　jirai：ランダムに地雷（1）が配置された2次元配列
**　jiraiCount：その座標位置に隣接（8方向）する地雷の数　地雷自身の場合9を設定し区別できるようにする
**　
*/
int setjiraicount(int jirai[][20],int jiraiCount[][20]) {
    // jiraicount配列を設定する
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

/*
**　x,yで指定された座標が地雷ならば、周辺（８箇所）のjiraiCountのカウントを加算する
**　int x, int y
**　jirai：ランダムに地雷（1）が配置された2次元配列
**　jiraiCount：その座標位置に隣接（8方向）する地雷の数　地雷自身の場合9を設定し区別できるようにする
**
*/
void sellCountup(int x, int y, int jirai[][20], int jiraiCount[][20]) {
    //　指定された座標の周辺が地雷ならば1加算する
    for(int i = -1; i<2; i++) {
        for(int j = -1; j<2; j++) {
            if ( (x + i) < 0 | (x + i) > 19 | (y + j) < 0 | (y + j) > 19) {
                //　フィールドの外ならば何もしない
            } else {
                //　地雷ならばjiraiCountのカウントを1加算する
                if (jirai[y][x] == 1)  jiraiCount[y+j][x+i]++;
            }
        }
    }
}