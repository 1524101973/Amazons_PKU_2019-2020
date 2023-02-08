#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>
#include <windows.h>
#include <queue>

using namespace std;

#define GRIDSIZE 8
#define OBSTACLE 2
#define grid_black 1
#define grid_white -1

int map[GRIDSIZE][GRIDSIZE] = {0}; // 先x后y，记录棋盘状态
int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,-1,1,-1,0,1};
double alpha;
const char SAVE_FILE[30] = "save_board.txt";
const char SAVE_FILE_tmp[50] = "save_board_tmp.txt";
bool isRunning;
int pos_black[10], pos_white[10];//黑白棋的位置
char ch;
char strcin[1001];
int tmp1 = 1, player;
int tmp_r[9][9] = {{0}};
int round_amazon = 1;

// 判断是否在地图内
inline bool inMap (int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}

void rule()
{
	cout << "           在10*10的棋盘上,每方有四个棋子(四个Amazons);\n" <<
			"每个棋子都相当于国际象棋中的皇后,它们的行棋方法与皇后相同,但不能穿过阻碍;\n" << 
			"        当轮到一方行棋时,此方只能而且必须移动四个Amazons中的一个\n" <<
			"             并在移动完成后,由当前移动的棋子释放一个障碍\n" <<
			"           障碍的释放方法与棋子的移动方法相同(不能穿过障碍)\n" <<
			"                     同样障碍的放置也是必须的\n" <<
			"      当某方完成某次移动后,对方四个棋子均不能再移动时,对方将输掉比赛\n " <<
			"                 每次开局位于棋盘下方的玩家先手\n " <<
			"             整个比赛中双方均不能吃掉对方或己方的棋子或障碍\n";
	cout << "\n";
	cout << "   在游戏中你需要输入\n" << 
			"	        x0 y0，即所要动的棋子的坐标\n" <<
			"	        x1 y1，即将棋子移动到的目的地的坐标\n" <<
			"	        x2 y2, 即障碍物放置的位置坐标\n";
	Sleep(3 * 1000);
}

void victory1()
{
	system("cls");
	cout << "		 ⊂_ヽ\n";
    cout << "		 　 ＼＼   Λ＿Λ\n";
    cout << "		 　　 ＼  (‘ㅅ’) \n";
    cout << "		 　　　 >　⌒ヽ\n";
    cout << "		 　　　 / 　 へ＼\n";
    cout << "		 　　  /　　/　ヽ_つ\n";
    cout << "		 　　  ﾚ　ノ　　 \n";
    cout << "		 　　 /　/\n";
    cout << "		 　  /　/|\n";
    cout << "		 　 (　(ヽ\n";
    cout << "		 　 |　|、＼\n";
    cout << "		 　 | 丿  ＼ ⌒)\n";
    cout << "		 　 | |　　 ) /\n";
    cout << "		 `ノ )　　 Lﾉ\n";
	Sleep(0.05 * 1000);
	return;
}

void victory2()
{
	system("cls");
	cout << "		 ⊂_ヽ\n";
    cout << "		　 ＼＼  Λ＿Λ\n";
    cout << "		　　 ＼ (‘ㅅ’) \n";
    cout << "		　　　  >　⌒ヽ\n";
    cout << "		　　　 / 　 へ＼\n";
    cout << "		　　  /　　/　＼＼\n";
    cout << "		　　  ﾚ　ノ　　 ヽ_つ\n";
    cout << "		　　 /　/\n";
    cout << "		　  /　/|\n";
    cout << "		　 (　(ヽ\n";
    cout << "		　 |　|、＼\n";
    cout << "		　 | 丿 ＼ ⌒)\n";
    cout << "		　 | |　　) /\n";
    cout << "		 `ノ )　　Lﾉ\n";
	Sleep(0.05 * 1000);
	return;
}

void victory3()
{
	system("cls");
	cout << "\n";
	cout << "		⊂_ヽ  Λ＿Λ\n";
    cout << "		 　＼ (‘ㅅ’) \n";
    cout << "		 　　  >　⌒ヽ\n";
    cout << "		 　 　/ 　 へ＼\n";
    cout << "		 　  /　　/　＼＼\n";
    cout << "		 　　ﾚ　ノ　　 ヽ_つ\n";
    cout << "		 　/　/\n";
    cout << "		  /　/|\n";
    cout << "		 (　(ヽ\n";
    cout << "		 |　|、＼\n";
    cout << "		 | 丿 ＼ ⌒)\n";
    cout << "		 | |　　) /\n";
    cout << "		 `ノ )　　Lﾉ\n";
	Sleep(0.05 * 1000);
	return;
}

void defeat()
{
	cout << "¸ ― ― ―｜ ― ￣￣;;　;;￣￣;;｀、 　＼\n";
	cout << "　　　　｜　　　/　　　　;;　;; 　　;;　＼　　　　　　 　＼\n";
	cout << "　　　　｜　　/　　　　　;; 　 ;;　 　;;　　＼ 　　 　　　＼\n";
	cout << "　　　　 ｜　/　　　　　　;　　;; 　 　;;　　 ＼　　　　 　　\n";
	cout << "　　　　｀ /　　　　　　　　　 ;　　　;;　　｀　　　 　　＼\n";
	cout << "　　　　　 / 　　　¸　　　　　　　　　　　__–｀　　 　　ㅣ\n";
	cout << "　　　　　/=====;;＇¸　＼;;=====;.˛　　　＼　　　　　 　 　 ㅣ\n";
	cout << "　　　　 /________/　　;;____　　　’:　　　 　＼　　 　 　ㅣ\n";
	cout << "　　　　｜ 　 　 /　　　’_ 　 ￣￣￣=–　　　　｜　　　 　 ｜\n";
	cout << "　　　　 /￣　　/　　　 　　　　＇￣　　 　 　｜　　　　　｜\n";
	cout << "　　　　/ 　　／ 。 　 ´·， 　　　　　　　　 　｜　　　　　｜\n";
	cout << "　　　 ｜ 　　(·.¸　˛.-·-.¸_)　　　　　 　 　　 　｜　　　 　｜\n";
	cout << "　　　｜ 　 　，￣ 　　　｜　　　　 　　 　｜　¸.·´˚｀·¸　 ｜\n";
	cout << "　　　｜　　／ _　　　　 ｜　　　　 　　 ｜ 　／¸—-. ｜ ｜\n";
	cout << "　　　｜　 ／˛＿＿＿＿__¸　　　　 　　　└―＿／ ｜　ㅣ｜ ｜\n";
	cout << "　 　 ｜　 /　/￣￣￣￣￣/ 　　　　　　　　 　 　｜ 　 │ / 　\n";
	cout << "　 　 ｜　　˛/―――――/　　　　　　　　　　 　 　　／/ ｜\n";
	cout << "　 　 ｜　 　￣￣￣￣￣ 　　　　　　　　 　　　　￣　/　　｜\n";
	cout << "　 　｜　　　　　　　　　　　　　 　　 　　＿＿＿.·˙　 　｜\n";
	cout << "　 　｜ 　 ￣￣￣￣　　　　　　 　　 　/　　｜　　 　｜\n";
	cout << "　 　｜　　　　　　　　　　　　　　　　　　｜　　 　｜\n";
	cout << "　 　｜　　　　　　　　　˛.·　\n";
	cout << "　 　 ｜＿＿＿ 　　　　˛.·＇\n";
	cout << "　 　 　＼￣ 　￣￣￣￣\n";
	Sleep(1 * 1000);
	system("cls");
}

void fange()
{
	cout << "░░░░░░░░░▄░░░░░░░░░░░░░░▄\n";
	cout << "░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌\n";
	cout << "░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐ \n";
	cout << "░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐\n";
	cout << "░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐\n";
	cout << "░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌\n";
	cout << "░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒\n";
	cout << "░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒\n";
	cout << "░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▌\n";
	cout << "░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▌ \n";
	cout << "▐▒░▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▐ \n";
	cout << "▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▌\n"; 
	cout << "▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▐ \n";
	cout << "░▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▌ \n";
	cout << "░▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒\n";
	return;
}

bool ProcStep (int x0, int y0, int x1, int y1, int x2, int y2, int player, bool check_only)
{
    if (!inMap (x0, y0) || !inMap (x1, y1) || !inMap (x2, y2))
        return false;
    if (map[x0][y0] != player || map[x1][y1] != 0)
        return false;
    if (map[x2][y2] != 0 && !(x2 == x0 && y2 == y0))
        return false;
    if (!check_only)
    {
        map[x0][y0] = 0;
        map[x1][y1] = player;
        map[x2][y2] = OBSTACLE;
    }
    return true;
}
struct node
{
	int x, y;
	int step;
};

double K = 0.2;
int Qwhite[GRIDSIZE][GRIDSIZE] = {{0}};
int Qblack[GRIDSIZE][GRIDSIZE] = {{0}};
int Kwhite[GRIDSIZE][GRIDSIZE] = {{0}};
int Kblack[GRIDSIZE][GRIDSIZE] = {{0}};
int takeKW[GRIDSIZE][GRIDSIZE] = {{0}};
int takeKB[GRIDSIZE][GRIDSIZE] = {{0}};
int takeQW[GRIDSIZE][GRIDSIZE] = {{0}};
int takeQB[GRIDSIZE][GRIDSIZE] = {{0}};
int mobility[GRIDSIZE][GRIDSIZE] = {{0}};
void MOBILITY ()
{
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				int tempx = i + dx[k];
				int tempy = j + dy[k];
				if (inMap (tempx, tempy) && map[tempx][tempy] == 0)
					mobility[i][j]++;
			}
		}
}
void Queenmove_W (node pre)
{
	node st, next;
	queue <node> W;
	W.push (pre);
	while (!W.empty ())
	{
		st = W.front();
		W.pop();
		for (int k = 0; k < 8; k++)
		{
			next.x = st.x;
			next.y = st.y;
			next.step = st.step + 1;
			while (1)
			{
				next.x += dx[k];
				next.y += dy[k];
				if (takeQW[next.x][next.y] == 1)
					continue;
				if (map[next.x][next.y] == 0 && takeQW[next.x][next.y] == 0 && inMap (next.x, next.y))
				{
					Qwhite[next.x][next.y] = min (Qwhite[next.x][next.y], next.step);
					takeQW[next.x][next.y] = 1;
					W.push (next);
				}
				else
					break;
			}
		}
	}
}
void Queenmove_B (node pre)
{
	node st, next;
	queue <node> B;
	B.push (pre);
	while (!B.empty ())
	{
		st = B.front();
		B.pop();
		for (int k = 0; k < 8; k++)
		{
			next.x = st.x;
			next.y = st.y;
			next.step = st.step + 1;
			while (1)
			{
				next.x += dx[k];
				next.y += dy[k];
				if (takeQB[next.x][next.y] == 1)
					continue;
				if (map[next.x][next.y] == 0 && takeQB[next.x][next.y] == 0 && inMap (next.x, next.y))
				{
					Qblack[next.x][next.y] = min (Qblack[next.x][next.y], next.step);
					takeQB[next.x][next.y] = 1;
					B.push (next);
				}
				else
					break;
			}
		}
	}
}
void Kingmove_W (node pre)
{
	node st, next;
	queue <node> W;
	W.push (pre);
	while (!W.empty())
	{
		st = W.front();
		W.pop();
		for (int k = 0; k < 8; k++)
		{
			next.x = st.x + dx[k];
			next.y = st.y + dy[k];
			next.step = st.step + 1;
			if (map[next.x][next.y] == 0 && takeKW[next.x][next.y] == 0 && inMap (next.x, next.y))
			{
				Kwhite[next.x][next.y] = min (Kwhite[next.step][next.y], next.step);
				takeKW[next.x][next.y] = 1;
				W.push (next);
			}
		}
	}
}
void Kingmove_B (node pre)
{
	node st, next;
	queue <node> B;
	B.push (pre);
	while (!B.empty())
	{
		st = B.front();
		B.pop();
		for (int k = 0; k < 8; k++)
		{
			next.x = st.x + dx[k];
			next.y = st.y + dy[k];
			next.step = st.step + 1;
			if (map[next.x][next.y] == 0 && takeKB[next.x][next.y] == 0 && inMap (next.x, next.y))
			{
				Kblack[next.x][next.y] = min (Kblack[next.step][next.y], next.step);
				takeKB[next.x][next.y] = 1;
				B.push (next);
			}
		}
	}
}
double evaluate ()
{
	node w;
	int turn = round_amazon * 2 + 1;
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
		{
			if (map[i][j] == grid_white)
			{
				w.x = i;
				w.y = j;
				w.step = 0;
				memset (takeQW, 0, sizeof (takeQW));
				memset (takeKW, 0, sizeof (takeKW));
				takeQW[i][j] = 1;
				takeKW[i][j] = 1;
				Queenmove_W (w);
				Kingmove_W (w);
			}
			if (map[i][j] == grid_black)
			{
				w.x = i;
				w.y = j;
				w.step = 0;
				memset (takeQB, 0, sizeof (takeQB));
				memset (takeKB, 0, sizeof (takeKB));
				takeQB[i][j] = 1;
				takeQB[i][j] = 1;
				Queenmove_B (w);
				Kingmove_B (w);
			}
		}
	double t1 = 0, t2 = 0, p1 = 0, p2 = 0, m = 0;
	if (turn < 49)
	{
		memset (mobility, 0, sizeof (mobility));
		MOBILITY ();
		for (int i = 0; i < GRIDSIZE; i++)
			for (int j = 0; j < GRIDSIZE; j++)
			{
				if (map[i][j] == player)
				{
					int x = i, y = j;
					for (int k = 0; k < 8; k++)
					{
						for (int d = 1; d < GRIDSIZE; d++)
						{
							int tempx = x + dx[k] * d;
							int tempy = y + dy[k] * d;
							if (!inMap (tempx, tempy) || map[tempx][tempy] != 0)
								break;
							m += mobility[tempx][tempy] / d;
						}
					}
				}
				if (map[i][j] == -player)
				{
					int x = i, y = j;
					for (int k = 0; k < 8; k++)
					{
						for (int d = 1; d < GRIDSIZE; d++)
						{
							int tempx = x + dx[k] * d;
							int tempy = y + dy[k] * d;
							if (!inMap (tempx, tempy) || map[tempx][tempy] != 0)
								break;
							m -= mobility[tempx][tempy] / d;
						}
					}
				}
			}
	}
	// 计算position
	double tempQB, tempQW;
	// p1基于queen，p2基于king
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
		{
			if (map[i][j] == 0)
			{
				// 先搞p1
				tempQB = 1, tempQW = 1;
				if (Qblack[i][j] == 1000)
					tempQB = 0;
				else
				{
					for (int k = 0; k < Qblack[i][j]; k++)
						tempQB *= 0.5;
				}
				if (Qwhite[i][j] == 1000)
					tempQW = 0;
				else
				{
					for (int k = 0; k < Qwhite[i][j]; k++)
						tempQW *= 0.5;
				}
				p1 += (tempQB - tempQW) * player;
				// 再搞p2
				if (Kblack[i][j] == 1000 && Kwhite[i][j] == 1000)
					p2 += 0;
				else if (Kblack[i][j] == 1000)
				{
					if (player == grid_black)
						p2 -= 1;
					else
						p2 += 1;
				}
				else if (Kwhite[i][j] == 1000)
				{
					if (player == grid_white)
						p2 -= 1;
					else
						p2 += 1;
				}
				else
				{
					if (player == grid_black)
						p2 += min (1, max (-1, (Kwhite[i][j] - Kblack[i][j]) / 6));
					else
						p2 += min (1, max (-1, (Kblack[i][j] - Kwhite[i][j]) / 6));
				}
				// 搞t1
				if (Qblack[i][j] == Qwhite[i][j] && Qblack[i][j] == 1000)
					t1 += 0;
				else if (Qblack[i][j] == Qwhite[i][j] && Qblack[i][j] < 1000)
					t1 += K;
				else if (Qblack[i][j] < Qwhite[i][j])
					t1 += player;
				else 
					t1 -= player;
				// 搞t2
				if (Kblack[i][j] == Kwhite[i][j] && Kblack[i][j] == 1000)
					t2 += 0;
				else if (Kblack[i][j] == Kwhite[i][j] && Kblack[i][j] < 1000)
					t2 += K;
				else if (Kblack[i][j] < Kwhite[i][j])
					t2 += player;
				else
					t2 -= player;
			}
		}
	p1 *= 2;
	double value;
	if (turn <= 14)
		value = 0.2 * t1 + 0.48 * t2 + 0.11 * p1 + 0.11 * p2 + 0.2 * m;
	else if (turn <= 48)
		value = 0.4 * t1 + 0.25 * t2 + 0.2 * p1 + 0.2 * p2 + 0.06 * m;
	else
		value = 0.8 * t1 + 0.1 * t2 + 0.05 * p1 + 0.05 * p2;
	return value;
}

inline void Board(bool isNewGame)
{
	int turnID = 0;
	if (isNewGame)
	{
		for (int i = 0; i < GRIDSIZE; i++)
		{
			for (int j = 0; j < GRIDSIZE; j++)
				map[i][j] = 0;
		}
		// 定义黑白棋子位置
		map[0][2] = map[2][0] = map[5][0] = map[7][2] = 1;
		map[0][5] = map[2][7] = map[5][7] = map[7][5] = -1;
		// 把棋子的位置存入pos中
	}
	else
	{
		// 把文件中的信息存回来
		ifstream fin(SAVE_FILE);
		if (!fin)
		{
			cout << "算了，你还是玩新的一局吧";
			Sleep(1 * 1000);
			isRunning = false;
			return;
		}
		int x;				
		fin >> x; 
		round_amazon = x;
		for (int i = 0; i < GRIDSIZE; i++)
 		{
			for (int j = 0; j < GRIDSIZE; j++)
			{
				fin >> x;
				map[i][j] = x;
			}
		}
		fin.close();
	}
}

inline void DrawLine(int len)
{
	cout << "  +";
	for (int i = 0; i < len; i++)
		cout << "---+";
	cout << "\n";
}

inline void DrawBoard()
{
	system("cls");//清屏

	cout << "            --Round " << round_amazon << "--" << endl;
	
	cout << "    "; for (int x = 0; x < GRIDSIZE; x++) cout << x << "   "; cout << "\n";
	
	DrawLine(GRIDSIZE);

	for (int y = 0; y < GRIDSIZE; y++)
	{
		cout << y << " |";
		for (int x = 0; x < GRIDSIZE; x++)
		{
			char ch;
			switch (map[x][y])
			{
			case 1:
				ch = 'B'; break;
			case -1:
				ch = 'W'; break;
			case 2:
				ch = 'O'; break;
			default:
				ch = ' '; break;
			}
			cout << ' ' << ch << " |";
		}
		cout << "\n";
		DrawLine(GRIDSIZE);
	}
	cout << "____________________________________\n";
}

void SaveBoard()
{
	// 向SAVE_FILE存入数据
	ofstream fout(SAVE_FILE);
	fout << round_amazon << '\n';
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			fout << map[i][j] << ' ';
		}
		fout << '\n';
	}
	fout.close();
}

inline void SaveBoard_tmp()
{
	// 向SAVE_FILE存入数据
	ofstream fout(SAVE_FILE_tmp);
	fout << round_amazon << ' ';
	fout << '\n';
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			fout << map[i][j] << ' ';
		}
		fout << '\n';
	}
	fout.close();
}

int movex0, movey0, movex1, movey1, movex2, movey2; // 最后的解
			
inline void ShowMenu()//下棋界面的菜单
{
	cout << "1. 选择移动\n";
	cout << "2. 悔棋\n";
	cout << "3. 新游戏\n";
	cout << "4. 退出游戏\n";
	cout << "请输入[1/2/3/4]: ";
	while (1)
	{
		cin.getline (strcin, 1000);
		if (strcin[0] != '1' && strcin[0] != '2' && strcin[0] != '3' && strcin[0] != '4')
		{
			cout << "别调皮! 选择[1/2/3/4]中的数字 :";
			continue;
		}
        if (strlen (strcin) != 1)
        {
            cout << "你干啥打这么多字？输入一个就够了" << endl;
            continue;
        }
		break;
	}
	switch (strcin[0])
	{
		case '1':	// 选择移动
		{	
			SaveBoard_tmp();
			int tmp2 = 1;
			int flag1, flag2;
			while(tmp1)
			{
				cout << "选择黑棋(1) or 白棋(-1) [1/-1]: " << endl;
                cin.getline (strcin, 1000);
                while (1)
                {
                    if (strlen (strcin) != 1 && strlen (strcin) != 2)
                    {
                        cout << "再给你一次重来的机会" << endl;
                        cin.getline (strcin, 1000);
                        continue;
                    }
					if (strlen (strcin) == 1)
					{
						if (strcin[0] != '1')
						{
							cout << "再给你一次重来的机会" << endl;
							cin.getline (strcin, 1000);
							continue;
						}
						else
						{
							player = 1;
							tmp1 = 0;
							break;
						}
					}
					else
					{
						
						if (strcin[0] != '-' || strcin[1] != '1')
						{
							cout << "再给你一次重来的机会" << endl;
							cin.getline (strcin, 1000);
							continue;
						}
						else
						{
							player = -1;
							tmp1 = 0;
							break;
						}
					}
                }
			}
			int x0, y0, x1, y1, x2, y2;
			while(tmp2)
			{
				cout << "输入你的走法 格式[x0 y0 x1 y1 x2 y2]" << endl;
				cin.getline (strcin, 1000);
				while (1)
				{
					if (strlen (strcin) != 11)
					{
						cout << "请按照[x0 y0 x1 y1 x2 y2]的格式输入！" << endl;
						cin.getline (strcin, 1000);
						continue;
					}
					if (strcin[1] != ' ' || strcin[3] != ' ' || strcin[5] != ' ' || strcin[7] != ' ' || strcin[9] != ' ')
					{
						cout << "请按照[x0 y0 x1 y1 x2 y2]的格式输入！" << endl;
						cin.getline (strcin, 1000);
						continue;
					}
					else
					{
						x0 = strcin[0] - '0';
						y0 = strcin[2] - '0';
						x1 = strcin[4] - '0';
						y1 = strcin[6] - '0';
						x2 = strcin[8] - '0';
						y2 = strcin[10] - '0';
						break;
					}
				}
				if (ProcStep (x0, y0, x1, y1, x2, y2, player, true))
				{
					// 判断是否合法
					int checkrule = 0,i1, dio, i2, jojo;
					for (i1 = 0; i1 < 8; i1++)
					{
						for (dio = 1; dio < 8; dio++)
						{
							if (x0 + dx[i1] * dio == x1 && y0 + dy[i1] * dio == y1)
							{
								checkrule = 1;
								break;
							}
						}
						if (checkrule)
							break;
					}
					if (!checkrule)
					{
						cout << "请想好了再输入！" << endl;
						continue;
					}
					checkrule = 0;
					for (i2 = 0; i2 < 8; i2++)
					{
						for (jojo = 1; jojo < 8; jojo++)
						{
							if (x1 + dx[i2] * jojo == x2 && y1 + dy[i2] * jojo == y2)
							{
								checkrule = 1;
								break;
							}
						}
						if (checkrule)
							break;
					}
					if (!checkrule)
					{
						cout << "请想好了再输入！" << endl;
						continue;
					}
					//花式输出
					int oldx = x0, oldy = y0, newx, newy;
					for (int i = 1; i <= dio; i++)
					{
						newx = oldx + dx[i1];
						newy = oldy + dy[i1];
						map[newx][newy] = player;
						map[oldx][oldy] = 0;
						DrawBoard();
						Sleep (0.2 * 1000);
						oldx = newx;
						oldy = newy;
					}
					for (int i = 1; i <= jojo; i++)
					{
						newx = oldx + dx[i2];
						newy = oldy + dy[i2];
						map[newx][newy] = OBSTACLE;
						if (oldx != x1 || oldy != y1)
							map[oldx][oldy] = 0;
						DrawBoard();
						Sleep (0.2 * 1000);
						oldx = newx;
						oldy = newy;
					}

					cout << "输入1查看电脑走法" << endl;
					int fine;
					cin >> fine;	
					ch = cin.get();	

					int j1, j2, d1, d2;
					player *= -1; // 换成电脑
					flag1 = 0;
					alpha = -999999;
					int first = 1; // 判断是否为第一个
                    if (round_amazon <= 6)
                    {
                        flag1 = 1, flag2 = 1;
                        double max = -99999;
                        for (int i = 0; i < GRIDSIZE; i++)
                        {
                            for (int j = 0; j < GRIDSIZE; j++)
                            {
                                if (map[i][j] == player)
                                {
                                    for (int k = 0; k < 8; k++)
                                    {
                                        for (int delta = 1; delta < GRIDSIZE; delta++)
                                        {
                                            int xx = i + dx[k] * delta;
                                            int yy = j + dy[k] * delta;
                                            if (map[xx][yy] != 0 || !inMap (xx, yy))
                                                break;
                                            for (int l = 0; l < 8; l++)
                                            {
                                                for (int delta2 = 1; delta2 < GRIDSIZE; delta2++)
                                                {
                                                    int xxx = xx + dx[l] * delta2;
                                                    int yyy = yy + dy[l] * delta2;
                                                    if (!inMap (xxx, yyy))
                                                        break;
                                                    if (map[xxx][yyy] != 0 && !(i == xxx && j == yyy))
													    break;
												    if (ProcStep (i, j, xx, yy, xxx, yyy, player, true))
												    {
													    map[i][j] = 0;
													    map[xx][yy] = player;
													    map[xxx][yyy] = OBSTACLE;
                                                        for (int iiii = 0; iiii < GRIDSIZE; iiii++)
															for (int jjjj = 0; jjjj < GRIDSIZE; jjjj++)
															{
																Qblack[i][j] = 1000;
																Qwhite[i][j] = 1000;
																Kblack[i][j] = 1000;
																Kwhite[i][j] = 1000;
															}
														double temp = evaluate();
                                                        if (temp > max)
                                                        {
                                                            max = temp;
                                                            movex0 = i;
                                                            movey0 = j;
                                                            movex1 = xx;
                                                            movey1 = yy;
                                                            movex2 = xxx;
                                                            movey2 = yyy;
                                                            j1 = k;
                                                            j2 = l;
                                                            d1 = delta;
                                                            d2 = delta2;
                                                        }
                                                        map[xxx][yyy] = 0;
                                                        map[xx][yy] = 0;
                                                        map[i][j] = player;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
					for (int i = 0; i < GRIDSIZE; i++)
					{
						for (int j = 0; j < GRIDSIZE; j++)
						{
							if (map[i][j] == player)
							{
								for (int k = 0; k < 8; k++)
								{
									for (int delta = 1; delta < GRIDSIZE; delta++)
									{
										int xx = i + dx[k] * delta;
										int yy = j + dy[k] * delta;
										if (map[xx][yy] != 0 || !inMap (xx, yy))
											break;
										for (int l = 0; l < 8; l++)
										{
											for (int delta2 = 1; delta2 < GRIDSIZE; delta2++)
											{
												int xxx = xx + dx[l] * delta2;
												int yyy = yy + dy[l] * delta2;
												if (!inMap (xxx, yyy))
													break;
												if (map[xxx][yyy] != 0 && !(i == xxx && j == yyy))
													break;
												if (ProcStep (i, j, xx, yy, xxx, yyy, player, true))
												{
													// 第一步枚举结束
													flag1 = 1;
													map[i][j] = 0;
													map[xx][yy] = player;
													map[xxx][yyy] = OBSTACLE;
													player *= -1; // 换成玩家
													flag2 = 0;
													// 第二部枚举
													int checkalpha = 0; // 剪枝
													int MIN = 9999999;
													for (int ii = 0; ii < GRIDSIZE; ii++)
													{
														for (int jj = 0; jj < GRIDSIZE; jj++)
														{
															if (map[ii][jj] == player)
															{
																for (int kk = 0; kk < 8; kk++)
																{
																	for (int delta3 = 1; delta3 < GRIDSIZE; delta3++)
																	{
																		int xxxx = ii + dx[kk] * delta3;
																		int yyyy = jj + dy[kk] * delta3;
																		if (map[xxxx][yyyy] != 0 || !inMap (xxxx, yyyy))
																			break;
																		for (int ll = 0; ll < 8; ll++)
																		{
																			for (int delta4 = 1; delta4 < GRIDSIZE; delta4++)
																			{
																				int xxxxx = xxxx + dx[ll] * delta4;
																				int yyyyy = yyyy + dy[ll] * delta4;
																				if (!inMap (xxxxx, yyyyy))
																					break;
																				if (map[xxxxx][yyyyy] != 0 && !(ii == xxxxx && jj == yyyyy))
																					break;
																				if (ProcStep (ii, jj, xxxx, yyyy, xxxxx, yyyyy, player, true))
																				{
																					flag2 = 1;
																					map[ii][jj] = 0;
																					map[xxxx][yyyy] = player;
																					map[xxxxx][yyyyy] = OBSTACLE;
																					player *= -1; // 变回电脑
																					//
																					for (int iiii = 0; iiii < GRIDSIZE; iiii++)
																						for (int jjjj = 0; jjjj < GRIDSIZE; jjjj++)
																						{
																							Qblack[i][j] = 1000;
																							Qwhite[i][j] = 1000;
																							Kblack[i][j] = 1000;
																							Kwhite[i][j] = 1000;
																						}
																					double temp = evaluate();
																					if (temp < alpha && !first)
																					{
																						checkalpha = 1;
																						player *= -1;
																						map[xxxxx][yyyyy] = 0;
																						map[xxxx][yyyy] = 0;
																						map[ii][jj] = player;
																						break;
																					}
																					//
																					if (temp < MIN)
																						MIN = temp;
																					player *= -1; // 变回玩家
																					map[xxxxx][yyyyy] = 0;
																					map[xxxx][yyyy] = 0;
																					map[ii][jj] = player;
																				}
																			}
																			if (checkalpha)
																				break;
																		}
																		if (checkalpha)
																			break;
																	}
																	if (checkalpha)
																		break;
																}
															}
															if (checkalpha)
																break;
														}
														if (checkalpha)
															break;
													}
													if (!flag2)
													{
														movex0 = i;
														movey0 = j;
														movex1 = xx;
														movey1 = yy;
														movex2 = xxx;
														movey2 = yyy;
														j1 = k;
														j2 = l;
														d1 = delta;
														d2 = delta2;
														break;
													}
													if (!checkalpha)
													{
														if (first)
															first = 0;
														if (alpha < MIN)
														{
															alpha = MIN;
															movex0 = i;
															movey0 = j;
															movex1 = xx;
															movey1 = yy;
															movex2 = xxx;
															movey2 = yyy;
															j1 = k;
															j2 = l;
															d1 = delta;
															d2 = delta2;
														}
													}
													player *= -1; // 换回电脑
													map[xxx][yyy] = 0;
													map[xx][yy] = 0;
													map[i][j] = player;
												}
												if (!flag2)
													break;
											}
											if (!flag2)
												break;
										}
										if (!flag2)
											break;
									}
									if (!flag2)
										break;
								}
							}
							if (!flag2)
								break;
						}
						if (!flag2)
							break;
					}
                    }
					tmp2 = 0;
					//选手赢
					if (!flag1)
					{
						victory1();
						victory2();
						victory3();
						victory2();
						victory1();
						victory2();
						victory3();
						victory2();
						victory1();
						victory2();
						victory3();
						victory2();
						cout << "兄弟，你还可以啊！" << endl;
						cout << "请选择：" << endl;
						cout << "1.新游戏" << endl;
						cout << "2.退出"   << endl;
						cin.getline (strcin, 1000);
						while (1)
						{
							if (strlen (strcin) != 1)
							{
								cout << "这你都能输错？" << endl;
								cin.getline (strcin, 1000);
								continue;
							}
							if (strcin[0] != '1' && strcin[0] != '2')
							{
								cout << "这你都能输错？" << endl;
								cin.getline (strcin, 1000);
								continue;
							}
							if (strcin[0] == '1')
							{
								tmp1 = 1;
								Board (true);
								DrawBoard();
								ShowMenu();
								break;
							}
							else
								exit (0);
						}
						break;
					}
					//花式输出
					oldx = movex0;
					oldy = movey0;
					for (int i = 1; i <= d1; i++)
					{
						newx = oldx + dx[j1];
						newy = oldy + dy[j1];
						map[newx][newy] = player;
						map[oldx][oldy] = 0;
						DrawBoard();
						Sleep (0.2 * 1000);
						oldx = newx;
						oldy = newy;
					}
					for (int i = 1; i <= d2; i++)
					{
						newx = oldx + dx[j2];
						newy = oldy + dy[j2];
						map[newx][newy] = OBSTACLE;
						if (oldx != movex1 || oldy != movey1)
							map[oldx][oldy] = 0;
						DrawBoard();
						Sleep (0.2 * 1000);
						oldx = newx;
						oldy = newy;
					}
                    cout << "电脑的走法是" << movex0 << " " << movey0 << " " << movex1 << " " << movey1 << " " << movex2 << " " << movey2 << endl;
                    Sleep (1 * 1000);	
					player *= -1;
					//电脑赢
					if (!flag2)
					{
						defeat();
						cout << "这你都能输？" << endl;
						cout << "请选择：" << endl;
						cout << "1.新游戏" << endl;
						cout << "2.退出"   << endl;
						cin.getline (strcin, 1000);
						while (1)
						{
							if (strlen (strcin) != 1)
							{
								cout << "这你都能输错？" << endl;
								cin.getline (strcin, 1000);
								continue;
							}
							if (strcin[0] != '1' && strcin[0] != '2')
							{
								cout << "这你都能输错？" << endl;
								cin.getline (strcin, 1000);
								continue;
							}
							if (strcin[0] == '1')
							{
								tmp1 = 1;
								Board (true);
								DrawBoard();
								ShowMenu();
								break;
							}
							else
								exit (0);
						}
						break;
					}
					round_amazon++;
				}
				else
					cout << "请再尝试一次输入" << endl;
			}
		}
		break;
		case '2': // 悔棋
		{
			ifstream fin(SAVE_FILE_tmp);
			if (!fin)
			{
				cout << "呵呵，想多了吧";
				Sleep(1 * 1000);
				break;
			}
			int x;
			fin >> x;
			round_amazon = x;
			for (int i = 0; i < GRIDSIZE; i++)
			{
				for (int j = 0; j < GRIDSIZE; j++)
				{
					fin >> x;
					map[i][j] = x;
				}
			}
			fin.close();
			break;
		}
		case '3': // 新游戏
		{	
			round_amazon = 1;
			Board(true);
			DrawBoard();
			break;
		}
		case '4': // 退出游戏
		{	
			fange();
			cout << "你要保存吗 [y/n]: ";
			char ans;
			cin >> ans;
			if (ans == 'y') SaveBoard();
			else
			{
				remove(SAVE_FILE_tmp);
			}
			//若不选择保存的话就把原来的临时文件删除
			isRunning = false;
			break;
		}
	}
}


int main()//主页
{
	victory1();
	victory2();
	victory3();
	victory2();
	victory1();
	victory2();
	victory3();
	victory2();
	victory1();
	victory2();
	victory3();
	victory2();
	isRunning = true;
	system("cls");
	cout << "====================================================\n";
	Sleep(0.1 * 1000);
	cout << "                  来啊来啊快来快活啊\n";
	cout << "====================================================\n";
	Sleep(0.5 * 1000);
	system("cls");
	cout << "====================================================\n";
	cout << "                    快乐亚马逊棋\n";
	cout << "====================================================\n";
	Sleep(0.5 * 1000);
	cout << "                   1. 新游戏\n";
	cout << "                   2. 继续上次游戏\n";
	cout << "                   3. 游戏说明\n";
	cout << "                   4. 退出游戏\n";
	cout << "                   请输入 [1/2/3]: ";
    int wrongcnt = 0;
	while (1)
	{
		cin.getline (strcin, 1000);
		if (strcin[0] != '1' && strcin[0] != '2' && strcin[0] != '3' && strcin[0] != '4')
		{
			cout << "别闹! 选择[1/2/3]中的数字" << endl;
		}
        else if (strlen (strcin) != 1)
        {
            cout << "你干啥打这么多字？输入一个就够了" << endl;
        }
		else break;
        wrongcnt++;
        switch (wrongcnt)
        {
            case 1: cout << "再给你一次重来得机会" << endl; break;
            case 2: cout << "事不过三 别太过分了翔哥" << endl; break;
            case 3: cout << "你有本事再输错一次？" << endl; break;
        }
        if (wrongcnt == 4)
        {
            isRunning = false;
            break;
        }
	}
	switch (strcin[0])
	{
		case '1':
			Board(true);
			while(isRunning)
			{	
				DrawBoard();
				ShowMenu();
			}
			break;
		case '2':
			Board(false);
			while(isRunning)
			{	
				DrawBoard();
				ShowMenu();
			}
			break;
		case '3':
			rule();
			char hhh;
			cout << "Start a new game? [y/n]: ";
			cin >> hhh;
			if(hhh == 'y')
			{
				Board(true);
				while(isRunning)
				{	
					DrawBoard();
					ShowMenu();
				}
				break;
			}
			else break;
		case '4':
			break;
	}
}