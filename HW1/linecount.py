#!/usr/bin/env python
from mpi4py import MPI
import os

comm = MPI.COMM_WORLD
x = comm.rank
root = 0
files = [[] for i in range(comm.size)]
current = 0

if comm.rank == root:
	for filename in os.listdir("."):
	    if filename.endswith(".txt"):
	    	files[current].append(filename)
	    	current = (current + 1) % comm.size

my_files = comm.scatter(files, root)
# print ("rank = " + str(comm.rank) + "; my files are " + str(my_files))

num_lines = 0
for filename in my_files:
	num_lines = max(num_lines, sum(1 for line in open(filename)))

# print ("rank = " + str(comm.rank) + "; num_lines = " + str(num_lines))

y = comm.reduce(num_lines, op = MPI.MAX)

# print ("rank = " + str(x) + "; y = " + str(y))

if comm.rank == root:
	print(y)