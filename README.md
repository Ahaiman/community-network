Community Structure in Networks
===================

> In complex networks, a network is said to have a **community structure** if the nodes of the network can be grouped into groups of nodes with dense connections internally, and sparser connections between the groups.

--------
Project Description
-------------
This project contains implementation of the main algorithm for detecting community structures (or clusters) in a network. 
The ability to detect such groups is of significant importance.
For example, partitioning a protein-protein interaction network into clusters can provide a modular view of the network, with different groups of nodes performing different functions within the cell.

> Note:
> * Each module in the project, contains fill information about the purpose of the file, the structure used (if exists) and their functions.
> * The full information, can be found in the header files.
> * For further project's organization considerations, you can use folders. In that case, the "makefile" should be modified respectively.

The Goal
-------------
The goal of this project is to find a division that **maximizes the modularity**:
A division of the graph into groups such that the modularity Q, the sum of all group
modularities, is close to maximal.


The Mathematical Basis
-------------
we represent a network by a graph G = (V,E), and let A be the adjacency matrix of G.
![](examples/1.png)

A given group of vertices in a network is considered a **community** if the number of edges
within the group is significantly more than expected (by chance). We define the **modularity
of a group** as the number of edges within the group minus the **expected** number of edges in
a random graph with the same nodes' degrees.

![](examples/2.png)

Design
-------------
![Click](examples/3.jpg)

![Click](examples/4.jpg)


Executing the Project
-------------
The executable file name is "cluster" (according to the makefile).
It receives two command-line arguments:
The 1st is an input filename, and the 2nd is an output filename. 
The input of the program is a network (a graph), and the output is a list of groups (the division of the network).

File Format
-------------
The input and output files are both **binary** files consisting only of integers.
Binary files are not "human-readable" and cannot be edited in a text editor.
There are no lines, whitespace, or other separators, rather these files consist only of a stream
of bytes. The size of each value in the file is 4 bytes, as the size of an integer in most machines.
This can be determined in code by sizeof(int).

Technology Wise
-------------
This project was created using C language, partitioned into files (modules) and functions.
The design of the program, including interfaces, function declarations, and partition into modules, is described in the "design" section.

Executing The Project
-------------
The makefile compiles all relevant parts of the code and creates an executable named cluster. 
The code will be executed by running the "make all" command in a **UNIX** terminal.
The makefile also contains a clean command.

