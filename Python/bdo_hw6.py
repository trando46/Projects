# Bao Tran Do
# 05/23/2021


import numpy as np 
import sys, subprocess
import pydot 
import pygraphviz as pgv 

def matrix(file):
    contents = open(file).read().strip()
    return [item.split() for item in contents.split('\n')[:]] 


def adjacencyMatrix(A, name):
    rows = len(A)
    columns = len(A[0])

    G = pgv.AGraph() 

    graphDirected = False

    # Check when there is nothing there 
    if rows == 0 and columns == 0:
        return 
    elif rows == 1 and columns == 1: 
        # Check if it is null 
        if(A[0][0] != 'null'):
            G.add_node(str(1))
        else: 
            # check if there is only 1 element 
            return 
    elif rows > 1 and columns > 1: 
        if rows == columns:
            print(rows)
            print(columns)

            # checking for directed graph
            for i in range(rows):
                for j in range(columns):
                    if A[i][j] != A[j][i]:
                        graphDirected = True 

            # setting the graph type 
            if graphDirected == False:
                # not a directed graph 
                G = pgv.AGraph(strict=True, directed=False)
            else: 
                #directed graph 
                G = pgv.AGraph(strict=False, directed=True)
    
            # adding the nodes and edges 
            for i in range(rows):
                for j in range(columns):
                    if A[i][j] == '1':
                        # remove the line below this 
                        #if G.has_edge(i+1,j+1) == False and G.has_edge(j+1,i+1) == False: 
                        G.add_edge(str(i +1), str(j + 1), color='blue')
                    elif A[i][j] == '0':
                        # if there is no connection just draw the nodes
                        G.add_node(str(i+1))

    print(G.is_directed())
    G.layout() 
    G.write(name+'.dot')
    G.draw(name+'.png')

def creation(file,name):
    adjacencyMatrix(matrix(file), name)



    #graph = pydot.Dot('my_graph', graph_type='graph', bgcolor='yellow')

creation('adj1.txt','adj1')
creation('adj2.txt','adj2')
creation('adj3.txt','adj3')
creation('adj4.txt','adj4')


