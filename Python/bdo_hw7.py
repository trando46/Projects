
# Bao Tran Do 
# 06/02/2021
# Algorithm from: https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
# Algorithm from: chapter 10 lecture slides
# Note: Only postive edge weights are taken into consideration 


import numpy as np 


# Defining infinity. This value will be used when any of the 
# vertices are not connected to each other at all (meaning no edges are connected)
INF = 999999999

# Solving for the shortest distances between every pair of vertices 
def floyd(arr):
	rows, cols = len(arr), len(arr)


	# Checking when 1 element is none
	if(arr == None):
		return 

    # Checking when there are more than 1 element for None
	for i in range(rows):
		for j in range(cols):
			if(arr[i][j] == None):
				return

	
	# initialize to infinity 
	dist = [[INF for i in range(cols)] for j in range(rows)]

	# add the weight of the edges from arr to dist
	for i in range(rows):
		for j in range(cols):
			dist[i][j] = (arr[i][j])

	# for each vertex to itself set it to 0
	for i in range(rows):
		dist[i][i] = 0

	for k in range(rows):
		for i in range(rows):
			for j in range(rows):
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

	return dist 


def printingMatrix(arr):

	# Checking when 1 element is none
	if(arr == None):
		return 

    # Checking when there are more than 1 element for None
	for i in range(len(arr)):
		for j in range(len(arr)):
			if(arr[i][j] == None):
				return

	rows = len(arr)

	for i in range(rows):
		for j in range(rows):
			if(arr[i][j] == INF):
				arr[i][j] = 'INF'
			

	printingarr = np.array(arr)
	print(printingarr)


def callingTest(arr, num):

	print('\n--------------------------------------Test case # ' + str(num) + '----------------------------------------------------\n')
	print('Shortest distance\n')
	printingMatrix(floyd(arr))
	print('')

	print('Weighted Graph\n')
	printingMatrix(arr)
	

# Testing 1 vertices
test1 = [[0]]
# Test 2 vertices where the edges arent touching
test2 = [[0,0],[0,0]] 
# Test 3 vertices where some of the edges are touching and arrowing moving counterclockwise
test3 = [[0,1,INF],
		 [INF,0,2],
		 [3,INF,0]]
# This test case came from the slide in lecture 10. Slide # 40
test4 = [[0, INF, 3, INF],
         [2, 0, INF, INF],
         [INF, 7, 0, 1],
         [6, INF, INF, 0]] 
# Testing when it is moving counterclockwise in a box 
test5 = [[0, 1, INF, INF],
         [INF, 0, 2, INF],
         [INF, INF, 0, 3],
         [4, INF, INF, 0]]
# Testing when the direction changes so that there is INF 
test6 = [[0,1,INF],
		 [INF,0,INF],
		 [3,2,0]]
# Testing when there is no value at all 
test7 = [[None]]
test8 = [[None,None],
		 [None,None]]
        

print("Displaying the shortest distances between every pair of vertices and only taking postivie edge weights into consideration") 
callingTest(test1,1)
callingTest(test2,2)
callingTest(test3,3)
callingTest(test4,4)
callingTest(test5,5)
callingTest(test6,6)
callingTest(test7,7)
callingTest(test8,8)




