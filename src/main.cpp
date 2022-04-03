#include <iostream>
#include <fstream>

#include "brainF.h"
#include "scislBF.h"
#include "5DbrainF.h"

void usage() {
	std::cout << "Using the command line!!!\n";
	std::cout << "\"filename\" : runs that file using basic C++ interpreter.\n";
	std::cout << "-s \"filename\" : runs that file using Scisl interpreter.\n";
	std::cout << "-M \"filename\" : runs that file using basic C++ interpreter.\n\n";
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
	if (argc <= 1 || argc > 3) {
		usage();
		return 0;
	}


	// Last argument is a filename which we open
	std::ifstream file(argv[argc - 1]);
	if (file.is_open()) {
		std::string asString = fileToString(file);
		if (argc == 2) {
			runCppBF(asString);
		}
		else {
			std::string flag = argv[1];
			if (flag.size() <= 1 || flag.size() > 2 || flag[0] != '-') {
				usage();
			}
			else {
				switch (flag[1])
				{
				case 's':
				{
					std::ifstream encrypted("ENCRYPTEDbf.scisl");
					std::string encryptedAndSecret = fileToString(encrypted);
					encrypted.close();
					decrypt(encryptedAndSecret);
					std::ofstream decrypted("NOTdecrypted.scisl");
					decrypted << encryptedAndSecret;
					decrypted.close();
					return runScislBF(asString);
					break;
				}
				case 'M':
					runCpp5dBF(asString);
					break;
				default:
					usage();
					break;
				}
			}


		}
		file.close();
	}
	else {
		std::cout << "Could not open file " << argv[argc - 1] << '\n';
		return -1;
	}

	return 0;
}