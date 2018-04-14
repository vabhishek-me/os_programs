## pthread - POSIX Threading Library

```
#include <pthread.h>
```

## The Pthreads API

The subroutines which comprise the Pthreads API can be informally grouped into four major groups:

 - **Thread management:** Routines that work directly on threads - creating, detaching, joining, etc. They also include functions to set/query thread attributes (joinable, scheduling etc.)

 - **Mutexes:** Routines that deal with synchronization, called a "mutex", which is an abbreviation for "mutual exclusion". Mutex functions provide for creating, destroying, locking and unlocking mutexes. These are supplemented by mutex attribute functions that set or modify attributes associated with mutexes.

 - **Condition variables:** Routines that address communications between threads that share a mutex. Based upon programmer specified conditions. This group includes functions to create, destroy, wait and signal based upon specified variable values. Functions to set/query condition variable attributes are also included.

 - **Synchronization:** Routines that manage read/write locks and barriers.

#### Naming Conventions

|     Routine Prefix      |      Functional Group       |
|:------------------------|:----------------------------|
|` pthread_ `             | Threads themselves and miscellaneous subroutines |
|` pthread_attr_ `        | Thread attributes objects |
|` pthread_mutex_ `       | Mutexes |
|` pthread_mutexattr_ `   | Mutex attributes objects. |
|` pthread_cond_ `        | Condition variables |
|` pthread_condattr_ `    | Condition attributes objects |
|` pthread_key_ `         | Thread-specific data keys |
|` pthread_rwlock_ `      | Read/write locks |
|` pthread_barrier_ `     | Synchronization barriers |

#### Thread Management

 - `pthread_create` arguments:

    - **thread:** An opaque, unique identifier for the new thread returned by the subroutine.

    - **attr:** An opaque attribute object that may be used to set thread attributes. You can specify a thread attributes object, or NULL for the default values.

    - **start_routine:** the C routine that the thread will execute once it is created.

    - **arg:** A single argument that may be passed to start_routine. It must be passed by reference as a pointer cast of type void. NULL may be used if no argument is to be passed.

 - The ` pthread_create() ` routine permits the programmer to pass one argument to the thread start routine. For cases where multiple arguments must be passed, this limitation is easily overcome by creating a structure which contains all of the arguments, and then passing a pointer to that structure in the pthread_create() routine. All arguments must be passed by reference and cast to (void *).

 - ` pthread_attr_t ` - Attributes include:

    - Detached or joinable state
    - Scheduling inheritance
    - Scheduling policy
    - Scheduling parameters
    - Scheduling contention scope
    - Stack size
    - Stack address
    - Stack guard (overflow) size

 - The ` pthread_exit() ` routine allows the programmer to specify an optional termination status parameter. This optional parameter is typically returned to threads "joining" the terminated thread.

    - There is a definite problem if main() finishes before the threads it spawned if you don't call pthread_exit() explicitly. All of the threads it created will terminate because main() is done and no longer exists to support the threads.

    - By having main() explicitly call pthread_exit() as the last thing it does, main() will block and be kept alive to support the threads it created until they are done.

 - The ` pthread_join() ` subroutine blocks the calling thread until the specified threadid thread terminates. The programmer is able to obtain the target thread's termination return status if it was specified in the target thread's call to pthread_exit().

 - When a thread is created, one of its attributes defines whether it is joinable or detached. Only threads that are created as joinable can be joined. If a thread is created as detached, it can never be joined.

 - To explicitly create a thread as joinable or detached, the attr argument in the pthread_create() routine is used. The typical 4 step process is:

    - Declare a pthread attribute variable of the ` pthread_attr_t ` data type
    - Initialize the attribute variable with ` pthread_attr_init() `
    - Set the attribute detached status with ` pthread_attr_setdetachstate() `
    - When done, free library resources used by the attribute with ` pthread_attr_destroy() `

 - The ` pthread_detach() ` routine can be used to explicitly detach a thread even though it was created as joinable.
    - The function pthread_detach() can be called from any thread, in particular from within the thread to detach (any thread can obtain its own thread ID using the pthread_self() API).
    - **Recommendation:** If a thread requires joining, consider explicitly creating it as joinable. This provides portability as not all implementations may create threads as joinable by default.

 - ` pthread_self ` returns the unique, system assigned thread ID of the calling thread.

 - ` pthread_equal ` compares two thread IDs. If the two IDs are different 0 is returned, otherwise a non-zero value is returned.

```c

// pthread variable
pthread_t tid;

// pthread attribute
pthread_attr_t attr;

// initialize attributes
pthread_attr_init(&attr);

// destroy attributes - should be destroyed after pthread_create
pthread_attr_destroy(&attr);

// detach a thread -- does not needs to be joined
pthread_detach(tid)

// set detached state - e.g PTHREAD_CREATE_JOINABLE or PTHREAD_CREATE_DETACHED
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)

// get detached state
int
pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);

/* 
 * pthread create and run thread
 * returns 0 for successful thread creation or any non-zero value for error
 */
int pthread_create(pthread_t *restrict thread, 
		   const pthread_attr_t *restrict attr,
		   void *(*start_routine)(void*),
		   void *restrict arg);

// pthread join - blocks the calling thread until the specified threadid thread terminates
pthread_join(pthread_t thread, 
             void **status);

// exit from a thread function
pthread_exit(void *status);

// cancel a thread from some other thread
pthread_cancel(thread_id);

// pthread id - should be called inside the thread routine or function
pthread_self();

// compare two thread ids
pthread_equal(thread_id_1, thread_id_2);

// pthread once - to call a function only once for all threads
pthread_once_t once_control = PTHREAD_ONCE_INIT;  // pthread once control variable
pthread_once(&once_control, onceFunction);     // pthread once called

```

**NOTE:**
The Pthreads API provides several routines that may be used to specify how threads are scheduled for execution.
For example, threads can be scheduled to run FIFO (first-in first-out), RR (round-robin) or OTHER (operating system determines).
It also provides the ability to set a thread's scheduling priority value.

### Examples

 - pthread returning value using pthread_exit() and pthread_join() [pthread_return_value.c](./pthread_return_value.c)


#### Learning Resources

 - <https://computing.llnl.gov/tutorials/pthreads/>
 - <http://www.domaigne.com/blog/computing/joinable-and-detached-threads/>
 - <https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/ptonce.htm>
