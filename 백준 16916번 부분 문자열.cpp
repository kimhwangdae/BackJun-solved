#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int main(void) {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string inputString, inputSubString;

	cin >> inputString >> inputSubString;

	
	if (strstr((char*)inputString.c_str(), (char*)inputSubString.c_str()) == NULL)
	{
		cout << 0;
	}
	else {
		cout << 1;
	}

}