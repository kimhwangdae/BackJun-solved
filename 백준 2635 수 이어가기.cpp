#include <iostream>

using namespace std;


const int MAX = 30000 + 1;

int arr[MAX];
int frist,MaxCnt=0;
int result[MAX];
void func(int cnt,int idx)
{
	if (idx < 0)
	{
		if (cnt >= MaxCnt)
		{
			MaxCnt = cnt;
			for (int i = 0; i < MaxCnt; i++)
			{
				if (arr[i] >= 0)
				{
					result[i] = arr[i];
				}
				else
				{
					MaxCnt--;
				}
			}
		}
		return;
	}

	arr[cnt] = arr[cnt - 2] - arr[cnt - 1];
	int temp = arr[cnt - 2] - arr[cnt - 1];
	func(cnt + 1, temp);
	
}

int main()
{
	cin >> frist;
	arr[0] = frist;
	for (int i = 1; i <= frist; i++)
	{
		arr[1] = i;
		func(2,arr[0]-arr[1]);
	}
	cout << MaxCnt<<endl;
	for (int i = 0; i < MaxCnt; i++)
	{
		cout << result[i] << " ";
	}
}