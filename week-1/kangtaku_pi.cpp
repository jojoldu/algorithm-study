#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#define M 10001
using namespace std;

char input[M];
int v[M];

int calcStr(char *str) {
	int i, size = strlen(str);
	int x = str[0] - '0', y;
	int point = 0, gap;
	for (i = 1; i < size; i++) {
		y = str[i] - '0';
		point |= (x != y) ? 4 : 0; // 모든숫자가 같지 않다면
		if (i == 1) {
			gap = x - y;
		}
		else {
			point |= (gap != x - y) ? 2 : 0; // 등차수열이이 아닌경우
			point |= (y != str[i - 2] - '0') ? 1 : 0; // 두개의 숫자가 반복하지 않다면
		}
		x = y;
	}

	if ((point & 4) == 0) return 1;
	if ((point & 2) == 0) return (gap == 1 || gap == -1) ? 2 : 5;
	if ((point & 1) == 0) return 4;
	return 10;
}

int pi(int n) {
	if (v[n] != 999999){
		return v[n];
	}
	if (n == 0) {
		return 0;
	}
	if (n < 3) {
		return 9999999;
	}
	int &rtn = v[n];
	char subStr[6];
	for (int i = 3; i <= 5 && n - i >= 0; i++) {
		strncpy(subStr, input + n - i, i);
		subStr[i] = '\0';
		rtn = min(rtn, pi(n - i) + calcStr(subStr));
	}
	return rtn;
}

int main()
{
	int cases, i;
	cin >> cases;
	while (cases--) {
		cin >> input;
		for (int i = 0; i <= strlen(input); i++) {
			v[i] = 999999;
		}
		cout << pi(strlen(input)) << endl;
	}
	return 0;
}