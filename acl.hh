#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
using namespace std;

struct acl{
    deque<char*> path;
    deque<deque<char*> > users;
    deque<deque<char*> > userPerms;
};
char* path = (char*)"/Users/namanaggarwal/Desktop/IIITD/sem5/NSS1/Assignment1/acl.txt";

int cmp(char* a, char* b){
    // check if characters of a is part of b
    // if yes then return 0 else return -1
    int i=0;
    int j=0;
    while (i<strlen(a) && j<strlen(b)){
        if (a[i] == b[j]){
            i++;
            j=0;
        }
        else{
            j++;
        }
    }
    if (i==strlen(a)){
        return 0;
    }
    return -1;
}

struct acl* initACL(){
    // read acl file and store it in a data structure
    // return the data structure
    FILE *fp = fopen(path,"r");
    if(fp == NULL){
        printf("Error opening acl file\n");
        return NULL;
    }
    char *line = NULL;
    size_t len = 0;
    struct acl *aclList = (struct acl*)malloc(sizeof(struct acl));
    while (getline(&line,&len,fp) != -1){
        char *lineDup = strdup(line);
        char *token = strtok(lineDup,":");
        aclList->path.push_back(token);
        token = strtok(NULL,":");
        for (int i=0 ; i<strlen(token) ; i++){
            if (token[i] == '\n') {
                token[i] = '\0';
                break;
            }
        }
        // now let us store all the users in array split by space in a string and store it in a queue
        token = strtok(token," ");
        deque<char*> users;
        while(token!=NULL){
            users.push_back(token);
            for (int i=0 ; i<strlen(token) ; i++){
                if (token[i] == '\n') {
                    token[i] = '\0';
                    break;
                }
            }
            token = strtok(NULL," ");
        }
        aclList->users.push_back(users);
        token = strtok(strdup(line),":");
        token = strtok(NULL,":");
        token = strtok(NULL,":");
        token = strtok(token," ");
        // now let us store all the user permissions in array split by space in a string and store it in a queue
        deque<char*> userPerms;
        while(token!=NULL){
            int i;
            for (i=0 ; i<strlen(token) ; i++){
                if (token[i] == '\n') {
                    token[i] = '\0';
                    break;
                }
            }
            userPerms.push_back(token);
            token = strtok(NULL," ");
        }
        aclList->userPerms.push_back(userPerms);
    }
    fclose(fp);
    free(line);
    return aclList;
}

int checkAcessPerms(int ownerid){
    // check if the user is root or owner of the file
    // if yes then return 0 else return -1
    return (getuid() == 0 || getuid() == ownerid) ? 0:-1;
}

int getOwnerID(char *path){
    // get the owner id of the file
    struct stat fileStat;
    if(stat(path,&fileStat) == 0){
        return fileStat.st_uid;
    }
    return -1;
}

char* getAbsolutePath(char *relativePath){
    char* absolutePath = realpath(relativePath, NULL);

    if (absolutePath != nullptr) {
        free(absolutePath); // Don't forget to free the dynamically allocated memory
    } else {
        perror("realpath");
    }
    return absolutePath;
}

int checkAcessPerms(char* path, char* user, char* perm, char* type){
    // check for given path(i.e. file location) the user has the given permission or not
    // hasPerms ? 1:0
    if (getuid() == 0){ //if user is root then he has all the permissions
        return 0;
    }
    char* defaultOwnerPermFile =(char*) "rw"; //default owner permission
    char* defaultOtherPermFile =(char*) "r"; //default other permission
    char* defaultOwnerPermDir = (char*)"rwx"; //default owner permission
    char* defaultOtherPermDir = (char*)"x"; //default other permission
    struct acl *aclList = initACL(); // get the acl list
    if (aclList == NULL){
        printf("Error in reading acl file\n");
        return -11;
    }
    
    int validPath = -1;
    int validUser = -1;
    int validPerm = -1;
    int i, j, k;
    for (i = 0; i<aclList->path.size() ; i++){ // check if the given path is present in the acl list, if not then default permissions will be checked
        if (strcmp(aclList->path[i],path) == 0){
            validPath = 1;
            break;
        }
    }
    if (validPath==1){
        for (j=0 ; j<aclList->users[i].size() ; j++){ // check if the given user is present in the acl list, if not then default permissions will be checked
            if (strcmp(aclList->users[i][j],user) == 0){
                validUser = 1;
                break;
            }
        }
    }
    if (validUser==1){
        // check if for the validated user permission is there or not
        if (cmp(perm,aclList->userPerms[i][j]) == 0){
            validPerm = 1;
            return 0;
        }
        return -12;
    }

    if (validUser==-1 || validPath==-1){
        // check for default owner and other permissions
        if (strcmp(type,"d") == 0){
            if (getuid() == getOwnerID(path)){ //check if user trying to access is owner of the file
                if (cmp(perm,defaultOwnerPermDir) == 0){ // check if the required permission is permisable with default owner permission
                    return 0;
                }
                return -15;
            }
            else if (cmp(perm,defaultOtherPermDir) == 0){
                return 0;
            }
            return -16;
        }
        if (getuid() == getOwnerID(path)){ //check if user trying to access is owner of the file
            if (cmp(perm,defaultOwnerPermFile) == 0){ // check if the required permission is permisable with default owner permission
                return 0;
            }
            return -13;
        }
        else if (cmp(perm,defaultOtherPermFile) == 0){
            return 0;
        }
        return -14;
    }
    return -19;
}