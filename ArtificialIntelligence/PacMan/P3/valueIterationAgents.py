# valueIterationAgents.py
# -----------------------
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


# valueIterationAgents.py
# -----------------------
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
# May 29, 2023

import mdp, util

from learningAgents import ValueEstimationAgent
import collections

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0
        self.runValueIteration()

    def runValueIteration(self):
        # Write value iteration code here
        "*** YOUR CODE HERE ***"
        # Notes: (from the lecture slide)
        # MDP consists of
        # States S
        # Actions A
        # Transitions T(s,a,s') = P(s'|s,a)
        # Rewards R(s,a,s') (and discount (gamma)
        # Start state S0

        # Quantities
        # Policy = map of states of actions (strategy for choosing action at each step)
        # Utility = sum of discounted rewards
        # Values = expected future utility from a state (max node)
        # Q-Values = expected future utility from a q-state (chance node)
        # optimal policy (optimal action from state s) extracted from Q-function -> pi*(s) = argmax(Q(S,a))

        # To find an optimal policy
        # maximize over Q(s,a). Solve for Q*(sa,a) then V*(s) is obtained.

        # In value iteration, at each step we want to
        # For each state, it takes the maximum action value ot be estimated
        # A single time policy evalution (policy extraction)

        # Steps to compute for value iteration: (Compute the optimal state value function by iteratively updating the
        # estimate V(s)
        # 1) Start with a random value function V(s)
        # 2) At each step, update it
        # 3) look-ahead one step to calculate rewards
        # 4) Review all possible actions at each iteration to find maximum value
        # 5) Update value
        # 6) Value iteration guaranteed to converge.

        # Bellman's Equations:
        # V*(s) = max(Q*(s,a))
        # Q*(s,a) = sum(T(s,a,s')[R(s,a,s') + gamma(V*(s'))]
        # V*(s) = max(Q*(s,a)) = max (sum(T(s,a,s')[R(s,a,s') + gamma(V*(s'))])

        # Get the list of states
        listOfStates = self.mdp.getStates()
        #print(listOfStates)
        #print(util.Counter)
        #print(self.mdp) # <gridworld.Gridworld object at 0x7fa8b029f3a0>
        #print(self.discount) # 0.9
        #print(self.iterations) # 100
        #print(self.values) # {}
        #action = self.mdp.getPossibleActions(state)
        #nextState, transitionalProbability = self.mdp.getTransitionStatesAndProbs(state, action)
        #getReward = self.mdp.getReward(state, action, nextState)
        #isTerminal = self.mdp.isTerminal(state)

        # this return an array of states
        #print(listOfStates ) # ['TERMINAL_STATE', (0, 0), (0, 1), (0, 2), (1, 0), (1, 2), (2, 0), (2, 1), (2, 2), (3, 0), (3, 1), (3, 2)]
        #for state in listOfStates:
            #print("getPossibleActions:")
            #print(state) # ex// (0, 0)
            #action = self.mdp.getPossibleActions(state)
            #print(action) # ex// ('north', 'west', 'south', 'east')

        # Notes: Your value iteration agent is an offline planner, not a reinforcement learning agent, and so the relevant
        # training option is the number of iterations of value iteration it should run (option -i) in its initial
        # planning phase. ValueIterationAgent takes an MDP on construction and runs value iteration for the specified
        # number of iterations before the constructor returns.

        # We want to runs the value iteration for the specified number of iterations before the constructor returns so
        # we want to initially loop through the self.iterations. Currently, self.iterations = 100 when printed
        # using the parts of the pseudocode from lecture L11_MDP2_valueIteration
        # we want to solve for this equation V*(s) = max(Q*(s,a)) = max (sum(T(s,a,s')[R(s,a,s') + gamma(V*(s'))]) for
        # every state. Remember that when solve for Q*(s,a) then V*(s) is obtained
        # In value iteration, at each step
            # For each state, it takes the maximum action value to be the estimated state value
            # A single time policy evaluation (policy extraction)
        for iterationIndex in range(self.iterations):
            # copy the dictionary of the immediate value so that we can use this to update any changes in the qValues
            # for each of the state so that we can compared it to the previous dictionary to see if all the states
            #converges
            prev = self.values.copy()
            # for each of the state we want to get the best action and the q-value of each of the state
            for state in listOfStates:
                # we don't want to look for the qValue at the terminal state since there would be no actions.
                if state != "TERMINAL_STATE":
                    # get the optimal action for this specific state in order to get the estimated state value
                    action = self.getAction(state)
                    #print(type(action)) # string type
                    # if there is an optimal action we want to get the qValue of this optimal action for this state to
                    # get the estimated state value
                    if action != "()":
                        # get the Q-value for this specific state
                        qValue = self.getQValue(state, action)
                        #print(qValue)
                        # V*(s) = max(Q*(s,a))
                        # add the state and their updated qValue to the temporary dictionary since we found the max
                        # value for this particular state
                        prev[state] = qValue
                        #print(prev)
                        #print()
            # we want to check whether any of the qValues changes between the self.values and the temporary dictionary
            # that contains the updated result of qValue for that particular state. If both dictionary are the same
            # that means all of the states' values converges
            if prev == self.values:
                print(("This iteration is when all the value converges {}").format(iterationIndex))
                break
            else:
                # if the values do not converges we want to assign it to the updated values from the temporary dictionary
                self.values = prev



    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        """
          Compute the Q-value of action in state from the
          value function stored in self.values.
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # Notes: (from lecture slide L11_MDP2_valueIteration and pseudocode)
        # Want to find the value for q-value for each of the values
        # Q(s,a) -> is the expected utility of taking action a in state S
        # Bellman's Equation -> Q*(s,a) = sum(T(s,a,s')[R(s,a,s') + gamma(V*(s'))]

        # Need to solve for:
        # computeQValueFromValues(state, action) returns the Q-value of the (state, action) pair given by the value
        # function given by self.values

        # the counter to keep track of the sum of all the QValue based on one of the Bellman's equation
        sumOfQValue = 0
        # copy the previous values so that we can do data manipulation without affecting the self.values
        prevValues = self.values.copy()

        # Get the next state and the transitional probability to calculate for the Q(s,a)
        for nextState, transitionalProbability in self.mdp.getTransitionStatesAndProbs(state, action):
            # Q*(s,a) = sum(T(s,a,s')[R(s,a,s') + gamma(V*(s'))]
            reward = self.mdp.getReward(state, action, nextState)
            sumOfQValue += transitionalProbability * (reward + self.discount * prevValues[nextState])
        return sumOfQValue


    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.

          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()

        # If the legalAction is at the terminal state meaning that there are no more actions left to take we want to
        # return none. State -> actions (the printing of this was taken care of in runValueIterations(). Uncomment the
        # loop to see the output)
        # EX// TERMINAL_STATE -> ()
        # Ex// (0, 0) -> ('north', 'west', 'south', 'east')
        if state == "TERMINAL_STATE":
            return None

        # Get the list of legal actions for the given state that is not terminal state
        listOflegalActions = self.mdp.getPossibleActions(state)

        # Notes: (from lecture slide L11_MDP2_valueIteration)
        # Need to find the policy. In order to do that we to calculate each of the legalAction of each of the state
        # and gets its transitionalProbability and next state information and reward function to find the Q*(S,a).
        # Since,  The policy is the best action in the given state according to the values currently stored in self.values.
        # Essentially, need to solve for pi*(s):  argmax(Q*(s,a)).
        # Remember that finding an optimal policy leads to generating the maximum reward. A POLICY is a mapping from
        # states to actions

        # This is a temporary dictionary to store the action and its qvalue so that we can find the best action after
        # computing the Qvalues for each of the actions.
        tempDictionary = {}
        for legalAction in listOflegalActions:
            # want to calculate for the Q-values. We can do that by calling the computeQvaluesFromValues()
            tempDictionary[legalAction] = self.computeQValueFromValues(state, legalAction)

        # find the best action with the highest q-values
        bestAction = sorted(tempDictionary, key=tempDictionary.get, reverse=True)

        # return that best action aka the optimal policy for that given state.
        return bestAction[0]


    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)

class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        An AsynchronousValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs cyclic value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 1000):
        """
          Your cyclic value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy. Each iteration
          updates the value of only one state, which cycles through
          the states list. If the chosen state is terminal, nothing
          happens in that iteration.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state)
              mdp.isTerminal(state)
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        # Notes: (From instruction)
        # The reason this class is called AsynchronousValueIterationAgent is because we will update only one
        # state in each iteration, as opposed to doing a batch-style update. Here is how cyclic value iteration works.
        # In the first iteration, only update the value of the first state in the states list. In the second iteration,
        # only update the value of the second. Keep going until you have updated the value of each state once,
        # then start back at the first state for the subsequent iteration. If the state picked for updating is terminal,
        # nothing happens in that iteration. You can implement it as indexing into the states variable defined in the
        # code skeleton.
        # Make sure to handle the case when a state has no available actions in an MDP (think about what this means
        # for future rewards).

        # Get the states
        listOfStates = self.mdp.getStates()
        #print(listOfStates) # EX// ['TERMINAL_STATE', (0, 0), (1, 0), (2, 0)]

        # This is the counter variable to keep track of what state we are currently checking for the QValue since
        # we are not updating all the states in batches. Instead we are updating 1 state per iteration. Decided to use
        # the indexing into the states variable per the instruction suggested
        indexCounter = 0

        # Running the number of iterations to update 1 state per iteration until we run out of all the iterations.
        for iterationNum in range(self.iterations):
            # Need to reset the counter when we already went through the whole list of states because we have to keep
            # updating the value for each of the state in the list until the whole iterations loop is done.
            if indexCounter == len(listOfStates):
                indexCounter = 0
            # Get the state from the current index counter
            state = listOfStates[indexCounter]
            # Only update the state's value if it is not a terminal state and the action is not empty. This will ensure
            # that it is handling cases when the state has no available actions.
            if state != "TERMINAL_STATE":
                # get the action of this state
                action = self.getAction(state)
                if action != "()":
                    # get the QValue for this state based on the action
                    qValue = self.getQValue(state, action)
                    # Store this state's q value
                    self.values[state] = qValue
                    #print(self.values)
            # increment the counter so that we can look at the next state in the list and compute for that q value
            indexCounter += 1
        #print(self.values)




class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A PrioritizedSweepingValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs prioritized sweeping value iteration
        for a given number of iterations using the supplied parameters.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100, theta = 1e-5):
        """
          Your prioritized sweeping value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        """Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)"""
        # This function is based on the algorithm that is provided in the specification.

        # Useful initialiazing information to help with this function
        # Get the list of states
        listOfStates = self.mdp.getStates()

        # initialize the predecessors list
        predessorsListOfAllStates = {}

        # Compute predecessors of all states.
        # Need to find all of the predecssors of all the given states.
        for state in listOfStates:
            # if state is not terminal-state
            if state != "TERMINAL_STATE":
                # for each of the action that lead to a successor state from this current state we want to do
                # the following
                for action in self.mdp.getPossibleActions(state):
                    # if action is not empty
                    if action != "()":
                        # get the next state. Since the getTransitionStateandProbs returned two values need to
                        # declare the transitionalProbability
                        for nextState, transitionalProbability in self.mdp.getTransitionStatesAndProbs(state, action):
                            # if the next state is not in the predessorsList we need to add it to the list and assigned
                            # their predessor state which is the current state.
                            if nextState not in predessorsListOfAllStates:
                                # When you compute predecessors of a state, make sure to store them in a set, not a list, to avoid duplicates.
                                predessorsListOfAllStates[nextState] = set()
                                predessorsListOfAllStates[nextState].add(state)
                            else:
                                # if the nextState (successor) is in the predessorsList for this current state
                                # iteration (looping) add this current state to the list that keep tracks of all the
                                # predeessors of this current nextState.
                                predessorsListOfAllStates[nextState].add(state)

        # Initialize an empty priority queue.
        priorityQueue = util.PriorityQueue()

        # For each non-terminal state s, do: (note: to make the autograder work for this question, you must iterate over
        # states in the order returned by self.mdp.getStates())
        # Find the absolute value of the difference between the current value of s in self.values and the highest
        # Q-value across all possible actions from s (this represents what the value should be);
        # call this number diff. Do NOT update self.values[s] in this step.
        # Push s into the priority queue with priority -diff (note that this is negative).
        # We use a negative because the priority queue is a min heap, but we want to prioritize updating states that
        # have a higher error.

        # iterating over the states in the order returned by self.mdp.getStates()
        for state in listOfStates:
            # if state is not terminal-state do the following
            if state != "TERMINAL_STATE":
                # get the optimal action by calling the getaction()
                optimalAction = self.getAction(state)
                # if the optimal action is not empty do the following
                if optimalAction != "()":
                    # we want to calculate qvalue which will give us the highest qvalue
                    highestQValue = self.getQValue(state, optimalAction)
                    currentStateValue = self.values[state]
                    # calculate the diff by taking the absolute value of the difference bettween the current value of
                    # this current state and the highest Q-Value across all of the possible actions from the current
                    # state
                    diff = abs(currentStateValue - highestQValue)
                    # pushing the state into the priority queue with priority -diff (note that this is negative) We
                    # are using a negative because the priority queue is a min heap, but we want to prioritize updating
                    # states that have a higher error.
                    priorityQueue.push(state, -diff)

        # For iteration in 0, 1, 2, ..., self.iterations - 1, do:
            #-If the priority queue is empty, then terminate.
            #-Pop a state s off the priority queue.
            #-Update s's value (if it is not a terminal state) in self.values.
            #-For each predecessor p of s, do:
            #-Find the absolute value of the difference between the current value of p in self.values and the highest
                #Q-value across all possible actions from p (this represents what the value should be); call this number
                #diff. Do NOT update self.values[p] in this step.
            #-If diff > theta, push p into the priority queue with priority -diff (note that this is negative), as long
                #as it does not already exist in the priority queue with equal or lower priority. As before, we use a
                #negative because the priority queue is a min heap, but we want to prioritize updating states that have
                #a higher error.

        for iterationIndex in range(self.iterations):
            # If the priority queue is empty, then terminate.
            if priorityQueue.isEmpty():
                break

            # Pop a state s off the priority queue.
            state = priorityQueue.pop()

            #Update s's value (if it is not a terminal state) in self.values.
            if state != "TERMINAL_STATE":
                # get the optimal action by calling the getaction()
                optimalAction = self.getAction(state)
                # if the optimal action is not empty do the following
                if optimalAction != "()":
                    # we want to calculate qvalue which will give us the highest qvalue
                    highestQValue = self.getQValue(state, optimalAction)
                    self.values[state] = highestQValue

            # For each predecessor p of s, do
            for predessorState in predessorsListOfAllStates[state]:
                if predessorState!= "TERMINAL_STATE":
                    # get the optimal action by calling the getaction()
                    optimalAction = self.getAction(predessorState)
                    # if the optimal action is not empty do the following
                    if optimalAction != "()":
                        # we want to calculate qvalue which will give us the highest qvalue
                        highestQValue = self.getQValue(predessorState, optimalAction)
                        currentStateValue = self.values[predessorState]
                        # Find the absolute value of the difference between the current value of p in self.values and
                        # the highest Q-value across all possible actions from p (this represents what the value
                        # should be); call this number diff. Do NOT update self.values[p] in this step.
                        diff = abs(currentStateValue - highestQValue)
                        # If diff > theta, push p into the priority queue with priority -diff (note that this
                        # is negative), as long as it does not already exist in the priority queue with equal or
                        # lower priority. As before, we use a negative because the priority queue is a min heap, but
                        # we want to prioritize updating states that have a higher error.
                        if diff > self.theta:
                            priorityQueue.update(predessorState, -diff)






