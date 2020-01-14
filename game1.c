/* クオリティCプログラミング　中級編
**
**　課題：C言語でゲームを作る
**　
**　マインスイーパーの遊び方：
**　20ｘ20座標のバトルフィールドに地雷が埋めています。
**　地雷以外の場所を、次々と当てていき最後まで地雷を踏まなければ勝ちです。
**　地雷を踏んだ時点でゲームオーバーです。
**　最初に地雷の数を1-399の範囲で指定します。
**　次に座標ｘ、ｙと指示（ｃはチャレンジする、fは地雷と思われるのでフラグ（F）を立てる）を入力します。
**　場所に表示される記号は以下の通りです
**　1-8の数字；この場所に隣接する場所（8箇所）に表示された数だけの地雷があります。すでにチェック済となります。
**　F：地雷と思われる場所につけたフラグです
**　空白：チェック済の場所です。
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game1.h"

//  jirai[y][x] : 配列の1次元目はｙ（縦）方向　配列の2次元目はｘ（横）方向とする　
//　1：地雷が埋まっている場所 0：地雷がない場所で未チェック 2:　地雷がない場所でチェック済
//　地雷は、その個数を指定し、setjirai()で最初にランダムに配置する
int jirai[20][20]; // 地雷の場所は1　それ以外は0
int jirairetu[400]; // ランダムに地雷を配置するためのワークエリア
int visible[20][20]; // true: 内容を表示（チェック済） false : -を表示（未チェックを示す）
int possible[20][20]; // true: 多分地雷だろうとしてチェック false : ノーコメント
//  jiraiCount[y][x] : 配列の1次元目はｙ（縦）方向　配列の2次元目はｘ（横）方向とする
// 周りにある地雷数　自身が地雷の時は9とする
int jiraiCount[20][20];
// ゲームの状況　-:まだチェックしていない場所　o:チェック済の場所　
//　1-8：周りに地雷がある場所　x:地雷
//　\0 は文字列の終端を示す　これがないとprintf文が暴走する恐れがある
//　-の場所が地雷だけになれば、プレイヤーの勝利でゲーム終了
//　チェック場所が地雷の場合、プレイヤーの負けでゲーム終了
char marks[20][21];

//　場所を入力させ、チェックを行う
int inputnumber() {
    int x;
    int y;
    char flag;
    printf("check cell => input x y c :\n");
    printf("flag at cell => input x y f :\n");
    printf("input x y (c or f) :");
    scanf("%d %d %c", &x,&y,&flag);
    // 地雷なら終了なのでfalseを返す
    x--;
    y--;
    if (flag == 'f') {
        // すでにフラグが立っていれば、クリアする
        if (possible[y][x] == true) {
            possible[y][x] = false;
            visible[y][x] = false;  
            return true;          
        }
        if (visible[y][x] == false) {
            possible[y][x] = true;
            visible[y][x] = true;
            return true;
        }
    } 

    visible[y][x] = true;
    if (jiraiCount[y][x] == 9) return false;

    // 選択場所に連続して隣接する地雷以外の場所をチェック済にする
    //　地雷の状態を示すjirai[][]を修正する
    if (jiraiCount[y][x] != 0 & jiraiCount[y][x] != 9) {
        // 隣接する地雷があるならば、周辺をチェックしないで戻る
        return true;
    }
    //　周辺をチェックし拡大する
    expandZero( x,  y,  jiraiCount,  visible);

    return true;
}

// main
int main() {
    // フィールドに地雷を埋める
    int count = 10;
    printf("input bomb count:");
    scanf("%d", &count);
    if (count > 400 | count < 1) count = 200;
    setjirai(count, jirairetu, jirai);
    // marks[20][21]の初期化 
    for (int i=0;i<20;i++) {
        for (int j=0;j<20;j++) {
            marks[i][j] = '-'; 
        } 
        marks[i][20] = '\0';
    } 

    //　場所ごとに周りの地雷数を調べjiraiCount[][]に設定する
    setjiraicount(jirai,jiraiCount);
    // 初期バトルフィールドの描画
    drawbattlefield(visible,marks,jiraiCount,possible);

    //　チェックする場所を指定する
    int result = true;
    while(1) {
        //　チェックする場所をx　ｙで入力させる
        //　結果が1（地雷）ならば終了
        result = inputnumber();
        if (result == false) break;

        drawbattlefield(visible,marks,jiraiCount,possible);
        
        // 地雷以外の場所でまだ'-'の場所が存在するか調べる
        int rest =0;
        for(int y=0;y<20;y++) {
            for(int x=0;x<20;x++) {
                if (jirai[y][x] != 1 & marks[y][x] == '-') {
                    rest++;
                }
            }
        }        
        if (rest == 0) {
            // すべてクリアしているので終了する
            result = true;
            break;
        } 
    }
    // 地雷の表示
    for (int y=0;y<20;y++) {
        for (int x=0;x<20;x++) {
            if (jiraiCount[y][x] == 9) visible[y][x] = true;
        }
    }
    drawbattlefield(visible,marks,jiraiCount,possible);
    //　結果表示
    if (result == false) printf("\n\n\n You lose!\n\n");
    else printf("\n\n\n Congratulations !!!\n\n");
}

