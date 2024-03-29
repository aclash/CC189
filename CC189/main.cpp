#include <algorithm>
#include <assert.h>
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

template <typename T>
void output(vector<T>& vec)
{
	for (auto& x : vec)
		cout << x << " , ";
	cout << endl;
}

template <typename T>
void output(vector<vector<T>>& vecs)
{
	for (auto& vec : vecs) {
		for (auto& x : vec) {
			cout << x << " ";
		}
		cout << endl;
	}
}
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

//1.6 string compression: input: aaabbcccc; output: a3b2c4
//int to char(smaller than 10): char ch = '0' + num;
//int to char*: char* itoa(int num, char*, int base)
//char* to int: int atoi(const char*)
//int to string: to_string(int num)
//string to int: int stoi(const string& str, size_t num = 0, size_t base = 0)
//in java: string copy is O(n^2) since each character's copy will make a copy of whole string(1 + 2 + 3 + ... + n), 
//StringBuilder is O(n)
//StringBuilder sb = new StringBuilder(len)
//for (int i = 0; i < str.length(); ++i) {
//	sb.append(str[i]);
//}
//tc: O(n), n is length of str
//sc: O(n), n is length of str
//optimazation: each copy of string will take more time, for example, if the capacity of stringbuild is full, it need double of
//its size and rearrage each element, so we can compute the length of final string in advance so that set the size of stringbuild in advance
int computeSize(string str) {
	assert(str.size() > 0);
	int sum = 0;
	int cnt = 1;
	char firstChar = str[0];
	for (int i = 1; i < str.size(); ++i) {
		if (firstChar != str[i]) {
			sum += (to_string(cnt).length() + 1);
			cnt = 1;
			firstChar = str[i];
		}
		else
			++cnt;
	}
	sum += (to_string(cnt).length() + 1);
	return sum;
}

string stringCompression(string str) {
	string ret;
	if (str.size() == 0)
		return str;
	int len = computeSize(str);
	if (len >= str.length())
		return str;
	else
		ret.resize(len);

	//must initialize to empty string otherwise push_back will insert element after empty elment
	//********//
	ret = "";
	//************//

	char firstChar = str[0];
	int cnt = 1;
	for (int i = 1; i < str.size(); ++i) {
		if (firstChar == str[i])
			++cnt;
		else {
			ret.push_back(firstChar);
			ret += to_string(cnt);
			firstChar = str[i];
			cnt = 1;
		}
	}
	ret.push_back(firstChar);
	ret += to_string(cnt);
	if (ret.length() < str.length())
		return ret;
	else
		return str;
}

//1.7 Given N*N matrix, rotate it by 90 degree in place.
//tc: O(N^2)
//sc: O(1)
void rotateMatrix(vector<vector<int>>& matrix) {
	if (matrix.size() == 0)
		return;
	int cnt = 0;
	int N = matrix.size();
	for (int i = 0; i <= (N - 2) / 2; ++i) {
		for (int j = i; j <= N - 2 - i; ++j) {
			++cnt;
			int tmp = matrix[i][j];
			int x = i;
			int y = j;
			for (int k = 0; k < 4; ++k) {
				int xx = y;
				int yy = N - 1 - x;
				swap(matrix[xx][yy], tmp);
				x = xx;
				y = yy;
			}
		}
	}
	assert(cnt == ((N * N) % 2 == 0 ? N * N / 4 : (N * N - 1) / 4));
}

//1.8
//Given a matrix, if any entry is 0, set its row and column as 0
//tc: O(M*N)
//sc: O(M+N)
//optimization: sc could be O(1), tc also O(M * N), take first row and first col as storage
void SetZero(vector<vector<int>>& matrix) {
	int row = matrix.size();
	if (row <= 0)
		return;
	int col = matrix[0].size();
	vector<bool> flag_row(row);
	vector<bool> flag_col(col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (matrix[i][j] == 0) {
				flag_row[i] = true;
				flag_col[j] = true;
			}
		}
	}
	for (int i = 0; i < row; ++i) {
		if (flag_row[i]) {
			for (int j = 0; j < col; ++j)
				matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < col; ++i) {
		if (flag_col[i]) {
			for (int j = 0; j < row; ++j)
				matrix[j][i] = 0;
		}
	}
}

void OptZeroMatrix(vector<vector<int>>& matrix) {
	int row = matrix.size();
	if (row <= 0)
		return;
	int col = matrix[0].size();
	int row0 = 1;
	int col0 = 1;
	for (int i = 0; i < col; ++i) {
		if (matrix[0][i] == 0) {
			row0 = 0;
			break;
		}
	}
	for (int i = 0; i < row; ++i) {
		if (matrix[i][0] == 0) {
			col0 = 0;
			break;
		}
	}
	for (int i = 1; i < row; ++i) {
		for (int j = 1; j < col; ++j) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}
	for (int i = 1; i < col; ++i) {
		if (matrix[0][i] == 0) {
			for (int j = 1; j < row; ++j) {
				matrix[j][i] = 0;
			}
		}
	}
	for (int i = 1; i < row; ++i) {
		if (matrix[i][0] == 0) {
			for (int j = 1; j < col; ++j) {
				matrix[i][j] = 0;
			}
		}
	}
	if (row0 == 0)
		for (int i = 0; i < row; ++i)
			matrix[0][i] = 0;
	if (col0 == 0)
		for (int i = 0; i < col; ++i)
			matrix[i][0] = 0;
}

//* 1.9 Given two string, check if one is the rotation of another.
// impressive..... S1 = xy, S2 = yx, S1 is substring of xyxy, and always be substring of S1S1, 
//the length of S1 must be equal to S2	
bool isRotation(string str1, string str2) {
	if (str1.length() != str2.length())
		return false;
	string str = str1 + str1;
	if (str.find(str2) != string::npos)
		return true;
	else
		return false;
}
int main()
{
	string str;
	/*while (cin >> str) {
		cout << stringCompression(str) << endl;
	}*/
	//vector<vector<int>> vec = { {0, 2, 3, 4, 0}, {6, 7, 8 ,9 ,10},{ 11, 12, 0, 14, 15 } ,{ 16, 17, 18, 19, 20 } ,{ 21, 22, 23, 24, 25 } };
	//OptZeroMatrix(vec);
	//output(vec);
	cout << isRotation("2221", "1222");
	system("pause");
	return 0;
}
