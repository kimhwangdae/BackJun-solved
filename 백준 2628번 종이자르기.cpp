#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int X, Y,K;
	cin >> X >> Y>>K;
	vector <int> hight;
	vector <int> withd;
	vector<int>hight_long;
	vector<int>withd_long;
	for (int i = 0; i < K; i++)
	{
		int choice, Num;
		cin >> choice >> Num;
		if (choice == 0)
		{
			hight.push_back(Num);
		}
		else
		{
			withd.push_back(Num);
		}
	}

	hight.push_back(Y);
	withd.push_back(X);
	sort(hight.begin(), hight.end());
	sort(withd.begin(), withd.end());

	for (int i = 0; i < hight.size(); i++)
	{
		if (i == 0)
		{
			hight_long.push_back(hight[i]);
		}
		else
		{
			hight_long.push_back(hight[i] - hight[i - 1]);
		}
	}

	for (int i = 0; i < withd.size(); i++)
	{
		if (i == 0)
		{
			withd_long.push_back(withd[i]);
		}
		else
		{
			withd_long.push_back(withd[i] - withd[i - 1]);
		}
	}

	sort(hight_long.begin(), hight_long.end());
	sort(withd_long.begin(), withd_long.end());
	
	cout << hight_long.back() * withd_long.back() << endl;

}
/*int main()
{
	int paper[MAX][MAX];
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	memset(paper, 0, sizeof(paper));

	int Cnt = 0,anw=0;
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++)
	{
		int choice, Num;
		cin >> choice >> Num;

		if (choice == 0)
		{
			if (Num > M / 2)
			{
				for (int i = 0; i < Num; i++)
				{
					for (int j = 0; j < N; i++)
					{
						paper[i][j] += 1;

					}
				}
				Cnt++;
			}
			else if (Num <= M / 2)
			{
				for (int i = Num; i < M; i++)
				{
					for (int j = 0; j < N; j++)
					{
						paper[i][j] += 1;

					}
				}
				Cnt++;
			}
		}

		if (choice == 1)
		{
			if (Num > N / 2)
			{
				for (int i = 0; i < M; i++)
				{
					for (int j = 0; j < Num; j++)
					{
						paper[i][j] += 1;

					}
				}
				Cnt++;
			}
			else if (Num <= N / 2)
			{
				for (int i = 0; i < M; i++)
				{
					for (int j = Num; j < N; j++)
					{
						paper[i][j] += 1;

					}
				}
				Cnt++;
			}
		}

	}

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Cnt == paper[i][j])
			{
				anw++;
			}
		}
	}
	cout << anw;

	return 0;
}*/// 처음에 시간초과로 실패한 코드..
