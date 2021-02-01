#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int INF = 987654321;
const int MAX = 8;

int Map[MAX][MAX], CopyMap[MAX][MAX];
vector <pair<int, int>>virus;
vector<pair<int,int>>barrier;
int N, M,result;
bool vi[MAX][MAX];
typedef struct Dir
{
	int y, x;

}Dir;

Dir moveDir[4] = { {1,0},{0,1},{-1,0},{0,-1} };

void copy()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			CopyMap[i][j] = Map[i][j];
		}
	}
	
}

int NumCount()
{
	int Cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (CopyMap[i][j] == 0)
			{
				Cnt++;
			}
		}
	}
	return Cnt;
}

int BFS()
{
	queue<pair<int, int>>q;
	for (int i = 0; i < virus.size(); i++)
	{
		q.push({ virus[i].first,virus[i].second });
	}

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_y = y + moveDir[i].y;
			int next_x = x + moveDir[i].x;

			if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < M)
			{
				if (CopyMap[next_y][next_x] == 0)
				{
					CopyMap[next_y][next_x] = 2;
					q.push({ next_y,next_x });

				}

			}
		}
	}


	return NumCount();
}

void DFS(int Cnt)
{
	if (Cnt == 3)
	{
		for (int i = 0; i < barrier.size(); i++)
		{
			CopyMap[barrier[i].first][barrier[i].second] = 1;
		}
		result = max(result, BFS());
		
		copy();
		return;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (vi[i][j] == true) continue;
			vi[i][j] = true;
			barrier.push_back({ i,j });
			DFS(Cnt + 1);
			vi[i][j] = false;
			barrier.pop_back();
		}
	}
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 2)
			{
				virus.push_back({ i,j });
			}
			if (Map[i][j] != 0)
			{
				vi[i][j] = true;
			}
		}
	}
	result = -INF;
	copy();
	DFS(0);
	cout << result << endl;
}