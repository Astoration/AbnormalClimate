#include "stdafx.h"
#include "ZeroConsole.h"

ZeroConsole::ZeroConsole() {
	int hCrt;
	FILE* hf;

	AllocConsole();

	hCrt = _open_osfhandle(long(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
	hf = _fdopen(hCrt, "w");

	*stdout = *hf;
	setvbuf(stdout, NULL, _IONBF, 0);
}

ZeroConsole::~ZeroConsole() {

}
