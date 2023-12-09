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