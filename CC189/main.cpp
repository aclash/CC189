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

//1.2 Given two strings, write a method to decide if one is a permutation of the other.
//question: can I assume the string consists of only ASCII character? Otherwise need more space to store character's hash value
//time complexity: O(n), n is the length of string
//space complexity: O(1), integer array with length of 256.
bool isPermuation(string str1, string str2) {
	if (str1.length() != str2.length())
		return false;
	int hash[128];
	memset(hash, 0, sizeof(hash));
	for (int i = 0; i < str1.size(); ++i) {
		++hash[str1[i]];
		--hash[str2[i]];
	}
	for (int i = 0; i < 128; ++i)
		if (hash[i] != 0)
			return false;
	return true;
}

//1.3 Write a method to replace all spaces with %20
void URLify(string& str, int length) {
	int spaceCnt = 0;
	int len = length < str.size() ? length : str.size();
	for (int i = 0; i < len; ++i) {
		if (str[i] == ' ')
			++spaceCnt;
	}
	str.resize(length + spaceCnt * 2);
	for (int i = length - 1, j = str.size() - 1; i >= 0, j >=0; --i) {
		if (str[i] != ' ') {
			str[j] = str[i];
			--j;
		}
		else {
			str[j] = '0';
			str[j - 1] = '2';
			str[j - 2] = '%';
			j -= 3;
		}
	}
}

//void URLify(char[] str, int length) {
//	
//}
int main()
{
	string str;
	int len;
	while (getline(cin, str)) {
		cin >> len;
		URLify(str, len);
		cout << str<<endl;
		cin.get();
	}
	system("pause");
	return 0;
}
