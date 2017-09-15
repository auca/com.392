Lab Tasks
=========

During labs students will have to practice with common shared- and
distributed-memory API for parallel programming.

You can use the AUCA server for this work through SSH at 'auca.space'. The login
has the format `<last name>_<first letter of the first name>`.

## Lab #1, Pthreads

### Task #1, "hello, world"

The program should create one thread and print a "hello, world" message from it.

Sample output

    hello, world

### Task #2, "N Threads"

The program should read a number `n` from standard input and create `n` number
of threads that print a greeting message to standard output.

Sample output

    Hello
    Hello
    Hello

### Task #3, "Thread Argument"

The program shouild read a number `n` from standard input, create `n` number of
threads that print a greeting followed by the thread's number.

    Greeting, from thread #1
    Greeting, from thread #3
    Greeting, from thread #2

### Task #4, "Alarm"

Scan continuously for input for a number of seconds. Set up a timer to print an
alarm message in the specified number of seconds. Use threads and the `sleep`
function from `unistd.h` header to create each timer.

Sample

    10
    Alarm! 10 seconds have passed
    2
    Alarm! 2 seconds have passed

### Task #5, "Race"

The program should try to calculate a total sum for two sets of numbers. For
every set it should use a separate thread.

Sample

    The total sum is 42

### Task #6, "Producer and Consumers"

The task will be described in class.

### Documentation

    man pthreads

### Links

* [POSIX Threads Programming Guide](https://computing.llnl.gov/tutorials/pthreads)

### Books

* C Programming: A Modern Approach, 2nd Edition by K. N. King
* Programming with POSIX Threads, David R. Butenhof

