//Calcium Network Framework
//Net and Web
#pragma once
#include"TextProces.h"
#include"Verinfo.h"

using namespace std;

//Back
//   -1 Skip Show
//   -2 Failed to Check
string checkupdate() {
	if (cfg_autoupdate == "false") {
		return "-3";
	}
	readbufferA = GetURLCode(NETUpdateAPI);
	if (readbufferA == "URLError.FailedGet") {
		return "-2";
	}
	if (readbufferA == Str_VerCode) {
		return "-1";
	}
	else {
		return readbufferA;
	}
}

bool optscript(string file,string outfile) {
	if (check_file_existence(file)) {}
	else {
		return false;
	}
	
	ofstream optfiles;
	optfiles.open(outfile);

	readbufferC = "";
	for (int lr=1; readbufferC != "overline";lr++) {

		if (readbufferC != "") {
			optfiles << readbufferC <<endl;
		}

		readbufferC = LineReader_noerror(file,lr);
		readbufferC = HeadSpaceClean(readbufferC);
	}

	optfiles.close();

	return true;
}