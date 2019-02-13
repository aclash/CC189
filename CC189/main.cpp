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

//take array as parameter
//vector<char> URLify(const char str[], int length) {
//	vector<char> ret(length + 1);
//	strcpy_s(&ret[0], length, str);
//	return ret;
//}

//1.4 Given a string, write a method to check if it is a permutation of a palindrome.
//assume the string consists of only ASCII
//time complexity: O(n), n is the length of string
//space complexity: O(1), 128 integer
//optimization: if the string only consists of lowercase, use one int as hash, check if hash_int has exactly one bit set to 1: number & (number - 1) == 0
bool isPermutationPalindrome(string str) {
	vector<int> hash(128);
	int checker = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (hash[str[i]] == 0) {
			++checker;
			++hash[str[i]];
		}
		else {
			--checker;
			--hash[str[i]];
		}
	}
	if (checker == 0 || checker == 1)
		return true;
	else
		return false;
}

bool isPermutationPalindromeLowerCase(string str) {
	int int_hash = 0;
	for (int i = 0; i < str.size(); ++i) {
		int val = str[i] - 'a';
		if (int_hash & (1 << val) == 0)
			int_hash |= (1 << val);
		else
			int_hash &= ~(1 << val);
	}
	if (int_hash == 0 || (int_hash & (int_hash - 1) == 0))
		return true;
	else
		return false;
}

//1.5 Given two string, there are 3 types of edits can be performed on strings: insert/delete/replace a character; 
//check if they are on edit away.
//time complexity: O(n), n is the lenght of short string 
//space complexity: O(1)
bool isOneWayEdit(string str1, string str2) {
	if (str1.length() == str2.length()) {
		bool flag = false;
		for (int i = 0; i < str1.size(); ++i) {
			if (str1[i] != str2[i]) {
				if (flag)
					return false;
				else
					flag = true;
			}
		}
	}
	else if (str1.length() == str2.length() + 1) {
		bool flag = false;
		for (int i = 0, index = 0; i < str2.size(); ++i, ++index) {
			if (str1[index] != str2[i]) {
				++index;
				if (flag)
					return false;
				else
					flag = true;
			}
		}
	}
	else if (str1.length() == str2.length() - 1) {
		bool flag = false;
		for (int i = 0, index = 0; i < str1.size(); ++i, ++index) {
			if (str1[i] != str2[index]) {
				++index;
				if (flag)
					return false;
				else
					flag = true;
			}
		}
	}
	else
		return false;
	return true;
}

int main()
{
	string str1, str2;
	while (getline(cin, str1) && getline(cin, str2)) {
		cout << isOneWayEdit(str1, str2) << endl;
	}
	system("pause");
	return 0;
}
