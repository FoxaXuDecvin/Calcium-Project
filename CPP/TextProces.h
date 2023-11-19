#pragma once
#include"Includer.h"
#include"VarSpace.h"

using namespace std;
//TEXT READ


//COPYRIGHT FOXAXU SOFTWARE TEAM
// Text command Process
// Cpp Includer

//DEFIND
int checkChar(string text, string chechchar);

//Only Support Read 1 Char Size,Read Size A"B$C "+$ = B
bool check_file_existence(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        return true;
    } else {
        return false;
    }
}

//Read Env NEW
string PartRead(string Info, string StartMark, string EndMark) {
	clmSpace();
	int MaxInfoSize = Info.size();
	int startmarkadd, endmarkadd,readptr;
	string readbufferPR;
	readptr = 0;

	if (StartMark == "$FROMSTART$") {
		startmarkadd = 0;
		goto SKIPGETMARKSTART;
	}

	//GetStart
	for (; readbufferPR != StartMark; readptr++) {
		if (readptr > MaxInfoSize) {
			return "sizeoutStart";
		}
		readbufferPR = Info[readptr];
	}
	
	startmarkadd = readptr;

	SKIPGETMARKSTART:
	readbufferPR = "";
	//GetEnd
	for (; readbufferPR != EndMark; readptr++) {
		if (readptr > MaxInfoSize) {
			return "sizeoutEnd";
		}
		readbufferPR = Info[readptr];
	}

	endmarkadd = readptr;

	//cout << "Start :  " << startmarkadd << "  End :  " << endmarkadd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferPR = "";
	endmarkadd--;
	for (readptr = startmarkadd; readptr != endmarkadd; readptr++) {
		readbufferPR = readbufferPR + Info[readptr];
	}

	return readbufferPR;
}

//Read Env NEW PART
//Use StartMark
string PartReadA(string Info, string StartMark, string EndMark,int RPartSizeA) {
	//Anti Search All
	clmSpace();
	readbufferA = StartMark + EndMark;
	if (checkChar(Info, readbufferA) == 1) {
		return "";
	}

	int MAXSIZEA = Info.size();
	int readptr = 0;
	PartSizeA = RPartSizeA;
	int cbuffer = 0;

	int getStart, getEnd , getcurrent = 0;

	//FindStart
	if (StartMark == EndMark) {
		PartSizeA = PartSizeA * 2;
		PartSizeA--;
		PartSizeA--;
	}

	while (PartSizeA != getcurrent) {
		for (; readbufferC != StartMark; readptr++) {
			readbufferC = Info[readptr];
			if (readbufferC == StartMark) {
				getcurrent++;
			}
			//cout << "Read :  " << readptr << "Data :  " << readbufferC << endl;
			if (readptr > MAXSIZEA)return "pra.failed mark";
		}
		
		//cout << "A :  " << readbufferC << "  B :  " << getcurrent << endl;
		readbufferC = "";
	}
	//cout << "Start :  " << readptr << "  PartSA :  " << PartSizeA << endl;

	//GetStart
	for (; readbufferD != StartMark; readptr++) {
		if (readptr > MAXSIZEA) {
			return "sizeoutStart";
		}
		readbufferD = Info[readptr];
	}

	getStart = readptr;

SKIPGETMARKSTART:
	readbufferD = "";
	//GetEnd
	for (; readbufferD != EndMark; readptr++) {
		if (readptr > MAXSIZEA) {
			return "sizeoutEnd";
		}
		readbufferD = Info[readptr];
	}

	getEnd = readptr;

	//cout << "Start :  " << startmarkadd << "  End :  " << endmarkadd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferD = "";
	getEnd--;
	for (readptr = getStart; readptr != getEnd; readptr++) {
		readbufferD = readbufferD + Info[readptr];
	}

	return readbufferD;

}


//ReadSize
// FoxaXu good work 3 = Fox
string SizeRead(string Info, int Size) {
	clmSpace();
	if (Size > Info.size()) {
		return "SizeRead.OverSize";
	}

	string TempInfo;
	for (int ReadCharSize = 0; ReadCharSize != Size; ReadCharSize++) {
		TempInfo = TempInfo + Info[ReadCharSize];
	}

	return TempInfo;
}

//Read Size from End
// This is FoxaXu 4=xaXu
string EndSizeRead(string Info, int LateSize) {
	clmSpace();
	int InfoSize = Info.size();
	int EndAddress = InfoSize - LateSize;
	if (EndAddress < 0) {
		return "EndSizeRead.LateSizeOverSmall";
	}
	string TempInfo,ReadChar;

	for (int LateRead = InfoSize; LateRead != EndAddress; LateRead--) {
		ReadChar = Info[LateRead];
		TempInfo = TempInfo + ReadChar;
	}

	return TempInfo;
}

//Get Char Address int
// ABC$DEFG$
int TextGetSizeAddress(string Info, string MarkSize, int NumBit) {
	clmSpace();
	int MaxSizeInfo = Info.size();
	int CurrentNumBit = 0;
	int StartRead = 0;
	string TempInfo, charRead;

	while (CurrentNumBit != NumBit) {
		for (int EndRead; charRead != MarkSize; StartRead++) {
			charRead = Info[StartRead];
		}
		CurrentNumBit++;
	}

	return StartRead;
}

//Char Size Read
//Example ABCDEFG S=C E=F DE
string PartReadSize(string Info, int StartSize, int EndSize) {
	clmSpace();
	StartSize--; EndSize--;
	int MaxInfoSize = Info.size();
	if (StartSize > EndSize) {
		return "PartReadSize.StartOverThanEnd";
	}
	if (StartSize == EndSize) {
		return "";
	}
	if (EndSize > MaxInfoSize) {
		return "PartReadSize.EndSizeOverMaxinfo";
	}
	int CurrentSize = StartSize;

	string TempInfo, charRead;
	while (CurrentSize <= EndSize) {
		charRead = Info[CurrentSize];
		TempInfo = TempInfo + charRead;
		CurrentSize++;
	}

	return TempInfo;
}

//API For LineReader
int CountLines(string filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename.c_str());
	if (ReadFile.fail())
	{
		return 0;
	}
	else
	{
		while (getline(ReadFile, tmp, '\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}

//Read LineSize
//Like : 
//
//      #Calcium
//      BEFORE
//      FOXAXU
//      After
//
//Read  :
//
//      LineReader(ExampleFile,3) return FOXAXU
string LineReader(string File, int line_number) {
	clmSpace();
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(File.c_str());
	lines = CountLines(File);

	if (line_number <= 0)
	{
		return "LineError";
	}
	if (file.fail())
	{
		return "ReadFailed";
	}
	if (line_number > lines)
	{
		return "overline";
	}
	while (getline(file, temp) && i < line_number - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

int checkChar(string text,string chechchar ) {
	const char* c = chechchar.c_str();

	if (text.find(c) != string::npos) {
		return 1;
	}
	else {
		return 0;
	}
}

string cutlineblockA(string lines, string cutmark, int line) {
	string backapi;

	if (checkChar(lines, cutmark) == 0) {
		return "NUL";
	}

	char* readcut = NULL;

	char Texts[65535] = "a";
	char CUMark[65535] = "a";

	strcpy(Texts, lines.c_str());
	strcpy(CUMark, cutmark.c_str());

	int cutrecord = 1;
	char* token = strtok(Texts, CUMark);
	if (token == NULL) {
		backapi = "";
		return backapi;
	}

	if (cutrecord == line) {

		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}

NextRollCR:
	if (cutrecord == line) {
		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}
	if (token == NULL) {
		backapi = "";
		return backapi;
	}
	cutrecord++;
	token = strtok(NULL, CUMark);
	goto NextRollCR;
}

string HeadSpaceClean(string Info) {
	int maxCSize = Info.size();
	string readMCS, tempInfo;
	int currentFit;

	//cout << "Max C Size :  _" << maxCSize << endl;
	for (currentFit = 0; currentFit < maxCSize; currentFit++) {
		readMCS = Info[currentFit];
		//cout << "Read MCS :  _" << readMCS << endl;
		if (readMCS == " ") {}
		else {
			while (currentFit < maxCSize) {
				//cout << "Trans Add : _" << Info[currentFit] << endl;
				tempInfo = tempInfo + Info[currentFit];
				currentFit++;
			}
		}
	}
	return tempInfo;
}

string HeadSpaceCleanA(string Info) {
	int maxCSize = Info.size();
	string readMCS, tempInfo;
	int currentFit;

	//cout << "Max C Size :  _" << maxCSize << endl;
	for (currentFit = 0; currentFit < maxCSize; currentFit++) {
		readMCS = Info[currentFit];
		//cout << "Read MCS :  _" << readMCS << endl;
		if (readMCS == " ") {}
		else {
			while (currentFit < maxCSize) {
				//cout << "Trans Add : _" << Info[currentFit] << endl;
				tempInfo = tempInfo + Info[currentFit];
				if (tempInfo == " ") {
					return tempInfo;
				}
				currentFit++;
			}
		}
	}
	return tempInfo;
}

int charTotal(string info,string markchar){
	int charsize = info.size();
	int totalget = 0;
	for(int readsize = 0;charsize != readsize;readsize++){
		readbuffer = info[readsize];
		if (readbuffer == markchar){
			totalget ++;
			continue;
		}
		else {
			continue;
		}
	}
	return totalget;
}

//Replace Char
string ReplaceChar(string info, string replaceword, string nword) {
	//cout << "New Replace :  _" << info << "_  _" << replaceword << "_  _" << nword << "_" << endl;
	int checkanti = checkChar(info, replaceword);
	if (checkanti == 1) {
		std::string dst_str = info;
			std::string::size_type pos = 0;
		while ((pos = dst_str.find(replaceword)) != std::string::npos)
		{
			dst_str.replace(pos, replaceword.length(), nword);
		}
		//cout << "Return Data :  _" << dst_str <<"_" << endl;
		return dst_str;
	}
	else {
		//cout << "Return Data :  _" << info << "_" << endl;
		return info;
	}
}

void NoticeBox(string info,string title){
	if (NoticeBoxMode == 0) {
		return;
	}
	else {
		cout << "-----------------------------" << title << "------------------------------" << endl;
		cout << info << endl;
		cout << "-------------------------------END--------------------------------" << endl;
		return;
	}
	return;
}

int SpawnRandomNum(int min, int max) {

	string minb, maxb;
	minb = to_string(min);
	maxb = to_string(max);

	//string chars = "Min :  " + minb + "   Max :   " + maxb + "  Bug Report";
	//MessageBox(0, chars.c_str(), "MXBug Report", MB_OK);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max); // Missing
	int outdata = dis(gen);
	
	//string dis_str = to_string(dis(gen));
	//MessageBox(0,dis_str.c_str(),"Bug check",MB_OK);
	
	return dis(gen);
}

string CODETRANS(string INFO) {
	INFO = ReplaceChar(INFO, "\\1", "!");
	INFO = ReplaceChar(INFO, "\\2", "@");
	INFO = ReplaceChar(INFO, "\\3", "#");
	INFO = ReplaceChar(INFO, "\\4", "$");
	INFO = ReplaceChar(INFO, "\\5", "%");
	INFO = ReplaceChar(INFO, "\\6", "^");
	INFO = ReplaceChar(INFO, "\\7", "&");
	INFO = ReplaceChar(INFO, "\\8", "*");
	INFO = ReplaceChar(INFO, "\\9", "(");
	INFO = ReplaceChar(INFO, "\\0", ")");
	INFO = ReplaceChar(INFO, "\\f", ";");
	INFO = ReplaceChar(INFO, "\\y", "\"");
	INFO = ReplaceChar(INFO, "\\d", "");
	INFO = ReplaceChar(INFO, "(OF)", "");
	INFO = ReplaceChar(INFO, "\\\\", "\\");
	return INFO;
}

// -4 == Not Found
int FindCharLine(int startline,string file, string charData) {
	clmSpace();
	while (true) {
		readbufferA = LineReader(file, startline);
		readbufferA = HeadSpaceCleanA(readbufferA);
		if (readbufferA == "overline") {
			return -4;
		}

		if (checkChar(readbufferA, charData) == 1) {
			return startline;
		}
		startline++;
	}
}