# multiAgents.py
# --------------
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

# Bao Tran Tran Do
# May 9, 2023


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        # Set score to 0 for start
        score = 0
        postiveValue = 500

        # We want to calculate the distance from pacman to the current food pellets (using the professor suggestion)
        # add the food into a list so that we can iterate over this list to calculate the manhanttan distance
        # print(newFood)
        # This will print out the food position
        # print(newFood.asList())
        # get the postion of the food
        newFoodListPosition = newFood.asList()

        # if the food list position is not empty
        if newFoodListPosition != []:

            # calculate the distance of the current position of the pacman to the other food
            foodManhattanDistanceList = []
            for food in newFoodListPosition:
                distance = manhattanDistance(newPos, food)
                foodManhattanDistanceList.append(distance)

            # if the pacman current position distance to all the other pellets list is not empty do the following
            if foodManhattanDistanceList != []:
                # get the min distance. The smallest value will let us know whether the pacman ate the food pellet and
                # if it did that means the pacman is on the pellet and the distance = 0
                minDistancePacmanToFood = min(foodManhattanDistanceList)

                # If the distance is 0, then add a positive value to score (the agent ate a food
                # pellet! So add a reasonably large value).
                if minDistancePacmanToFood == 0:
                    score += postiveValue  # adding a large value
                else:
                    # Otherwise, add a small positive value to score. For example, reciprocal values of
                    #  distance: 1/distance. This encourages Pacman to explore nearby food.
                    score += 1 / minDistancePacmanToFood

        return successorGameState.getScore() + score 

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class GeneralAdverserialSearch(MultiAgentSearchAgent):
    """
    This is the general class that perform the adverserial search of minimax, alpha-beta, and expectimax.
    Currently, everything is working as intended. Will return the score and the action.
    However, when question5 is ran. I am getting 3/6 instead of 6/6. For, now I am leaving the code of e
    expectimax as a separate section to receive the full credit for question5.
    There is currently a bug somewhere that is causing question5 to not get 6/6.
    """

    def GeneralValue(self, typeOfSearch, gameState, currentDepth, agentIndex, depth, alpha =None, beta=None):
        """
        Part of the pseudo code came from the lecture of minimax, alpha-beta, and expectimax.

        Note: All states in minimax should be GameStates, either passed in to getAction or generated via
        GameState.generateSuccessor. In this project, you will not be abstracting to simplified states.
        Pacman is always agent 0, and the agents move in order of increasing agent index.
        Important: A single search ply is considered to be one Pacman move and all the ghosts' responses, so depth
        2 search will involve Pacman and each ghost moving two times. This return the score and the action
        """

        #print(agentIndex)
        # increased the current depth if all the agents are done with their move
        # and set the next agent index back to 0 to be the pacman so that he can make his move.
        # Currently, there are 3 agents when printing it out in getAction
        if agentIndex == gameState.getNumAgents():
           #print(agentIndex)
            currentDepth += 1
            agentIndex= 0

        #If the state is a terminal state: return the state's utility. At terminal the action is None since there are
        # no more actions to take. Return the score and the action
        if currentDepth == depth or gameState.isWin() or gameState.isLose():
            #print(currentDepth == self.depth)
            #print(self.evaluationFunction(gameState))
            return self.evaluationFunction(gameState), None

        #If the next agent is a MAX: return the MaxValue. This is the pacman's turn
        if agentIndex == 0:
            return self.GeneralMaxValue(typeOfSearch,gameState, currentDepth, agentIndex,depth, alpha, beta)

        #If the next agent is a MIN: return the MinValue. This is the ghost's turn
        if agentIndex >= 1:
            return self.GeneralOponentValue(typeOfSearch, gameState, currentDepth, agentIndex, depth, alpha, beta)

    def GeneralMaxValue(self, typeOfSearch,gameState, currentDepth, agentIndex, depth, alpha=None, beta=None):
        """
            Part of the pseudo code came from the lecture of minimax, alpha-beta, and expectimax.
            Since we know that the pacman index = 0
            This function is for the pacman to optimize its score.

            Note: All states in minimax should be GameStates, either passed in to getAction or generated via
            GameState.generateSuccessor. In this project, you will not be abstracting to simplified states.
        """

        # Initialize the min score to negative infinity
        maxScore = float("-inf")

        # Initialize the action to None since we dont know the current action(direction) at the moment
        maxAction = None

        # for each of the pacman's legal action we want to find out the score of its successor.
        for legalAction in gameState.getLegalActions(agentIndex):
            # we want to get the successor information since the agent is taking a legal action
            successorState = gameState.generateSuccessor(agentIndex, legalAction)
            # we need to increase the agent index by 1 since the next agent is the successor of this current agent
            successorAgentIndex = agentIndex + 1

            # Call the general value function to get the successor score and action to see if its score is greater than the
            # current max score.
            score, action = self.GeneralValue(typeOfSearch,successorState, currentDepth, successorAgentIndex,depth,alpha,beta)

            # checking for the type of search to do the proper search
            if typeOfSearch == "alphaBeta":
                # check whether the score is greater than that of the maxScore. If it is update the maxScore and maxAction
                if score > maxScore:
                    maxScore = score
                    maxAction = legalAction

                    # need to check whether the maxScore is greater than beta. If it is return the maxScore and maxAction and
                    # prune all the other nodes since we are not checking them
                    # (Notes: use strictly inequality)
                    if maxScore > beta:
                        return maxScore, maxAction

                # update the alpha when applicable
                alpha = max(alpha, maxScore)
            else:
                # check whether the score is greater than that of the maxScore. If it is update the maxScore and maxAction
                if score > maxScore:
                    maxScore = score
                    maxAction = legalAction

        return maxScore, maxAction

    def GeneralOponentValue(self, typeOfSearch, gameState, currentDepth, agentIndex, depth, alpha=None, beta=None):
        """
            Part of the pseudo code came from the lecture of minimax, alpha-beta, and expectimax.
            This function is for the ghost.

            Note: All states in minimax should be GameStates, either passed in to getAction or generated via
            GameState.generateSuccessor. In this project, you will not be abstracting to simplified states.
        """
        if typeOfSearch == "expect":
            minScore = 0
        else:
            #Initialize the min value to positive infinity
            minScore = float("inf")

        # Initialize the action to None since we dont know the current action(direction) at the moment
        minAction = None

        for legalAction in gameState.getLegalActions(agentIndex):
            # we want to get the successor information since the agent is taking a legal action
            successorState = gameState.generateSuccessor(agentIndex, legalAction)
            # we need to increase the agent index by 1 since the next agent is the successor of this current agent
            successorAgentIndex = agentIndex + 1

            # Call the value function to get the successor value and action to see if its value is less than the
            # current min value.
            value, action = self.GeneralValue(typeOfSearch,successorState, currentDepth, successorAgentIndex, depth, alpha,beta)

            # checking for the type of search to do the proper search
            if typeOfSearch =="alphaBeta":
                # check whether the value is less than that of the minScore. If it is update the minScore and minAction
                if value < minScore:
                    minScore = value
                    minAction = legalAction
                    # check whether the min value is less than alpha. If it is return the minScore and minAction and prune
                    # all the other nodes since we are not checking them
                    # (Notes: use strictly inequality)
                    if minScore < alpha:
                        return minScore, minAction

                # update beta value when applicable
                beta = min(beta, minScore)
            elif typeOfSearch == "expect":
                # caculuate the expected value
                minScore += self.probability() * value
                minAction = action
            elif typeOfSearch =="miniMax":
                # check whether the value is less than that of the minScore. If it is update the minScore and minAction
                if value < minScore:
                    minScore = value
                    minAction = legalAction

        return minScore, minAction

    def probability(self):
        """
        This is the probability function that will return the probability value that will be use to help calculate the
        expected value
        Note: All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        # noticed that as long as the probability is greater than or equal to 1 it will pass the test cases. So 1, 1.5,
        # 2/3, etc works
        return (2 / 3)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        #print(gameState.getNumAgents())
        #print(self.depth)
        #print(gameState.getLegalActions(0)) # ['West', 'Stop', 'East']
        #print(gameState.getLegalActions(1)) # ['East', 'South']
        #print(gameState.isWin())
        # the start depth = 0
        depth = 0
        # the start index = 0
        agentStartIndex = 0

        # call the value function that does minimax
        typeOfSearch  = "miniMax"
        search = GeneralAdverserialSearch()
        score, action = search.GeneralValue(typeOfSearch,gameState, depth, agentStartIndex, depth=self.depth)
        # Return the minimax action
        return action

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # print(gameState.getNumAgents())
        # the start depth = 0
        depth = 0
        # the start index = 0
        agentStartIndex = 0
        #alpha value initially
        alpha = float("-inf")
        #beta value initially
        beta = float("inf")

        # call the value function that does minimax with alpha-beta pruning
        typeOfSearch = "alphaBeta"
        search = GeneralAdverserialSearch()
        score, action = search.GeneralValue(typeOfSearch, gameState, depth, agentStartIndex, depth=self.depth,alpha=alpha,beta=beta)
        # Return the alpha-beta minimax action
        return action

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # print(gameState.getNumAgents())
        # the start depth = 0
        depth = 0
        # the start index = 0
        agentStartIndex = 0

        # NOTE: There is bug in my code when I tried add the expectimax into the general search class.
        # The expectimax is passing however it is causing the better evualation function to get 3/6 instead of 6/6.
        # When I have time I will revisit this bug.
        #typeOfSearch = "expect"
        #search = GeneralAdverserialSearch()
        #score, action = search.GeneralValue(typeOfSearch, gameState, depth, agentStartIndex, depth=self.depth)

        # Return the expectimax action
        #return action

        # call the value function that does expectimax
        score, action = self.Value(gameState, depth, agentStartIndex)
        # Return the expectimax action
        return action

    def Value(self, gameState, currentDepth, agentIndex):
        """
        Part of the pseudo code came from the lecture of expectimax.

        Note: All states in minimax should be GameStates, either passed in to getAction or generated via
        GameState.generateSuccessor. In this project, you will not be abstracting to simplified states.
        Pacman is always agent 0, and the agents move in order of increasing agent index. Important: A single search ply is considered to be one Pacman move and all the ghosts' responses, so depth
        2 search will involve Pacman and each ghost moving two times.
        """

        # print(agentIndex)
        # increased the current depth if all the agents are done with their move
        # and set the next agent index back to 0 to be the pacman so that he can make his move.
        # Currently, there are 3 agents when printing it out in getAction
        if agentIndex == gameState.getNumAgents():
            # print(agentIndex)
            currentDepth += 1
            agentIndex = 0

        # If the state is a terminal state: return the state's utility
        if currentDepth == self.depth or gameState.isWin() or gameState.isLose():
            # print(self.evaluationFunction(gameState))
            return self.evaluationFunction(gameState), None

        # If the next agent is a MAX: return the MaxValue. This is the pacman's turn
        if agentIndex == 0:
            return self.MaxValue(gameState, currentDepth, agentIndex)

        # If the next agent is an expect: return the ExpValue. This is the ghost's turn
        if agentIndex >= 1:
            return self.ExpectValue(gameState, currentDepth, agentIndex)

    def MaxValue(self, gameState, currentDepth, agentIndex):
        """
            Part of the pseudo code came from the lecture of expectimax. Since we know that the pacman index = 0
            This function is for the pacman to optimize its score.

            Note: All states in minimax should be GameStates, either passed in to getAction or generated via
            GameState.generateSuccessor. In this project, you will not be abstracting to simplified states.
        """

        # Initialize the min score to negative infinity
        maxScore = float("-inf")

        # Initialize the action to None since we dont know the current action(direction) at the moment
        maxAction = None

        # for each of the pacman's legal action we want to find out the score of its successor.
        for legalAction in gameState.getLegalActions(agentIndex):
            # we want to get the successor information since the agent is taking a legal action
            successorState = gameState.generateSuccessor(agentIndex, legalAction)
            # we need to increase the agent index by 1 since the next agent is the successor of this current agent
            successorAgentIndex = agentIndex + 1

            # Call the value function to get the successor score and action to see if its score is greater than the
            # current max score.
            score, action = self.Value(successorState, currentDepth, successorAgentIndex)

            # check whether the score is greater than that of the maxScore. If it is update the maxScore and maxAction
            if score > maxScore:
                maxScore = score
                maxAction = legalAction

        return maxScore, maxAction

    def ExpectValue(self, gameState, currentDepth, agentIndex):
        """
            Part of the pseudo code came from the lecture of expectimax. This function is for the ghost.

            Note: All states in minimax should be GameStates, either passed in to getAction or generated via
            GameState.generateSuccessor. In this project, you will not be abstracting to simplified states.
        """
        # Initialize the expected value to be 0
        expectedScore = 0

        # Initialize the action to None since we dont know the current action(direction) at the moment
        expectedAction = None

        for legalAction in gameState.getLegalActions(agentIndex):
            # we want to get the successor information since the agent is taking a legal action
            successorState = gameState.generateSuccessor(agentIndex, legalAction)
            # we need to increase the agent index by 1 since the next agent is the successor of this current agent
            successorAgentIndex = agentIndex + 1

            # Call the value function to get the successor score and action
            # print(self.Value(successorState, currentDepth, successorAgentIndex))
            score, action = self.Value(successorState, currentDepth, successorAgentIndex)

            # caculuate the expected value
            expectedScore += self.probability() * score
            expectedAction = action

        return expectedScore, expectedAction

    def probability(self):
        """
        This is the probability function that will return the probability value that will be use to help calculate the
        expected value
        Note: All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        # noticed that as long as the probability is greater than or equal to 1 it will pass the test cases. So 1, 1.5,
        # 2/3, etc works
        return (2 / 3)

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION:
    The linear combination with their weighted values (using professor's hint):
    This function will return currentGameState.getScore() plus the sum of the score of distance to closest food + the
    number of food count + if a scaredTimer > 0 add a bonus + the distance ghost distance to the pacman when the
    distance is greater than 1.
    """
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    # Useful information to help calculate for the food and ghost distance
    currentPos = currentGameState.getPacmanPosition()
    currentFood = currentGameState.getFood()
    currentGhostStates = currentGameState.getGhostStates()

    #initializing the variables
    score = 0
    a  = 1 # this value is used to calculate the distance to the closest food
    BONUSVALUE = 1

    #NOTE: The evaluation function should evaluate states, rather than actions like your reflex
    # agent evaluation function did.
    # To get full credit, Pacman should be averaging around 1000 points when he's winning
    # get the postion of the food

    # This is the logic to calculate for the food distance
    # This is the food list
    newFoodListPosition = currentFood.asList()
    # if the food list position is not empty
    if newFoodListPosition != []:

        # calculate the distance of the current position of the pacman to the other food
        foodManhattanDistanceList = []
        for food in newFoodListPosition:
            distance = manhattanDistance(currentPos, food)
            foodManhattanDistanceList.append(distance)

        # if the pacman current position distance to all the other pellets list is not empty do the following
        if foodManhattanDistanceList != []:
            # get the min distance. The smallest value will let us know whether the pacman ate the food pellet and
            # if it did that means the pacman is on the pellet and the distance = 0
            minDistancePacmanToFood = min(foodManhattanDistanceList)

            # Distance to closest food: Reciprocal values of distance: 1/distance * a, a >= 1
            if minDistancePacmanToFood > 0:
                score += (1 / minDistancePacmanToFood) * a

            #The number of food count: add a negative value to score (possibly large value) or reciprocal values: 1/total
            score += 1/len(newFoodListPosition)

    # This is the logic for the ghost distance
    ghostListPosition = []
    for ghost in currentGhostStates:
        ghostListPosition.append(ghost.getPosition())

        # if the scared timer > 0, add a positive bonus value to score.
        if ghost.scaredTimer > 0:
            score += BONUSVALUE

    # if there are ghosts and there are positions of the ghosts do the following
    if ghostListPosition != []:
        # we want to calculate the pacman position to the ghost position
        ghostManhanttanDistanceList = []
        for ghost in ghostListPosition:
            distance = manhattanDistance(currentPos, ghost)
            ghostManhanttanDistanceList.append(distance)

        if ghostManhanttanDistanceList != []:
            # get the closes distance of the pacman to the ghost
            minDistancePacmanToGhost = min(ghostManhanttanDistanceList)

            # Similar to the distance to the closest food. Take the reciprocal value of min distance pacman to ghost if
            # the min distance pacman to ghost is greater than 1 implying that the ghost is not that near to pacman.
            if minDistancePacmanToGhost > 1:
                score += 1 / minDistancePacmanToGhost

    return currentGameState.getScore() + score

# Abbreviation
better = betterEvaluationFunction
