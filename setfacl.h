#include<string>
#include<cstring>
#include<queue>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<iostream>
#include <filesystem>
#include "acl.hh"
using namespace std;
// char* path = "/Users/namanaggarwal/Desktop/IIITD/sem5/NSS1/Assignment1/acl.txt";


// void writeACL(struct acl *aclList){
//     // write the acl struct to acl file
//     // struct acl *aclList = initACL();
//     FILE *fp = fopen(path,"w");
//     if(fp == NULL){
//         printf("Error opening acl file\n");
//         return;
//     }
//     for (int i = 0; i < aclList->path.size(); i++){
//         fprintf(fp,"%s:",aclList->path[i]);
//         printf("%s: ",aclList->path[i]);
//         for (int j = 0; j < aclList->users[i].size(); j++){
//             fprintf(fp,"%s ",aclList->users[i][j]);
//             printf("%s ",aclList->users[i][j]);
//         }
//         fprintf(fp,":");
//         for (int j = 0; j < aclList->userPerms[i].size(); j++){
//             fprintf(fp,"%s ",aclList->userPerms[i][j]);
//             printf("%s ",aclList->userPerms[i][j]);
//         }
//         fprintf(fp,"\n");
//         printf("\n");
//     }
//     fclose(fp);
// }

void writeACL(struct acl *aclList){
    // write the acl struct to acl file
    const char* xattr_name = "acl";
	std::string xattr_value = "";
	std::string path = strdup(aclList->path[0]);
	xattr_value= xattr_value + path + ":";
	printf("%s: ",aclList->path[0]);
	for (int j = 0; j < aclList->users[0].size(); j++){
		xattr_value = xattr_value + aclList->users[0][j] + " ";
		printf("%s ",aclList->users[0][j]);
	}
	printf(": ");
	xattr_value = xattr_value + ":";
	for (int j = 0; j < aclList->userPerms[0].size(); j++){
		xattr_value = xattr_value + aclList->userPerms[0][j] + " ";
		printf("%s ",aclList->userPerms[0][j]);
	}
	printf("\n");
	xattr_value = xattr_value + "\n";
	const char* filename = aclList->path[0];
	const char* xattr_value1 = xattr_value.c_str();
	if (setxattr(filename, xattr_name, xattr_value1, strlen(xattr_value1), 0,0) == -1) {
        perror("setxattr");
    }
}

int setACL(char *pathA,char *user,char *perms,char *flag){
    // location/file : user1 user2 user3 : userPerms1 userPerms2 userPerms3 : group1 group2 group3 : rwx rwx rwx
    char* path = (char*)malloc(sizeof(char)*strlen(pathA));
    strcpy(path,pathA);
    struct acl *aclList = initACL(pathA);
    // if (aclList == NULL){
        // printf("Error initializing acl list\n");
        // return -1;
    // }
    for (int i = 0; i < aclList->path.size(); i++){
        if (strcmp(aclList->path[i],path) == 0){
            // path exists in acl file
            if (strcmp(flag,"x")==0){
                // remove all user and perm for this path from acl file
                // aclList->path.erase(aclList->path.begin()+i);
                while(!aclList->users[i].empty()){
                    aclList->users[i].pop_front();
                }
                aclList->users[i].push_back((char*)"");
                while(!aclList->userPerms[i].empty()){
                    aclList->userPerms[i].pop_front();
                }
                aclList->userPerms[i].push_back((char*)"");
                // write the updated acl struct to acl file
                writeACL(aclList);
                return 0;
            }
            // now we have to check if user exists in acl file
            for (int j = 0; j < aclList->users[i].size(); j++){
                if(strcmp(aclList->users[i][j],user) == 0){
                    // user exists in acl file
                    // update the perms for the user
                    aclList->userPerms[i][j] = perms;
                    // write the updated acl struct to acl file
                    writeACL(aclList);
                    return 0;
                }
            }
            // user does not exist in acl file
            // add the user to the acl file
            aclList->users[i].push_back(user);
            aclList->userPerms[i].push_back(perms);
            // write the updated acl struct to acl file
            writeACL(aclList);
            return 0;
        }
    }
    // path does not exist in acl file so add it
    aclList->path.push_back(path);
    deque<char*> users;
    users.push_back(user);
    aclList->users.push_back(users);
    deque<char*> userPerms;
    userPerms.push_back(perms);
    aclList->userPerms.push_back(userPerms);
    // write the updated acl struct to acl file
    writeACL(aclList);
    return 0;
}
