#pragma once
#include"Includer.h"
#include"Verinfo.h"
#include"CalciumKernel.h"
#include"NetworkFrame.h"

using namespace std;

string usertypebuffer;

int randsize = SpawnRandomNum(1,99999999);

void OpenCaShell(){
    shellmode = 1;
    cout << "Calcium Shell Loading... " << endl;
    readbufferA = checkupdate();
    cout << endl;
    cout << "Calcium Shell console. Platfom :  " << RunPlatfom <<endl;
    cout << "Calcium version :  " << CodeName << " " << Str_VerCode << "." << endl;
    cout << "Version Code:     " << VerNotice << endl;
    cout << "File Path :  " << GetFilePath() << endl;
    cout << "Run Path :  " << SocketAPI_GETPATH() << endl;
    cout << "Using Config :  " << cfgfile << endl;
    cout << "Copyright FoxaXu Software@. " << YearInfo << endl;
    cout << "Command :  \"help\" to get more info. or use \"endscript\" to exit" <<endl;
    cout << "Github :  https://github.com/FoxaXuDecvin/Calcium-Project" << endl;
    cout << endl;
    if (readbufferA == "-2") {
        cout << "Failed to Check Update. Please check your internet. Your Version is :  " << Str_VerCode << endl;
    }
    else {
        if (readbufferA == "-1") {
            cout << "No any Update was found.Your Version is :  " << Str_VerCode << endl;
        }
        if (readbufferA == "-3") {
            cout << "Update is Disabled.Your Version is :  " << Str_VerCode << endl;
        }
        else {
            cout << "It`s time to Update your calcium version. New Version :  " << readbufferA << "   is Release Now" << endl;
        }
    }
    cout << endl;
    BackShell:
    cout << endl;
    cout << "Calcium Shell   $ ";
    getline(cin,usertypebuffer);

    if (SizeRead(usertypebuffer,4) == "-ca "){
        ReadScript = 1;
        readbuffer = PartRead(usertypebuffer," ","$FROMEND$");
        readbuffer = ReplaceChar(readbuffer, "\"", "");
        if (check_file_existence(readbuffer)){
            numbuffer = rollscript(readbuffer);
            VarSpace = "varspace;";
            VarSpaceMax = 0;
            if (numbuffer == 1001){
                //Return UnknownError
                cout << "Script Return Error" << endl;
            }
            if (numbuffer == 1002){
                //Return FileDestroy
                cout << "Script Run Error" << endl;
                cout << "Read Failed :  This File is Destroy." <<endl;
                cout << "File : " << RunScript << endl;
            }
            goto BackShell;
        }
        else {
            cout << "File Not Exist :  " << readbuffer << endl;
            cout << "Please Check your type and try again" <<endl;
            goto BackShell;
        }
    }

    if (usertypebuffer == "help"){
        cout << endl;
        cout << "For Calcium Please visit https://calcium.foxaxu.com/help" << endl;
        cout << "Use Command \"help.eula\" \"help.copyright\" \"help.cainfo\"  Get More Info"<<endl;
        cout << "You can use \"endscript\" to Close this Program" << endl;
        goto BackShell;
    }
    if (usertypebuffer == "help.eula"){
        cout << endl;
        cout << "https://calcium.foxaxu.com/eula" <<endl;
        goto BackShell;
    }
    if (usertypebuffer == "help.copyright"){
        cout << endl;
        cout << "Copyright FoxaXu Software@. " << YearInfo <<endl;
        cout << "Calcium Run Platfom. All rights reserved" <<endl;
        cout << "Product Design By FoxaXu." <<endl;
        cout << "Info :  https://calcium.foxaxu.com" << endl;
        goto BackShell;
    }
    if (usertypebuffer == "testchar") {
        readbuffer = "\"1\"\"2\"\"3\"\"4\"";
        readbufferA = PartReadA(readbuffer, "\"", "\"", 1);
        cout << readbufferA << endl;
        goto BackShell;
    }

    cmdbuffer = usertypebuffer;
    numbuffer = CMDCore();
    if (numbuffer == -1){
        return;
    }
    goto BackShell;
}