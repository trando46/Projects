# qlearningAgents.py
# ------------------
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

from game import *
from learningAgents import ReinforcementAgent
from featureExtractors import *

import random,util,math

class QLearningAgent(ReinforcementAgent):
    """
      Q-Learning Agent

      Functions you should fill in:
        - computeValueFromQValues
        - computeActionFromQValues
        - getQValue
        - getAction
        - update

      Instance variables you have access to
        - self.epsilon (exploration prob)
        - self.alpha (learning rate)
        - self.discount (discount rate)

      Functions you should use
        - self.getLegalActions(state)
          which returns legal actions for a state
    """
    def __init__(self, **args):
        "You can initialize Q-values here..."
        ReinforcementAgent.__init__(self, **args)

        "*** YOUR CODE HERE ***"
        # initializing the Q-Value
        self.QValue = util.Counter()

    def getQValue(self, state, action):
        """
          Returns Q(state,action)
          Should return 0.0 if we have never seen a state
          or the Q node value otherwise
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        currentQ = (state, action)

        # return 0.0 if the currentQ is never seen before
        if currentQ not in self.QValue:
            return 0.0
        return self.QValue[currentQ]

    def computeValueFromQValues(self, state):
        """
          Returns max_action Q(state,action)
          where the max is over legal actions.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return a value of 0.0.
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()

        # Important: Make sure that in your computeValueFromQValues and computeActionFromQValues functions, you only
        # access Q values by calling getQValue . This abstraction will be useful for question 10 when you override
        # getQValue to use features of state-action pairs rather than state-action pairs directly

        # If it is a terminal state we want to return 0.0 since there are no legal actions to take
        if state == "TERMINAL_STATE":
            return 0.0

        # Initialize a holder for all of the qValues
        qValuesList = []

        # get the list of legal actions
        listOfLegalActions = self.getLegalActions(state)

        # if there are legal actions calculate the max q value
        if len(listOfLegalActions) != 0:
            # get the qvalue for every legal action
            for legalAction in listOfLegalActions:
                qValuesList.append(self.getQValue(state,legalAction))

            # return the max q value
            return max(qValuesList)

        return 0.0


    def computeActionFromQValues(self, state):
        """
          Compute the best action to take in a state.  Note that if there
          are no legal actions, which is the case at the terminal state,
          you should return None.
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # Note: For computeActionFromQValues, you should break ties randomly for better behavior.
        # The random.choice() function will help. In a particular state, actions that your agent hasn't seen before
        # still have a Q-value, specifically a Q-value of zero, and if all of the actions that your agent has seen
        # before have a negative Q-value, an unseen action may be optimal.

        # if the state is a terminal state, that means there are no legal actions so return None
        if state == "TERMINAL_STATE":
            return None

        # Important: Make sure that in your computeValueFromQValues and computeActionFromQValues functions, you only
        # access Q values by calling getQValue . This abstraction will be useful for question 10 when you override
        # getQValue to use features of state-action pairs rather than state-action pairs directly

        # get the list of legal actions
        listOfLegalActions = self.getLegalActions(state)

        # get the value of the current given state
        #print("testing")
        #print(self.computeValueFromQValues(state))
        currentStateValue = self.computeValueFromQValues(state)

        # initialize a list of potential action to when run through the random.choice()
        listOfPotentialActions = []

        for legalAction in listOfLegalActions:
            currentLegalActionQValue = self.getQValue(state,legalAction)
            # if the current state value is equivalent to that of the current legal action q value we want to append
            # it to the list of potential actions because this is the best action to take for this current state value
            # since the current state value is alreadu the max q value. There is nothing greater than this
            if currentStateValue == currentLegalActionQValue:
                listOfPotentialActions.append((legalAction))

        #print(listOfPotentialActions)

        # get a random action to take
        randomActionToTake = random.choice(listOfPotentialActions)

        return randomActionToTake


    def getAction(self, state):
        """
          Compute the action to take in the current state.  With
          probability self.epsilon, we should take a random action and
          take the best policy action otherwise.  Note that if there are
          no legal actions, which is the case at the terminal state, you
          should choose None as the action.

          HINT: You might want to use util.flipCoin(prob)
          HINT: To pick randomly from a list, use random.choice(list)
        """
        # Pick Action
        legalActions = self.getLegalActions(state)
        action = None
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # Note: Note that choosing a random action may result in choosing the best action - that is, you should not
        # choose a random sub-optimal action, but rather any random legal action.

        # if the state is a terminal state, that means there are no legal actions so return None
        if state == "TERMINAL_STATE":
            return None

        # get a random action to take
        randomActionToTake = random.choice(legalActions)

        # With probability self.epsilon, we should take a random action and take the best policy action otherwise.
        if util.flipCoin(self.epsilon):
            return randomActionToTake
        else:
            # take the best policy action otherwise.
            return self.getPolicy(state)

        #return action

    def update(self, state, action, nextState, reward):
        """
          The parent class calls this to observe a
          state = action => nextState and reward transition.
          You should do your Q-Value update here

          NOTE: You should never call this function,
          it will be called on your behalf
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # Note: from the lecture slide
        # Sample of Q(s,a): sample = R(s,a,s’) + γmaxa’Q (s’,a’)
        # Update Q(s,a) : Q (s,a) <= (1 - α ) Q(s,a) + α *sample

        # calculate sample. Remember that Q(s',a') already returned the max
        sample = reward + self.discount * self.computeValueFromQValues(nextState)

        # Q(s,a)
        currentQValue = self.getQValue(state,action)

        # (1 - α ) Q(s,a)
        firstPart = (1 - self.alpha) * currentQValue

        # alpha * sample
        secondPart = self.alpha * sample

        # get the update Q(s,a)
        update = firstPart + secondPart

        # assign this new update Q(s,a) to the (state,action) stored in the self.Qvalues
        currentQ = (state,action)
        self.QValue[currentQ] = update

    def getPolicy(self, state):
        return self.computeActionFromQValues(state)

    def getValue(self, state):
        return self.computeValueFromQValues(state)


class PacmanQAgent(QLearningAgent):
    "Exactly the same as QLearningAgent, but with different default parameters"

    def __init__(self, epsilon=0.05,gamma=0.8,alpha=0.2, numTraining=0, **args):
        """
        These default parameters can be changed from the pacman.py command line.
        For example, to change the exploration rate, try:
            python pacman.py -p PacmanQLearningAgent -a epsilon=0.1

        alpha    - learning rate
        epsilon  - exploration rate
        gamma    - discount factor
        numTraining - number of training episodes, i.e. no learning after these many episodes
        """
        args['epsilon'] = epsilon
        args['gamma'] = gamma
        args['alpha'] = alpha
        args['numTraining'] = numTraining
        self.index = 0  # This is always Pacman
        QLearningAgent.__init__(self, **args)

    def getAction(self, state):
        """
        Simply calls the getAction method of QLearningAgent and then
        informs parent of action for Pacman.  Do not change or remove this
        method.
        """
        action = QLearningAgent.getAction(self,state)
        self.doAction(state,action)
        return action


class ApproximateQAgent(PacmanQAgent):
    """
       ApproximateQLearningAgent

       You should only have to overwrite getQValue
       and update.  All other QLearningAgent functions
       should work as is.
    """
    def __init__(self, extractor='IdentityExtractor', **args):
        self.featExtractor = util.lookup(extractor, globals())()
        PacmanQAgent.__init__(self, **args)
        self.weights = util.Counter()

    def getWeights(self):
        return self.weights

    def getQValue(self, state, action):
        """
          Should return Q(state,action) = w * featureVector
          where * is the dotProduct operator
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()

        # get the weight
        w = self.getWeights()

        # extract the feature function value by calling the getFeatures() from the feature extractor class
        #print(self.featExtractor.getFeatures(state,action))
        featureVector = self.featExtractor.getFeatures(state,action)

        # Q(state,action) = w * featureVector
        q = w * featureVector
        return q

    def update(self, state, action, nextState, reward):
        """
           Should update your weights based on transition
        """
        "*** YOUR CODE HERE ***"
        #util.raiseNotDefined()
        # Notes: using lecture slide notes for the equations to compute the update for the approximate QAgent
        # Transition: Qnew(s,a) = R(s,a,s') + gammamaxQ(s',a')
        # Difference: Qnew(s,a) - Q(s,a)
        # weight update: wi + alpha[difference]fi(s,a)
        # fi(s,a) -> feature function

        # Note: Approximate Q-learning assumes the existence of a feature function f(s,a) over state and action pairs,
        # which yields a vector f1(s,a) .. fi(s,a) .. fn(s,a) of feature values. We provide feature functions for you in
        # featureExtractors.py. Feature vectors are util.Counter (like a dictionary) objects containing the non-zero
        # pairs of features and values; all omitted features have value zero.

        # get the new Q value from the next state
        qNew = reward + self.discount*self.getValue(nextState)
        # get the current/old value of this current state
        qCurrent = self.getQValue(state,action)
        # get the feature function value
        featureVector = self.featExtractor.getFeatures(state,action)

        # calculate the difference
        difference = qNew - qCurrent

        # update the weights of each of the features
        for feature in featureVector:
            alpha = self.alpha
            featureValue = featureVector[feature]
            self.weights[feature] += alpha * difference * featureValue


    def final(self, state):
        "Called at the end of each game."
        # call the super-class final method
        PacmanQAgent.final(self, state)

        # did we finish training?
        if self.episodesSoFar == self.numTraining:
            # you might want to print your weights here for debugging
            "*** YOUR CODE HERE ***"
            pass
