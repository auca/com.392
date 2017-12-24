Lab Tasks
=========

During labs students will have to practice with common shared- and
distributed-memory API for parallel programming.

You can use the AUCA server for this work through SSH at 'auca.space'. The login
has the format `<last name>_<first letter of the first name>`.

## Lab #1, Pthreads

### Task #1, hello, world

The program should create one thread and print a "hello, world" message from it.

Sample output

```
hello, world
```

### Task #2, N Threads

The program should read a number `n` from standard input and create `n` number
of threads that print a greeting message to standard output.

Sample output

```
Hello
Hello
Hello
```

### Task #3, Thread Argument

The program should read a number `n` from standard input, create `n` number of
threads that print a greeting followed by the thread's number.

```
Greeting, from thread #1
Greeting, from thread #3
Greeting, from thread #2
```

### Task #4, Alarm

Scan continuously for input for a number of seconds. Set up a timer to print an
alarm message in the specified number of seconds. Use threads and the `sleep`
function from `unistd.h` header to create each timer.

Sample

```
10
Alarm! 10 seconds have passed
2
Alarm! 2 seconds have passed
```

### Task #5, Race

The program should try to calculate a total sum for two sets of numbers. For
every set it should use a separate thread.

Sample

```
The total sum is 42
```

### Task #6, Producer and Consumers

Create a number of consumer threads that try to remove some work by
decrementing a globally shared counter by one. Create a second producers
thread that tries to add multiple work items by incrementing the
counter by some fixed value greater than one.

Print the output for every major operation from the producer thread
and from the consumer threads.

```
Specify the <number of threads to start>
2
Producer: locking the mutex
Producer: incrementing the value to 4 and signaling
Consumer #1: locking the mutex
Consumer #2: locking the mutex
Producer: unlocking the mutex
Consumer #1: decrementing the value to 3
Consumer #1: unlocking the mutex
Consumer #1: locking the mutex
Consumer #2: decrementing the value to 2
Consumer #2: unlocking the mutex
Consumer #2: locking the mutex
Consumer #1: decrementing the value to 1
Consumer #1: unlocking the mutex
Consumer #1: locking the mutex
Consumer #2: decrementing the value to 0
Consumer #2: unlocking the mutex
Consumer #2: locking the mutex
Consumer #1: the counter is equal to zero. Waiting for signal
Consumer #2: the counter is equal to zero. Waiting for signal
```

### Task #7, Readers–writer Lock

Given a sample lab, try to solve the multiple-readers-and-single-writer problem.

### Task #8, Hello from MPI

Given _N_ processes, send a "hello" message from processes with ranks _1...N_ to
the process with rank _0_.

```
Hello, from a master process 0.
Waiting for messages.
Hello, from a generic process 1 out of 3.
Hello, from a generic process 2 out of 3.
Got a message 'hello' in master from process 1.
Got a message 'hello' in master from process 2.
```

### Task #9, Ping Pong

Send a fixed number of pings from one process to another. The number of
processes should be two. The ping message should be an integer counter. The
counter should be incremented by the sender before processing. The receiving
process should print the received message. After that, the two processes should
swap roles.

```
Process 0 out of 2 is sending 1 to process 1
Process 1 out of 2 got 1 from process 0
Process 1 out of 2 is sending 2 to process 0
Process 0 out of 2 got 2 from process 1
Process 0 out of 2 is sending 3 to process 1
Process 1 out of 2 got 3 from process 0
Process 1 out of 2 is sending 4 to process 0
Process 0 out of 2 got 4 from process 1
Process 0 out of 2 is sending 5 to process 1
Process 1 out of 2 got 5 from process 0
Process 1 out of 2 is sending 6 to process 0
Process 0 out of 2 got 6 from process 1
Process 0 out of 2 is sending 7 to process 1
Process 1 out of 2 got 7 from process 0
Process 1 out of 2 is sending 8 to process 0
Process 0 out of 2 got 8 from process 1
Process 0 out of 2 is sending 9 to process 1
Process 1 out of 2 got 9 from process 0
Process 1 out of 2 is sending 10 to process 0
Process 0 out of 2 got 10 from process 1
```

### Task #10, Ring

Pass some integer value (e.g., 42) around _N_ processes starting from the root
process with rank 0. Every process should print a message upon receiving the
data token.

```
Process 0 out of 10 has a token 42
Process 1 out of 10 has a token 0
Process 2 out of 10 has a token 0
Process 3 out of 10 has a token 0
Process 4 out of 10 has a token 0
Process 5 out of 10 has a token 0
Process 6 out of 10 has a token 0
Process 7 out of 10 has a token 0
Process 8 out of 10 has a token 0
Process 9 out of 10 has a token 0
Process 0 out of 10 is sending the token 42 to process 1
Process 1 out of 10 got the token 42 from process 0
Process 1 out of 10 is sending the token 42 to process 2
Process 2 out of 10 got the token 42 from process 1
Process 2 out of 10 is sending the token 42 to process 3
Process 3 out of 10 got the token 42 from process 2
Process 3 out of 10 is sending the token 42 to process 4
Process 4 out of 10 got the token 42 from process 3
Process 4 out of 10 is sending the token 42 to process 5
Process 5 out of 10 got the token 42 from process 4
Process 5 out of 10 is sending the token 42 to process 6
Process 6 out of 10 got the token 42 from process 5
Process 6 out of 10 is sending the token 42 to process 7
Process 7 out of 10 got the token 42 from process 6
Process 7 out of 10 is sending the token 42 to process 8
Process 8 out of 10 got the token 42 from process 7
Process 8 out of 10 is sending the token 42 to process 9
Process 9 out of 10 got the token 42 from process 8
Process 9 out of 10 is sending the token 42 to process 0
Process 0 out of 10 got the token 42 from process 9
```

### Task #11, Broadcast

Read the documentation about the `MPI_Bcast` call. Try to implement a simple
version of the call with the functions `MPI_Send` and `MPI_Recv`.

Benchmark your implementation with the real call to `MPI_Bcast`. Use the
`MPI_Wtime` to measure function execution time. Use the `MPI_Barrier` to
synchronize the process between calls.

```
my_bcast time 1.483231
mpi_bcast time 0.000322
```

### Task #12, Parallel Average

Calculate the average of a list of random numbers. Use `MPI_Scatter` and
`MPI_Gather` in the first implementation. Use `MPI_Scatter` and `MPI_Reduce` in
the second implementation. Benchmark two solutions with different list sizes.

```
Parallel average: 1174297336.84, time: 0.01
Serial average: 1174297336.84, time: 0.12
```

### Compilation

#### Pthreads

To compile your program on Linux run the following

    LDFLAGS=-pthread make <Source File Name>

To compile your program on Mac OS run the following

    make <Source File Name>

#### MPI

To compile your program with MPICH

    CC=mpicc make <Source File Name>

To run your program

    mpiexec -n 10 ./<Program File Name>
    
where the `-n` flag specifies the number of processes to start.

### Documentation

    man pthreads
    MPICH man pages

### Links

#### Pthreads

* [POSIX Threads Programming Guide](https://computing.llnl.gov/tutorials/pthreads)

#### MPI

* [MPICH](http://www.mpich.org/static/docs/latest/www)
* [MPI Tutorial](http://mpitutorial.com/tutorials)

### Books

* C Programming: A Modern Approach, 2nd Edition by K. N. King

#### Pthreads

* Programming with POSIX Threads, David R. Butenhof

#### MPI

* An Introduction to Parallel Programming by Peter Pacheco

