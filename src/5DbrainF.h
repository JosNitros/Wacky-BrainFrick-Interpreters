#ifndef _5DBRAINF_H
#define _5DBRAINF_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "common.h"

void runCpp5dBF(std::string& inputString);

struct timeline {
	std::vector<char*> ptrs;
	char* memory;
	char* instructionPtr;
	std::stack<char*> returnIndex = {};
	std::vector<char*> history = {};

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
		returnIndex = std::move(other.returnIndex);
		history = std::move(other.history);
		other.memory = nullptr;
		other.instructionPtr = nullptr;
		other.history = {};
	}

	timeline& operator=(const timeline&) = delete;
	timeline& operator=(timeline&& other) noexcept {
		memory = std::move(other.memory);
		ptrs = std::move(other.ptrs);
		returnIndex = std::move(other.returnIndex);
		history = std::move(other.history);
		other.memory = nullptr;
		other.instructionPtr = nullptr;
		other.history = {};
		return *this;
	}

	~timeline() {
		delete[] memory;
		for (char* h : history) {
			delete[] h;
		}
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

		std::vector<char*> newHistory;
		for (char* ptr : history) {
			char* t = new char[BF_MEM_SIZE];
			for (unsigned int i = 0; i < BF_MEM_SIZE; i++) {
				t[i] = ptr[i];
			}
			newHistory.push_back(t);
		}

		out.ptrs = std::move(newPtrs);
		out.instructionPtr = instructionPtr;
		out.returnIndex = returnIndex;
		out.history = std::move(newHistory);
		return out;
	}

	void advance(int &index);
};

#endif