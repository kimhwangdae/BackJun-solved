#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 10;

const int INF = 987654321;
int N, M, K, Time = 0;
int Map[MAX][MAX], S2D2[MAX][MAX];
vector<int> tree[MAX][MAX];
typedef struct Dir
{
	int y, x;
}Dir;

Dir moveDir[8] = { {1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,-1},{-1,0},{-1,1} };

void spring()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tree[i][j].size())
			{
				int dead = 0;
				vector<int>temp;
				sort(tree[i][j].begin(), tree[i][j].end());
				for (int k = 0; k < tree[i][j].size(); k++)
				{
					int age = tree[i][j][k];
					if (Map[i][j] >= age)
					{
						Map[i][j] -= age;
						temp.push_back(age + 1);
					}
					else
					{
						dead += age / 2;
					}
				}

				tree[i][j].clear();
				for (int k = 0; k < temp.size(); k++)
				{
					tree[i][j].push_back(temp[k]);
				}
				Map[i][j] += dead;
			}
		}
	}
}

void fall()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tree[i][j].size())
			{
				for (int k = 0; k < tree[i][j].size(); k++)
				{
					int age = tree[i][j][k];

					if (age % 5 == 0)
					{
						for (int d = 0; d < 8; d++)
						{
							int next_y = i + moveDir[d].y;
							int next_x = j + moveDir[d].x;

							if (0 <= next_y && next_y < N && next_x >= 0 && next_x < N)
							{
								tree[next_y][next_x].push_back(1);
							}
						}
					}
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
			Map[i][j] = 5;
			cin >> S2D2[i][j];
		}
	}
	
	for (int i = 0; i < M; i++)
	{
		int x, y, z;
		cin >> y >> x >> z;
		tree[y-1][x-1].push_back(z);

	}


	while (K--)
	{
		spring();
		fall();
		winter();
	}
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result += tree[i][j].size();
		}
	}
	cout << result << "\n";
}