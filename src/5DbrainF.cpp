#include "5DbrainF.h"
#include <iostream>
#include <fstream>
#include <stack>

std::vector<timeline> timelines;
void advance() {
	for (int i = 0; i < timelines.size();i++) {
		timeline& line=timelines[i];
		line.advance(i);
	}
}

void timeline::advance(int& index) {
	switch (*this->instructionPtr) {
	case '>':
		for (char* ptr : this->ptrs) {
			++ptr;
		}
		break;
	case '<':
		for (char* ptr : this->ptrs) {
			--ptr;
		}
		break;
	case '+':
	{
		char* t = new char[BF_MEM_SIZE];
		for (unsigned int i = 0; i < BF_MEM_SIZE; i++) {
			t[i] = memory[i];
		}
		history.push_back(t);

		for (char* ptr : this->ptrs) {
			++(*ptr);
		}
		break;
	}
	case '-':
	{
		char* t = new char[BF_MEM_SIZE];
		for (unsigned int i = 0; i < BF_MEM_SIZE; i++) {
			t[i] = memory[i];
		}
		history.push_back(t);

		for (char* ptr : this->ptrs) {
			--(*ptr);
		}
		break;
	}
	case '.':
		for (char* ptr : this->ptrs) {
			putchar(*ptr);
		}
		break;
	case ',':
	{
		char* t = new char[BF_MEM_SIZE];
		for (unsigned int i = 0; i < BF_MEM_SIZE; i++) {
			t[i] = memory[i];
		}
		history.push_back(t);

		int c = getchar();
		for (char* ptr : this->ptrs) {
			*ptr = c;
		}
		break;
	}
	case '[':
	{
		//skip over loop if value at pointer = 0
		bool allZero = true;
		for (char* ptr : this->ptrs) {
			if (*ptr != 0) {
				allZero = false;
				break;
			}
		}

		if (allZero) {
			//find matching bracket and go past it
			int leftBrackets = 0;
			this->instructionPtr++;
			for (; (*this->instructionPtr != ']' || leftBrackets != 0); this->instructionPtr++) {
				//std::cout << inputString.at(currentIndex);
				if (*this->instructionPtr == '[') {
					leftBrackets++;
				}
				else if (*this->instructionPtr == ']') {
					leftBrackets--;
				}

			}
		}
		else {
			//push returnIndex on stack
			returnIndex.push(this->instructionPtr);
		}
		break;
	}
	case ']':
		//Go back to matching bracket (assume this is skipped over if initial loop condition is false
		if (!returnIndex.empty()) {
			this->instructionPtr = returnIndex.top() - 1;
			//subtract 1 from index since it adds 1 after each iteration
			returnIndex.pop();
		}
		break;
	case '~':
	{
		if (history.size() > 0) {
			delete[] memory;
			memory = history.back();
			history.pop_back();
		}
		break;
	}
	case '(':
	{
		//create new parallel universe below current one (if more universes exist below current one, move them down)
		timelines.insert(timelines.begin() + index + 1, copy());
		timelines[index + 1].instructionPtr++;

		//then move current one past parenthesis
		int leftParenthesis = 0;
		for (; ((*this->instructionPtr) != ']' || leftParenthesis != 0); instructionPtr++) {
			if (*instructionPtr == '(') {
				leftParenthesis += 1;
			}
			else if (*instructionPtr == ')') {
				leftParenthesis -= 1;
			}

		}

		break;
	}
	case ')':
		//if not the main timeline, delete current universe  (if else do nothing)
		if (index != 0) {
			timelines.erase(timelines.begin()+(index--)); // LOL!!!!

		}
		break;
	case 'v':
		if (!(index + 1 >= timelines.size())) {
			for (char *ptr : ptrs) {
				timelines[index + 1].ptrs.push_back(ptr);
			}
		}
		ptrs = {};
		break;
	case '^':
		if (!(index == 0)) {
			for (char* ptr : ptrs) {
				timelines[index -1].ptrs.push_back(ptr);
			}
		}
		ptrs = {};
		break;
	default:
		break;
	}
	this->instructionPtr++;
	// @TODO kill timeline once done executing
}

void runCpp5dBF(std::string& inputString) {
	//Initialize buffer
	//HUGE shoutout to BrainFr*ak wikipedia page https://en.wikipedia.org/wiki/
	timelines.emplace_back(inputString.data());
	while (timelines[0].instructionPtr < (inputString.data() + inputString.size())) {
		advance();
	}
}