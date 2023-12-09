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

//Enabled Extend
//0 - FAIL   1 -TRUE
int StartExtend(string Head) {
    readbufferA = Head;
        cout << "Connect Server :  " << cfg_usingserver;
        cout << "Try to Find :  " << readbufferA << endl;
        readbufferB = GetURLCode(cfg_usingserver + readbufferA);

        if (readbufferB != "URLError.FailedGet") {
            string ReplaceUP = ReplaceChar(UsingPath, "\\", "/");
            URLDown(readbufferB, ReplaceUP + readbufferA);
            readbufferC = LineReader(ReplaceUP + readbufferA,2);

            if(readbufferC == "overline"){
                readbufferCMDVAR = ReplaceUP + readbufferA;
                remove(readbufferCMDVAR.c_str());
                return 0;
            }

            if (check_file_existence(ReplaceUP + readbufferA)) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
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
        if (SizeRead(cmdbuffer, 8) == "clearcon") {
            cleanConsole();
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
            if (charTotal(cmdbuffer, "<") + charTotal(cmdbuffer, ">") == 2) {
                readbufferA = PartRead(cmdbuffer, "<", ">");
                ReturnDATA = atoi(readbufferA.c_str());
            }
            //Select End Task
            return -1;
        }

        if (SizeRead(cmdbuffer, 5) == "throw") {
            if (charTotal(cmdbuffer, "<") + charTotal(cmdbuffer, ">") == 2) {
                readbufferA = PartRead(cmdbuffer, "<", ">");
                cout << "script.throw :  (" << readbufferA << ")" << endl;
                return 0;
            }
            NoticeBox("Command Error ->.  Unknown Throw Code. Format :  throw<INFO>", "ERROR");
            return 0;
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
            readbufferA = PartRead(cmdbuffer, " ", "$FROMEND$");
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
        if (SizeRead(cmdbuffer, 5) == "sleep") {
            if (charTotal(cmdbuffer, "(") + charTotal(cmdbuffer, ")") != 2) {
                NoticeBox("Sleep Command Error, Format Error", "ERROR");
                return 0;
            }
            readbufferC = PartRead(cmdbuffer, "(", ")");
            sleepapi(atoi(readbufferC.c_str()));
            return 0;
        }

        //API
        if (SizeRead(cmdbuffer, 10) == "socket.api") {
            string SA_INFO, SA_HEAD;
            //Copy VAR
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
            
            SA_INFO = PartReadA(cmdbuffer, "\"", "\"",1);//Var CharInfo
            SA_HEAD = PartRead(cmdbuffer, " ", "=");

            //SOCKET API - ARGV MODE
            if (SA_HEAD == "noticebox") {
                if (SA_INFO == "1") {
                    NoticeBoxMode = 1;
                    VarExtendAPI = "ok";
                    return 0;
                }
                if (SA_INFO == "0") {
                    NoticeBoxMode = 0;
                    VarExtendAPI = "ok";
                    return 0;
                }

                //Socket Failed
                NoticeBox("Socket.API.Error:UnsupportType ->  NoticeBoxMode : " + SA_INFO, "Socket.Api.Error");
                return 0;
            }

            //Unknown Socket API
            UNKNOWNSAPI:
            NoticeBox("Unknown Socket API ->  _" + readbufferB + "_", "Socket.Api.Error");
            return 0;
        }
        if (SizeRead(cmdbuffer, 3) == "box") {
            if (checkChar(cmdbuffer, "=") == 1) {
                if (checkChar(cmdbuffer, " =") == 1) {
                    readbufferB = PartReadA(cmdbuffer, " ", " ", 1);
                }
                else {
                    readbufferB = PartReadA(cmdbuffer, " ", "=", 1);
                }
            }
            else {
                readbufferB = PartRead(cmdbuffer, " ", "$FROMEND$");
            }

            if (readbufferB == "geturlcode") {
                readbufferA = PartRead(cmdbuffer, "\"", "\"");//URL
                VarExtendAPI = GetURLCode(readbufferA);
                return 0;
            }
            if (readbufferB == "fileread") {
                 VarExtendAPI = LineReader(PartReadA(cmdbuffer, "\"", "\"", 1),atoi(PartReadA(cmdbuffer, "\"", "\"", 2).c_str()));//URL
                 return 0;
            }

            if (readbufferB == "folder.remove") {
                if (charTotal(cmdbuffer, "\"") != 2) {
                    NoticeBox("Folder API Error. Format Error Using \"DIR\" ", "ERROR");
                    return 0;
                }

                readbufferC = PartRead(cmdbuffer, "\"", "\"");

                bool BACKDELAPI = boxrmdir(readbufferC);
                if (BACKDELAPI) {
                    VarExtendAPI = "true";
                }
                else {
                    VarExtendAPI = "false";
                }

                return 0;
            }

            if (readbufferB == "folder.exist") {
                if (charTotal(cmdbuffer, "\"") != 2) {
                    NoticeBox("Folder API Error. Format Error Using \"DIR\" ", "ERROR");
                    return 0;
                }

                readbufferC = PartRead(cmdbuffer, "\"", "\"");

                bool fexst = ExistFolder_check(readbufferC);
                if (fexst) {
                    VarExtendAPI = "true";
                }
                else {
                    VarExtendAPI = "false";
                }

                return 0;
            }

            if (readbufferB == "folder.make") {
                if (charTotal(cmdbuffer, "\"") != 2) {
                    NoticeBox("Folder API Error. Format Error Using \"DIR\" ", "ERROR");
                    return 0;
                }

                readbufferC = PartRead(cmdbuffer, "\"", "\"");

                bool BACKDELAPI = boxmkdir(readbufferC);
                if (BACKDELAPI) {
                    VarExtendAPI = "true";
                }
                else {
                    VarExtendAPI = "false";
                }

                return 0;
            }

            if (readbufferB == "getcaname") {
                VarExtendAPI = GetFileName();
                return 0;
            }

            if (readbufferB == "type") {
                if (charTotal(cmdbuffer, "\"") != 2) {
                    NoticeBox("Type Command Error, Please use \"File\"", "ERROR");
                    return 0;
                }
                readbufferC = PartRead(cmdbuffer, "\"", "\"");
                typetext(readbufferC);
                return 0;
            }

            NoticeBox("Box Command Error -> Unknown Type :  (" + readbufferB + ").", "ERROR");
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
        if (SizeRead(cmdbuffer, 7) == "cintype") {
            readbufferC = "";
            if (charTotal(cmdbuffer, "\"") == 2) {
                readbufferC = PartRead(cmdbuffer,"\"","\"");
            }
            
            string typeptr;

            cout << readbufferC;
            getline(cin, typeptr);

            VarExtendAPI = typeptr;

            return 0;
        }

        if (SizeRead(cmdbuffer, 8) == "cleanram") {
            clmSpace();
            return 0;
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
        if (SizeRead(cmdbuffer, 9) == "runscript") {
            if (charTotal(cmdbuffer, "\"") != 2) {
                cout << "RunScript Format Error " << endl;
                return -1;
            }
            string NewRunScript = PartRead(cmdbuffer, "\"", "\"");
            if (!check_file_existence(NewRunScript)) {
                cout << "Failed to Load Script :  " << NewRunScript << endl;
                return -1;
            }
            int a = rollscript(NewRunScript);
            if (a == 1001) {
                //Return UnknownError
                NoticeBox("File Return Error", "ERROR");
            }
            if (a == 1002) {
                //Return FileDestroy
                NoticeBox("Run Error\n Read Failed :  This File is Destroy.\nInclude File : _" + NewRunScript + "_", "ERROR");
            }

            return -1;
        }

        //Include

        if (SizeRead(cmdbuffer,6)=="#using"){
            string UsingFile;
            if (charTotal(cmdbuffer, "\"") == 2) {
                UsingFile = PartRead(cmdbuffer, "\"", "\"");
            }
            else {
                if (charTotal(cmdbuffer, "<") + charTotal(cmdbuffer, ">") == 2) {
                    readbufferCMDVAR = PartRead(cmdbuffer, "<", ">");
                    UsingFile = UsingPath + "/" + readbufferCMDVAR;
                    if (!check_file_existence(UsingFile)) {
                        if (StartExtend(readbufferCMDVAR) == 1) {
                            cout << readbufferCMDVAR << "is Ready" << endl;
                        }
                        else {
                            cout << "Failed to Download :  " << UsingFile << endl;
                            return 0;
                        }
                    }
                }
                else {
                    NoticeBox("Failed to Using Command. Null File Mark", "ERROR");
                    return 0;
                }
            }

            if(check_file_existence(UsingFile)){}
            else {
                NoticeBox("Failed to Using :  _" + UsingFile + "_.\n" + "Please Check is file exist", "ERROR");
                return 0;
            }
            
            while(true){
                NowTao++;
                //cout << "Current Now Tao :  " << NowTao << endl;
                if (NowTao == cfg_maxusing) {
                    cout << "Using Command Over Max :  " << cfg_maxusing << endl;
                    cout << "This Settings Anti Stack overflow. You can set :  settings.cfg_maxusing=-1 to Close this tool" << endl;
                    cout << "Press Enter to Continue " << endl;
                    getchar();
                }
                string OldRunScript = RunScript;
                int OldReadScript = ReadScript;
                ReadScript = 1;
                int a = rollscript(UsingFile);
                if (a == 1001){
                    //Return UnknownError
                    NoticeBox("Using File Return Error","ERROR");
                }
                if (a == 1002){
                    //Return FileDestroy
                    NoticeBox("Using Run Error\n Read Failed :  This File is Destroy.\nInclude File : _" + UsingFile + "_", "ERROR");
                }
                RunScript = OldRunScript;
                ReadScript = OldReadScript;
                //cout << "CURRENT :  " << RunScript << endl;
                break;
            }
            return 0;
        }
        
        if (SizeRead(cmdbuffer, 3) == "net") {
            if (PartReadA(cmdbuffer, " ", " ", 1) == "using") {
                if (StartExtend(PartReadA(cmdbuffer, "\"", "\"", 1)) == 1) {
                    cout << PartReadA(cmdbuffer, "\"", "\"", 1) << "  is Ready" << endl;
                    return 0;
                }
                else {
                    cout << "Failed to Download :  " << PartReadA(cmdbuffer, "\"", "\"", 1) << endl;
                    return 0;
                }
            }
            if (PartReadA(cmdbuffer, " ", " ", 1) == "remove") {
                readbufferC = UsingPath + PartReadA(cmdbuffer, "\"", "\"", 1);
                //cout << "Remove :  " << readbufferC << endl;
                if (check_file_existence(readbufferC)) {
                    remove(readbufferC.c_str());
                }
                else {
                    cout << "No This File" << endl;
                }
                return 0;
            }
            cout << "Unknown Net Command " << endl;
            return 0;
        }

        //UnknownCOMMAND
        NoticeBox("Script Exception. Line: " + to_string(ScriptLine) + "(Buffer :  " + to_string(ReadScript) + ") . Unknown Command :   -" + cmdbuffer + "-\n" + "    -In File :  _" + RunScript + "_ -","ERROR");
        VarExtendAPI = "cmderr";
        return 0;
}