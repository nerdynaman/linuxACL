```ACL's are stored in extended attributes i.e. xattr of file or dir```

## Installation
```bash
git clone https://github.com/nerdynaman/linuxACL.git
cd linuxACL
make
```

## Attacks prevented
1) Switching back to uid of caller after execution, so that if attacker gets access to root/owner of file, he can't do much
2) Only root or file owner can change acl
3) Allowing to add acl only for users which exist so new users when created will not have any acl
4) Before creating file or dir check if user has perms to write in that dir
5) Can't set acl for files or dir which does not exists
6) If file is deleted then acl is also deleted 
