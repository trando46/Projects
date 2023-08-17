# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).

Author: Bao Tran Tran Do
Date: April 10, 2023
Version: 1.0
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))

    Source for pseudocode: https://en.wikipedia.org/wiki/Depth-first_search
    using the iterative route
    """
    #note from the hw
    # Implement the depth-first search (DFS) algorithm in the depthFirstSearch function in search.py.
    # To make your algorithm complete, write the graph search version of DFS,
    # which avoids expanding any already visited states.
    # need to use a stack cause DFS is a LIFO

    #print("Start:", problem.getStartState())
    # Start: (5, 5)
    #print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # Is the start a goal? False
    #print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    # Start's successors: [((5, 4), 'South', 1), ((4, 5), 'West', 1)]

    # initialize the variables
    dfsStack = util.Stack()  # this is a temporary holder for the nodes for the DFS - LIFO
    startState = problem.getStartState()  # the start state
    isStartAGoal = problem.isGoalState(problem.getStartState())  # check to see of the start position is the goal
    # Remember that a search node must contain not only a state but also the information necessary to reconstruct the path (plan) which gets to that state.
    startNode = (startState, [])  # a tuple to contain the start node state and also its path (node, path)

    # push the startNode into the stack (reminder the start node will expand to have different nodes as their children
    # when you go out to explore
    dfsStack.push(startNode)

    # if the stack is not empty call the genericSearchMethod
    if not dfsStack.isEmpty():
        return genericSearchMethod(problem,type="DFS",dataStructure=dfsStack,isStartAGoal=isStartAGoal)

    util.raiseNotDefined()

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first.

    Source code for pseudocode: https://en.wikipedia.org/wiki/Breadth-first_search
    """
    #print("Start:", problem.getStartState())
    # Start: (5, 5)
    #print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # Is the start a goal? False
    #print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    # Start's successors: [((5, 4), 'South', 1), ((4, 5), 'West', 1)]

    # initialize the variables
    bfsQueue = util.Queue()  # this is a temporary holder for the nodes for the BFS - FIFO
    startState = problem.getStartState()  # the start state
    isStartAGoal = problem.isGoalState(problem.getStartState())  # check to see of the start position is the goal
    # Remember that a search node must contain not only a state but also the information necessary to reconstruct the path (plan) which gets to that state.
    startNode = (startState, [])  # a tuple to contain the start node state and also its path (node, path)

    # push the startNode into the queue (reminder the start node will expand to have different nodes as their children
    # when you go out to explore
    bfsQueue.push(startNode)

    # if the queue is not empy call the genericSearchMethod
    if not bfsQueue.isEmpty():
        return genericSearchMethod(problem,type ="BFS",dataStructure=bfsQueue, isStartAGoal=isStartAGoal)

    util.raiseNotDefined()

def uniformCostSearch(problem):
    """Search the node of least total cost first.

    L3b_uniformedSearch.pdf file from lecture slide 32 have a pseudocode for uniform search
    """

    # Need to replace BFS FIFO queue with priority queue
    # need to track cost so far

    #print("Start:", problem.getStartState())
    # Start: (5, 5)
    #print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # Is the start a goal? False
    #print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    # Start's successors: [((5, 4), 'South', 1), ((4, 5), 'West', 1)]

    # initialize the variables
    ucsPriorityQueue= util.PriorityQueue() # this is a temporary holder for the nodes for the UCS-priorityQueue
    startState = problem.getStartState()  # the start state
    isStartAGoal = problem.isGoalState(problem.getStartState())  # check to see of the start position is the goal
    # Remember that a search node must contain not only a state but also the information necessary to reconstruct the path (plan) which gets to that state.
    startNode = (startState, [], 0)  # a tuple to contain the start node state and also its path, and the sum of the cost (node, path, sum of the cost)

    # insert the root into priority queue
    initialCost = 0
    # the priority selection is looking at the edgeCost to see which route to go for UCS
    ucsPriorityQueue.push(startNode,initialCost)

    # do the search of the UCS if the priorityQueue is not empty
    if not ucsPriorityQueue.isEmpty():
        return genericSearchMethod(problem, type="UCS", dataStructure=ucsPriorityQueue,isStartAGoal=isStartAGoal)

    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):

    """Search the node that has the lowest combined cost and heuristic first."""
    # Note: A* is very similar to that of UCS, only difference is that the h(n) value is added with the g(n) to get the
    # f(n) value. f(n) = g(n) + h(n)

    #print("Start:", problem.getStartState())
    # Start: (5, 5)
    #print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # Is the start a goal? False
    #print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    # Start's successors: [((5, 4), 'South', 1), ((4, 5), 'West', 1)]

    # initialize the variables
    aStarPriorityQueue = util.PriorityQueue()  # this is a temporary holder for the nodes for the A* -prioritQueue
    startState = problem.getStartState()  # the start state
    isStartAGoal = problem.isGoalState(problem.getStartState())  # check to see of the start position is the goal
    # Remember that a search node must contain not only a state but also the information necessary to reconstruct the path (plan) which gets to that state.
    startNode = (startState, [],0)  # a tuple to contain the start node state and also its path, and the sum of the cost (node, path, sum of the cost)

    # insert the root into priority queue
    initialCost = 0
    # the priority selection is looking at the edgeCost to see which route to go for UCS
    aStarPriorityQueue.push(startNode, initialCost)

    # do the search of the A* if the priorityQueue is not empty
    if not aStarPriorityQueue.isEmpty():
        return genericSearchMethod(problem, type="A*", dataStructure=aStarPriorityQueue,isStartAGoal=isStartAGoal,heuristic=heuristic)

    util.raiseNotDefined()

def genericSearchMethod(problem, type,dataStructure, isStartAGoal, heuristic=nullHeuristic):
    """
    This function is a generic search method function for DFS, BFS, UCS, A*. Depends on the algorithm the way how the
    element is push to the dataStructure will varies.

    """
    # tracker of explored node so that we don't have to explore the same node again
    explored = set()

    while not dataStructure.isEmpty():
        # pop the last item in the data structure
        popNode = dataStructure.pop()

        popNodeState = popNode[0]
        popNodePathDirection = popNode[1]
        isPopNodeAGoal = problem.isGoalState(popNodeState)

        # need to keep track of the cost for UCS and A*
        if type == "UCS" or type == "A*":
            popNodeSumOfCost = popNode[2]

        # check if the node that is pop is the start position and whether or not it is a goal.
        # if it is the goal return its path
        if popNodeState == isStartAGoal:
            return popNodePathDirection

        # check if the current pop node is a goal state
        if isPopNodeAGoal == True:
            #print("[GOAL-FOUND] The current node found is the goal: " + str(popNodeState))
            return popNodePathDirection

        # check if the node is not yet explored if not then mark it as explored and get the successor and
        # push it to the stack.
        if popNodeState not in explored:
            # marke it as discovered
            explored.add(popNodeState)

            # push the children to the data structure and make sure that it is not explored already
            for children in problem.getSuccessors(popNodeState):
                childrenNodeState = children[0]
                childrenNodePathDirection = [children[1]]

                #UCS and A* have very similar structure in fringe
                if type == "UCS" or type == "A*":
                    childredNodeCost = children[2]
                    sumOfCost = popNodeSumOfCost + childredNodeCost
                    childrenNode = (childrenNodeState, popNodePathDirection + childrenNodePathDirection, sumOfCost)

                    if childrenNodeState not in explored:

                        if type == "UCS":
                            dataStructure.push(childrenNode, sumOfCost)

                        if type == "A*":
                            childreNodeHeuristic = heuristic(childrenNodeState, problem)
                            sumOfEdgeCost = popNodeSumOfCost + childredNodeCost
                            # need to add the heuristic value to the sum of the edgecost
                            dataStructure.push(childrenNode, sumOfEdgeCost + childreNodeHeuristic)

                # DFS and BFS have very similar structure in fringe
                if type == "DFS" or type == "BFS":
                    if childrenNodeState not in explored:
                        dataStructure.push((childrenNodeState, popNodePathDirection + childrenNodePathDirection))

    util.raiseNotDefined()

# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
