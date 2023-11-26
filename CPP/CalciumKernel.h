#pragma once
#include"TextProces.h"
#include"CASK.h"

int CMDCore();

//BackCode
// 1000 - OK
// 1001 - Error
// 1002 - Error File Destroy
int rollscript(string RollFile){
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
         if (SizeRead(cmdbuffer, 1) == ":") {
             //GotoMark
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
//      -1 -AutoExit
int CMDCore(){
    cmdbuffer = HeadSpaceClean(cmdbuffer);
    rescmdbuffer = cmdbuffer;
    cmdbuffer = TransVar(cmdbuffer);

    //cout << "After Trans CMD BUFFER :  _" << cmdbuffer << "_" << endl;
        if (cmdbuffer == "") {
             //EmptyShell
             return 0;
        }
        if (SizeRead(cmdbuffer, 1) == "{") {
            //EmptyShell
            return 0;
        }
        if (SizeRead(cmdbuffer, 1) == "}") {
            //EmptyShell
            return 0;
        }

        //IF
        if (SizeRead(cmdbuffer, 2) == "if") {
            //Run if Else
            if (checkChar(cmdbuffer, "(") == 1) {
                if (checkChar(cmdbuffer, ")") == 1) {
                    //Rule True
                    readbuffer = PartRead(cmdbuffer, "(", ")");
                    readbuffer = CODETRANS(readbuffer);

                    //RunCommand
                    VarExtendAPI = "";
                    cmdbuffer = readbuffer;
                    CMDCore();
                    if (VarExtendAPI == "true") {
                        //RunCommand Box
                        getFsize = FindCharLine(ReadScript, RunScript, "{");
                        if (getFsize == -4) {
                            NoticeBox("If Error -> No Mark", "ERROR");
                            return 0;
                        }
                        getFsize++;

                        getESize = FindCharLine(ReadScript, RunScript, "}");
                        if (getESize == -4) {
                            NoticeBox("If Error -> No Mark", "ERROR");
                            return 0;
                        }
                        
                        //RollCommand
                        clmSpace();
                        while (true) {
                            if (getFsize == getESize)break;
                            readbufferA = LineReader(RunScript, getFsize);
                            readbufferA = CODETRANS(readbufferA);
                            cmdbuffer = readbufferA;
                            numbufferA = CMDCore();

                            if (numbufferA == -1) {
                                return -1;
                            }
                            getFsize++;
                        }
                        readbufferA = LineReader(RunScript, getESize);
                        
                        //cout << "END : " << ReadScript << endl;
                        if (checkChar(readbufferA,"}else{") == 1) {
                            getESize++;
                            getESize = FindCharLine(getESize, RunScript, "}");
                            if (getFsize == -4) {
                                NoticeBox("If Error -> No Mark", "ERROR");
                                return 0;
                            }
                            ReadScript = getESize;
                            //cout << "2END : " << ReadScript << endl;
                            return 0;
                        }
                        ReadScript = getESize;
                        return 0;
                    }

                    if (VarExtendAPI == "false") {
                        //FIND ELSE
                        //RunCommand Box
                        getFsize = FindCharLine(ReadScript, RunScript, "}else{");
                        if (getFsize == -4) {
                            getFsize = FindCharLine(ReadScript, RunScript, "}");
                            ReadScript = getFsize;
                            return 0;
                        }
                        getFsize++;

                        getESize = FindCharLine(ReadScript, RunScript, "}");
                        if (getFsize == -4) {
                            NoticeBox("If Error -> No Mark", "ERROR");
                            return 0;
                        }

                        while (true) {
                            if (getFsize == getESize)break;
                            readbufferA = LineReader(RunScript, getFsize);
                            readbufferA = CODETRANS(readbufferA);
                            cmdbuffer = readbufferA;
                            numbufferA = CMDCore();

                            if (numbufferA == -1) {
                                return -1;
                            }
                            getFsize++;
                        }
                        readbufferA = LineReader(RunScript, getESize);

                        //cout << "END : " << ReadScript << endl;
                        ReadScript = getESize;
                        return 0;
                    }
                }
            }
            
            NoticeBox("If Command error  ->  Format Error","ERROR");
            return 0;
        }

        if (SizeRead(cmdbuffer, 2) == "cp") {
            if (charTotal(cmdbuffer, "\"") != 4) {
                NoticeBox("Comparison Error -> Format Error", "ERROR");
                return 0;
            }
            readbufferA = CODETRANS(PartReadA(cmdbuffer, "\"", "\"", 1));
            readbufferB = CODETRANS(PartReadA(cmdbuffer, "\"", "\"", 2));
            //TransLate
            //cout << "A : " << readbufferA << "   B : " << readbufferB << endl;
            if (checkChar(cmdbuffer, "==") == 1) {
                //Same
                if (readbufferA == readbufferB) {
                    VarExtendAPI = ca_true;
                }
                else {
                    VarExtendAPI = ca_false;
                }
            }
            if (checkChar(cmdbuffer, "!=") == 1) {
                //UnSame
                if (readbufferA == readbufferB) {
                    VarExtendAPI = ca_false;
                }
                else {
                    VarExtendAPI = ca_true;
                }
            }
            

            //R
            return 0;
        }

        //OS
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
            if (charTotal(cmdbuffer, "(") + charTotal(cmdbuffer, ")") >= 2){
                //Command Mode
                if (charTotal(cmdbuffer, "(") + charTotal(cmdbuffer, ")") >= 2) {}
                else{
                    NoticeBox("cout Format Error, Add (MESSAGE)", "ERROR");
                    return 0;
                }
                readbufferA = PartRead(cmdbuffer, "(", ")");//VarCMD
                readbufferA = HeadSpaceCleanA(readbufferA);

                //Clean VarAPI
                VarExtendAPI = "null";
                readbufferA = CODETRANS(readbufferA);
                cmdbuffer = readbufferA;
                numbufferA = CMDCore();

                if (numbufferA == -1) {
                    return -1;
                }

                cout << VarExtendAPI << endl;
                return 0;
            }
            if (charTotal(cmdbuffer, "\"") != 2) {
                NoticeBox("Cout Format Error -> Use \"MESSAGE \"", "ERROR");
                return 0;
            }
            readbuffer = PartRead(cmdbuffer,"\"","\"");
            readbuffer = CODETRANS(readbuffer);
            cout << readbuffer << endl;
            return 0;
        }
        if (SizeRead(cmdbuffer,6)=="system"){
            //Win/Linux Console Command
            if (charTotal(cmdbuffer,"\"") != 2){
                NoticeBox("Script Exception. Line: " + to_string(ScriptLine) + "(Buffer :  " + to_string(ReadScript) + ").Cout Command Error : TOO MANY QUOTATION", "ERROR");
                return 0;
            }
            readbuffer = PartRead(cmdbuffer,"\"","\"");
            readbuffer = CODETRANS(readbuffer);
            numbuffer = system(readbuffer.c_str());
            VarExtendAPI = to_string(numbuffer);
            return 0;
        }
        if (SizeRead(cmdbuffer,4)=="stop"){
            //Press Enter to continue
            if (charTotal(cmdbuffer, "\"") != 2) {
                NoticeBox("Calcium.CommandBox.Error ->  stop box Error", "ERROR");
                return 0;
            }
            readbufferA = PartRead(cmdbuffer, "\"", "\"");
            if (readbufferA == "sizeoutStart") {
                cout << "Press Enter to continue";
                getchar();
                return 0;
            }
            else {
                cout << readbufferA;
                getchar();
                return 0;
            }
        }
        if (SizeRead(cmdbuffer,9)=="endscript"){
            //Select End Task
            return -1;
        }

        //Var
        if (SizeRead(cmdbuffer,3)=="var"){
            //Create VarSpace
            clmSpace();
            int RunMode = 0;
            if (charTotal(cmdbuffer, "(") + charTotal(cmdbuffer, ")") >= 2) {
                RunMode = 1;
            }
            ResVarp = PartRead(rescmdbuffer," ","=");//VarName
            ResVarp = HeadSpaceCleanA(ResVarp);
            varspacedelete(ResVarp);

            //Command Mode
            if (RunMode == 1) {
                if(charTotal(cmdbuffer,"(") + charTotal(cmdbuffer,")") >= 2){}
                else {
                    NoticeBox("var create failed. -> Please Use (Command)", "ERROR");
                    return 0;
                }
                readbufferA = PartRead(cmdbuffer, "(", ")");//VarCMD
                //cout << "COMMAND : " << readbufferA << "            CMDBUFF :  " << cmdbuffer << endl;
                readbufferA = HeadSpaceCleanA(readbufferA);
                if (readbufferA == "") {
                    NoticeBox("var create failed. -> Unsupport Type", "ERROR");
                    return 0;
                }

                //Clean VarAPI
                VarExtendAPI = "null";
                readbufferA = CODETRANS(readbufferA);
                cmdbuffer = readbufferA;
                numbufferA = CMDCore();

                if (numbufferA == -1) {
                    return -1;
                }

                numbufferA = varspaceadd(ResVarp, VarExtendAPI);
                if (numbufferA == 1) {
                    NoticeBox("Var :  \"" + readbufferB + "\" Data :  _" + VarExtendAPI + "_,   Create Failed", "ERROR");
                    return 0;
                }
                return 0;
            }
            //Command ENd
            if (charTotal(cmdbuffer, "\"") != 2) {
                NoticeBox("var create failed. -> Please Use \"Message\"", "ERROR");
                return 0;
            }

            readbufferA = PartRead(cmdbuffer,"\"","\"");//Var CharInfo
            //cout << "Create VarSpace  " << readbufferB << endl;
            //cout << "Create VarSpace Info  " << readbufferA << endl;
            varspacedelete(ResVarp);
            numbuffer = varspaceadd(ResVarp,readbufferA);
            clmSpace();
            if (numbuffer == 1){
                NoticeBox("Var :  " + ResVarp + "  Create Failed","ERROR");
                return 0;
            }
            return 0;
        }
        if (SizeRead(cmdbuffer,6)=="delete"){
            readbufferA = PartRead(rescmdbuffer," ",";");//Delvarname
            varspacedelete(readbufferA);
            return 0;
        }
        if (SizeRead(cmdbuffer, 6) == "cmdvar") {
            //Other VarSpace CMD;
            if (charTotal(cmdbuffer, "&") != 2) {
                NoticeBox("Script Exception.Line: " + to_string(ScriptLine) + ".Create Var Error : SORT FORMAT ERROR\n Total Size = " + to_string(charTotal(cmdbuffer, "&")), "ERROR");
                return 0;
            }
            if (checkChar(cmdbuffer, "=") == 0) {
                NoticeBox("Script Exception.Line: " + to_string(ScriptLine) + ".Create Var Error : No \"=\" Mark", "ERROR");
                return 0;
            }
            if (checkChar(cmdbuffer, ";") == 0) {
                NoticeBox("Script Exception.Line: " + to_string(ScriptLine) + ".Create Var Error : No \";\" End Mark", "ERROR");
                return 0;
            }

            readbufferA = PartRead(cmdbuffer, "=", ";");//VarCMD
            readbufferCMDVAR = PartRead(rescmdbuffer, "&", "&");//VarName

            //Clean VarAPI
            VarExtendAPI = "null";
            readbufferA = CODETRANS(readbufferA);
            cmdbuffer = readbufferA;
            numbufferA = CMDCore();

            if (numbufferA == -1) {
                return -1;
            }

            varspacedelete(readbufferCMDVAR);
            numbufferA = varspaceadd(readbufferCMDVAR, VarExtendAPI);
            if (numbuffer == 1) {
                NoticeBox("Var :  \"" + readbufferCMDVAR + "\" Data :  _" + VarExtendAPI + "_,   Create Failed", "ERROR");
                return 0;
            }
            return 0;

        }
        //Var -End
        if (SizeRead(cmdbuffer,4)=="list"){
            if (charTotal(cmdbuffer, "\"") != 2) {
                NoticeBox("Script Exception. Line: " + to_string(ScriptLine) + " . List Tool Error :   Format Error", "ERROR");
                return 0;
            }
            readbufferA = PartRead(cmdbuffer, "\"", "\"");
            if (readbufferA == "vp") {
                cout << "VarSpace. Size : " + to_string(VarSpaceMax) + " List ->" << endl;
                cout << "---------------------------------------------------------------------" << endl;
                cout << VarSpace << endl;
                cout << "---------------------------------------------------------------------" << endl;
                cout << "END" << endl;
                return 0;
            }

            if (readbufferA == "nb") {
                cout << "Notice Box State is  -> " << to_string(NoticeBoxMode) << endl;
                cout << "0 -disabled  1 -enabled" << endl;
                return 0;
            }
            NoticeBox("Script Exception. Line: " + to_string(ScriptLine) + " . List Tool Error :   No This Select", "ERROR");
            return 0;
        }
        
        //API
        if (SizeRead(cmdbuffer, 10) == "socket.api") {
            //Copy VAR
            readbufferB = PartRead(cmdbuffer, " ", "=");
            if (checkChar(cmdbuffer, "=") == 0) {
                readbufferB = PartRead(cmdbuffer, " ", ";");
                //No ParaMode
                if (readbufferB == "noticebox") {
                    VarExtendAPI = to_string(NoticeBoxMode);
                    return 0;
                }
                if (readbufferB == "getversion") {
                    VarExtendAPI = to_string(VerCode);
                    return 0;
                }
                if (readbufferB == "getsys") {
                    VarExtendAPI = SocketAPI_GETSYS();
                    return 0;
                }
                if (readbufferB == "getpath") {
                    VarExtendAPI = SocketAPI_GETPATH();
                    return 0;
                }
                goto UNKNOWNSAPI;
            }
            if (charTotal(cmdbuffer, "\"") != 2) {
                NoticeBox("Script Exception. Line: " + to_string(ScriptLine) + " . Socket API Error :   SORT FORMAT ERROR", "ERROR");
                return 0;
            }
            readbufferA = PartRead(cmdbuffer, "\"", "\"");//Var CharInfo
            
            //SOCKET API - ARGV MODE
            if (readbufferB == "noticebox") {
                if (readbufferA == "1") {
                    NoticeBoxMode = 1;
                    VarExtendAPI = "ok";
                    return 0;
                }
                if (readbufferA == "0") {
                    NoticeBoxMode = 0;
                    VarExtendAPI = "ok";
                    return 0;
                }

                //Socket Failed
                NoticeBox("Socket.API.Error:UnsupportType ->  NoticeBoxMode", "Socket.Api.Error");
                return 0;
            }


            //Unknown Socket API
            UNKNOWNSAPI:
            NoticeBox("Unknown Socket API ->  " + readbufferB, "Socket.Api.Error");
            return 0;
        }
        if (SizeRead(cmdbuffer, 3) == "box") {
            readbufferB = PartRead(cmdbuffer, "&", "&");
            if (readbufferB == "geturlcode") {
                readbufferA = PartRead(cmdbuffer, "\"", "\"");//URL
                VarExtendAPI = GetURLCode(readbufferA);
                return 0;
            }

            NoticeBox("Box Command Error -> Unknown Type :  " + readbufferB + ".", "ERROR");
            return 0;

        }
        if (SizeRead(cmdbuffer, 7) == "URLDown") {
            if (charTotal(cmdbuffer, "\"") != 4) {
                NoticeBox("URLDown Failed -> Format Error", "ERROR");
                return 0;
            }
            readbufferA = CODETRANS(PartReadA(cmdbuffer, "\"", "\"", 1));
            readbufferB = CODETRANS(PartReadA(cmdbuffer, "\"", "\"", 2));
            cout << "Request Internet Download :" << endl;
            cout << "URL :  " << readbufferA << endl;
            cout << "Save :  " << readbufferB << endl;
            numbufferA = URLDown(readbufferA, readbufferB);

            if (numbufferA == 1) {
                VarExtendAPI = "true";
                return 0;
            }
            else {
                NoticeBox("Internet Error - > URLDown Failed", "DownloadFailed");
                VarExtendAPI = "false";
                return 0;
            }
        }

        //END
        if (SizeRead(cmdbuffer, 4) == "goto") {
            //Press Enter to continue
            if (charTotal(cmdbuffer, "\"") != 2) {
                NoticeBox("Calcium.CommandBox.Error ->  goto Format Error", "ERROR");
                return 0;
            }
            readbufferA = PartRead(cmdbuffer, "\"", "\"");
            if (readbufferA == "sizeoutStart") {
                NoticeBox("Calcium.CommandBox.Error ->  goto Format Error", "ERROR");
                return 0;
            }
            if (readbufferA == "sizeoutEnd"){
                NoticeBox("Calcium.CommandBox.Error ->  goto Format Error", "ERROR");
                return 0;
            }

            //FIND LINE
            if (RunScript == "NULL") {
                NoticeBox("Calcium.CommandBox.Error ->  goto Error :  File Not Select", "ERROR");
                return 0;
            }

            readbufferB = "";
            numbufferA = 0;
            numbufferB = 0;

            for (int rollgoto = 1; true; rollgoto++) {
                readbufferB = LineReader(RunScript,rollgoto);
                if (readbufferB == "overline") {
                    NoticeBox("Calcium.CommandBox.Error ->  goto Error :  Mark Not Found", "Command Crash");
                    return -1;
                }
                numbufferA = rollgoto;

                if (readbufferB == readbufferA) {
                    numbufferB = 1;
                    break;
                }
            }

            //Roll
            if (numbufferB == 1) {
                ReadScript = numbufferA;
                return 0;
            }
            else {
                NoticeBox("Calcium.CommandBox.Error ->  goto Error :  Mark Not Found", "Command Crash");
                return 1;
            }


        }
        //Include

        if (SizeRead(cmdbuffer,8)=="#Include"){
            readbufferA = PartRead(cmdbuffer,"\"","\"");
            readbufferA = ReplaceChar(readbufferA,"\";","");

            if(check_file_existence(readbufferA)){}
            else {
                NoticeBox("Failed to Include :  _" + readbufferA + "_.\n" + "Please Check is file exist", "ERROR");
                return 0;
            }

            while(true){
                int a = rollscript(readbufferA);
                if (a == 1001){
                    //Return UnknownError
                    NoticeBox("Include File Return Error","ERROR");
                }
                if (a == 1002){
                    //Return FileDestroy
                    NoticeBox("Include Run Error\n Read Failed :  This File is Destroy.\nInclude File : _" + readbufferA + "_", "ERROR");
                }
                break;
            }
            return 0;
        }
        
        //UnknownCOMMAND
        NoticeBox("Script Exception. Line: " + to_string(ScriptLine) + "(Buffer :  " + to_string(ReadScript) + ") . Unknown Command :   -" + cmdbuffer + "-\n" + "    -In File :  _" + RunScript + "_ -","ERROR");
        VarExtendAPI = "cmderr";
        return 0;
}