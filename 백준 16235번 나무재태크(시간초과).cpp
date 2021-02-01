#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 10;

const int INF = 987654321;
int N, M, K, Time = 0;
int Map[MAX][MAX],S2D2[MAX][MAX];
vector<pair<int, pair<int, pair<int, int>>>>tree;

typedef struct Dir
{
	int y, x;
}Dir;

Dir moveDir[8] = { {0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1} };

void spring()
{
	sort(tree.begin(), tree.end());
	
	for (int i = 0; i < tree.size(); i++)
	{
		int y = tree[i].second.second.first;
		int x = tree[i].second.second.second;
		int tree_age = tree[i].first;
		int tree_nourishment = tree[i].second.first;
		if (Map[y][x] >= tree_age)
		{
			Map[y][x] = Map[y][x] - tree_age;
			tree[i].second.first = tree_nourishment + 1;
			
			tree[i].first = tree_age + 1;
			tree[i].second.first = 0;
			
		}
		else
		{
			tree[i].first = INF;
			tree[i].second.first = tree_age;
		}
	}
}

void summer()
{
	sort(tree.begin(), tree.end());
	
	int cnt = 0;

	for (int i = 0; i < tree.size(); i++)
	{
		if (tree[i].first == INF)
		{
			Map[tree[i].second.second.first][tree[i].second.second.second] += (tree[i].second.first) / 2;
			cnt++;
		}
	}

	for (int i = 0; i < cnt; i++)
	{
		tree.pop_back();
	}
}

void fall()
{
	int temp = tree.size();
	for (int i = 0; i < temp; i++)
	{
		if ((tree[i].first % 5) == 0)
		{
			int y = tree[i].second.second.first;
			int x = tree[i].second.second.second;

			for (int j = 0; j < 8; j++)
			{
				int next_y = y + moveDir[j].y;
				int next_x = x + moveDir[j].x;
				
				if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < N)
				{
					tree.push_back({ 1,{0,{next_y,next_x}} });
				}
			}
		}
	
	}
}

void winter()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Map[i][j] += S2D2[i][j];
		}
	}
}
int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N >> M >> K;
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			 Map[i][j]=5;
			 cin >> S2D2[i][j];
		}
	}
	int x, y, z;

	for (int i = 0; i < M; i++)
	{

		cin >> y >> x >> z;
		tree.push_back({ z,{0,{y-1,x-1}}});
	}
	

	while (Time < K)
	{
		spring();
		summer();
		fall();
		winter();
		Time++;
	}
	cout << tree.size();
}