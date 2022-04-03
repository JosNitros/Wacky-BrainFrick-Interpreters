#include "5DbrainF.h"
#include <iostream>
#include <fstream>
#include <stack>

std::vector<timeline> timelines;
void advance() {
	for (timeline& line : timelines) {
		line.advance();
	}
}

void timeline::advance() {
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
		for (char* ptr : this->ptrs) {
			++(*ptr);
		}
		break;
	case '-':
		for (char* ptr : this->ptrs) {
			--(*ptr);
		}
		break;
	case '.':
		for (char* ptr : this->ptrs) {
			putchar(*ptr);
		}
		break;
	case ',':
		int c = getchar();
		for (char* ptr : this->ptrs) {
			*ptr = c;
		}
		break;
	case '[': // @TODO
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
	case ']': // @TODO
		//Go back to matching bracket (assume this is skipped over if initial loop condition is false
		if (!returnIndex.empty()) {
			this->instructionPtr = returnIndex.top() - 1;
			//subtract 1 from index since it adds 1 after each iteration
			returnIndex.pop();
		}
		break;
		//@TODO timetravel instructions
	default:
		break;
	}
	this->instructionPtr++;
	// @TODO kill timeline once done executing
}

void runCpp5dBF(std::string inputString) {
	//Initialize buffer
	//HUGE shoutout to BrainFr*ak wikipedia page https://en.wikipedia.org/wiki/
	timeline firstTimeline(inputString.data());

	//use stack to go back to beginning of each loop
	std::stack<int> returnIndex;

	//need index for moving backwards in string when doing loops
	for (currentIndex; currentIndex <= lastIndex; currentIndex++) {
		//Check every possible character
		//std::cout << inputString.at(currentIndex);
		switch (inputString.at(currentIndex)) {
		case '>':
			++ptr;
			break;
		case '<':
			--ptr;
			break;
		case '+':
			++ * ptr;
			break;
		case '-':
			-- * ptr;
			break;
		case '.':
			putchar(*ptr);
			break;
		case ',':
			*ptr = getchar();
			break;
		case '[':
			//skip over loop if value at pointer = 0
			if (!*ptr) {
				//find matching bracket and go past it
				int leftBrackets = 0;
				currentIndex += 1;
				for (currentIndex; (inputString.at(currentIndex) != ']' || leftBrackets != 0); currentIndex++) {
					//std::cout << inputString.at(currentIndex);
					if (inputString.at(currentIndex) == '[') {
						leftBrackets += 1;
					}
					else if (inputString.at(currentIndex) == ']') {
						leftBrackets -= 1;
					}

				}
			}
			else {
				//push returnIndex on stack
				returnIndex.push(currentIndex);
			}
			break;
		case ']':
			//Go back to matching bracket (assume this is skipped over if initial loop condition is false
			if (!returnIndex.empty()) {
				currentIndex = returnIndex.top() - 1;
				//subtract 1 from index since it adds 1 after each iteration
				returnIndex.pop();
			}
			break;

		//huge HUGE shoutout to https://esolangs.org/wiki/5D_Brainfuck_With_Multiverse_Time_Travel

		break;

		}
	}
}