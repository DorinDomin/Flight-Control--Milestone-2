# Searching Algorithms Server-Ex4
Purpose of this extercise- implement a few searches algorithms, compare them (by who had the smalles run time), and using the best algorithm as the problem solver on the server side. Among this create parallel server (that can work with multiple clients), and a serial server (that can accept clients one after the other.

## Usage

In order to use the project, you need to do the following steps:

First, you need to define a kind of problem,solution and algorithm in the code. The default is a maze problem that returns the shortest path using a*.

Then, run the following commands in the terminal (first cd to the right path)
```
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

./a.out 5400
```

After that you can start connecting to the socket with telnet and send it different problems and recieve solutions

## How it works:

### The Algorithms

The algorithms are all types of searchers that can solve problems

### The Server

There are 2 types of servers you can choose to use, parallel or serial

### The File Manager

Solutions are saved on the disk and if a solution already exists for a given problem, we return it instead of calculating it.

### The ClientHandler

Defines how to handle each client. Has a kind of File Manager and Solver.


## Version Control

We used Git for this project

https://github.com/DorinDomin/Flight-Control--Milestone-2

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.


## Authors
Dorin Domin, Netanel Tamir
