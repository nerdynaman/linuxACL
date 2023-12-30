#include "acl.hh"


int getfacl(int argc, char* argv[]){
    char* path = getAbsolutePath(argv[1]);
    if (path == NULL){
        printf("Error getting absolute path\n");
        return -1;
    }
    struct acl* aclList = initACL(path);
    if (aclList == NULL){
        printf("Error initializing acl list\n");
        return -1;
    }
    for (int i=0 ; i<aclList->path.size() ; i++){
        if (strcmp(aclList->path[i], path) != 0){
            continue;
        }
        printf("%s: ",aclList->path[i]);
        for (int j=0 ; j<aclList->users[i].size() ; j++){
            printf("%s ",aclList->users[i][j]);
        }
        printf(": ");
        for (int j=0 ; j<aclList->userPerms[i].size() ; j++){
            printf("%s ",aclList->userPerms[i][j]);
        }
        printf("\n");
        break;
    }
    setuid(getuid());
    return 0;
}

int main(int argc, char* argv[]){
    getfacl(argc, argv);
    return 0;
}