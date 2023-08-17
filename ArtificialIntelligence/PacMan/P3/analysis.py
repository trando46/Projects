# analysis.py
# -----------
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

######################
# ANALYSIS QUESTIONS #
######################

# Set the given parameters to obtain the specified policies through
# value iteration.

def question2():
    answerDiscount = 0.9
    # Note: Noise refers to how often an agent ends up in an unintended successor state when they perform an action
    # Since we want the optimal policy to causes the agent to attempt to cross the bridge and we know that the agent
    # initially starts near the low-reward state (so toward where 1.00 is at) we need the agent to cross the bridge to
    # get to 10.00. By the noise definition, I picked 0.0 because if there are no noise then that means the agent will
    # not be distracted and just cross the bridge.
    answerNoise = 0.0
    return answerDiscount, answerNoise

def question3a():
    # Prefer the close exit (+1), risking the cliff (-10)
    # Since the agent prefer to exit the game now we want the agent to have a lower discount value so that the agent
    # can exhibit the greedy behavior to quickly take the closes exit which turns out to be the exit payoff of (+1)
    answerDiscount = 0.01
    answerNoise = 0.0
    answerLivingReward = 0.0
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3b():
    # Prefer the close exit (+1), but avoiding the cliff (-10)
    # Since the agent want to avoid the cliff. I need to adjust the answerLivingReward to a positive value to encourage
    # the pacman to stay alive. The closer it is to the 1. The more likely the agent will try to survive.
    # The agent still want to get to the closes exit which is (+1). Need to have the discount
    # to behave as greedy as possible. The answernoise needs to set it to the lowest value as possible. Can't set the
    # value to 0 it will not pass the test.
    answerDiscount = 0.01
    answerNoise = 0.01
    answerLivingReward = 0.9
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3c():
    # Prefer the distant exit (+10), risking the cliff (-10)
    # Since the agent prefer to get the (+10) want to have the discount value to be 1 since the agent prefer to
    # get this reward at a later time. # Since the agent prefer taking the risk of the cliff want to set the living
    # reward to a negative reward so that the agent will be acting out to quickly find the exit and increased the likely
    # hood of hitting the cliff by introducing some noise.
    answerDiscount = 1.0
    answerNoise = 0.1
    answerLivingReward = -1.0
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3d():
    # Prefer the distant exit (+10), avoiding the cliff (-10)
    # Since the agent prefer to get to the (+10) we want to have the discount to be close to 1 and since the agent
    # wants to avoid the cliff we want to encourage the agent to stay alive by giving it a positive reward number.
    # keeping the answerNoise value to be the same as that of question3c and passed the test.
    answerDiscount = 0.9
    answerNoise = 0.1
    answerLivingReward = 0.9
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3e():
    # Avoid both exits and the cliff (so an episode should never terminate)
    # Since the agent wants to avoid both the exits and the cliff. Need to set the living reward to 1 to encourage the
    # agent to stay alive and stay in the game as long as possible. Due to wanting to avoid to exit want to set the
    # discount value to 1.0 so that the agent prefers the reward in the long term. Have the answerNoise to be 0 since
    # we dont want the agent to randomly end up in an unintended successor state.
    answerDiscount = 1.0
    answerNoise = 0.0
    answerLivingReward = 1.0
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question8():
    answerEpsilon = None
    answerLearningRate = None
    # note: not possible is passing the test
    # tried other values only NOT POSSIBLE pass this test.
    return 'NOT POSSIBLE'

    #return answerEpsilon, answerLearningRate
    # If not possible, return 'NOT POSSIBLE'

if __name__ == '__main__':
    print('Answers to analysis questions:')
    import analysis
    for q in [q for q in dir(analysis) if q.startswith('question')]:
        response = getattr(analysis, q)()
        print('  Question %s:\t%s' % (q, str(response)))
