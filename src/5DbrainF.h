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

	timeline() = delete;

	timeline(char* instructions) {
		memory = new char[30000];
		instructionPtr = instructions;
		ptrs.push_back(memory);
	}

	timeline(const timeline& ) = delete;
	timeline(timeline&& other) noexcept {
		memory = std::move(other.memory);
		ptrs = std::move(other.ptrs);
		other.memory = nullptr;
		other.instructionPtr = nullptr;
	}

	timeline& operator=(const timeline&) = delete;
	timeline& operator=(timeline&& other) noexcept {
		memory = std::move(other.memory);
		ptrs = std::move(other.ptrs);
		other.memory = nullptr;
		other.instructionPtr = nullptr;
	}

	~timeline() {
		delete[] memory;
	}

	void advance();
};

#endif