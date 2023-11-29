#pragma once
#include <fstream>
#include <iostream>
#include "string_hasher.h"

bool OpenFile(std::ifstream& input, std::string filename) {
	input.open(filename);
	if (!input.is_open()) {
		std::cout << "Ошибка открытия файла" << std::endl;
		return false;
	}
	return true;
}


std::string GetInputString(std::ifstream& input) {
	std::string  str;
	std::getline(input, str);
	return str;
}

/*
CheckSubstringsTask takes string from file
and for queries_count times takes positions A anb B
and the length of substrings from that positions
outstream gets std::string "yes"/"no" marks for every query
if substrings are equal
example of input
acabaca
3
4 3 2
3 4 0
2 0 1
exaple of output
no
yes
no
*/
int CheckSubstringsTask(std::string in_filename, std::string out_filename) {
	std::ifstream input;
	if (!OpenFile(input, in_filename)) return 1;
	std::string input_str = GetInputString(input);
	HashTable hash_table = StringHasher(input_str);
	uint32_t queries_count = 0;
	input >> queries_count;
	std::ofstream output;
	output.open(out_filename);
	uint32_t Length = 0;
	uint32_t pos_A = 0;
	uint32_t pos_B = 0;
	while (queries_count > 0) {
		input >> Length;
		input >> pos_A;
		input >> pos_B;
		bool ans = EqualSubstrings(hash_table, pos_A + 1, pos_B + 1, Length);
		ans ? output << "yes\n"s : output << "no\n";
		--queries_count;
	}
	return 0;
}

/*
HasCirclePartTask takes string from input
and returns size of circle part
example of input
bcabcab
example of output
3
*/
int HasCirclePartTask(std::string in_filename, std::string out_filename) {
	std::ifstream input;
	if (!OpenFile(input, in_filename)) return 1;
	std::string input_str = GetInputString(input);
	std::ofstream output;
	output.open(out_filename);
	output << HasCircleSubstr(input_str).size();
	return 0;
}

/*
ZFunctionTask takes string from input
and gives to output info about Z-function for string
*/
int ZFunctionTask(std::string in_filename, std::string out_filename) {
	std::ifstream input;
	if (!OpenFile(input, in_filename)) return 1;
	std::string input_str = GetInputString(input);
	std::ofstream output;
	output.open(out_filename);
	std::vector<size_t> z_vector = ZFunction(input_str);
	for (size_t i : z_vector) {
		output << i << " ";
	}
	return 0;
}

/*
MirrorFuncTask takes number of objects and M variants which
object can take
and return of variants of palindroms
input example
6 2
1 1 2 2 1 1
output example
3 5 6
*/
int MirrorFuncTask(std::string in_filename, std::string out_filename) {
	std::ifstream input;
	if (!OpenFile(input, in_filename)) return 1;
	int NumOfObjects = 0;
	input >> NumOfObjects;
	int M = 0;
	input >> M;
	std::vector<int> numbers;
	numbers.reserve(NumOfObjects);
	while (NumOfObjects > 0) {
		int num;
		input >> num;
		numbers.push_back(num);
		input.get();
		--NumOfObjects;
	}
	std::ofstream output;
	output.open(out_filename);
	std::vector<int> ans = MirrorFunc(numbers);
	for (size_t i = ans.size(); i > 0; --i) {
		output << ans[i - 1] << " ";
	}
	return 0;
}

/*
AllPolindromsTask takes string and counts all polindroms
in string
input example
aba
outpeut example
4 (a, b, a, aba)
*/
int AllPolindromsTask(std::string in_filename, std::string out_filename) {
	std::ifstream input;
	if (!OpenFile(input, in_filename)) return 1;
	std::string input_str = GetInputString(input);
	std::ofstream output;
	output.open(out_filename);
	int ans = PolySubs(input_str);
	output << ans;
	return 0;
}