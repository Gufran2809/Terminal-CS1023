commands ls,cp,mv,grep,ps can be executed using this terminal:

1.ls 
    ls [option]
    this is the same as the orginal command.
    the executable options for the command are:
    1. -l 2. -o 3. -a 4. -g 
 2.ps 
    ps[option]
    this is the same as the orginal command.
    the executable options for the command are:
    1. -af 2. -f 3. -A 4. -p
 3.cp 
    cp[option]
    this is the same as the orginal command.
    the executable options for the command are:
    1. -l 2. -n 3. -v 4. -u
 4.mv
    mv[option]
    this is the same as the orginal command.
    the executable options for the command are:
    1. -l 2. -n 3. -v 4. -u
  5.grep
    grep[option]
    this is the same as the orginal command.
    the executable options for the command are:
    1. -c 2. -n 3. -v 
  type 'man [command]' and enter for detailed usage of options of command
  

    
   The requirements to execute this terminal are:
-->A linux ubuntu machine.
-->GCC should be installed in the machine :
	If GCC is not installed in your machine,do the following:
	open the terminal on your machine and run the following commands:
		--> "sudo apt update"
		--> "sudo apt install build-essential"
		OR
		--> "sudo apt install gcc"
	To check if installed then run the following command:
		--> "gcc --version"
--> libreadline:
Install libreadline in your machine:
For that run the following command on your terminal:
		--> "sudo apt-get install libreadline8 libreadline-dev"
Now you are ready to execute the terminal!

steps to execute:

-->change the directory to the directory where the files are located.
-->Now run the following commands:
	--> "make" (To compile the executable files.)
	--> "./myshell" (To execute the terminal.)
