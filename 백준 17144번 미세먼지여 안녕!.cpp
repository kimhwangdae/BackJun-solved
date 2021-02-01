#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 51;

vector<pair<int, int>>airclear;
int R, C, T;
int Map[MAX][MAX];
int Dust_Map[MAX][MAX];
int copy_ARR[MAX][MAX];
bool vi[MAX][MAX];

typedef struct Dir
{
	int y,x;
}Dir;

Dir moveDir[4] = { {-1,0},{1,0},{0,1},{0,-1} };

int ccw[4] = { 2,0,3,1 };
int cw[4] = { 2,1,3,0 };


void filter()
{
	int y = airclear[0].first;
	int x = airclear[0].second + 1;
	Map[y][x] = 0;

	for (int i = 0; i < 4; i++)
	{
		while (1)
		{
			int next_x = x + moveDir[ccw[i]].x;
			int next_y = y + moveDir[ccw[i]].y;

			if (next_y == airclear[0].first && next_x == airclear[0].second)
			{
				break;
			}
			if (!(0 <= next_y && next_y < R && 0 <= next_x && next_x < C))
			{
				break;
			}
			Map[next_y][next_x] = copy_ARR[y][x];
			y = next_y;
			x = next_x;
		}
	}

	 y = airclear[1].first;
	 x = airclear[1].second + 1;
	Map[y][x] = 0;

	for (int i = 0; i < 4; i++)
	{
		while (1)
		{
			int next_x = x + moveDir[cw[i]].x;
			int next_y = y + moveDir[cw[i]].y;

			if (next_y == airclear[1].first && next_x == airclear[1].second)
			{
				break;
			}
			if (!(0 <= next_y && next_y < R && 0 <= next_x && next_x < C))
			{
				break;
			}
			Map[next_y][next_x] = copy_ARR[y][x];
			y = next_y;
			x = next_x;
		}
	}
}

void diffusion()
{

	memset(Dust_Map, 0, sizeof(Dust_Map));

	queue<pair<int, int>>q;
	for (int i = 0; i < R; i++)
	{
		for (int  j= 0;  j< C; j++)
		{
			if (Map[i][j] >= 1)
			{
				q.push({ i,j });
			}
		}
	}

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			Dust_Map[i][j] = Map[i][j];
		}
	}
	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		int temp = Dust_Map[y][x] / 5;
		if (temp == 0)
		{
			continue;
		}
		for (int i = 0; i < 4; i++)
		{
			int next_y = y + moveDir[i].y;   
			int next_x = x + moveDir[i].x;
			
			if (next_y >= 0 && next_y < R && next_x >= 0 && next_x < C)
			{
				if (Dust_Map[next_y][next_x] >=0)
				{
					Map[next_y][next_x] += temp;
					Map[y][x] -= temp;
				}
			}
		}
		
		
	}
}
void copy()
{
	memset(copy_ARR, 0, sizeof(copy_ARR));
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			copy_ARR[i][j]=Map[i][j];
		}

	}
}

int count()
{
	int cnt=0;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (Map[i][j] >= 1)
			{
				cnt += Map[i][j];
			}
		}
	}
	return cnt;
}

int main()
{
	cin >> R >> C >> T;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == -1)
			{
				airclear.push_back({ i,j });
			}
		}
	}
	int cnt = 0;
	while (cnt < T)
	{

		
		diffusion();
		copy();
		filter();
		
		cnt++;
	}
	cout << count()<<endl;
}