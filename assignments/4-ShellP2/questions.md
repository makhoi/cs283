1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  fork creates a new process so the shell can continue running while the command executes in a separate child process. If we used execvp directly in the shell, the shell itself would be replaced by the new program, making it impossible to handle multiple commands.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If fork() fails, it means the system couldn’t create a new process, usually due to resource limits. My implementation checks if fork() returns -1 and prints an error message using perror(), then returns an error code to avoid executing further commands.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  execvp() searches for the command in directories listed in the PATH environment variable. It checks each directory in PATH until it finds an executable matching the command name.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  wait() makes the parent shell process wait for the child process to finish, preventing zombie processes. If we didn’t call it, the child would remain in a zombie state until the shell exits or the system cleans it up.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  WEXITSTATUS() extracts the exit status of the child process after it terminates. It’s important because it lets us know if the command ran successfully (0) or failed with an error code.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  It detects when an argument starts with a quote and ensures everything inside the quotes is treated as a single argument, even if it contains spaces. This is necessary to correctly handle commands like echo "hello world" where "hello world" should be passed as one argument.



7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  I removed pipe parsing since it’s not needed in this step and switched from using a command list to a single cmd_buff structure. The hardest part was handling spaces correctly, especially inside quotes, without breaking argument parsing.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  Signals let processes communicate asynchronously by sending notifications about events like termination or interrupts. Unlike pipes or shared memory, signals are lightweight and don’t require a direct data exchange between processes.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  
    SIGKILL (9): Immediately terminates a process and cannot be ignored or caught. Used when a process is unresponsive.
    SIGTERM (15): Politely asks a process to terminate, allowing it to clean up resources before exiting.
    SIGINT (2): Sent when the user presses Ctrl+C, typically used to stop a running program from the terminal.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  SIGSTOP pauses a process but doesn’t terminate it. Unlike SIGINT, it cannot be caught, blocked, or ignored because it’s meant to forcefully suspend execution until SIGCONT is sent.