#include "scislBF.h"

#include "../scisl/compiler/compiler.h"
#include "../scisl/interoperability/tables.h"

#include <iostream>

scisl::program* bf = nullptr;

int initScisl() {
	std::string tmp = "";
	scisl::registerVar("inpt", tmp);

	bf = scisl::compile("bf.scisl");

	if (bf == nullptr) return -1;
	bf->decompile("DECOMP_bf.scisl");

	return 0;
}

int runScislBF(std::string& ipt) {
	if (bf == nullptr) {
		int err = initScisl();
		if (err != 0) {
			return -1;
		}
	}

	scisl::updateVar("inpt", ipt);
	bf->curInstr = 0;

	return bf->run();
}