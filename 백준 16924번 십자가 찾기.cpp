#include <iostream>
#include <vector>

using namespace std;


typedef struct {
	int y, x;
}Dir;

Dir MoveDir[4] = { {0,1 },{0,-1},{1,0},{-1,0} };
const int MAX = 100 + 1;

bool vi[MAX][MAX] = {false,};
int N, M;
char Map[MAX][MAX];

vector <pair<int,pair<int,int>>>v;
int FindCross(int y,int x,int cnt) {

	for (int i = 0; i < 4; i++)
	{
		int next_y = y + (MoveDir[i].y*cnt);
		int next_x = x + (MoveDir[i].x*cnt);

		if (Map[next_y][next_x] != '*') {
			return 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int next_y = y + (MoveDir[i].y * cnt);
		int next_x = x + (MoveDir[i].x * cnt);
		vi[y][x]=false;
		vi[next_y][next_x] = false;
	}
	FindCross(y, x, cnt + 1);
	v.push_back({ y,{x,cnt} });


	return 0;
}


int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == '*') {
				vi[i][j] = true;
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (Map[i][j] == '.') {
				continue;
			}
			FindCross(i, j, 1);
		}
	}
	int true_cnt = 0;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (vi[i][j] == true) {
				true_cnt++;

			}
		}
	}
	if (true_cnt > 0) {
		cout << "-1" << endl;
		return 0;
	}
	else{
		int temp = v.size();
		cout << temp << "\n";
		for (int i = 0; i < temp; i++)
		{
			cout << v[i].first << " " << v[i].second.first << " " << v[i].second.second << "\n";
		}
	}

	return 0;
}