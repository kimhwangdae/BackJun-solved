#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 20 + 1;
int N,Time=0;

vector<pair<int, pair<int, pair<int,int>>>>shark;
vector<pair<int, pair<int, int>>>fish;
int Map[MAX][MAX];
bool vi[MAX][MAX];

typedef struct Dir
{
	int y, x;
}Dir;

Dir moveDir[4] = { {0,1},{-1,0},{0,-1},{1,0} };

void BFS()
{
	memset(vi, 0, sizeof(vi));

	queue<pair<int, pair<int, int>>>q;
	q.push({ 0,{shark.front().second.second.first,shark.front().second.second.second} });
	vi[q.front().second.first][q.front().second.second] = true;
	

	while (!q.empty())
	{
		int y = q.front().second.first;
		int x = q.front().second.second;
		int time = q.front().first;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_y = y + moveDir[i].y;
			int next_x = x + moveDir[i].x;

			if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < N&&!vi[next_y][next_x])
			{
				if (Map[next_y][next_x] < shark.front().first && Map[next_y][next_x] != 0)
				{
					fish.push_back({ time + 1,{next_y,next_x} });
					vi[next_y][next_x] = true;
				}
				if (Map[next_y][next_x] == 0||Map[next_y][next_x]==shark.front().first)
				{
					q.push({ time + 1,{next_y,next_x} });
					vi[next_y][next_x] = true;
				}
			}

		}
	}
}

void position_decision()
{
	sort(fish.begin(), fish.end());

	int shark_size = shark.front().first;
	int shark_eat = shark.front().second.first+1;
	Map[shark.front().second.second.first][shark.front().second.second.second] = 0;

	shark.pop_back();
	if (shark_size == shark_eat)
	{
		shark.push_back({ shark_size+1 ,{0, { fish.front().second.first,fish.front().second.second } } });

	}
	else
	{
		shark.push_back({ shark_size ,{shark_eat, { fish.front().second.first,fish.front().second.second } } });

	}
	Map[shark.front().second.second.first][shark.front().second.second.second] = 9;
	Time += fish.front().first;

	fish.clear();

	return;
}
int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];

			if (Map[i][j] == 9)
			{
				shark.push_back({ 2,{0,{i,j}} });
			}
		}
	}
	while (1)
	{
		BFS();
		if (fish.size() == 0)break;
		position_decision();
		
	}
	cout << Time;
	
}