#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int Dp[101][100001] = { 0, };

int main()
{
	cin >> N >> K;
	vector<pair<int, int>>wv;

	for (int i = 0; i < N; i++)
	{
		int w, v;
		cin >> w >> v;
		wv.push_back(make_pair(w, v));
	}
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= K; j++)
		{
			if (i == 0)
			{
				if (wv[i].first <= j)
				{
					Dp[i][j] = wv[i].second;
				}
				continue;
			}
			if (wv[i].first <= j)
			{
				Dp[i][j] = max(Dp[i - 1][j], wv[i].second + Dp[i - 1][j - wv[i].first]);
			}
			else
				Dp[i][j] = Dp[i - 1][j];
		}
	}

	
	cout << Dp[N - 1][K];

	
}