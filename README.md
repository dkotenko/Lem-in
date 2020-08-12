# Lem-in
School 42 project: a combination of Shortest path problem and Maximum flow problem

Summary: we have non-directed acycled graph with nodes Start and End. Also we have objects that must be conducted from Start to End in accordance to a rule: every vertex, except Start and End, can contain only one object in a turn. We must find a way to conduct N objects from Start to End by minimal number of turns and print object moves every turn.

**How to solve this problem**  
Lets call a sequence of nodes from Start to End as Path. The minimal number of turns can be provided by k shortests Paths. To find them we must find, by different ways, the shortest Path and delete its nodes from the graph until k will be reached. Also we must remember about crossing Paths (Pic. 1)
![](<img/Edrowzee example.png>)  
Pic. 1. Crossing Paths example. Author: [Edrowzee](https://github.com/nApTu3aHs)  
  
Here we have n = 6 object to provide. And there is a situation when we could not delete every Shortest Path, because we will have 3 Paths (0345, 01625, 07895) when there is Paths (0325, 0745) with less amount of turns to conduct objects. [Disjoint Path Finding](http://www.macfreek.nl/memory/Disjoint_Path_Finding) is the way to operate crossing paths.  
  
**What was implemented in this project**
- best possible solution search
- relatively fast speed ( < 3 seconds)
- hash tables
- Python Visualizer

**How to run Python Visualizer**  
./lem-in "inputfile" | Python3 vi/vi.py  
![](<img/viz.png>)  
Pic. 2. Python Visualization
