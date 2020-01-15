#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game1.h"


/*
**　フィールドの行を描画する
**　最初の3カラムは行番号　次の20カラムはフィールドの状態（marks）
**
*/
int printrow(int rownumber, char *row) {
    printf("%2d %s\n", rownumber, row);
}

/*
**　フィールドのヘッダー行を描画する
**
*/
int printHeader(){
    printf("   00000000011111111112\n");
    printf("   12345678901234567890\n");
}

/*
**　0-9のintを文字に変換する
**　marksにセットする記号用で、汎用的にintを変換するものではない
*/
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

/*
**　jirai[20][20]に指定された数(count)の地雷を埋める
*/
int setjirai(int count, int jirai[][20]){
    // 0から19までの乱数を発生
    int cc = 0;
    int jirairetu[400]; // ランダムに地雷を配置するためのワークエリア
    //　同じ地雷数でも、地雷の位置が毎回変わるようにsrandに、今の時刻を渡す
    srand(time(NULL));
    //　0-399のランダムな数値を発生させる
    while(1) {
        int pos = rand() % 400;
        //　すでに発生済の数値はカウントしない
        if (jirairetu[pos] != 1) {
            jirairetu[pos] = 1;
            cc++;
        }
        if (cc == count) break;
    }
    //　1次元配列を２次元配列：jiraiにする
    for (int i=0;i<400;i++) {
        int x = i % 20;
        int y = i / 20;
        if (jirairetu[i] == 1) jirai[y][x] = 1;
    }
}