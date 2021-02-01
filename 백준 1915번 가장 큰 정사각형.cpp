#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 4;
typedef struct {
	int y, x;
}Dir;

Dir moveDir[9] = { {0, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };

typedef struct {
	int y, x, num, dir;
}Fish;

Fish fish[17];
int result;
Fish shark;
int Map[MAX][MAX] = {0,};

int Solved(Fish fish,int Map[MAX][MAX],Fish shark,int eat_fish) {
	
	result = max(result, eat_fish);
	
	for (int i = 1; i < 17 ; i++)
	{
		int y = fish[i].y;
		int x = fish[i].x;
		int num = fish[i].num;
		int dir = fish[i].dir;

		if (dir == 0) {
			continue;
		}
		
		int next_y = y + moveDir[dir].y;
		int next_x = x + moveDir[dir].x;

		int dirChangeCnt = 0;

		for(dirChangeCnt = 0;  dirChangeCnt< 8; dirChangeCnt++)
		{
			next_y = y + moveDir[dir].y;
			next_x = x + moveDir[dir].x;

			if (next_y < 0 || next_y >= MAX || next_x < 0 || next_x >= MAX) {
				fish[i].dir = (dir == 8) ? 1 : dir + 1;
				dir = fish[i].dir;

				continue;
			}

			if (next_y == shark.y && next_x == shark.x) {
				fish[i].dir = (dir == 8) ? 1 : dir + 1;
				dir = fish[i].dir;

				continue;
			}

			break;
		}
		if (dirChangeCnt == 8) {
			continue;
		}

		int nextIdx = fish[next_y][next_x];

		if (nextIdx) {
			fish[nextIdx].y = y;
			fish[nextIdx].x = x;
			Map[y][x] = nextIdx;
		}

		else {
			Map[y][x] = 0;
		}

		fish[i].y = next_y;
		fish[i].x = next.x;
		Map[next_y][next_x] = i;
	}

	int y = shark.y;
	int x = shark.x;
	int dir = shark.dir;
	
	for (int i = 1; i <= 3; i++)
	{
		Fish tempFish[17];
		for (int j = 0; j <17 ; j++)
		{
			tempFish[j] = fish[j];
		}

		int tempMap[MAX][MAX];

		for (int j = 0; j < MAX; j++)
		{
			for (int k = 0; k < MAX; k++)
			{
				tempMap[j][k] = Map[j][k];
			}
		}


		int next_y = y + moveDir[dir].y * i;
		int next_x = x + moveDir[dir].x * i;
	
		if (next_y < 0 || next_y >= MAX || next_x < 0 || next_x >= MAX) {
			continue;
		}

		if (tempMap[next_y][next_x] == 0) {
			continue;
		}

		shark.y = next_y;
		shark.x = next_x;

		int score = tempMap[next_y][next_x];
		tempMap[next_y][next_x] = 0;

		shark.dir = tempMap[score].dir;
		tempMap[score].dir = 0;

		Solved(tempFish, tempMap, shark, eat_fish + score);
	
	}
}

int main() {

	cin.tie(0);
	ios_base::sync_with_stdio(0);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int num, dir;
			cin >> num >> dir;
			if (i == 0 && j == 0) {
				shark = { i,j,num,dir };
				continue;
			}
			
			Map[i][j] = num;
			fish[num] = { i,j,num,dir };
		}
	}

	Solved(fish,Map,shark,shark.num);

	cout << result << "\n";
	return 0;
}