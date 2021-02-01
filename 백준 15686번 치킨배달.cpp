#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 50;
const int INF = 987654321;

int N, M;
int result;
int Map[MAX][MAX];
bool vi[13];
vector<pair<int, int>>house;
vector<pair<int, int>>chicken;

int Destince(pair<int, int> a, pair<int, int> b)
{
	return ( abs(a.first - b.first) + abs(a.second - b.second));
}

void DFS(int idx, int selection)
{
	if (selection == M)
	{
		int temp_a = 0;
		for (int i = 0; i < house.size(); i++)
		{
			int temp = INF;
			for (int j = 0; j < chicken.size(); j++)
			{
				if (vi[j])
				{
					temp = min(temp, Destince(house[i], chicken[j]));
				}
			}
			temp_a += temp;
		}
		result = min(result, temp_a);
		return;
	}
	if (idx == chicken.size())
		return;
	vi[idx] = true;
	DFS(idx + 1, selection + 1);
	vi[idx] = false;
	DFS(idx + 1, selection);

}
int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 1)
			{
				house.push_back({ i,j });
			}
			else if (Map[i][j] == 2)
			{
				chicken.push_back({ i,j });
			}
		}
	}
	result = INF;
	DFS(0, 0);
	cout << result << endl;
}