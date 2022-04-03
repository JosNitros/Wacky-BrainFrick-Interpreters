#include "scislBF.h"

#include "../scisl/compiler/compiler.h"
#include "../scisl/interoperability/tables.h"
#include "../scisl/runtime/stl.h"

#include <iostream>

#include "common.h"

scisl::program* bf = nullptr;

void sresize(scisl::program& p, const scisl::instruction& instr) {
	scisl::value& str = instr.arguments[0].getValue();
	scisl::value& size = instr.arguments[1].getValue();
	std::string* rstr = (std::string*)(str.val);
	rstr->resize(SCISL_CAST_INT(size.val));
}

void getChr(scisl::program& p, const scisl::instruction& instr) {
	scisl::value& chr = instr.arguments[0].getValue();

	std::string c;
	std::cin >> c;
	if (c.size() == 0) {
		chr = 0;
	}
	else {
		chr = c[0];
	}
}

void pop(scisl::program& p, const scisl::instruction& instr) {
	scisl::value& stk = instr.arguments[0].getValue();
	scisl::value& ret = instr.arguments[1].getValue();

	std::string* s = (std::string*)(stk.val);
	int* magic = (int*)(s->data() + s->size() - 4);
	ret = *magic;
	*s = s->substr(0, s->size() - 4);
}

void push(scisl::program& p, const scisl::instruction& instr) {
	scisl::value& stk = instr.arguments[0].getValue();
	scisl::value& v = instr.arguments[1].getValue();

	std::string* s = (std::string*)(stk.val);
	s->resize(s->size() + 4);
	int* magic = (int*)(s->data() + s->size() - 4);
	*magic = SCISL_CAST_INT(v.val);
}

int initScisl() {
	std::string tmp = "";
	scisl::registerVar("inpt", tmp);
	scisl::defineMacro("BF_MEM_SIZE", std::to_string(BF_MEM_SIZE));
	scisl::registerFunc("resize", sresize, 2, 2, "si", scisl::type::error, SCISL_F_NO_JMP);
	scisl::registerFunc("cin", getChr, 1, 1, "n", scisl::type::error, SCISL_F_NO_JMP);
	scisl::registerFunc("pop", pop, 2, 2, "si", scisl::type::error, SCISL_F_NO_JMP);
	scisl::registerFunc("push", push, 2, 2, "si", scisl::type::error, SCISL_F_NO_JMP);

	bf = scisl::compile("NOTdecrypted.scisl");
	std::remove("NOTdecrypted.scisl");

	if (bf == nullptr) return -1;
	//bf->decompile("src/DECOMP_bf.scisl");

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