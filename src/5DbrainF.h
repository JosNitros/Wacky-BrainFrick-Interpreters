#ifndef _5DBRAINF_H
#define _5DBRAINF_H
#include <iostream>
#include <fstream>
#include <vector>

#include "common.h"

void runCpp5dBF(std::string& inputString);

struct timeline {
	std::vector<char*> ptrs;
	char* memory;
	char* instructionPtr;

	timeline() = delete;

	timeline(char* instructions) {
		memory = new char[BF_MEM_SIZE];
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

	timeline copy() {
		timeline out(nullptr);
		for (unsigned int i = 0; i < BF_MEM_SIZE; i++) {
			out.memory[i] = memory[i];
		}

		std::vector<char*> newPtrs;
		for (char* ptr : ptrs) {
			newPtrs.emplace_back(ptr - memory + out.memory);
		}

		out.ptrs = std::move(newPtrs);
		out.instructionPtr = instructionPtr;
		return out;
	}

	void advance();
};

#endif