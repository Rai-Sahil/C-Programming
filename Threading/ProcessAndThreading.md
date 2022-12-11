# Process

* System call is involved in these. Using fork system call.
* OS treats different processes differently. 
* Different process have different copies of code, data and files.
* Content switching very lower.
* Blocking one process will not block another process.
* Independent

# Threads

* No system call required in user level thread. It is basically an API
* The whole thread is just one case.
* Threads have the same code same files just different stacks and registers.
* They are very fast.
* Content switching is faster.
* Blocking a thread will block entire process as well.
* Interdependent

Each program can have number of process executing in it and each process have number of threads in it. It is a basic unit of CPU utilization.
## Contents of a Thread
* Thread ID -> A program counter -> register set -> stack

If a process has more than one thread at a time it can perform more than one task at a time.

## Benefits of Multi Threading
1. Responsiveness
    - Even if it part of it is stopped rest of the program will still work.
2. Resource Sharing
    - Threads shares the code, data and files. Allows many threads under the same address.
3. Economy 
    - Allocating memory to process is costly. Hence we have threads because they share data
4. Utilizaion of Multiprocessor Architecture
    - Increases concurrency.
