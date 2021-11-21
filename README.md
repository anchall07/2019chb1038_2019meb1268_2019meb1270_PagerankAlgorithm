# CS201_PageRankAlgo_Project
In this project we analyse and implement the page rank algorithm as introduced by Lawrence Page and Sergey Brin that computes ranking scores for the nodes using the network created by the incoming edges in the graph. Thus it is intended for directed graphs, although undirected graphs can be treated as well by converting them into directed graphs.

FinalCode.c file presen tin the Code folder of this repository contains list implementation of page rank algorithm in C language. Once the program is run, it prompts the user for a text file name containing the graph data. Once entered, it calculates the page ranks of all the vertices and displays them in descending order.

PROGRAM FILE: FinalCode.c
INPUT: Name of text file containing graph data. The name of text file along with'.txt' extension should not be more than 15 characters. For example,  dataset01.txt is a valid input as it is a text file and total number of characters is 13.

OUTPUT: The output will contain the following,
  1. Total Number of Vertices in Graph
  2. Total Number of Edges in Graph
  3. Total Number of Iterations executed to calculate page rank of all the vertices in the graph
  4. A list of all the vertices with their calculated page ranks in descending order
  5. Execution Time of Page rank Algorithm
 
 FORMAT OF TEXT FILE CONTAINING GRAPH DATA:
 The text file containing graph data should stricly follow the format mentioned below.
 
  First line should contain the total number of vertices in the graph.The following lines contain data about the directed edges of the graph.
  From the second line onwards, the first entry in each line should be the source vertex number of the directed edge followed by the destination vertex number seperated by a 'space'. 

Some sample text files have been provided in the Dataset folder of this repository. The outputs to those datasets can be seen in the Output folder.
