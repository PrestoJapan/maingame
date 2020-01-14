int printrow(int rownumber, char *row);
int printHeader();
int checkxy(int x, int y); // 指定した座標が地雷なら1を戻す
int inputnumber();
char sitoa(int i);
int printjirai();
int printjiraicount();
int drawbattlefield(int visible[][20],char marks[][21],int jiraiCount[][20],int possible[][20]);
int printmap(int fieldsmap[][20]);
int setjiraicount(int jirai[][20],int jiraiCount[][20]);
int setjirai(int count, int jirairetu[], int jirai[][20]);
int expandZero(int x, int y, int jiraiCount[][20], int visible[][20]);
void sellCountup(int x, int y, int jirai[][20], int jiraiCount[][20]);
char sitoa(int i);

#define true 1
#define false 0