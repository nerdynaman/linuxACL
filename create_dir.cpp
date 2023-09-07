#include"setfacl.hh"
#include<pwd.h>
int main(int argc, char* argv[]){
    if (argc!=2){
        cout<<"Invalid number of arguments"<<endl;
        return 0;
    }
    // check if the directory exists
    if (access(argv[1],F_OK) != -1){
        cout<<"Directory exists"<<endl;
        setuid(getuid());
        return 0;
    }
    // check the perms for writing in the current directory
    char *path = getcwd(NULL,0);
    // getting current username
    struct passwd *pw = getpwuid(getuid());
    char *username = pw->pw_name;
// check if the user has write perms in the current directory
    int perms = checkAcessPerms(path,username,(char*)"w",(char*)"d"); 
    if (perms < 0){
        cout<<"You do not have permission to create directory"<<endl;
        return 0;
    }
    // create the directory
    int status = mkdir(argv[1],0751);
    path = getAbsolutePath(argv[1]);
    char* absPath = (char*)malloc(sizeof(char)*strlen(path));
    strcpy(absPath,path);
    // set the owner of the directory to the user calling this program
    setACL(absPath,username,(char*)"rwxo",(char*)"m"); //for the newly created directory marking it as owner and giving all perms
    if (status == -1){
        cout<<"Error in creating directory"<<endl;
        return 0;
    }
    cout<<"Directory created successfully"<<endl;
    setuid(getuid());
}