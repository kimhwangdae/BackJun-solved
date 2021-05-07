#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 100000 + 1;

vector<pair<int, int>>graph[MAX];
int N, M;
bool vi[MAX] = { false, };
int start, finish;

bool BFS(int Mid) {

	queue <int> q;
	q.push({ start });
	vi[start] = true;
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		if (curr == finish) {
			return true;
		}
		for (int i = 0; i < graph[curr].size(); i++) {
			int next = graph[curr][i].first;
			int NextCost = graph[curr][i].second;

			if (!vi[next] && Mid <= NextCost) {
				vi[next] = true;
				q.push(next);
			}
		}
	}
	return false;
}

int main() {
	cout.tie(0);
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	cin >> N >> M;

	int MaxCost = 0;
	for (int i = 0; i < M; i++) {
		int temp_start, temp_end, cost;
		cin >> temp_start >> temp_end >> cost;

		graph[temp_start].push_back({ temp_end,cost });
		graph[temp_end].push_back({ temp_start,cost });

		MaxCost = max(MaxCost, cost);
	}
	cin >> start >> finish;

	int right = MaxCost;
	int left = 0;

	while (left <= right) {

		memset(vi, false, sizeof(vi));
		
		int mid = (left + right) / 2;

		if (BFS(mid)) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	cout << right << endl;
}