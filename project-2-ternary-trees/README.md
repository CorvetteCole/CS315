# About
This program reads an amount of integers (n) from standard input, inserts them in to an empty tree (type defined by a parameter) and then prints the tree in symmetric order.

# Usage
In addition with standard input being piped in, this program require 3 parameters as well. 
- The first is n and it refers to the amount of integers to read from standard input
- The second refers to the number of values present per node in the tree (e.g. should a node contain just a, ab, abc, etc)
- The third refers to the number of children each node in the tree should have. For a ternary tree this should be 3, for a quaternary tree this would be 4, and so on. 

Example: `./randGen.pl 49 10000 | ./ternary 1000 2 3`

You can also just use `make run`

# Extra Credit
I did technically turn this project in a little bit late, but I am hoping that could be overlooked in terms of extra credit since it is late BECAUSE of the extra credit. It was a really cool challenge so I just kept working and it made the project late. I actually wrote some code that handles any combination of values and children per node which was actually quite hard to initially model. I have lots of drawings etc that I would have loved to include had they been cleaned up a little bit. 
