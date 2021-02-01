#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int MAX = 20 + 1;
int N, M, Gas;

typedef struct {
	int y, x;
}Dir;

Dir moveDir[4] = { {-1,0},{0,1},{1,0},{0,-1} };
map<pair<int, int>, pair<int, int>> pass2des;
int Map[MAX][MAX];
bool vi[MAX][MAX];

typedef struct {
	int y, x, gas;
}State;

State start;

bool operator <(State a, State b) {

	if (a.gas < b.gas) {
		return true;
	}
	if (a.gas == b.gas) {
		if (a.y > b.y) {
			return true;
		}
		if (a.y == b.y) {
			if (a.x > b.x) {
				return true;
			}
		}
	}

	return false;
}
int FindPass() {

	memset(vi, 0, sizeof(vi));
	priority_queue<State> q;
	q.push({ start.y, start.x, start.gas });
	vi[start.y][start.x] = true;

	
	while (!q.empty()) {
		int y = q.top().y;
		int x = q.top().x;
		int cur_gas = q.top().gas;

		q.pop();

		if (cur_gas == -1) {
			return -1;
		}

		if (pass2des[{y, x}].first != 0 && pass2des.count({ y,x }) >= 1) {
			start = { y,x,cur_gas };
			return 0;
		}
		for (int i = 0; i < 4; i++)
		{
			int next_y = y + moveDir[i].y;
			int next_x = x + moveDir[i].x;

			if (next_y <= 0 || next_y > N || next_x <= 0 || next_x > N || Map[next_y][next_x] == 1) {

				continue;
			}
			if (vi[next_y][next_x]) {
				continue;
			}

			q.push({ next_y,next_x,cur_gas - 1 });
			vi[next_y][next_x] = true;
		}
	}
	return -1;
}


int FindDest() {
	memset(vi, 0, sizeof(vi));
	pair<int, int> destinaion = { pass2des[{start.y,start.x}] };
	pass2des[{start.y, start.x}] = { 0,0 };
	queue<pair<int,pair<int,pair<int,int>>>> q;
	q.push({ start.y, { start.x,{start.gas,0} } });
	vi[start.y][start.x] = true;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second.first;
		int cur_gas = q.front().second.second.first;
		int cnt = q.front().second.second.second;

		q.pop();

		if (cur_gas == -1) {
			
			return -1;
		}
		if (destinaion.first == y && destinaion.second == x) {
			start = { y,x,cnt * 2 + cur_gas };
			return 0;
		}

		for (int i = 0; i < 4; i++)
		{
			int next_y = y + moveDir[i].y;
			int next_x = x + moveDir[i].x;

			if (next_y <= 0 || next_y > N || next_x <= 0 || next_x > N || Map[next_y][next_x] == 1) {

				continue;
			}
			if (vi[next_y][next_x]) {
				continue;
			}
			q.push({ next_y,{next_x,{cur_gas - 1,cnt + 1}} });
			vi[next_y][next_x] = true;

		}

	}
	return -1;
	
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> N >> M >> Gas;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> Map[i][j];
		}
	}
	cin >> start.y >> start.x;

	
	start.gas = Gas;

	for (int i = 0; i < M; i++)
	{
		int pass_y, pass_x, dest_y, dest_x;
		cin >> pass_y >> pass_x >> dest_y >> dest_x;

		pass2des[{pass_y, pass_x}] = { dest_y,dest_x };
	}


	while (M--) {

		if (FindPass() == -1)
		{
			cout << "-1" << "\n";
			return 0;
		}
		if (FindDest() == -1) {
			cout << "-1" << "\n";
			return 0;
		}
		if (M == 0) {
			cout << start.gas << "\n";
			return 0;
		}
		
	}
}