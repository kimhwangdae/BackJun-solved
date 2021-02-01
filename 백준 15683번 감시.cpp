#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX = 8;
const int INF = 987654321;
int result;
int N, M;
int Map[MAX][MAX],copyMap[MAX][MAX];
int vi[MAX][MAX][4];
vector <pair<int, int>>v;
vector<int>angle;

typedef struct Dir {
	int y, x;

}Dir;

Dir moveDir[4] = { {1,0},{0,1},{-1,0},{0,-1} };


int NumCount()
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (copyMap[i][j]==0)
			{
				cnt++;
			}
		}
		
	}

	
	return cnt;
}

void copy()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			
			copyMap[i][j] = Map[i][j];
		}
	}
}

void DFS(int cnt)
{
	if (cnt == v.size())
	{
		for (int i = 0; i < angle.size(); i++)
		{
			int x = v[i].second;
			int y = v[i].first;

			for (int j = 0; j < 4; j++)
			{
				if (vi[y][x][j])
				{
					int next_y = y + moveDir[(angle[i] + j) % 4].y;
					int next_x = x + moveDir[(angle[i] + j) % 4].x;
					if (next_y>=0&&next_y<N&&next_x>=0&&next_x<M)
					{
						while (1)
						{
							if (!(next_y >= 0 && next_y < N && next_x >= 0 && next_x < M))
							{
								break;
							}
							if( copyMap[next_y][next_x] == 6)
							{
								break;
							}
							if (copyMap[next_y][next_x] == 0)
							{
								copyMap[next_y][next_x] = -1;
							}
							next_y = next_y + moveDir[(angle[i] + j )% 4 ].y;
							next_x = next_x + moveDir[(angle[i] + j) % 4].x;
						}
					}
				}
			}
		}

		result = min(result, NumCount());
		copy();
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		
		angle.push_back(i);
		DFS(cnt + 1);
		angle.pop_back();
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

			if (Map[i][j] > 0 && Map[i][j] < 6)
			{
				v.push_back({ i,j });
				if (Map[i][j] == 1)
				{
					vi[i][j][0] = true;
				}
				else if (Map[i][j] == 2)
				{
					vi[i][j][0] = true;
					vi[i][j][2] = true;
				}
				else if (Map[i][j] == 3)
				{
					vi[i][j][0] = true;
					vi[i][j][1] = true;
				}
				else if (Map[i][j] == 4)
				{
					vi[i][j][0] = true;
					vi[i][j][1] = true;
					vi[i][j][2] = true;
				}
				else
				{
					vi[i][j][0] = true;
					vi[i][j][1] = true;
					vi[i][j][2] = true;
					vi[i][j][3] = true;
				}
			}
		}
	}
	result = INF;
	copy();
	DFS(0);

	cout << result << endl;
}