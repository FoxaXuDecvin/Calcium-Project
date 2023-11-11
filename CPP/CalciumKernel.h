#pragma once
#include"TextProces.h"

int CMDCore();

//BackCode
// 1000 - OK
// 1001 - Error
// 1002 - Error File Destroy
int rollscript(string RollFile){
    int ReadScript = 0;
    RunScript = RollFile;
    while (true)
    {
        ReadScript++;
        ScriptLine = ReadScript;
        cmdbuffer = LineReader(RollFile,ScriptLine);
        if(cmdbuffer == "ReadFailed"){
            cout << "Text Engine Read Failed :  File _" << RollFile << "_" <<endl;
            return 1002;
        }
        cmdbuffer = HeadSpaceClean(cmdbuffer);

         if (cmdbuffer == ""){
            //EmptyInfo
            continue;
        }

        if (cmdbuffer == "overline"){
            return 1000;
        }      
        //& is VarMark

        sizebuffer = CMDCore();
        RunScript = RollFile;

        if (sizebuffer == -1) {
            return 1000;
        }
    }

}

//Return 0 -ok
//       1 -FAILED
//      -1 -AutoExit
int CMDCore(){
    rescmdbuffer = cmdbuffer;
    cmdbuffer = TransVar(cmdbuffer);

    //cout << "After Trans CMD BUFFER :  _" << cmdbuffer << "_" << endl;

        if(SizeRead(cmdbuffer,8)=="#Calcium"){
            //Calcium Sign Mark
            return 0;
        }
        if(SizeRead(cmdbuffer,2)=="$$"){
            //calcium Notice
            return 0;
        }
        if(SizeRead(cmdbuffer,4)=="cout"){
            //Output Text
            if (charTotal(cmdbuffer,"\"") != 2){
                coutll();
                cout << "Script Exception. Line: " << to_string(ScriptLine) << " . Cout Command Error :   QUOTATION FORMAT ERROR" << endl;
                coutll();
                return 0;
            }
            readbuffer = PartRead(cmdbuffer,"\"","\"");
            cout << readbuffer << endl;
            return 0;
        }
        if (SizeRead(cmdbuffer,6)=="system"){
            //Win/Linux Console Command
            if (charTotal(cmdbuffer,"\"") != 2){
                coutll();
                cout << "Script Exception. Line: " << to_string(ScriptLine) << " . Cout Command Error :   TOO MANY QUOTATION" << endl;
                coutll();
                return 0;
            }
            readbuffer = PartRead(cmdbuffer,"\"","\"");
            system(readbuffer.c_str());
            return 0;
        }
        if (SizeRead(cmdbuffer,4)=="stop"){
            //Press Enter to continue
            cout << "Press Enter to Continue";
            getchar();
            return 0;
        }
        if (SizeRead(cmdbuffer,9)=="endscript"){
            //Select End Task
            return -1;
        }
        
        if (SizeRead(cmdbuffer,3)=="var"){
            //Create VarSpace
            if(charTotal(cmdbuffer,"&")!=2){
                coutll();
                cout << "Script Exception. Line: " << to_string(ScriptLine) << " . Create Var Error :   SORT FORMAT ERROR" << endl;
                coutll();
                return 0;
            }
            if(charTotal(cmdbuffer,"\"")!=2){
                coutll();
                cout << "Script Exception. Line: " << to_string(ScriptLine) << " . Create Var Error :   SORT FORMAT ERROR" << endl;
                coutll();
                return 0;
            }
            readbufferB = PartRead(cmdbuffer,"&","&");//VarName
            readbufferA = PartRead(cmdbuffer,"\"","\"");//Var CharInfo
            //cout << "Create VarSpace  " << readbufferB << endl;
            //cout << "Create VarSpace Info  " << readbufferA << endl;
            numbuffer = varspaceadd(readbufferB,readbufferA);
            if (numbuffer == 1){
                coutll();
                cout << "Var :  " << readbuffer << "  Create Failed" <<endl;
                coutll();
                return 0;
            }
            return 0;
        }

        if (SizeRead(cmdbuffer,6)=="delete"){
            readbufferA = PartRead(rescmdbuffer,"&","&");//Delvarname
            varspacedelete(readbufferA);
            return 0;
        }

        if (SizeRead(cmdbuffer,4)=="lsvp"){
            cout << VarSpace << endl;
            return 0;
        }

        //Include

        if (SizeRead(cmdbuffer,8)=="#Include"){
            readbufferA = PartRead(cmdbuffer,"\"","\"");
            readbufferA = ReplaceChar(readbufferA,"\";","");

            if(check_file_existence(readbufferA)){}
            else {
                coutll();
                cout << "Failed to Include :  _" << readbufferA << "_." <<endl;
                cout << "Please Check is file exist" <<endl;
                coutll();
                return 0;
            }

            while(true){
                int a = rollscript(readbufferA);
                if (a == 1001){
                    //Return UnknownError
                    coutll();
                    cout << "Include File Return Error" << endl;
                    coutll();
                }
                if (a == 1002){
                    //Return FileDestroy
                    coutll();
                    cout << "Include Run Error" << endl;
                    cout << "Read Failed :  This File is Destroy." <<endl;
                    cout << "Include File : _" << readbufferA << "_" << endl;
                    coutll();
                }
                break;
            }
            return 0;
        }
        coutll();
        cout << "Script Exception. Line: " << to_string(ScriptLine) << " . Unknown Command :   -" << cmdbuffer << "-" << endl;
        cout << "    -In File :  _" << RunScript << "_ -" << endl;
        coutll();
        return 0;
}