#include "acl.hh"


int getfacl(){
    struct acl* aclList = initACL();
    if (aclList == NULL){
        printf("Error initializing acl list\n");
        return -1;
    }
    for (int i=0 ; i<aclList->users.size() ; i++){
        printf("%s: ",aclList->path[i]);
        for (int j=0 ; j<aclList->users[i].size() ; j++){
            printf("%s \n",aclList->users[i][j]);
        }
        printf(": ");
        for (int j=0 ; j<aclList->userPerms[i].size() ; j++){
            printf("%s ",aclList->userPerms[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    getfacl();
    return 0;
}