#include <iostream>
#include <vector>


using namespace std;

typedef struct {

	int y, x;
}Dir;

typedef struct {
	int y, x, m, s, d;
}Fire;

Dir moveDir[8] = { {-1,0},{-1,1 },{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

const int MAX = 51;
int N, M, K;
vector<Fire> Fireball[MAX][MAX];
vector<Fire> Fireball_temp[MAX][MAX];

void MoveFire() {

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Fireball[i][j].size() == 0) {
				continue;
			}
			int size = Fireball[i][j].size();
			for (int k = 0; k < size; k++)
			{
				int y = Fireball[i][j].back().y;
				int x = Fireball[i][j].back().x;
				int weight = Fireball[i][j].back().m;
				int speed = Fireball[i][j].back().s;
				int dir = Fireball[i][j].back().d;


				int Move = speed % N;
				int next_y = y + (moveDir[dir].y * Move);
				int next_x = x + (moveDir[dir].x * Move);

				if (next_y <= 0)
					next_y = next_y + N;
				if (next_y > N)
					next_y = next_y - N;
				if (next_x <= 0)
					next_x = next_x + N;
				if (next_x > N)
					next_x = next_x - N;

				Fireball_temp[next_y][next_x].push_back({ next_y,next_x,weight,speed,dir });
				Fireball[i][j].pop_back();
			}
		}
	}
}

void SeparationFire() {

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Fireball_temp[i][j].size() == 0)
			{
				continue;
			}
			else if (Fireball_temp[i][j].size() == 1) {
				Fireball[i][j] = Fireball_temp[i][j];
				Fireball_temp[i][j].clear();
			}
			else if (Fireball_temp[i][j].size() >= 2) {


				int Sum_Weight = 0;
				int Sum_speed = 0;
				int temp_dir = 0;
				bool flag = false;
				for (int k = 0; k < Fireball_temp[i][j].size(); k++)
				{
					Sum_Weight += Fireball_temp[i][j][k].m;
					Sum_speed += Fireball_temp[i][j][k].s;

					if (k == 0) {
						temp_dir = Fireball_temp[i][j][k].d % 2;
					}
					if (temp_dir != Fireball_temp[i][j][k].d % 2) {

						flag = true;
					}
				}


				Sum_Weight = Sum_Weight / 5;
				if (Sum_Weight == 0) {
					Fireball_temp[i][j].clear();
					continue;
				}
				Sum_speed = Sum_speed / Fireball_temp[i][j].size();
				if (flag == false) {
					for (int k = 0; k < 8; k += 2)
					{
						int next_y = i + (moveDir[k].y * Sum_speed);
						int next_x = j + (moveDir[k].x * Sum_speed);

						if (next_y <= 0)
							next_y = next_y + N;
						if (next_y > N)
							next_y = next_y - N;
						if (next_x <= 0)
							next_x = next_x + N;
						if (next_x > N)
							next_x = next_x - N;

						Fireball[i][j].push_back({ i,j,Sum_Weight,Sum_speed,k });
					}
				}
				else {
					for (int k = 1; k < 8; k += 2)
					{
						int next_y = i + moveDir[k].y;
						int next_x = j + moveDir[k].x;

						if (next_y <= 0)
							next_y = next_y + N;
						if (next_y > N)
							next_y = next_y - N;
						if (next_x <= 0)
							next_x = next_x + N;
						if (next_x > N)
							next_x = next_x - N;

						Fireball[i][j].push_back({ i,j,Sum_Weight,Sum_speed,k });
					}

				}
				Fireball_temp[i][j].clear();
			}


		}
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> N >> M >> K;

	for (int i = 0; i < M; i++)
	{

		int y, x, m, s, d;
		cin >> y >> x >> m >> s >> d;
		Fireball[y][x].push_back({ y,x,m,s,d });
	}
	int Sum = 0;
	while (K--)
	{
		MoveFire();
		SeparationFire();
		Sum = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (Fireball[i][j].size() == 0) {
					continue;
				}
				for (int k = 0; k < Fireball[i][j].size(); k++)
				{
					Sum += Fireball[i][j][k].m;
				}
			}
		}

	}
	cout << Sum;


	return 0;
}