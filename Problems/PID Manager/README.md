# PID Manager

### Question

Create a Process Id (PID) manager that keeps track of free PIDs and ensures that no two active processes are having the same pid.
Once a process terminates the PID manager may assigns its pid to new process.


Use the following constants to identify the range of possible pid values:

```
#define MIN PID 100
#define MAX PID 1000
```

You may use any data structure of your choice to represent the availability of process identifiers. 
One strategy is to adopt what Linux has done and use a bitmap in which a value of 0 at position i indicates that a process id of value i is available and a value of 1 indicates that the process id is currently in use.


Implement the following API for obtaining and releasing a pid:

 - ` int allocate map(void) ` - Creates and initializes a data structure for representing pids; returns—1 if unsuccessfull, 1 if successfull.
 - ` int allocate pid(void) ` - Allocates and returns a pid; returns— 1 if unable to allocate a pid (all pids are in use).
 - ` void release pid(int pid) ` - Releases a pid.


Modify the above problem by writing a multithreaded program that tests your solution. 
You will create a number of threads; for example, 100; and each thread will request a pid, sleep for a random period of time, and then release the pid. (Sleeping for a random period of time approximates the typical pid usage in which a pid is assigned to a new process, the process executes and then terminates, and the pid is released on the process’s termination.)

---

### Implementation

 - [PID Manager](./pid_manager.c)
