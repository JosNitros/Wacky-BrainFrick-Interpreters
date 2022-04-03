#ifndef _5DBRAINF_H
#define _5DBRAINF_H
#include <iostream>
#include <fstream>
#include <vector>
void runCpp5dBF(std::string inputString);

struct timeline {
	std::vector<char*> ptrs;
	char* memory;
	char* instructionPtr;

	void advance();
};

#endif