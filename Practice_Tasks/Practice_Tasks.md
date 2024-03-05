Practice Tasks
==============

Here you can find a list of simple programs to illustrate theoretical points discussed during lecture classes or to show the fundamentals of famous parallel or distributed APIs.

## Developer Tools

The following tool is required to be installed to work on this course. It contains the Git version control system that you will use to submit your work to the instructor. The Git installation package also includes a virtual terminal Mintty, the command interpreter Bash, and an SSH client to connect and work with the course server.

* [Git SCM](https://git-scm.com)

On macOS, it is recommended to install the official command-line developer tools from Apple by opening the `Terminal.app` and running the following command.

```bash
xcode-select --install
```

The following code editor is optional. It is not required, but it can be helpful if you will not feel comfortable working with the command-line interface for long periods. You have to install the 'Remote - SSH' extension from the editor to use it with our remote server.

* [Microsoft Visual Studio Code](https://code.visualstudio.com)

This virtualization software and the OS images will allow you to set up your development environment on your computer to not depend on the course server. It is optional to set it up. You are on your own here as we will not help you figure out what to do to get your environment up and running. Internet is full of information about the process, though.

* [Oracle VM VirtualBox](https://www.virtualbox.org)
* [Ubuntu 22.04 Desktop](https://ubuntu.com/#download) with GUI or the [server](https://ubuntu.com/download/server) version without it

## Development Environment

To setup, a development environment, open the terminal (for example, through `git-bash` on Windows) and run the Secure Copy (`scp`) program to download credentials to your machine to login to the course server. Your credentials will include public and private RSA cryptographic keys with a configuration file to point to our server with your login information. To download the keys, you will have to agree with any prompts by typing `yes` and pressing enter. You will also have to type the password when prompted. The password will be given to you during the class. The passwords will be disabled two weeks after the start of the course. Ensure to get your keys before that. You will not be able to see your password when you type it. It is normal not to leak it to your command-line history file or show it to people nearby. Continue typing the password. If the system does not accept your password multiple times, type it into a text editor, cut and paste it into the terminal window. Remember that `CTRL+C` and `CTRL+V` key combinations do not work in most Unix terminals. You will have to use other key combinations that are different for different terminals. Mintty on Windows uses `CTRL+INSERT` and `SHIFT+INSERT` by default. macOS terminal users are luckier as they can use the standard `COMMAND+C` and `COMMAND+V` key combinations.

```bash
# WARNING: If you have existing .ssh keys or configuration files, make a backup of them first.
scp -r <AUCA login>@auca.space:~/.ssh ~/
```

Do not forget to replace `<AUCA login>`, including the `<` and `>` character, with your actual AUCA login. For example, `toksaitov_d` would be the text the instructor of this course would write to download the keys to access the server.

From now on, you can access the server with all the necessary tools installed by issuing the following command in your terminal.

```bash
ssh auca
```

To terminate the connection from the remote server, you can issue the `exit` command.

You may have to do additional things for MPI tasks to access a second server called `auca-peer`. Refer to the instructor's suggestions during a class on what to do.

You must use your machine with an Nvidia GPU for CUDA tasks or ask the instructor to prepare a lab machine for you at AUCA.

## Pipelining

1. [data_and_struct_hazards.c](https://gist.github.com/toksaitov/ff551ec29be3179c7d52def2d91597ae)
2. [control_hazards.c](https://gist.github.com/toksaitov/b1b387a7cf0eeb435b6c2ae4f496b7d5)

## Caches

1. [dram_latency.c](https://gist.github.com/toksaitov/f6767b03fd4970370b4d8caae4a85b3f)
2. [mem_bound.c](https://gist.github.com/toksaitov/2c660e10d064613c1dce18dc36640d1f)
3. [cache_hierarchy.cpp](https://gist.github.com/toksaitov/ed3370f30e10ea1b79bf289a02233b6b)

## PThreads

1. [simple_thread.c](https://gist.github.com/toksaitov/c4fcdcd4ba181d8a27992bc49e733d3d)
2. [thread_args.c](https://gist.github.com/toksaitov/47ce3c26267c6b71ebde01d4b4cadbd8)
3. [mutex.c](https://gist.github.com/toksaitov/562bafcb7e927ef56af2e14347afa118)
4. [spinlock.c](https://gist.github.com/toksaitov/c0c4055ca8fec61d7b4d9ca222a34abb)
6. [barrier.c](https://gist.github.com/toksaitov/fd2a416a2ead84c4f69a110425356308)
7. [semaphore.c](https://gist.github.com/toksaitov/0278a28feb4e9c04a3e7b83ee79a9019)
8. [cond_var.c](https://gist.github.com/toksaitov/759459765e164e9243c031167a8c7a3f)

## MPI

1. [send_recv.c](https://gist.github.com/toksaitov/f24156db3cb8659c38362d1e4e4bd644)
2. [ring.c](https://gist.github.com/toksaitov/96fc5f730ccd19ebfe2cd2cde31673d3)
3. [broadcast.c](https://gist.github.com/toksaitov/b7ddb8d1191bbfb7ca978ec5494863c1)
4. [scatter_gather.c](https://gist.github.com/toksaitov/60fca893881361ad2c1731b6bd5119e3)
5. [reduce.c](https://gist.github.com/toksaitov/41dc5864c98ce785f5783e983b7e9cef)

## CUDA

1. [vector.cu](https://gist.github.com/toksaitov/e6e5bdbeee80fed63387900db0f64566)
2. [matrix.cu](https://gist.github.com/toksaitov/af48605b2db18cd5a4a461287468b1db)
3. [reduce.cu](https://gist.github.com/toksaitov/7244013d213b838a8151cf791fcd1245)

## Documentation

* `man gcc`
* `man gdb`
* `man perf-stat`
* `man 7 pthreads`
* `man mpicc`
* `man mpiexec`
* `man MPI_*`

## Links

* [Beej's Guide to C Programming](http://beej.us/guide/bgc)
* [Unix Environment](https://drive.google.com/file/d/0B85z_dQxOMgLNDN3QTFrSmYxZm8/view)
* [POSIX Threads Programming Guide](https://hpc-tutorials.llnl.gov/posix)
* [MPI Tutorial](https://mpitutorial.com)
* [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html)

## Books

### Contemporary

* _C Programming: A Modern Approach, 2nd Edition by K. N. King_

* _Advanced Programming in the UNIX Environment, 3rd Edition by W. Richard Stevens, Stephen A. Rago_

### Classic

* _C Programming Language, 2nd Edition by Brian W. Kernighan, Dennis M. Ritchie_

* _The Unix Programming Environment by Brian W. Kernighan, Rob Pike_
