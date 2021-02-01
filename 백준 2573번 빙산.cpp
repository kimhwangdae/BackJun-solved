#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 300 + 1;
int N, M;
int iceberg[MAX][MAX];
int point[MAX][MAX];
int vi[MAX][MAX];

typedef struct Dir {
	int y;
	int x;

}Dir;

Dir moveDir[4] = { {1,0},{-1,0},{0,1},{0,-1} };
// 얼마만큼 녹여야 할지 찾는 함수
void MeltingPoint()
{
	memset(point, 0, sizeof(point));
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
			int next_x = x + moveDir[i].x;
			int next_y = y + moveDir[i].y;
			
			if (next_x >= 0 && next_x < M && next_y >= 0 && next_y < N)
			{
				if (!vi[next_y][next_x] && iceberg[next_y][next_x] != 0)
				{
					int Cnt = 0;
					for (int j = 0; j < 4; j++)
					{
						int temp_x = next_x + moveDir[j].x;
						int temp_y = next_y + moveDir[j].y;
						if (iceberg[temp_y][temp_x] == 0)
						{
							Cnt++;
						}
					}
					point[next_y][next_x] = Cnt;
					q.push({ next_y,next_x });
					vi[next_y][next_x] = true;
					
				}
				else if(!vi[next_y][next_x])
				{
					q.push({ next_y,next_x });
					vi[next_y][next_x] = true;
				}
			}
		}
	}
}

// 빙산을 녹여야 할 만큼 녹여줌
void Melting()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			iceberg[i][j] -= point[i][j];
			if (iceberg[i][j] < 0)
			{
				iceberg[i][j] = 0;
			}
		}
	}
}

void DFS(int y, int x)
{
	vi[y][x] = true;
	for (int i = 0; i < 4; i++)
	{
		int next_x = x + moveDir[i].x;
		int next_y = y + moveDir[i].y;
		if (next_x >= 0 && next_x < M && next_y >= 0 && next_y < N)
		{
			if (!vi[next_y][next_x] && iceberg[next_y][next_x] != 0)
			{
				vi[next_y][next_x] = true;
				DFS(next_y, next_x);
			}
		}
	}

}
// 정답을 DFS 방식으로 찾아냄.
int allClear()
{
	memset(vi, 0, sizeof(vi));

	int cnt=0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (iceberg[i][j] == 0)
			{
				vi[i][j] = true;
			}
			if (!vi[i][j] && iceberg[i][j] != 0)
			{
				DFS(i, j);
				cnt++;
			}
		}
	}
	if (cnt >= 2)
	{
		return 2;
	}
	else if (cnt == 0)
	{
		return 0;
	}
	else if (cnt == 1)
	{
		return 1;
	}
}


int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> iceberg[i][j];
		}
	}
	int Cnt = 0;
	while (1)
	{
		MeltingPoint();
		Melting();

		Cnt++;
		if (allClear()==2)
		{
			cout << Cnt;
			break;
		}
		if (allClear() == 0)
		{
			cout << "0";
			break;
		}
		
	}
	
}