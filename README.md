# XV6

Instructor: Professor Nael B. Abu-Ghazaleh
Team: Arman Irani & Varun Chawla
June 8th, 2021
Lab 2 XV6 Adding Real Kernel Threads to XV6
Summary of Work
The changes are majorly done via clone system call that was used to create a new
child thread but under the same address space of its parent. Major effort was spent in
creating thread.c and proc.c having locking and cloning routines.
Implementation was divided in 3 phases viz.
1. Clone routine creation
2. Creating threading routines and utilizing spin locks.
3. Frisbee.c Simulation
Simulation of the programs is done via frisbee.c and the simulation results came as
expected mentioned in the project 2 directives. A total of about 12 files were
changed for implementing and we will walk you through the changes below.
Changes
Files Changed
1. Makefile
2. usys.S
3. user.h
4. thread.h
5. thread.c
6. sysproc.c
7. syscall.c
8. syscall.h
9. proc.h
10. defs.h
11. frisbee.c
12. Proc.c
 
1. Makefile
- Added thread library
- Frisbee.c to user programs
2. usys.S
- Added SYSCALL(clone) 
3. user.h
- Added “int clone(void*, int);
- Added declarations of the functions in thread.c
- Added lock_t structure
 4. thread.h
- Created header file for library
- Initialization for lock state (lock_t)

5. thread.c
- C file for thread library implementation
- Created files as lock functions, lock_init, lock_acquire, lock_release,
and thread_create
- Allocates enough memory space for the new thread process and will
start the routine function if and only if the cloned process is new. 
 6. Sysproc.c
- Added sys_clone(void) function to call clone and pass in the size of
parent and pointer to the child’s new stack
 7. Syscall.h 
- Added number for SYS_clone
8. syscall.c
- Added code for sys_clone implementation.
 9. Proc.h
- Added “isthread” int value in the proc struct. This will be useful in
wait() and exit() so that the system knows how to handle threads. This
value is updated to 1 if the process is identified as a thread.
 10. Proc.c
- Added clone function
- Creates a new process that shares the address space of its parent.
- Sets the process “isthread = 1”
- Returns PID of new process
- Modified wait()
- Only free’s the processes page table and physical memory if it is
not a thread. I.e. “isthread ==1”. This avoids closing the file
descriptors before all the threads are done.
- Modified exit()
- Disabled passing the abandoned children to the first process,
which should not be done until the last thread has completed.

11. frisbee.c
- User program to run the frisbee simulation game.
- Creates a user entered number of threads and passes, and for each calls
the “passprintfunction” which handles the logic for printing out when a
thread has “passed” a token to another thread. 
12. defs.h
- Added int clone(void*, int);
Final Output 
$ frisbee 4 6
