#include <algorithm>
#include <bitset>
#include <fstream>
#include <functional>
#include <iterator>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
//1.1 implement an algorithm to determine if a string has all unique charactera, What if you cannot use additional data structures?
//question: can I assume the string consists of only ASCII charater? Otherwise I should increase the storage.
//time complexity: O(N), N is the lenght of string, or it could be O(1), since the length of string no more than 128.
//space complexity: O(1), a constant, 128 Bytes.
//optimization: if the character only consist of lower letter, could you reduce the space usage? use 32bit int.
bool isUnique(string str) {
	bool hash[128];
	memset(hash, false, sizeof(hash));
	if (str.size() > 128)
		return false;
	for (int i = 0; i < str.size(); ++i) {
		if (hash[str[i]] != false)
			return false;
		else
			hash[str[i]] = true;
	}
	return true;
}

bool isUnique_onlyLower(string str) {
	int checker = 0;
	for (int i = 0; i < str.size(); ++i) {
		int val = str[i] - 'a';
		bool flag = checker & (1 << val);
		if (checker & (1 << val))
			return false;
		else
			checker |= (1 << val);
	}
	return true;
}

int main()
{
	string str;
	while (cin >> str) {
		cout << isUnique_onlyLower(str) << endl;
	}
	system("pause");
	return 0;
}
