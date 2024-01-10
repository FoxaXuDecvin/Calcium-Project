#pragma once
#include<Windows.h> 
#include<direct.h>
#include <fstream>
#include <io.h>
#include <string>
#include <vector>
#include<ShlObj.h>
//Design For Windows
const std::string pathsign = "\\";
string RunPlatfom = "Windows (MSVC 64Bit)";//Must Include Windows/Linux one

//Linux s   Windows  ms
//Default Use s
void sleepapi(int num) {
	int cutth = num * 1000;
	Sleep(cutth);
	return;
}

void cleanConsole() {
	system("cls");
}

void foldercreateapi(string dir) {
	mkdir(dir.c_str());
}

bool check_file_existenceA(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		return true;
	}
	else {
		return false;
	}
}
//NET CORE

#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")
using namespace std;
LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

//0-FAILED
//1-TRUE
bool URLDown(string URL, string Save) {
	remove(Save.c_str());

	LPCWSTR LcDsp = stringToLPCWSTR(Save);
	LPCWSTR LcURL = stringToLPCWSTR(URL);
	HRESULT applydownload = URLDownloadToFileW(
		nullptr,
		LcURL,
		LcDsp,
		0,
		nullptr
	);
	if (check_file_existenceA(Save)) {
		return true;
	}
	else {
		return false;
	}
	
}

//GetFilePath
// Resource File
string GetFilePath(void) {
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr:函数功能：查找一个字符c在另一个字符串str中末次出现的位置（也就是从str的右侧开始查找字符c首次出现的位置），
	并返回这个位置的地址。如果未能找到指定字符，那么函数将返回NULL。
	使用这个地址返回从最后一个字符c到str末尾的字符串。
	*/
	(strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串//
	string path = szFilePath;
	return path;
}

string GetFileName(void) {
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr:函数功能：查找一个字符c在另一个字符串str中末次出现的位置（也就是从str的右侧开始查找字符c首次出现的位置），
	并返回这个位置的地址。如果未能找到指定字符，那么函数将返回NULL。
	使用这个地址返回从最后一个字符c到str末尾的字符串。
	*/
	string path = szFilePath;
	return path;
}

void removeDirectoryAPIX(string dir) {
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		//cout << "无文件" << endl;
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			removeDirectoryAPIX(newDir.c_str());//先遍历删除文件夹下的文件，再删除空的文件夹
			//cout << newDir.c_str() << endl;
			if (_rmdir(newDir.c_str()) == 0) {//删除空文件夹
				//cout << "delete empty dir success" << endl;
			}
			else {
				//cout << "delete empty dir error" << endl;
			}
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			//cout << file_path.c_str() << endl;
			if (remove(file_path.c_str()) == 0) {//删除文件
				//cout << "delete file success" << endl;
			}
			else {
				//cout << "delete file error" << endl;
			}
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);

	rmdir(dir.c_str());
	return;
}

//WINAPI
int testAdminA() {
	BOOL ISADM = IsUserAnAdmin();
	if (ISADM) {
		return 1;
	}
	else {
		return 0;
	}
}

void sysreg_fun(void) {
	readbufferC = GetFileName();
	int TSAREG = testAdminA();
	if (TSAREG == 1) {
		cout << "Calcium Register" << endl;
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript /ve /t REG_SZ /d \"Calcium Run Script\" /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell /ve /t REG_SZ /d  \"open\" /f");

		//Reg Open
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\open /f");
		
		readbuffer = "reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\open\\command /ve /t REG_SZ /f /d \"" + readbufferC + " -ca \\\"%1\\\"\"";
		system(readbuffer.c_str());

		//Reg Runas
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\runas /f");
		
		readbuffer = "reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\runas\\command /ve /t REG_SZ /f /d \"" + readbufferC + " -ca \\\"%1\\\"\"";
		system(readbuffer.c_str());

		//Reg Debug
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\Debug /f");

		readbuffer = "reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\Debug\\command /ve /t REG_SZ /f /d \"" + readbufferC + " -ca \\\"%1\\\" -debug\"";
		system(readbuffer.c_str());

		//EDIT
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\edit /f");
		system("reg add HKEY_CLASSES_ROOT\\CalciumScript\\shell\\edit\\command /ve /t REG_SZ /f /d \"Notepad.exe \\\"%1\\\"\"");

		system("reg add HKEY_CLASSES_ROOT\\.ca /ve /t REG_SZ /d  \"CalciumScript \" /f");
		system("reg add HKEY_CLASSES_ROOT\\.cascript /ve /t REG_SZ /d  \"CalciumScript \" /f");
		system("reg add HKEY_CLASSES_ROOT\\.casp /ve /t REG_SZ /d  \"CalciumScript \" /f");
		system("reg add HKEY_CLASSES_ROOT\\.capt /ve /t REG_SZ /d  \"CalciumPackage \" /f");

		system("assoc .ca=CalciumScript");
		system("assoc .cascript=CalciumScript");
		cout << "Complete" << endl;
		return;
	}
	cout << "Failed. Please use Administrator" <<endl;
	return;
}

void sysunreg_fun() {
	int TSAREG = testAdminA();
	if (TSAREG == 1) {
		cout << "Calcium UnRegister" << endl;
		cout << "Delete Register" << endl;
		system("reg delete HKEY_CLASSES_ROOT\\CalciumScript /f");
		system("reg delete HKEY_CLASSES_ROOT\\CalciumPackage /f");
		system("reg delete HKEY_CLASSES_ROOT\\.ca /f");
		system("reg delete HKEY_CLASSES_ROOT\\.cascript /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\.ca /f");
		system("reg delete HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\.cascript /f");
		system("reg delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.ca /f");
		system("reg delete HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.cascript /f");
		//删除CAC

		cout << "Complete" << endl;
		return;
	}
	cout << "Failed. Please use Administrator" << endl;
	return;
}