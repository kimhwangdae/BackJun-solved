#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

const int MAX = 100;

typedef struct {

	int y, x;
}Dir;

Dir moveDir[4] = { {1,0},{-1,0}, {0,1},{0,-1 } };

int M, N;

bool vi[MAX][MAX];
int Map[MAX][MAX];


typedef struct {
	int y, x, block;
}Map_cnt;

struct cmp {
	bool operator()(Map_cnt a, Map_cnt b) {
		if (a.block > b.block) {
			return true;
		}
		return false;
	}
};

int BFS() {

	priority_queue<Map_cnt , vector<Map_cnt>, cmp>pq;
	pq.push({ 0,0,0 });
	vi[0][0] = true;

	while (!pq.empty()) {
		int y = pq.top().y;
		int x = pq.top().x;
		int block = pq.top().block;

		pq.pop();
		if (y == N - 1 && x == M - 1) {
			return block;
		}

		for (int i = 0; i < 4; i++) {
			int next_y = y + moveDir[i].y;
			int next_x = x + moveDir[i].x;
			
			if (next_y < 0 || next_y >= N || next_x < 0 || next_x >= M || vi[next_y][next_x]) {
				continue;
			}
			if (Map[next_y][next_x] == 1) {
				pq.push({ next_y,next_x,block + 1 });
				
			}
			else {
				pq.push({ next_y,next_x,block });
			}
			vi[next_y][next_x] = true;
		}
	}

}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> M >> N;
	string str;
	for (int i = 0; i < N; i++)
	{	cin >> str;
	for (int j = 0; j < str.length(); j++) {
		Map[i][j]=str[j]-'0';
		}
	}

	cout << BFS() << "\n";
}