from mrjob.job import MRJob
from mrjob.job import MRStep
import re
import os
import sys
import time

class MRMatrixReduceOneStep(MRJob):

	def steps(self):
		return [MRStep(mapper = self.mapper_first_iteration, reducer = self.reducer_first_iteration),
			MRStep(mapper = self.mapper_second_iteration, reducer = self.reducer_second_iteration)]

	def mapper_first_iteration(self, _, line):

		if len(line.split()) == 2:
			return 

		i, j, value = line.split()
		filename = os.environ['map_input_file']

		if filename == 'File1ForLab3.txt':
			yield j, ('Matrix-identifier-1', i, value)
		else:
			yield i, ('Matrix-identifier-2', j, value)

	def reducer_first_iteration(self, j, val):

		matrix_1_values  = []
		matrix_2_values  = []

		for values in val:
			if values[0] == 'Matrix-identifier-1':
				matrix_1_values.append(values)
			else:
				matrix_2_values.append(values)

		for (a, i, value_1) in matrix_1_values:
			for (b, k, value_2) in matrix_2_values:
				yield j, (i, k, int(value_1) * int(value_2))

	def mapper_second_iteration(self, j, val):
		yield (val[0], val[1]), val[2]

	def reducer_second_iteration(self, key, val):
		yield key, sum(val)


timeText = open("time2.txt", "w")
start = time.time()

WORD_RE = re.compile(r"[\w']+")

MRMatrixReduceOneStep.run()

end = time.time()
timeText.write(str(end-start))
timeText.close()
