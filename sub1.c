#include <stdio.h>
#include <stdlib.h>
#include "game1.h"

/*
**
**　フィールド（ゲーム面）を再描画する　フィールドは再描画度とに画面に追加で描画され　
**　ターミナル画面のスクロールで過去の履歴が表示される
**　visible：チェック済の座標
**　marks：座標に表示する文字　-, F, 1-8の数字, x, 空白　のいずれか
**　jiraiCount：その座標位置に隣接（8方向）する地雷の数
**　possible：プレイヤーが地雷であるとしてマークした座標
**　
*/
int drawbattlefield(int visible[][20],char marks[][21],int jiraiCount[][20],int possible[][20])
{
    // marksを書き直す
    for (int y=0;y<20;y++) {
        for (int x=0;x<20;x++) {
            //　チェック済の座標に適切な文字をセットする            
            if (visible[y][x] == true) {
                //　チェック済ならば、隣接地雷数を表示する
                //　ただし地雷数がゼロならば空白、地雷そのものならxにする
                marks[y][x] = sitoa(jiraiCount[y][x]);
                if (jiraiCount[y][x] == 0) marks[y][x] = ' ';
                else if (jiraiCount[y][x] == 9) marks[y][x] = 'x';
            } else {
                //　チェック済でない座標は-とする
                marks[y][x] = '-';
            }
            //　possibleな座標にFをセットする
            if (possible[y][x] == true) {
                marks[y][x] = 'F';
            }
        } 
    } 
    //　座標（1-20）のヘッダ（ｘ軸）を描画する
    printHeader();
    //　行を描画する
    for (int i=1;i<21;i++) {
        printrow(i, marks[i-1]);
    } 
};

/*
**　プレイヤーが選択した地雷数が0の場所を拡張する
**　0がつながる場所を拡張し、拡張された0に隣接する地雷以外の座標もvisible(チェック済)とする
*/
int expandZero(int x, int y, int jiraiCount[][20], int visible[][20])
{
    //　最初に0の座標を拡張する
    //　変更された数をカウントし、変更がなくなるまで繰り返す
    int changes = 0;
    while (1) {
        changes = 0;
        for (int y=0;y<20;y++) {
            for (int x=0;x<20;x++) {
                //　座標 (x, y) のvisibleがtrueの場合、その上下左右が0で、かつvisibleでない場所をvisibleにする
                if (visible[y][x] == true) {
                    if (y > 0 & jiraiCount[y - 1][x] == 0 & visible[y - 1][x] == false) {visible[y - 1][x] = true;changes++;}
                    if (y < 19 & jiraiCount[y + 1][x] == 0 & visible[y + 1][x] == false) {visible[y + 1][x] = true;changes++;}
                    if (x > 0 & jiraiCount[y][x - 1] == 0 & visible[y][x - 1] == false) {visible[y][x - 1] = true;changes++;}
                    if (x < 19 & jiraiCount[y][x + 1] == 0 & visible[y][x + 1] == false) {visible[y][x + 1] = true;changes++;}
                }
            }
        }
        //　changesが0になればループを終了する
        if ( changes == 0) break;
    }

    //　0でvisibleな場所の上下左右に位置して、かつ地雷でない場所もvisibleにする
    //　変更された数をカウントし、変更がなくなるまで繰り返す
    while (1) {
        changes = 0;
        for (int y=0;y<20;y++) {
            for (int x=0;x<20;x++) {
                // visibleがtrueで地雷数が0の座標の場合、その上下左右が地雷でなく、かつvisibleでない場所をvisibleにする
                if (visible[y][x] == true & jiraiCount[y][x] == 0) {
                    if (y > 0 & jiraiCount[y - 1][x] != 9 & visible[y - 1][x] == false) {visible[y - 1][x] = true;changes++;}
                    if (y < 19 & jiraiCount[y + 1][x] != 9 & visible[y + 1][x] == false) {visible[y + 1][x] = true;changes++;}
                    if (x > 0 & jiraiCount[y][x - 1] != 9 & visible[y][x - 1] == false) {visible[y][x - 1] = true;changes++;}
                    if (x < 19 & jiraiCount[y][x + 1] != 9 & visible[y][x + 1] == false) {visible[y][x + 1] = true;changes++;}
                }
            }
        }
        //　changesが0になればループを終了する
        if ( changes == 0) break;
    }
    return true;
}


// DEGUG用　intの２次元配列をプリントする
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

