Lab Tasks
=========

Students will have to build small programs during labs to take a look at
hardware effects or familiarize themselves with the fundamentals of a particular
parallel or distributed API.

You can use the AUCA server for this work through SSH at 'auca.space'. The login
has the format `<last name>_<first letter of the first name>`.

## Lab #1, Data Hazards

In the first lab, you will be given an example program to illustrate the data
dependency hazards that limit a superscalar CPU's parallelism.

Refer to the `data.c` file in the `Source` directory.

Profile the first approach to sum numbers.

```bash
perf stat -e instructions,cycles,cycle_activity.stalls_total ./data 1
```

Profile the second approach to sum numbers.

```bash
perf stat -e instructions,cycles,cycle_activity.stalls_total ./data 2
```

In both cases, the `perf` program will display instruction and cycle count,
and the number of pipeline stalls. Compare the results. Try to explain them.

## Lab #2, Control Hazards

In the second lab, you will get an example program to illustrate the control
dependencies that limit a pipelined CPU's parallelism.

Refer to the `branch.c` file in the `Source` directory.

First, generate the the input data by running the program with the `-g` flag.

```bash
./branch -g
```

Next, profile it with `perf`.

```bash
perf stat -e instructions,cycles,branch-misses,cycle_activity.stalls_total ./branch
```

It will display instruction and cycle count, the number of branch mispredictions, and
the number of pipeline stalls.

Next, generate the sorted data.

```bash
./branch -g -s
```

Finally, run the profiler with the program again.

```bash
perf stat -e instructions,cycles,branch-misses,cycle_activity.stalls_total ./branch
```

Compare the results.

During labs students will have to practice with common shared- and
distributed-memory API for parallel programming.

You can use the AUCA server for this work through SSH at 'auca.space'. The login
has the format `<last name>_<first letter of the first name>`.

## Lab #3, Pthreads

### Task #1, hello, world

The program should create one thread and print a "hello, world" message from it.

Sample output

```
hello, world
```

### Task #2, Thread Arguments

The program should read a number `n` from standard input, create `n` number of
threads that print a greeting followed by the thread's number.

```
Greeting, from thread #1
Greeting, from thread #3
Greeting, from thread #2
```

### Task #3, Race

The program should try to calculate a total sum for two sets of numbers. For
every set it should use a separate thread.

Sample

```
The total sum is 42
```

### Task #4, Producer and Consumers

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

### Documentation

* `man ls`
* `man mkdir`
* `man touch`
* `man mv`
* `man cp`
* `man rm`
* `man pwd`
* `man perf-stat`

### Links

* [Beej's Guide to C Programming](http://beej.us/guide/bgc)
* [Unix Environment](https://drive.google.com/file/d/0B85z_dQxOMgLNDN3QTFrSmYxZm8/view)
* [POSIX Threads Programming Guide](https://hpc-tutorials.llnl.gov/posix)

### Books

#### Contemporary

* _C Programming: A Modern Approach, 2nd Edition by K. N. King_

* _Advanced Programming in the UNIX Environment, 3rd Edition by W. Richard
Stevens, Stephen A. Rago_

#### Classic

* _C Programming Language, 2nd Edition by Brian W. Kernighan, Dennis M.
Ritchie_

* _The Unix Programming Environment by Brian W. Kernighan, Rob Pike_
