#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 50;
const int INF = 987654321;

vector <pair<int, int>>virus;
vector <int> temp;
int Map[MAX][MAX],CopyMap[MAX][MAX];
int N, M;
bool flag;
int result;

typedef struct Dir
{
	int y, x;
}Dir;

Dir moveDir[4] = { {1,0},{0,1},{-1,0},{0,-1} };

void DFS(int Cnt)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			CopyMap[i][j] = Map[i][j];
		}
	}
	queue<pair<int,int>> q;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i])
		{
			q.push(virus[i]);
			CopyMap[virus[i].first][virus[i].second] = 3;

		}
	}
	int time = 0;
	while (!q.empty())
	{
		int size = q.size();
		if (Cnt==0)
		{
			flag = true;
			result = min(result, time);
			break;
		}

		time++;
		for (int i = 0; i < size; i++)
		{
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int j = 0; j < 4; j++)
			{
				int next_y = y + moveDir[j].y;
				int next_x = x + moveDir[j].x;

				if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N)
				{
					if (CopyMap[next_y][next_x] == 0 || CopyMap[next_y][next_x] == 2)
					{
						if (CopyMap[next_y][next_x] == 0)
						{
							Cnt--;
						}
						CopyMap[next_y][next_x] = 3;
						q.push({ next_y,next_x });

					}
				}

			}
			
		}
	

	}
	return;
}


int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];

			if (Map[i][j]==2)
			{
				virus.push_back({ i,j });
			}
		}
	}
	temp.resize(virus.size());
	
	for (int i = 0; i < virus.size(); i++)
	{
		temp[i] = 0;
	}
	for (int i = 0; i < M; i++)
	{
		temp[i] = 1;
	}
	sort(temp.begin(), temp.end());
	
	int Cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j] == 0)
			{
				Cnt++;
			}
		}
	}
	result = INF;
	do
	{
		DFS(Cnt);
	} while (next_permutation(temp.begin(), temp.end()));

	if (flag==false)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << result << endl;
	}
}