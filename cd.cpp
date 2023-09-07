#include "acl.hh"
#include <unistd.h>
#include <pwd.h>
int main(int argc, char* argv[]){
    if (access(argv[1],F_OK) == -1){
        printf("Directory does not exist\n");
        setuid(getuid());
        return 0;
    }
    char* path = getAbsolutePath(argv[1]);
    char* absPath = (char*)malloc(strlen(path)+1);
    strcpy(absPath,path);
    if (path == NULL){
        printf("Error getting absolute path\n");
        return -1;
    }
    // check if the directory exists
    struct passwd *pw = getpwuid((uid_t) getuid()); //get the name of user calling this program
    int perm = checkAcessPerms(absPath, pw->pw_name,"x","d");
    if (perm < 0){
        printf("You do not have permission to change directory\n");
        return 0;
    }
    int res = chdir(path);
    if (res < 0){
        printf("Error changing directory\n");
        return 0;
    }
    cout << "Current directory: " << getcwd(NULL,0) << endl;
    setuid(getuid());
    return 0;
}