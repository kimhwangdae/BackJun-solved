#include <iostream>

using namespace std;

const int MAX = 50;

int Map[MAX][MAX];

typedef struct Dir
{
	int y, x;
}Dir;

Dir moveDir[4] = { {-1,0},{0,1},{1,0},{0,-1} };
int N, M;
int r, c, d;

void DFS(int Cnt)
{
	Map[r][c] = 3;
	for (int i = 3; i>=0 ; i--)
	{
		int next_y = r + moveDir[(d + i) % 4].y;
		int next_x = c + moveDir[(d + i) % 4].x;
		
		if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < M)
		{
			if (Map[next_y][next_x] == 0)
			{
				r = next_y;
				c = next_x;
				d = (d + i) % 4;
				DFS(Cnt + 1);
				return;
			}
		}
	}
	if (Map[r + moveDir[(d + 2) % 4].y][c + moveDir[(d + 2) % 4].x] == 3)
	{
		r = r + moveDir[(d + 2)%4].y;
		c = c + moveDir[(d + 2)%4].x;
		DFS(Cnt);

		
	}
	else{

		cout << Cnt << endl;
		return;

		}
}
int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> N >> M;
	cin >> r >> c >> d;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
		}
	}
	Map[r][c] = 3;
	
	DFS(1);
}