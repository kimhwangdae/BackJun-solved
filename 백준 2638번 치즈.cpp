#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 100 + 1;
int N, M;
int cheese[MAX][MAX];
int vi[MAX][MAX];


typedef struct Dir
{
	int x;
	int y;
}Dir;

Dir moveDir[4] = { {1,0},{-1,0},{0,1},{0,-1} };

bool ClearAir()
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (cheese[i][j] == 0)
			{
				cnt++;
			}
		}
	}
	if (cnt == N * M)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PreAirToAir()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (vi[i][j] >= 2)
			{
				
				cheese[i][j] = 0;
			}
		}
	}
}


void BFS()
{
	memset(vi, 0, sizeof(vi));
	
	queue<pair<int, int>>q;
	q.push({ 0,0 });
	vi[0][0] = true;
	while (!q.empty())
	{
		int x = q.front().second;
		int y = q.front().first;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int next_x = x+moveDir[i].x;
			int next_y = y+moveDir[i].y;
			
			if (next_x >= 0 && next_x < M && next_y >= 0 && next_y < N)
			{
				if (vi[next_y][next_x] == 0 && cheese[next_y][next_x]==0)
				{
					vi[next_y][next_x] = 1;
					q.push({ next_y,next_x });
				}
				else if (cheese[next_y][next_x]>=1)
				{
					vi[next_y][next_x] += 1;
				}
			}
			
		}

	}
}

int main()
{
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> cheese[i][j];
		}
	}

	int Cnt = 0;

	while (1)
	{
		if (ClearAir())
		{
			break;
		}

		BFS();
		PreAirToAir();
		Cnt++;

	}
	cout <<	Cnt;
	
}