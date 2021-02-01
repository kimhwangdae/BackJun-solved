#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 20;

int N, M, Y, X, K;
int Map[MAX][MAX];
int dice[4][3] = { {0,0,0},{0,0,0},{0,0,0},{0,0,0} };
int temp[4][3];

void copy()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <3; j++)
		{
			temp[i][j] = dice[i][j];
		}
	}
}
void east()
{
	copy();
	dice[1][0] = temp[3][1];
	dice[1][1] = temp[1][0];
	dice[1][2] = temp[1][1];
	dice[3][1] = temp[1][2];
}

void west()
{
	copy();
	dice[1][0] = temp[1][1];
	dice[1][1] = temp[1][2];
	dice[1][2] = temp[3][1];
	dice[3][1] = temp[1][0];
}
void north()
{
	copy();
	for (int i = 0; i < 4; i++)
	{
		dice[i][1] = temp[(i + 1) % 4][1];
	}
}

void south()
{
	copy();
	for (int i = 0; i < 4; i++)
	{
		dice[i][1] = temp[(i + 3) % 4][1];
	}

}

void fucn(int y, int x)
{
	if(Map[y][x])
	{
		dice[1][1]=Map[y][x];
		Map[y][x] = 0;
	}
	else
	{
		Map[y][x] = dice[1][1];
	}
	cout << dice[3][1] << "\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> Y >> X >> K;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
		}
	}
	pair<int, int>dice_location = { Y,X };
	for (int i = 0; i < K; i++)
	{
		int order;
		cin >> order;
		switch (order)
		{
		case 1:
		{
			if (dice_location.second + 1 < M)
			{
				east();
				dice_location.second += 1;
				fucn(dice_location.first, dice_location.second);
			}
			break;

		}
		case 2:
		{
			if (dice_location.second - 1 >= 0)
			{
				west();
				dice_location.second -= 1;
				fucn(dice_location.first, dice_location.second);
			}
			break;

		}
		case 3:
		{
			if (dice_location.first - 1 >= 0)
			{
				north();
				dice_location.first -= 1;
				fucn(dice_location.first, dice_location.second);
			}
			break;
		}
		case 4:
		{
			if (dice_location.first + 1 < N)
			{
				south();
				dice_location.first += 1;
				fucn(dice_location.first, dice_location.second);
			}
			break;
		}
		}

	}
}