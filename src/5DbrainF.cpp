#include "5DbrainF.h"
#include <iostream>
#include <fstream>
#include <stack>

void runCpp5dBF(std::string inputString) {
	//Initialize buffer
	//HUGE shoutout to BrainFr*ak wikipedia page https://en.wikipedia.org/wiki/Brainfuck
	char array[30000] = { 0 };
	char* ptr = array;
	int lastIndex = inputString.length() - 1;
	int currentIndex = 0;
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