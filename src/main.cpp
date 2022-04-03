#include <iostream>
#include <fstream>

#include "brainF.h"
#include "scislBF.h"

void usage() {

}

std::string fileToString(std::ifstream& file) {
	std::string opt = "";

	if (!file.is_open()) {
		return "";
	}

	//thanks cppreference https://www.cplusplus.com/reference/istream/istream/seekg/
	file.seekg(0, file.end);
	size_t size = file.tellg();
	file.seekg(0, file.beg);

	opt.resize(size);
	file.read(opt.data(), size);

	return opt;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		usage();
		return 0;
	}

	// Last argument is a filename which we open

	std::ifstream file;
	file.open(argv[argc - 1]);
	
	
	if (file.is_open()) {
		// Read input from file
		std::string asString = fileToString(file);
		iterateString(asString);
    return runScislBF(asString);
	}

	else {
		std::cout << "Please enter a valid file name.\n";
		return -1;
	}

	return 0;
}