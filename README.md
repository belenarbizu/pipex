# pipex
The pipex program replicates a Unix shell pipeline to connect two commands using input and output files. <br/>
<br/>
Usage: ./pipex archivo1 comando1 comando2 archivo2<br/>
<br/>
When run with four arguments, the program redirects the contents of file1 to command1, passes the output of command1 to command2, and finally writes the result to file2. This is equivalent to the shell operation < file1 command1 | command2 > file2.<br/>
<br/>
Internally, pipex uses pipes, fork, and execve to create subprocesses and manage input/output redirection. The program ensures rigorous error handling and memory management to prevent unexpected crashes or memory leaks.
