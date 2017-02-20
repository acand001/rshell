#Rshell Command Shell

## Synopsis

The rshell program runs a Linux style command prompt which allows for the input of a single command or multiple commands utilizing semicolon, &&, or || as command connectors. Once the commands are entered they are executed in the order they were read and according to their command connectors. If and when a command fails rshell is designed to output and error message and return to the command prompt.

Example of command input:

```
$ command [arguments] [connector]
```

## Code Example

Our code is constructed of vectors and objects which reads and executes shell commands in the following manner:

The following is example code which we used to created objects which would then be evaluated and returned depending on their individual outcome.
```
	if(cnn.at(i) == "&&"){
        Cmds* cmds1 = new Cmds(cmds.at(j));
        j++;
        Cmds* cmds2 = new Cmds(cmds.at(j));
        And* A = new And(cmds1, cmds2);
        A->execute();
```

## Installation

The following are instructions for installing and running rshell
```
1. $ git clone  https://github.com/victormedel/CS100_Winter_2017
2. $ cd rshell
3. $ git checkout hw2
4. $ make
5. $ bin/rshell
```

## Tests

This Assignment required the creation of four test shell scripts which would handle the testing of the code. The following shell scripts have been created to test specific areas of the code.
```
single_command.sh	 	-Tests for single command inputs	
multi_command.sh		-Tests for multiple command inputs
commented_command.sh	-Tests for commented  inputs
exit.sh					-Test for the exit command within the application
```

## Known Bugs

The following are known bugs in our application, which will be addressed in a future.
```
1. After a comment(#) is detected additional commands are not captured
2. The program iterates through some of the commands twice as it was the only way for us to capture left and right arguments
```

## Contributors

Assignment was completed by:
```
Alex Candia
Victor Medel
```

## License

The GNU General Public License is a free, copyleft license for software and other kinds of works.