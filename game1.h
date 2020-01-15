/*
**　複数のｃプログラムで利用する関数定義
*/
int  checkxy(int x, int y); // 指定した座標が地雷なら1を戻す
int  drawbattlefield(int visible[][20],char marks[][21],int jiraiCount[][20],int possible[][20]);
int  expandZero(int x, int y, int jiraiCount[][20], int visible[][20]);
int  inputnumber();
int  printjirai();
int  printjiraicount();
int  printmap(int fieldsmap[][20]);
int  printrow(int rownumber, char *row);
int  printHeader();
int  setjiraicount(int jirai[][20],int jiraiCount[][20]);
int  setjirai(int count, int jirai[][20]);
void sellCountup(int x, int y, int jirai[][20], int jiraiCount[][20]);
char sitoa(int i);

// 真偽をわかりやすくするためにtrueとfalseを定義
#define true 1
#define false 0