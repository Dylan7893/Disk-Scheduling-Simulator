# Disk Scheduling Algorithms in C++

This C++ program implements and compares three common disk scheduling algorithms:

- **FCFS (First-Come, First-Served)**
- **SSTF (Shortest Seek Time First)**
- **LOOK (Elevator Algorithm)**

These algorithms are used in operating systems to optimize disk head movement and reduce seek time.

It allows the user to choose between a sample file or a custom file for input and displays a formatted output of disk head movements and their associated costs (seek, search, data, and total times).

## Input Format

Each line in the input file must follow the format:

Example (from `sample.txt`):

0 98 12  
4 183 8  
7 37 4  
...  

The program reads this data into `Requests` objects and simulates disk scheduling based on the user's chosen algorithm.

## Algorithms Explained

### 1. FCFS (First-Come, First-Served)
Services requests in the order they arrive. Simple but not optimal in terms of seek time.

### 2. SSTF (Shortest Seek Time First)
Selects the request closest to the current head position. Minimizes immediate seek time but may cause starvation.

### 3. LOOK
Moves the head in one direction servicing requests until none remain in that direction, then reverses. Unlike SCAN, it does not go all the way to the disk end unless needed.
