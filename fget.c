#include "acl.hh"
#include <iostream>
#include <stdio.h>
#include <pwd.h>
using namespace std;

int main(int argc, char* argv[]){
    if(argc!=2){
        cout<<"Invalid number of arguments"<<endl;
        return 0;
    }
    if (access(argv[1],F_OK) == -1){ //check if the file exists
        cout<<"File does not exist"<<endl;
        setuid(getuid());
        return 0;
    }
    int callerID = getuid(); // get uid of caller
    struct passwd *pw = getpwuid((uid_t) callerID); //get the name of user calling this program
    // cout << "User: " << pw->pw_name << endl;
    // copy absPath to a new char array
    char* absPath = (char*)malloc(sizeof(char)*strlen(getAbsolutePath(argv[1])));
    strcpy(absPath,getAbsolutePath(argv[1]));

    int res = checkAcessPerms(absPath, pw->pw_name,"r",""); //check if the user has write permission for the given file
    if (res < 0){
        cout << res << " "; //print the error code
        cout<<"You do not have permission to read to this file"<<endl;
        setuid(callerID);
        return 0;
    }
    setuid(getOwnerID(argv[1]));
    FILE *fp = fopen(argv[1],"r"); //open the file
    if (fp == NULL){
        cout<<"Error opening file"<<endl;
        setuid(callerID);
        return 0;
    }
    char* content = (char*)malloc(sizeof(char)*100);
    if (fgets(content,100,fp) == NULL){ //write the content to the file
        cout<<"Error reading file"<<endl;
        setuid(callerID);
        return 0;
    }
    cout<<content<<endl;
    fclose(fp);
    setuid(callerID);
    return 0;
}