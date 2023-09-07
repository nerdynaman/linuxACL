target:
	sudo g++ cd.cpp -o cd
	sudo g++ create_dir.cpp -o create_dir
	sudo g++ fget.cpp -o fget
	sudo g++ fput.cpp -o fput
	sudo g++ getfacl.cpp -o getfacl
	sudo g++ setfacl.cpp -o setfacl
	sudo chmod u+s cd
	sudo chmod u+s create_dir
	sudo chmod u+s fget
	sudo chmod u+s fput
	sudo chmod u+s getfacl
	sudo chmod u+s setfacl
clean:
	sudo rm cd
	sudo rm create_dir
	sudo rm fget
	sudo rm fput
	sudo rm getfacl
	sudo rm setfacl