1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My implementation calls waitpid() on each child process after forking them. This ensures that the shell waits for all child processes to complete before displaying the next prompt. If waitpid() were not used, child processes would become zombie processes, and the shell might continue accepting input while previous commands are still running, leading to unexpected behavior and resource leaks.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

After calling dup2(), unused pipe ends must be closed to prevent file descriptor leaks. If pipes remain open, processes might hang indefinitely waiting for input that will never arrive. This can lead to deadlocks where one process is waiting for the other to close a pipe, but the pipe is still open elsewhere.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

The cd command needs to change the shell’s working directory, which is a property of the parent shell process. If cd were implemented as an external command, the child process would change its own directory, but the parent shell would remain in the same location, making cd ineffective. This is why chdir() is called directly inside the shell.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

To support unlimited piped commands, I would replace the fixed CMD_MAX array with dynamically allocated memory using malloc() and realloc(). This would allow resizing based on the number of commands. The trade-off is higher memory management complexity and potential performance overhead if commands are frequently resized. A balance between preallocating reasonable space and resizing dynamically would be needed.