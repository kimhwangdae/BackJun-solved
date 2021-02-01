#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100 + 1;
int R, C, M;
int result = 0;
vector<pair<int, pair<int, int>>>shark[MAX][MAX];
queue<pair<pair<int, int>, pair<int, pair<int, int>>>>q;
typedef struct Dir
{
	int y, x;
}Dir;

Dir moveDir[4] = { {-1,0}, {1,0},{0,1}, {0,-1} };

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> R >> C >> M;

	for (int i = 0; i < M; i++)
	{
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		shark[r - 1][c - 1].push_back({ s,{d - 1,z} });
	}
	
	for (int c = 0; c < C; c++)
	{
		for (int i = 0; i < R; i++)
		{
			if (!shark[i][c].empty())
			{
				result += shark[i][c].front().second.second;
				shark[i][c].clear();
				break;
			}
		}
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (!shark[i][j].empty())
				{
					q.push({ {i,j},{shark[i][j].front().first,{shark[i][j].front().second.first,shark[i][j].front().second.second} } });
					shark[i][j].clear();
				}
			}
		}
		while (!q.empty())
		{
			int y = q.front().first.first;
			int x = q.front().first.second;
			int speed = q.front().second.first;
			int dir = q.front().second.second.first;
			int size = q.front().second.second.second;

			q.pop();

			for (int i = 0; i < speed; i++)
			{
				if (dir == 0 || dir == 1)
				{
					int next_y = y + moveDir[dir].y;
					if (next_y<0 || next_y>=R)
					{
						dir = 1 - dir;
					}
					y += moveDir[dir].y;
				}
				else
				{
					int next_x = x + moveDir[dir].x;
					if (next_x<0 || next_x>=C)
					{
						dir = 5 - dir;
					}
					x += moveDir[dir].x;
				}
			}
			if (!shark[y][x].empty())
			{
				if (shark[y][x].front().second.second < size)
				{
					shark[y][x].clear();
					shark[y][x].push_back({ speed,{dir,size} });
				}
			}
			else
			{
				shark[y][x].push_back({ speed,{dir,size} });
			}

		}
	}

	cout << result << "\n";
	
}