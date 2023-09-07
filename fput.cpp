#include "setfacl.hh"
#include <iostream>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
using namespace std;
// format fput <fileName>\ <input>
// issue : if the file does not exist then create it but owner of the file is root
int main(int argc, char *argv[]){
    if(argc!=2){
        cout<<"Invalid number of arguments"<<endl;
        return 0;
    }
    int flag = 0;
    if (access(argv[1],F_OK) == -1){ //check if the file exists
        cout<<"File does not exist"<<endl;
        char* path = getcwd(NULL,0); //get the current working directory
        // check the perms for writing in the current directory
        struct passwd *pw = getpwuid(getuid()); //get the name of user calling this program
        char *username = pw->pw_name;
        int perms = checkAcessPerms(path,username,(char*)"w",(char*)"d"); //check if the user has write permission for the current directory
        if (perms < 0){
            cout<<"You do not have permission to create file"<<endl;
            setuid(getuid());
            return 0;
        }
        FILE *fp = fopen(argv[1],"w"); //create the file if it does not exist
        if (fp == NULL){
            cout<<"Error creating file"<<endl;
            setuid(getuid());
            return 0;
        }
        fclose(fp);
        flag = 1;
    }
    struct passwd *pw = getpwuid((uid_t) getuid()); //get the name of user calling this program
    // copy absPath to a new char array
    char* absPath = (char*)malloc(sizeof(char)*strlen(getAbsolutePath(argv[1])));
    strcpy(absPath,getAbsolutePath(argv[1]));
    if (flag == 1){
        setACL(absPath,pw->pw_name,"rwo","m"); //for the newly created file marking it as owner and giving default perms
    }
    int res = checkAcessPerms(absPath, pw->pw_name,"w",""); //check if the user has write permission for the given file
    if (res < 0){
        cout << res << " "; //print the error code
        cout<<"You do not have permission to write to this file"<<endl;
        setuid(getuid());
        return 0;
    }
    char* content = (char*)malloc(sizeof(char)*100);
    cin>>content; //get the content to be written to the file
    FILE *fp = fopen(argv[1],"w"); //open the file
    if (fp == NULL){
        cout<<"Error opening file"<<endl;
        setuid(getuid());
        return 0;
    }
    if (fputs(content,fp) == -1){ //write the content to the file
        cout<<"Error writing to file"<<endl;
        setuid(getuid());
        return 0;
    }
    setuid(getuid()); //set the user id to the user calling this program
    return 0;
}