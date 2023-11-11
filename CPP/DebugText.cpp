#include"TextProces.h"

using namespace std;

int main(){
    string Info = "cout \"ABCDEFG\"";
    cout << "Res Info :  " << Info << endl;
    Info = PartRead(Info,"\"","\"");
    cout << "Replace Info :  " << Info << endl;
    return 0;
}