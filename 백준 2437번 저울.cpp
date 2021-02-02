#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1000;

int arr[MAX] = { 0, };
int N;
long long SUM = 0;
int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}
	sort(arr, arr + N, less<int>());

	for (int i = 0; i < N; i++)
	{
		if (arr[i] > SUM + 1) {
			break;
		}
		SUM += arr[i];
	}
	cout << SUM + 1 << "\n";
}