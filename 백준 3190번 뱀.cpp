#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int MAX = 101;
int Map[MAX][MAX];
int N, K,L;
int Time = 0;
int direction = 0;
int L_direction = 0;
queue<pair<int, char>>q;
queue<pair<int, int>>snake;
typedef struct Dir {
	int y, x;
}Dir;

Dir moveDir[4] = { {0,1},{-1,0},{0,-1},{1,0} };

int Move()
{
	int y = snake.back().first;
	int x = snake.back().second;

	int next_y = y+moveDir[direction].y;
	int next_x = x+moveDir[direction].x;
	
	if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < N&&Map[next_y][next_x]!=1)
	{

		if (Map[next_y][next_x] == 2)
		{
			Map[next_y][next_x] = 1;
			snake.push({ next_y,next_x });
		}
		else if (Map[next_y][next_x] == 0)
		{
			Map[next_y][next_x] = 1;
			Map[snake.front().first][snake.front().second] = 0;
			snake.push({ next_y,next_x });
			snake.pop();
		}

		return 0;
	}
	
	return -1;
}

void checkDir()
{
	int change_time = q.front().first;
	if (change_time != Time)
	{
		return;
	}
	char change_dir = q.front().second;
	q.pop();
	
	if (change_dir == 'L')
	{
		direction++;
		direction = direction % 4;
	}
	else if (change_dir == 'D')
	{
		direction = (3+direction)%4;
	}

	return;
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Map[i][j] = 0;
		}
	}
	
	Map[0][0] = 1;
	snake.push({ 0,0 });
	for (int i = 0; i < K; i++)
	{
		int temp_x, temp_y;
		cin >> temp_y >> temp_x;
		Map[temp_y-1][temp_x-1] = 2;
	}
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int temp_time;
		char temp_dir;
		cin >> temp_time >> temp_dir;
		q.push({ temp_time,temp_dir });
	}
	while (1)
	{
		Time++;
		if (Move() == -1)
		{
			break;
		}

		if (!q.empty())
		{
			checkDir();
		}
	}
	cout << Time << endl;
}