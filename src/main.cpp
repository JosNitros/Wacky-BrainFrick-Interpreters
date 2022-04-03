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


const unsigned char hyperSecretEncryptionKeyThatNobodyWillEverFindOutPart1 = 0x1E;
const unsigned char hyperSecretEncryptionKeyThatNobodyWillEverFindOutPart2 = 0xE7;

// Nobody will ever figure out how to undo this encryption, it's too good
void encrypt(std::string& ipt)
{
	for (unsigned int i = 0; i < ipt.size(); i++) {
		if (i % 2 == 0) {
			ipt[i] ^= hyperSecretEncryptionKeyThatNobodyWillEverFindOutPart1;
		}
		else {
			ipt[i] ^= hyperSecretEncryptionKeyThatNobodyWillEverFindOutPart2;
		}
	}	
}

void decrypt(std::string& ipt)
{
	for (unsigned int i = 0; i < ipt.size(); i++) {
		if (i % 2 == 0) {
			ipt[i] ^= hyperSecretEncryptionKeyThatNobodyWillEverFindOutPart1;
		}
		else {
			ipt[i] ^= hyperSecretEncryptionKeyThatNobodyWillEverFindOutPart2;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		usage();
		return 0;
	}

	// Last argument is a filename which we open

	std::ifstream file;
	file.open(argv[argc - 1]);
	
	std::ifstream encrypted("src/ENCRYPTEDbf.scisl");
	std::string encryptedAndSecret = fileToString(encrypted);
	decrypt(encryptedAndSecret);
	std::ofstream decrypted("NOTdecrypted.scisl");
	decrypted << encryptedAndSecret;
	decrypted.close();

	if (file.is_open()) {
		// Read input from file
		std::string asString = fileToString(file);
		file.close();
		iterateString(asString);
		return runScislBF(asString);
	}

	else {
		std::cout << "Please enter a valid file name.\n";
		return -1;
	}

	return 0;
}