target:
	sudo g++ cd.cpp -o cd
	sudo g++ create_dir.cpp -o create_dir
	sudo g++ fget.cpp -o fget
	sudo g++ fput.cpp -o fput
	sudo g++ getfacl.cpp -o getfacl
	sudo g++ setfacl.cpp -o setfacl
	sudo g++ sudo.cpp -o sudo
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