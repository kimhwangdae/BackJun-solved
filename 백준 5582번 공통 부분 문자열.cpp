#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int DP[4001][4001];

int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);

	string str1;
	string str2;

	str1 = " ";
	str2 = " ";

	string a, b;
	cin >> a;
	cin >> b;
	str1 += a;
	str2 += b;

	memset(DP, 0, sizeof(DP));
	for (int i = 1; i < str1.size(); i++) {
		for (int j = 1; j < str2.size(); j++) {
			if (str1[i] == str2[j]) {
				DP[i][j] = DP[i-1][j - 1] + 1;
			}
			else {
				DP[i][j] = 0;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i < str1.size(); i++) {
		for (int j = 1; j < str2.size(); j++) {
	
			if (DP[i][j] > ans)ans = DP[i][j];
		}
	}

	cout << ans << endl;
}