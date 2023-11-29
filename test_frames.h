#pragma once
#include <string>
#include <cassert>


void TestStringHasher() {
	std::string str = "abacababa"s;
	HashTable hash_table = StringHasher(str);
	assert(EqualSubstrings(hash_table, 1, 5, 3));
	assert(EqualSubstrings(hash_table, 1, 7, 3));
	assert(EqualSubstrings(hash_table, 7, 1, 3));
	assert(EqualSubstrings(hash_table, 2, 6, 2));
	assert(!EqualSubstrings(hash_table, 1, 5, 4));
	assert(!EqualSubstrings(hash_table, 4, 6, 3));
}

void TestCirclePart() {
	std::string str = "bcabcab"s;
	assert(HasCircleSubstr(str).size() == 3);
	assert(HasCircleSubstr("zzz").size() == 1);
	assert(HasCircleSubstr("cvtrcvtrcvtrcv").size() == 4);
	assert(HasCircleSubstr("anhyanhyanhyanhy").size() == 4);
	assert(HasCircleSubstr("y").size() == 1);
	assert(HasCircleSubstr("ygknedtcsewqxxv").size() == 15);
	assert(HasCircleSubstr("").size() == 0);
}

void TestZFunc() {
	assert(ZFunction("abracadabra"s) == std::vector<size_t>({ 0, 0, 0, 1, 0, 1, 0, 4, 0, 0, 1 }));
	assert(ZFunction("ab"s) == std::vector<size_t>({ 0, 0 }));
	assert(ZFunction("a"s) == std::vector<size_t>({ 0 }));
	assert(ZFunction("abrtaberabrtabgabr"s) == std::vector<size_t>({ 0, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 2, 0, 0, 3, 0, 0 }));
}

void TestMirrorFunc() {
	assert(MirrorFunc(std::vector<int>({ 1, 1, 2, 2, 1, 1 })) == std::vector<int>({ 6, 5, 3 }));
	assert(MirrorFunc(std::vector<int>({ 3, 4, 7, 5 })) == std::vector<int>({ 4 }));
	assert(MirrorFunc(std::vector<int>({ 3, 4, 4, 3, 7, 5 })) == std::vector<int>({ 6, 4 }));
	assert(MirrorFunc(std::vector<int>({ 1 })) == std::vector<int>({ 1 }));
	assert(MirrorFunc(std::vector<int>({ 3,3,3,3,3 })) == std::vector<int>({ 5, 4, 3 }));
	assert(MirrorFunc(std::vector<int>({ 3,4,5 })) == std::vector<int>({ 3 }));
	assert(MirrorFunc(std::vector<int>({ 3,3,3 })) == std::vector<int>({ 3, 2 }));
	assert(MirrorFunc(std::vector<int>({ 1,2,3,4,5,6,7,8,9 })) == std::vector<int>({ 9 }));
	assert(MirrorFunc(std::vector<int>({ 1,1,2,2,1,1,3,3,4,5 })) == std::vector<int>({ 10, 9, 7 }));
	assert(MirrorFunc(std::vector<int>({ 99, 54, 22, 22, 54, 99 })) == std::vector<int>({ 6, 3 }));
}

void TestPolySubs() {
	assert(PolySubs("framar") == 8);
	assert(PolySubs("aaa") == 6);
	assert(PolySubs("aba") == 4);
	assert(PolySubs("a") == 1);
	assert(PolySubs("bbbbbb") == 21);
	assert(PolySubs("vvvvvvvv") == 36);
	assert(PolySubs("vavfafvav") == 15);
	assert(PolySubs("ffcc") == 6);
	assert(PolySubs("aaabaa") == 12);
	assert(PolySubs("") == 0);
	assert(PolySubs("abaaba") == 11);
	assert(PolySubs("aa") == 3);
}

void TestFull() {
	TestStringHasher();
	TestCirclePart();
	TestMirrorFunc();
	TestPolySubs();
}