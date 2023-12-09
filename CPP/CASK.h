#pragma once
#include"TextProces.h"
// Calcium Socket API

string SocketAPI_GETSYS(void) {
	if (checkChar(RunPlatfom, "Windows") == 1) {
		return "win";
	}
	if (checkChar(RunPlatfom, "Linux") == 1) {
		return "lux";
	}
	return "unknown";
}

string SocketAPI_GETPATH(void) {
	char bufferC[DEFC_SHORT_1];
	getcwd(bufferC, DEFC_SHORT_1);
	return bufferC;
}

bool ExistFolder_check(string dir) {
	string tmpDoct = dir + pathsign + "test~" + to_string(SpawnRandomNum(1,999999)) + "~.mark";

	if (createmark(tmpDoct, "nWn")) {
		remove(tmpDoct.c_str());
		return true;
	}
	else {
		remove(tmpDoct.c_str());
		return false;
	}
}

bool boxrmdir(string dir) {
	dir = ReplaceChar(dir, "\\", "/");

	removeDirectoryAPIX(dir.c_str());

	//cout << "Remove Directory :  " << dir << endl;

	if (ExistFolder_check(dir)) {
		return false;
	}
	else {
		return true;
	}
}

bool boxmkdir(string dir) {
	dir = ReplaceChar(dir, "\\", "/");

	foldercreateapi(dir.c_str());

	//cout << "Remove Directory :  " << dir << endl;

	if (ExistFolder_check(dir)) {
		return true;
	}
	else {
		return false;
	}
}

int getdocmax(string file) {
	int maxread = 1;
    BackCheckRUN:
	string ReadNULLCheck = LineReader(file, maxread);
	if (ReadNULLCheck == "overline") {
		maxread--;
		return maxread;
	}
	maxread++;
	goto BackCheckRUN;
}

void typetext(string file) {
	if (check_file_existence(file)) {
		int maxdocsize = getdocmax(file);

		maxdocsize++;

		for (int startRoll = 1; maxdocsize != startRoll; startRoll++) {
			cout << LineReader(file, startRoll) << endl;
		}
		return;
	}
	else {
		cout << "ERROR FILE NOT EXIST : " << file << endl;
		return;
	}
}