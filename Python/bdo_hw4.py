# Bao Tran Do 
# 04/26/21
# HW 4


test1 = []
test2 = [0,1,2,3]
test3 = [ 0, 1, 2, 3, 4]
test4 = [3,1,4,1,5,9,2,6,5 ]
test5 = [ 9,8,7,6,5,4,3,2,1,0 ]
test6 = [1,0,3,2]
test7 = [1,0,3,2,4]

# Recusive of the merge sort algorithm
def mergeSort(arr):

	n = len(arr)
	left = []
	right = []

	# if the length of the array is greater than 1, divides the array into 2 separate 
	# arrays and copies the elements over 
	if n > 1:

		leftLength = n/2
		rightLength = n - leftLength

		# keep track of the array position for left arr 
		i = 0

		# Copy to the left array 
		while(i < leftLength):
			left.append(arr[i]) 
			i = i + 1

	    # Start at the index where i got left over from copying the arr's element into
	    # the left arr 
		j = i 

		# Copy to the right array 
		while(j < n):
			right.append(arr[j]) 
			j = j + 1 

		mergeSort(right)
		mergeSort(left)
		merge(left, right, arr)

	return arr 

# Helper function for mergeSort to merge all of the arrays together back into one
def merge(left,right, arr):

	# tracker for left array 
	i = 0 

	# tracker for right array 
	j = 0

	# tracker for the arr array 
	k = 0

	while i < len(left) and j < len(right):
		# if left arr is less than or equal to the content of the right 
		# array copy the left array element to the arr array 
		if left[i] <= right[j]:
			arr[k] = left[i]
			i = i + 1
		else: 
			# copy the right array over to the arr array 
			arr[k] = right[j]
			j = j + 1
		# increment the arr array index position 
		k = k + 1


	# if the tracker of left array the same length of left array length then
	# the left array is done copying over to the arr array 
	if i == len(left):
		# copied the remainding right array over to the arr array 
		while j < len(right):
			arr[k] = right[j]
			j = j + 1
			k = k + 1
	# if the tracker of right array the same length of right array length then
	# the right array is done copying over to the arr array 
	elif j == len(right):
		# copied the remainding left array over to the arr array 
		while i < len(left):
			arr[k] = left[i]
			i = i + 1
			k = k + 1
	return arr 
	
print(test1)
print(mergeSort(test1)) 
print('-------------------------------')
print(test2)
print(mergeSort(test2)) 
print('-------------------------------')
print(test3)
print(mergeSort(test3)) 
print('-------------------------------')
print(test4)
print(mergeSort(test4))
print('-------------------------------') 
print(test5)
print(mergeSort(test5)) 
print('-------------------------------') 
print(test6)
print(mergeSort(test6)) 
print('-------------------------------') 
print(test7)
print(mergeSort(test7)) 



		



