#pragma once
#include"Includer.h"
#include"Verinfo.h"
#include"CalciumKernel.h"

using namespace std;

string usertypebuffer;

int randsize = SpawnRandomNum(1,99999999);

void OpenCaShell(){
    cout << endl;
    cout << "Calcium Shell console" <<endl;
    cout << "Calcium version :  " << CodeName << " " << Str_VerCode << "." << endl;
    cout << "Notice Update:     " << VerNotice << endl;
    cout << "Run Platfom  :  " << RunPlatfom << endl;
    cout << "Command Shell. Seed :  " << randsize << endl;
    cout << "Copyright FoxaXu Software@. " << YearInfo << endl;
    cout << "Try to use Command :  \"help\" to get more info. or use \"endscript\" to exit" <<endl;
    cout << "Github :  https://github.com/FoxaXuDecvin/Calcium-Project" << endl;
    cout << endl;
    BackShell:
    cout << endl;
    cout << "Calcium Shell   $ ";
    getline(cin,usertypebuffer);

    if (SizeRead(usertypebuffer,4) == "-ca "){
        ReadScript = 1;
        if (charTotal(usertypebuffer, "\"") != 2) {
            NoticeBox("Command Format :  -ca \"Example.ca\" .  Run Script", " \"-ca\"  Help");
            goto BackShell;
        }
        readbuffer = PartRead(usertypebuffer,"\"","\"");
        if (check_file_existence(readbuffer)){
            numbuffer = rollscript(readbuffer);
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
        readbufferA = PartReadA(readbuffer, "\"", "\"", 4);
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