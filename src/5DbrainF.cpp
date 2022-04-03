#include "5DbrainF.h"
#include <iostream>
#include <fstream>
#include <stack>

std::vector<timeline> timelines;
void advance(std::string& is) {
	for (int i = 0; i < timelines.size();i++) {
		timeline& line=timelines[i];
		line.advance(i);

		if (i != 0 && line.instructionPtr >= is.data() + is.size()) {
			timelines.erase(timelines.begin() + (i--)); // LOL!!!!
		}
	}
}

void timeline::advance(int& index) {
	switch (*this->instructionPtr) {
	case '>':
		for (char*& ptr : this->ptrs) {
			++ptr;
		}
		break;
	case '<':
		for (char*& ptr : this->ptrs) {
			--ptr;
		}
		break;
	case '+':
	{
		history.push_back(copyMem());

		for (char* ptr : this->ptrs) {
			++(*ptr);
		}
		break;
	}
	case '-':
	{
		history.push_back(copyMem());

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
		history.push_back(copyMem());

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
		timeline cpy = copy();
		timelines.insert(timelines.begin() + index + 1, std::move(cpy));
		timelines[index + 1].instructionPtr++;

		// WE LOVE INVALIDATION, LETS GOO!!
		timeline& cur = timelines[index];

		//then move current one past parenthesis
		int leftParenthesis = 0;
		cur.instructionPtr++;
		for (; *cur.instructionPtr != ')' || leftParenthesis != 0; cur.instructionPtr++) {
			if (*cur.instructionPtr == '(') {
				leftParenthesis += 1;
			}
			else if (*cur.instructionPtr == ')') {
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
		else {
			ptrs = {};
		}
		break;
	case '^':
		if (!(index == 0)) {
			for (char* ptr : ptrs) {
				timelines[index -1].ptrs.push_back(ptr);
			}
		}
		else {
			ptrs = {};
		}
		break;

	case '@':
		if (index + 1 < timelines.size() && timelines[index+1].ptrs.size() > 0) {
			instructionPtr--;
		}
		break;
	default:
		break;
	}
	this->instructionPtr++;
}

void runCpp5dBF(std::string& inputString) {
	//Initialize buffer
	//HUGE shoutout to BrainFr*ak wikipedia page https://en.wikipedia.org/wiki/
	timelines.emplace_back(inputString.data());
	while (timelines[0].instructionPtr < (inputString.data() + inputString.size())) {
		advance(inputString);
	}
}