from collections import defaultdict
from itertools import combinations


def scale_row(row1, a, row2):
	"""
	row2 = a * row1
	>>> m = [1,2,3]
	>>> scale_row([5,4,2], 2, m)
	>>> m == [10, 8, 4]
	True
	"""
	for i, e in enumerate(row1):
		row2[i] = a*e


def add_row(row1, row2, row3):
	"""
	row3 = row1 + row2
	>>> m = [0,0,0]
	>>> add_row([1,2,3], [5,-1,0], m)
	>>> m == [6, 1, 3]
	True
	"""

	for i, e in enumerate(row1):
		row3[i] = e + row2[i]

def newRow(N):
	assert(type(N) == int)
	r = []
	for i in range(N):
		r.append(0)
	return r

class smatrix:
	def __init__(self, dmatrix):
		"""
		given a dense matrix, construct the sparse matrix
		>>> m = [[1,2,3], [1,2,3], [1,2,3]]
		>>> s = smatrix(m)
		>>> s.rank
		3
		"""
		matrix = defaultdict(list)
		num_rows = len(dmatrix)
		num_cols = len(dmatrix[0])
		for i, row in enumerate(dmatrix):
			for j, v in enumerate(row):
				matrix[v].append((i, j))

		self.matrix = matrix
		self.rank = len(matrix)
		self.num_rows = num_rows
		self.num_cols = num_cols

	def SparseMatrixMultiplication(self, B, C):
		"""
		SparseMatrixMultiplication the dense matrix A, with B, and store the result in C
		>>> m = [[1,2,3], [1,2,3], [1,2,3]]
		>>> s = smatrix(m)
		>>> B = [[1,1,1], [1,1,1], [1,1,1]]
		>>> C = [[0,0,0], [0,0,0], [0,0,0]]
		>>> s.SparseMatrixMultiplication(B, C)
		>>> C == [[6,6,6], [6,6,6], [6,6,6]]
		True
		"""
		A = self.matrix
		N = len(B[0])
		for v, indices in A.iteritems():
			dic = defaultdict(list)
			for (i, j) in indices:
				dic[i].append(j)

			for i, b_rows in dic.iteritems():
				B_row = newRow(N)
				for row in b_rows:
					add_row(B_row, B[row], B_row)
				scale_row(B_row, v, B_row)
				add_row(B_row, C[i], C[i])

	def serializeToFile(self, file_name, num=4):
		row = self.num_rows
		col = self.num_cols
		rank = self.rank
		matrix = self.matrix
		with open(file_name, 'w') as fw:
			fw.write("%d %d %d\n"%(row, col, rank))

			for v in matrix.keys():
				i_j_set_list = self.get_optimized_i_j_set(v, num)
				num_i_j_set = len(i_j_set_list)
				fw.write("%f %d \n"%(v, num_i_j_set))
				# construct the union of all i set
				i_set = i_j_set_list[0][0]
				for i_j_set in i_j_set_list:
					i_set = i_set.union(i_j_set[0])
				
				fw.write("%d "%len(i_set))
				for i in i_set:
					fw.write("%d "%i)
				fw.write("\n")
				
				for i_j_set in i_j_set_list:
					
					fw.write("%d "%len(i_j_set[0]))
					for i in i_j_set[0]:
						fw.write("%d "%i)
					fw.write("\n")
					
					fw.write("%d "%len(i_j_set[1]))
					for j in i_j_set[1]:
						fw.write("%d "%j)
					fw.write("\n")
			

	def _get_i_j_set_of_sparse_matrix(self, value):
		"""
		SparseMatrixMultiplication the dense matrix A, with B, and store the result in C
		>>> m = [[1,1,1], [2,2,2], [1,1,3]]
		>>> s = smatrix(m)
		>>> i_j_set = s._get_i_j_set_of_sparse_matrix(1)
		>>> i_j_set[0]
		set([0, 1, 2])
		>>> i_j_set[2]
		set([0, 1])
		"""
		row = self.num_rows
		col = self.num_cols
		i_j_pairs = self.matrix[value]
		i_j_set = defaultdict(set)
		for i, j in i_j_pairs:
			i_j_set[i].add(j)
		return i_j_set 

	def get_optimized_i_j_set(self, value, min):
		"""
		>>> m = [[1,2,1,1,1,1], [2,2,1,1,1,1], [1,2,2,2,2,2]]
		>>> s = smatrix(m)
		>>> l = s.get_optimized_i_j_set(1, 2)
		>>> (set([0,1]), set([2,3,4,5])) in l
		True
		>>> (set([0,2]), set([0])) in l
		True
		"""
		i_j_set = self._get_i_j_set_of_sparse_matrix(value)
		# convert the set to a list
		i_j_list = []
		for i, j in i_j_set.iteritems():
			i_j_list.append((set([i]), j))
		
		# iteratively merge the redundancies
		while True:
			stop_iteration = True
			for (ai, aj), (bi, bj) in combinations(i_j_list, 2):
				similar_values = aj.intersection(bj)
				
				if len(similar_values) == len(aj) and len(similar_values) == len(bj):
					i_j_list.remove((ai, aj))
					i_j_list.remove((bi, bj))
					i_j_list.append((ai.union(bi), aj))
					stop_iteration = False
					break

				if len(similar_values) >= min:
					stop_iteration = False	# some change is still taken place, proceed to next iteration
					i_j_list.remove((ai, aj))
					i_j_list.remove((bi, bj))
					new_aj = aj.difference(similar_values)
					new_bj = bj.difference(similar_values)
					if new_aj:
						i_j_list.append((ai, new_aj))
					if new_bj:
						i_j_list.append((bi, new_bj))
					i_j_list.append((ai.union(bi), similar_values))
					break
				else:
					continue
			if stop_iteration:
				break
			else:
				continue
		return i_j_list



def get_i_j_list_cost(i_j_list, minimum):
	"""
	>>> i_j_list = [(set([0,2]), set([0]))]
	>>> get_i_j_list_cost(i_j_list, 2)
	7
	>>> i_j_list = {1: set([0])}
	>>> get_i_j_list_cost(i_j_list, 2)
	5
	"""

	cost = 0
	if type(i_j_list) is dict:
		for (i, j) in i_j_list.iteritems():
			i_ = 1
			j_ = len(j)
			cost += j_ + (j_ / minimum) * 2 + 2 * i_
			if i_ % 8:
				cost += 2
	else:		
		for (i, j) in i_j_list:
			i_ = len(i)
			j_ = len(j)
			cost += j_ + (j_ / minimum) * 2 + 2 * i_
			if i_ % 8:
				cost += 2
	return cost