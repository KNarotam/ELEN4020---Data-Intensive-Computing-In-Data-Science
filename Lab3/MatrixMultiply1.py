from mrjob.job import MRJob
import re
import os
import sys
import time

class MRMatrixReduceOneStep(MRJob):

	def mapper(self, _, line):

		if len(line.split()) == 2:
			return 

		x, y, value = line.split()
		filename = os.environ['map_input_file']

		if filename == 'File1ForLab3.txt':
			for column in range(0, int(k)):
				yield (int(x), column), ('Matrix-identifier-1', int(y), int(value))
		else:
			for row in range(0, int(i)):
				yield (row, int(y)), ('Matrix-identifier-2', int(x), int(value))

	def reducer(self, key, val):

		matrix1Val = []
		matrix2Val = []
		productMatrix = []

		for values in val:
			if values[0] == 'Matrix-identifier-1':
				matrix1Val.append(values[2])
			else:
				matrix2Val.append(values[2])

		for iterator in range(0, int(j)):
			productMatrix.append(matrix1Val[iterator] * matrix2Val[iterator])
		yield key, sum(productMatrix)


timeText = open("time1.txt", "w")
start = time.time()

WORD_RE = re.compile(r"[\w']+")

matrix1 = open('/home/kishan/Documents/Lab 3/File1ForLab3.txt', 'rb')
matrix2 = open('/home/kishan/Documents/Lab 3/File2ForLab3.txt', 'rb')

i, j1 = matrix1.readline().split()
j2, k = matrix2.readline().split()

if j1 != j2:
	print('Basic law for matrix multiplication is not obeyed.')
	sys.exit("Error message")

j = j1

matrix1.close()
matrix2.close()

MRMatrixReduceOneStep.run()

end = time.time()
timeText.write(str(end-start))
timeText.close()

