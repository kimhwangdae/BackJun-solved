#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int N;

vector <pair<int,int>>graph[51];
vector <int>result[51];
void BFS(int idx)
{
	bool vi[51] = {false,};
	queue<pair<int, int>> q;
	vi[idx] = true;
	for (int i = 0; i < graph[idx].size(); i++)
	{
		q.push(make_pair(graph[idx][i].first, graph[idx][i].second));
	}
	while (!q.empty())
	{
		int now_hight = q.front().first;
		int next_node = q.front().second;
		result[idx].push_back(now_hight);

		q.pop();
		
		if (!vi[next_node])
		{
			vi[next_node] = true;
			for (int i = 0; i < graph[next_node].size(); i++)
			{
				int next_next_node = graph[next_node][i].second;
				q.push(make_pair(now_hight + 1, next_next_node));
			}
		}

	}

}
int main()
{
	int arr[51] = { 0, };
	int Min = 987654321,cnt=0;
	cin >> N;

	for (int i = 0;; i++)
	{
		int start, destination;
		cin >> start >> destination;
		if (start == -1 && destination == -1)
			break;
		graph[start].push_back(make_pair(0, destination));
		graph[destination].push_back(make_pair(0, start));

	}

	for (int i = 1; i <= N; i++)
	{
		BFS(i);
	}
	for (int i = 1; i <= N-1; i++)
	{
		
		Min = min(result[i].back(), result[i+1].back());
	}
	for (int i = 1; i <= N; i++)
	{
		if (Min == result[i].back())
		{
			cnt++;
			arr[i] = i;	
		}
		
	}
	cout << Min << " " << cnt << endl;
	for (int i = 1; i <= N; i++)
	{
		if (arr[i]!=0)
		{
			cout << arr[i] << " ";
		}
	}
}

