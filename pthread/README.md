# pthread - POSIX Threading Library

```
#include <pthread.h>
```

## The Pthreads API

The subroutines which comprise the Pthreads API can be informally grouped into four major groups:

 - **Thread management:** Routines that work directly on threads - creating, detaching, joining, etc. They also include functions to set/query thread attributes (joinable, scheduling etc.)

 - **Mutexes:** Routines that deal with synchronization, called a "mutex", which is an abbreviation for "mutual exclusion". Mutex functions provide for creating, destroying, locking and unlocking mutexes. These are supplemented by mutex attribute functions that set or modify attributes associated with mutexes.

 - **Condition variables:** Routines that address communications between threads that share a mutex. Based upon programmer specified conditions. This group includes functions to create, destroy, wait and signal based upon specified variable values. Functions to set/query condition variable attributes are also included.

 - **Synchronization:** Routines that manage read/write locks and barriers.

### Naming Conventions

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

### Thread Management

 - `pthread_create` arguments:

    - **thread:** An opaque, unique identifier for the new thread returned by the subroutine.

    - **attr:** An opaque attribute object that may be used to set thread attributes. You can specify a thread attributes object, or NULL for the default values.

    - **start_routine:** the C routine that the thread will execute once it is created.

    - **arg:** A single argument that may be passed to start_routine. It must be passed by reference as a pointer cast of type void. NULL may be used if no argument is to be passed.

 - The ` pthread_create() ` routine permits the programmer to pass one argument to the thread start routine. For cases where multiple arguments must be passed, this limitation is easily overcome by creating a structure which contains all of the arguments, and then passing a pointer to that structure in the `pthread_create()` routine. All arguments must be passed by reference and cast to `(void *)`.


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

    - There is a definite problem if `main()` finishes before the threads it spawned if you don't call `pthread_exit()` explicitly. All of the threads it created will terminate because `main()` is done and no longer exists to support the threads.

    - By having `main()` explicitly call `pthread_exit()` as the last thing it does, `main()` will block and be kept alive to support the threads it created until they are done.

 - The ` pthread_join() ` subroutine blocks the calling thread until the specified threadid thread terminates. The programmer is able to obtain the target thread's termination return status if it was specified in the target thread's call to `pthread_exit()`.

 - When a thread is created, one of its attributes defines whether it is joinable or detached. Only threads that are created as joinable can be joined. If a thread is created as detached, it can never be joined.

 - To explicitly create a thread as joinable or detached, the attr argument in the `pthread_create()` routine is used. The typical 4 step process is:

    - Declare a pthread attribute variable of the ` pthread_attr_t ` data type
    - Initialize the attribute variable with ` pthread_attr_init() `
    - Set the attribute detached status with ` pthread_attr_setdetachstate() `
    - When done, free library resources used by the attribute with ` pthread_attr_destroy() `

 - The ` pthread_detach() ` routine can be used to explicitly detach a thread even though it was created as joinable.

    - The function pthread_detach() can be called from any thread, in particular from within the thread to detach (any thread can obtain its own thread ID using the `pthread_self()` API).

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


### Mutexes

  - Mutex is an abbreviation for "mutual exclusion". Mutex variables are one of the primary means of implementing thread synchronization and for protecting shared data when multiple writes occur. The basic concept of a mutex as used in Pthreads is that only one thread can lock (or own) a mutex variable at any given time. Thus, even if several threads try to lock a mutex only one thread will be successful. No other thread can own that mutex until the owning thread unlocks that mutex.

  - A typical sequence in the use of a mutex is as follows:
    - Create and initialize a mutex variable
    - Several threads attempt to lock the mutex
    - Only one succeeds and that thread owns the mutex
    - The owner thread performs some set of actions
    - The owner unlocks the mutex
    - Another thread acquires the mutex and repeats the process
    - Finally the mutex is destroyed

  - When several threads compete for a mutex, the losers block at that call - an unblocking call is available with "trylock" instead of the "lock" call.

  - Mutex variables must be declared with type ` pthread_mutex_t `, and must be initialized before they can be used. There are two ways to initialize a mutex variable:

    - Statically, when it is declared. For example: ` pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER `

    - Dynamically, with the pthread_mutex_init() routine. This method permits setting mutex object attributes, attr.

  - The attr object is used to establish properties for the mutex object, and must be of type ` pthread_mutexattr_t ` if used (may be specified as NULL to accept defaults). The Pthreads standard defines three optional mutex attributes:
    - **Protocol:** Specifies the protocol used to prevent priority inversions for a mutex.
    - **Prioceiling:** Specifies the priority ceiling of a mutex.
    - **Process-shared:** Specifies the process sharing of a mutex.

  - The ` pthread_mutexattr_init() ` and ` pthread_mutexattr_destroy() ` routines are used to create and destroy mutex attribute objects respectively.

  - The ` pthread_mutex_lock() ` routine is used by a thread to acquire a lock on the specified mutex variable. If the mutex is already locked by another thread, this call will block the calling thread until the mutex is unlocked.

  - ` pthread_mutex_trylock() ` will attempt to lock a mutex. If the mutex is already locked, `pthread_mutex_trylock()` will not block waiting for the mutex, but will
     return an error condition. This routine may be useful in preventing deadlock conditions, as in a priority-inversion situation.

    - If successful, pthread_mutex_trylock() will return zero, otherwise an error number will be returned to indicate the error.

  - ` pthread_mutex_unlock() ` will unlock a mutex if called by the owning thread. Calling this routine is required after a thread has completed its use of protected data if other threads are to acquire the mutex for their work with the protected data. An error will be returned if:
    - If the mutex was already unlocked
    - If the mutex is owned by another thread

```c

  // pthread mutex variable
  pthread_mutex_t lock;


  // static initialization
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  /*
   * dynamic initialization
   */

  // create mutex with default attributes
  pthread_mutex_init(&lock, NULL);

  // create mutex with attributes
  pthread_mutexattr_t lock_attr;
  pthread_mutexattr_init(&lock_attr);
  pthread_mutex_init(&lock, &lock_attr)


  // mutex lock - blocking other
  pthread_mutex_lock(&lock)

  /*
   * pthread_mutex_trylock -- attempt to lock a mutex without blocking
   * returns 0 if locked or error if the mutex is already locked
   */
  pthread_mutex_trylock(&lock)

  // mutex unlock
  pthread_mutex_unlock(&lock)


  // destroy mutex variable
  pthread_mutex_destroy(&lock)

  // destroy mutex attribute
  pthread_mutexattr_destroy(&lock_attr);
```


### Condition Variables

  - While mutexes implement synchronization by controlling thread access to data, condition variables allow threads to synchronize based upon the actual value of data.

  - A condition variable is always used in conjunction with a mutex lock.

  - Condition variables must be declared with type ` pthread_cond_t `, and must be initialized before they can be used. There are two ways to initialize a condition variable:

    - Statically, when it is declared. For example: ` pthread_cond_t myconvar = PTHREAD_COND_INITIALIZER; `

    - Dynamically, with the ` pthread_cond_init() ` routine.

  - The optional attr object is used to set condition variable attributes. There is only one attribute defined for condition variables: process-shared, which allows the condition variable to be seen by threads in other processes. The attribute object, if used, must be of type ` pthread_condattr_t ` (may be specified as NULL to accept defaults).

  - The ` pthread_condattr_init() ` and ` pthread_condattr_destroy() ` routines are used to create and destroy condition variable attribute objects.

  - ` pthread_cond_destroy() ` should be used to free a condition variable that is no longer needed.

  - ` pthread_cond_wait() ` blocks the calling thread until the specified condition is signalled. This routine should be called while mutex is locked, and it will automatically release the mutex while it waits. After signal is received and thread is awakened, mutex will be automatically locked for use by the thread. The programmer is then responsible for unlocking mutex when the thread is finished with it.

  - **Recommendation:** Using a WHILE loop instead of an IF statement to check the waited for condition can help deal with several potential problems, such as:

     - If several threads are waiting for the same wake up signal, they will take turns acquiring the mutex, and any one of them can then modify the condition they all waited for.

     - If the thread received the signal in error due to a program bug

     - The Pthreads library is permitted to issue spurious wake ups to a waiting thread without violating the standard.

  - The ` pthread_cond_signal() ` routine is used to signal (or wake up) another thread which is waiting on the condition variable. It should be called after mutex is locked, and must unlock mutex in order for ` pthread_cond_wait() ` routine to complete.

  - The ` pthread_cond_broadcast() ` routine should be used instead of ` pthread_cond_signal() ` if more than one thread is in a blocking wait state.


```c

  // condition variable
  pthread_cond_t condition;
  

  // static initialization
  pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

  /*
   * dynamic initialization
   */

  // create condition variable with default attributes
  pthread_cond_init(&condition, NULL);

  // create condition variable with attributes
  pthread_condattr_t cattr;
  pthread_condattr_init(&cattr);
  pthread_cond_init(&condition, &cattr);

  
  // check and wait for condition
  pthread_cond_wait(&condition, &lock);

  // unblock one single thread waiting for a condition variable
  pthread_cond_signal(&condition);

  // unblock all threads waiting for a condition variable
  pthread_cond_broadcast(&condition);


  // destroy condition variable
  pthread_cond_destroy(&condition);

  // destroy condition attributes
  pthread_condattr_destroy(&cattr);

```

### Examples

 - pthread returning value using pthread_exit() and pthread_join() [pthread_return_value.c](./pthread_return_value.c)


#### Learning Resources

 - <https://computing.llnl.gov/tutorials/pthreads/>
 - <http://www.domaigne.com/blog/computing/joinable-and-detached-threads/>
 - <https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/ptonce.htm>
