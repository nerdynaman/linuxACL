#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<stdio.h>
using namespace std;

struct acl{
    deque<char*> path;
    deque<deque<char*> > users;
    deque<deque<char*> > userPerms;
};
char* path = "/Users/namanaggarwal/Desktop/IIITD/sem5/NSS1/Assignment1/acl.txt";

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
    return aclList;
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