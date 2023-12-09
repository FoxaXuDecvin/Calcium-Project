#pragma once
#include<unistd.h>
#include<string>
#include<iostream>
#include<dirent.h>
#include"curl/curl.h"
#include"sys/stat.h"

const std::string pathsign = "/";
string RunPlatfom = "Linux (GCC 64Bit)";//Must Include Windows/Linux one

//Linux s   Windows  ms
void sleepapi(int num) {
	sleep(num);
	return;
}

void cleanConsole() {
	system("clear");
}

void foldercreateapi(string dir) {
	mkdir(dir.c_str(),0755);
}

//Notice
//Use GCC Add Agrv :  -l curl
//Example URLDown("https://res.foxaxu.com/softwarecdn/FXROOTCert.zip","FXROOTCERT.zip");

//Design For Linux
bool check_file_existenceA(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		return true;
	}
	else {
		return false;
	}
}

//API--------------------------
//�����ļ����ݽ��պ���
size_t dl_req_reply(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	FILE *fp = (FILE *)user_p;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	//cout << (char *)buffer << endl;
	return return_size;
}

//http GET请求文件下载  
CURLcode dl_curl_get_req(const std::string &url, std::string filename)
{
	//int len = filename.length();
	//char* file_name = new char(len + 1);//char*最后有一个结束字符\0
	//strcpy_s(file_name, len + 1, filename.c_str());

	const char* file_name = filename.c_str();
	char* pc = new char[1024];//足够长
	strcpy(pc, file_name);

	FILE *fp = fopen(pc, "wb");

	//curl初始化  
	CURL *curl = curl_easy_init();
	// curl返回值 
	CURLcode res;
	if (curl)
	{
		//设置curl的请求头
		struct curl_slist* header_list = NULL;
		header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		//不接收响应头数据0代表不接收 1代表接收
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);

		//设置请求的URL地址 
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		//设置ssl验证
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		//CURLOPT_VERBOSE的值为1时，会显示详细的调试信息
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		//设置数据接收函数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &dl_req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		//设置超时时间
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6); // set transport and time out time  
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

		// 开启请求  
		res = curl_easy_perform(curl);
	}
	// 释放curl 
	curl_easy_cleanup(curl);
	//释放文件资源
	fclose(fp);

	return res;
}

//TOOLS
int checkCharN(string text,string chechchar ) {
	const char* c = chechchar.c_str();

	if (text.find(c) != string::npos) {
		return 1;
	}
	else {
		return 0;
	}
}
string ReplaceCharN(string info, string replaceword, string nword) {
	//cout << "New Replace :  _" << info << "_  _" << replaceword << "_  _" << nword << "_" << endl;
	int checkanti = checkCharN(info, replaceword);
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

//------------------------------
//0-FAILED
//1-TRUE
int URLDown(string URL, string Save) {
	Save = ReplaceCharN(Save,"\\","/");

	dl_curl_get_req(URL, Save);
	if (check_file_existenceA) {
		return 1;
	}
	else {
		return 0;
	}
}

//GetFilePath
// Resource File
string GetFilePath(void) {
	char szBuf[250];
	char szPath[250];

	memset(szBuf, 0x00, sizeof(szBuf));
	memset(szPath, 0x00, sizeof(szPath));

	getcwd(szBuf, sizeof(szBuf) - 1);
	//printf("buf:%s\n", szBuf);

	int ret = readlink("/proc/self/exe", szPath, sizeof(szPath) - 1);
	//printf("ret:%d\n", ret);
	//printf("path:%s\n", szPath);

	string ReplaceChar(string info, string replaceword, string nword);
	string DATA = ReplaceChar(szPath,"\\","/");

    string tempdata,outdata;
    int numbuffer = DATA.size();
    int baseNum=-1;

    while(true){
        tempdata = DATA[numbuffer];
        if (tempdata == "/") break;
        numbuffer--;
    }
    numbuffer--;
    while(baseNum != numbuffer){
        baseNum++;
        outdata = outdata + DATA[baseNum];
    };

	return outdata;
}

string GetFileName(void) {
	char szBuf[250];
	char szPath[250];

	memset(szBuf, 0x00, sizeof(szBuf));
	memset(szPath, 0x00, sizeof(szPath));

	getcwd(szBuf, sizeof(szBuf) - 1);
	//printf("buf:%s\n", szBuf);

	int ret = readlink("/proc/self/exe", szPath, sizeof(szPath) - 1);
	//printf("ret:%d\n", ret);
	//printf("path:%s\n", szPath);

	string ReplaceChar(string info, string replaceword, string nword);
	string DATA = ReplaceChar(szPath, "\\", "/");


	return DATA;
}


void Getfilepath(const char *path, const char *filename,  char *filepath)
{
    strcpy(filepath, path);
    if(filepath[strlen(path) - 1] != '/')
        strcat(filepath, "/");
    strcat(filepath, filename);
	//printf("path is = %s\n",filepath);
}
 
bool removeDirectoryAPIXCGI(const char* path)
{
    DIR *dir;
    struct dirent *dirinfo;
    struct stat statbuf;
    char filepath[256] = {0};
    lstat(path, &statbuf);
    
    if (S_ISREG(statbuf.st_mode))//判断是否是常规文件
    {
        remove(path);
    }
    else if (S_ISDIR(statbuf.st_mode))//判断是否是目录
    {
        if ((dir = opendir(path)) == NULL)
            return 1;
        while ((dirinfo = readdir(dir)) != NULL)
        {
            Getfilepath(path, dirinfo->d_name, filepath);
            if (strcmp(dirinfo->d_name, ".") == 0 || strcmp(dirinfo->d_name, "..") == 0)//判断是否是特殊目录
            continue;
            removeDirectoryAPIXCGI(filepath);
            rmdir(filepath);
        }
        closedir(dir);
    }
    return 0;
}

bool removeDirectoryAPIX(const char* path){
	int rdapi = removeDirectoryAPIXCGI(path);
	rmdir(path);
	return rdapi;
}