#include "acl.hh"
#include <pwd.h>
int main(int argc, char* argv[]){
	if (argc < 2){ // check if command given is valid
		cout << "Usage: sudo <command>" << endl;
		return 0;
	}
	char* path = getAbsolutePath(argv[1]); // get absolute path of file from relative path
	char* absPath = (char*)malloc(sizeof(char)*strlen(path));
	strcpy(absPath,getAbsolutePath(argv[1]));
	size_t userid = getOwnerID(absPath); // check owner of file
	if (userid != 0){ 
		setuid(userid); // if not root then switch to owner of file
	}
	struct passwd *pw = getpwuid(userid); // get username from uid
	int perm = checkAcessPerms(absPath,pw->pw_name,(char*)"x",(char*)""); // check if file owner has execute permission
	if (perm == -1){
		cout << "You do not have permission to execute this file" << endl;
		return 0;
	}
	// now execute the file
	char* args[argc-1];
	for (int i=1 ; i<argc ; i++){
		args[i-1] = argv[i];
	}	
	args[argc-1] = NULL;
	execv(path,args);

	return 0;
}