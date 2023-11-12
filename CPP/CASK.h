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