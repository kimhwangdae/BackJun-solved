#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int N, K;

vector<pair<int, int>>backpack;
int main()
{
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		int wihgt, val;
		cin >> wihgt>> val;
		backpack.push_back({ wight,val });
	}
	sort(backpack.begin(), backpack.end());

	for (int i = 0; i < backpack.szie(); i++)
	{
		cin >> backpack[i].first >> " " >> backpack[i].second >> endl;
	}
}