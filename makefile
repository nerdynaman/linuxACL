target:
	sudo g++ cd.c -o cd
	sudo g++ create_dir.c -o create_dir
	sudo g++ fget.c -o fget
	sudo g++ fput.c -o fput
	sudo g++ getfacl.c -o getfacl
	sudo g++ setfacl.c -o setfacl
	sudo g++ sudo.c -o sudo
	sudo chmod u+s cd
	sudo chmod u+s create_dir
	sudo chmod u+s fget
	sudo chmod u+s fput
	sudo chmod u+s getfacl
	sudo chmod u+s setfacl
	sudo chmod u+s sudo
	export create_dir=$(PWD)/create_dir
	export cd=$(PWD)/cd
	export fget=$(PWD)/fget
	export fput=$(PWD)/fput
	export getfacl=$(PWD)/getfacl
	export setfacl=$(PWD)/setfacl
	export sudo=$(PWD)/sudo
clean:
	sudo rm cd
	sudo rm create_dir
	sudo rm fget
	sudo rm fput
	sudo rm getfacl
	sudo rm setfacl
	sudo rm sudo