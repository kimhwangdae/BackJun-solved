#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;


int N, M, C;
int capacity[2000 + 1];

typedef struct {
	int send, receive, box;
}Box;

priority_queue<Box>pq;

bool operator <(Box a, Box b) {
	if (a.receive > b.receive) {
		return true;
	}
	if (a.receive == b.receive) {
		if (a.send > b.send) {
			return true;
		}
	}
	return false;
}


int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> N >> C >> M;

	int result = 0;
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		pq.push({ a,b,c });
	}

	for (int i = 0; i < M; i++)
	{
		int BoxCnt = 0;
		for (int j = pq.top().send; j < pq.top().receive; j++)
		{
			BoxCnt = max(BoxCnt, capacity[j]);
		}
		int temp = min(pq.top().box, C - BoxCnt);

		result += temp;
		for (int j = pq.top().send; j < pq.top().receive; j++)
		{
			capacity[j] += temp;
		}
		pq.pop();
	}
	cout << result << endl;

}