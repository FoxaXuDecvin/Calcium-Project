#pragma once
#include"TextProces.h"
#include"Verinfo.h"

//Includer Var Space

using namespace std;

string parameterGet;
string readbuffer;
string readbufferA;
string readbufferB;
string readbufferCMDVAR;

string cmdbuffer;
string rescmdbuffer;
string ResVarp;


string resinclude;

string RunScript = "NULL";

string VarExtendAPI;

//NET API
string GetFilePath(void);
const string NETUpdateAPI = "https://calciumservices.foxaxu.com/UpdateAPI/index.txt";
const string RunTime = GetFilePath() + "/CalciumRunTime";
const string UsingPath = GetFilePath() + "/CalciumRunTime/Using";
const string RunTemp = GetFilePath() + "/CalciumRunTime/Temp";

//END
int TransCheckAPI = 0;

int sizebuffer;
int numbuffer,numbufferA, numbufferB;
int resfileline;

int paragetsize;

int afterRollExit = 0;

int charnxmark = 0;

int ScriptLine = 1;

int ListWARNING = 0;

int ReturnDATA = 0;

int NoticeBoxMode = 1; // 1 - Output  0 - Close All Output

int ReadScript = 0;

int getFsize, getESize;

int cfg_maxerror,now_error = 0;
//Base
int numbufferC, PartSizeA;
string readbufferC, readbufferD, tempInfo;

//Text
string YearInfo = "2022-2023";

void clmSpace(void) {
	readbuffer = readbufferA = readbufferB = readbufferCMDVAR = "";
	numbufferC = PartSizeA = 0;
    readbufferC = readbufferD = tempInfo = "";
	sizebuffer = numbuffer = numbufferA = numbufferB = 0;
	return;
}

//LoadConfig
string GetFilePath(void);
const string cfgfile = GetFilePath() + "/Calcium~Config.cfg";

string cfg_autoupdate;
string cfg_defaultrun="notset";