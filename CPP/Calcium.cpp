#include"TextProces.h"
#include"CalciumShell.h"

using namespace std;

int main(int argc,char* argv[]){
    loadcfg();
    if(argc == 1){
        if (cfg_defaultrun != "notset") {
            if (check_file_existence(cfg_defaultrun)) {
                RunScript = cfg_defaultrun;
                goto SKIPRUNALL;
            }
            else {
                cout << "Failed to Load Default Script" << endl;
                cout << "seems file not exist :  " << cfg_defaultrun << endl;
            }
        }
        OpenCaShell();
        cout << endl;
        return ReturnDATA;
    }

    paragetsize = 0;
    charnxmark = 0;
    cout << endl;

    for(int readargc = 1,fileswitch = 0;readargc != argc;readargc++){
        readbuffer = argv[readargc];
        parameterGet = parameterGet + " " + readbuffer;

        if (fileswitch == 1){
            RunScript = readbuffer;
            fileswitch = 0;
            continue;
        }

        if (readbuffer == "-cascript"){
            fileswitch = 1;
            continue;
        }
        if (readbuffer == "-ca"){
            fileswitch = 1;
            continue;
        }
        if (readbuffer == "-version"){
            charnxmark = 1;
            cout << "Calcium Run Platfom" << endl;
            cout << "Version Info" << endl;
            cout << "Version : " << CodeName << "  " << Str_VerCode << endl;
            cout << "Developer Info :  " << VerNotice << endl;
            cout << "Run Platfom :  " << RunPlatfom << endl;
            cout << "Copyright FoxaXu Software" << endl;
            afterRollExit = 1;
            break;
        }
        if (readbuffer == "-osreg") {
            sysreg_fun();
            afterRollExit = 1;
            break;
        }
        if (readbuffer == "-osunreg") {
            sysunreg_fun();
            afterRollExit = 1;
            break;
        }
        if (readbuffer == "-debug") {
            scriptdebugmode = 1;
            break;
        }
        if (readbuffer == "-offnb") {
            NoticeBoxMode = 0;
            break;
        }
        if (readbuffer == "-opt") {
            fileswitch = 1;
            optmode = 1;
            continue;
        }
        cout << "Unknown Parameter :  " << readbuffer << endl;
    }

    if (charnxmark == 1){
        cout << endl;
    }
    if (afterRollExit == 1){
        return 0;
    }

SKIPRUNALL:
    if (optmode == 1) {
        if (check_file_existence(RunScript)) {}
        else {
            cout << "Cannot Find :  " << RunScript << endl;
            cout << "Check your type and try again" << endl;
            return 0;
        }

        string outopfile = RunScript;

        string tempdata,outbuffer;
        int numbuffer = outopfile.size();
        int baseNum = -1;

        while (true) {
            tempdata = outopfile[numbuffer];
            if (tempdata == ".") break;
            numbuffer--;
        }
        numbuffer--;
        while (baseNum != numbuffer) {
            baseNum++;
            outbuffer = outbuffer + outopfile[baseNum];
        };

        outopfile = outbuffer + cfg_optadd;

        cout << "optimal Mode" << endl;
        cout << "File :  " << RunScript << endl;
        cout << "Out :  " << outopfile << endl;
        sleepapi(1);
        cout << endl;

        if (optscript(RunScript, outopfile)) {
            cout << "File Successfully to Optimal. Save on " << outopfile << endl;
            return 0;
        }
        else {
            cout << "Failed to Optimal. File " << RunScript << endl;
            return 0;
        }

    }

    if (RunScript == "NOSET"){
        cout << "Use \"-cascript/-ca <file>\" Run Script" << endl;
        return 0;
    }
    if(check_file_existence(RunScript)){}
    else {
        cout << "Cannot Find :  " << RunScript << endl;
        cout << "Check your type and try again" << endl;
        return 0;
    }

    int a = rollscript(RunScript);
    if (a == 1001){
        //Return UnknownError
        cout << "Script Return Error" << endl;
    }
    if (a == 1002){
        //Return FileDestroy
        cout << "Script Run Error" << endl;
        cout << "Read Failed :  This File is Destroy." <<endl;
        cout << "File : " << RunScript << endl;
    }
    return ReturnDATA;
}