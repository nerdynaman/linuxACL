#include"setfacl.hh"
using namespace std;
//done first we check if the user calling this program is root or owner of the file
//done second we check if the file exists
//tbd third we check if the file is a directory
//tbd fourth we check if the file is a symbolic link
// flags to be implemented : 
//done -m : modify the acl
//done -x : remove the acl
// -b : remove all the acl
// for file owner acl is always what is set by chmod
// for root acl is always rwx
//done acl file will be stored in /var/acl , it will have acl for all the files
// initally we will only work with user keeping scope of group for later   
//done format of acl file :
//done location/file : user1 user2 user3 : userPerms1 userPerms2 userPerms3 : group1 group2 group3 : rwx rwx rwx
//done usage : setfacl [-m|-x|-b] u|g|o <user|group> <rwx> <file>


int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: setfacl [-m|-x|-b] u|g|o <user|group> <rwx> <file>");
        return 0;
    }

    if (strcmp(argv[1],"-m") == 0){
        if(access(argv[5],F_OK) == -1){
            printf("File does not exist\n");
            return 0;
        }  
        int accessPerms = checkAcessPerms(getOwnerID(argv[5]));
        if(accessPerms == -1){
            printf("You do not have permission to set acl for this file\n");
            return 0;
        }
        char *absPath;
        strcpy(absPath,getAbsolutePath(argv[5]));
        if(setACL(absPath,argv[3],argv[4],"")==-1){
            printf("Error setting acl\n");
            return 0;
        }
        else{
            printf("ACL set successfully\n");
            return 0;
        }
    }
    else if (strcmp(argv[1],"-x")==0){\
        if (access(argv[4],F_OK) == -1){
            printf("File does not exist\n");
            return 0;
        }
        int accessPerms = checkAcessPerms(getOwnerID(argv[4]));
        if(accessPerms == -1){
            printf("You do not have permission to set acl for this file\n");
            return 0;
        }
        char *absPath;
        strcpy(absPath,getAbsolutePath(argv[4]));
        if(setACL(absPath,argv[3],argv[4],"x")==-1){
            printf("Error removing acl\n");
            return 0;
        }
    }
    else if (strcmp(argv[1],"-b") == 0){
        return 0;
    }
    else{
        printf("Invalid flag\n");
        return 0;
    }

    return 0;
}