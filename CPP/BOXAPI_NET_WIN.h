#pragma once
#include<Windows.h> 
#include<direct.h>
#include <fstream>
#include <io.h>
#include <string>
#include <vector>
//Design For Windows
const std::string pathsign = "\\";

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
	strrchr:�������ܣ�����һ���ַ�c����һ���ַ���str��ĩ�γ��ֵ�λ�ã�Ҳ���Ǵ�str���Ҳ࿪ʼ�����ַ�c�״γ��ֵ�λ�ã���
	���������λ�õĵ�ַ�����δ���ҵ�ָ���ַ�����ô����������NULL��
	ʹ�������ַ���ش����һ���ַ�c��strĩβ���ַ�����
	*/
	(strrchr(szFilePath, '\\'))[0] = 0; // ɾ���ļ�����ֻ���·���ִ�//
	string path = szFilePath;
	return path;
}

string GetFileName(void) {
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr:�������ܣ�����һ���ַ�c����һ���ַ���str��ĩ�γ��ֵ�λ�ã�Ҳ���Ǵ�str���Ҳ࿪ʼ�����ַ�c�״γ��ֵ�λ�ã���
	���������λ�õĵ�ַ�����δ���ҵ�ָ���ַ�����ô����������NULL��
	ʹ�������ַ���ش����һ���ַ�c��strĩβ���ַ�����
	*/
	string path = szFilePath;
	return path;
}

void getFiles(string& dataPath, vector<string>& files)
{
	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	int i = 0;
	if ((hFile = _findfirst(p.assign(dataPath).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
				continue;
			else
				files.push_back(p.assign(dataPath).append("/").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void removeDirectoryAPIX(string dirPath) {
	vector<string> dirFileList;
	getFiles(dirPath, dirFileList);  //��ȡ�����ļ�
	while (!dirFileList.empty())
	{
		string fileName = dirFileList.back(); //�Ӻ���ǰɾ��
		DeleteFile(fileName.c_str()); //һ����ɾ�����ļ�
		dirFileList.pop_back();
	}
	RemoveDirectory(dirPath.c_str()); //ɾ���ļ��У����ļ��в������������ɾ��
	//ԭ�����ӣ�https ://blog.csdn.net/zf0104/article/details/122454940
}