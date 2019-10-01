#!/usr/bin/python
# coding=utf-8
import sys
import time
import random

start_time = time.time();

filename = sys.argv[1]

f = open(filename+'.graphs', 'r')

all_lines = list(f)

# for line in all_lines:
# 	print line

# u have the file now.

n2 = 0
n1 = 0
i = 0

NodeMapG1 = {}
NodeMapG2 = {}

f1 = open('var_vals.txt', 'w')

while all_lines[i] != '0 0\n':
	nos = all_lines[i].split()
	x = int(nos[0])
	y = int(nos[1])
	if (x not in NodeMapG2):
		NodeMapG2[x] = n2
		f1.write(str(n2) + " " + str(x) + "\n")
		n2 += 1
	if (y not in NodeMapG2):
		NodeMapG2[y] = n2
		f1.write(str(n2) + " " + str(y) + "\n")
		n2 += 1
	i += 1

f1.write("HEHE\n")
i += 1

while i < len(all_lines):
	nos = all_lines[i].split()
	x = int(nos[0])
	y = int(nos[1])
	if (x not in NodeMapG1):
		NodeMapG1[x] = n1
		f1.write(str(n1) + " " + str(x) + "\n")
		n1 += 1
	if (y not in NodeMapG1):
		NodeMapG1[y] = n1
		f1.write(str(n1) + " " + str(y) + "\n")
		n1 += 1
	i += 1

f1.close()


EdgesG2 = [[0 for i in range(n2)] for j in range(n2)]
EdgesG1 = [[0 for i in range(n1)] for j in range(n1)]

AdjG2_in = [[] for j in range(n2)]
AdjG2_out = [[] for j in range(n2)]
AdjG1_in = [[] for j in range(n1)]
AdjG1_out = [[] for j in range(n1)]


G2_out_not = {}
for i in range(n2):
	x = set()
	for j in range(n2):
		if j != i:
			x.add(j)
	G2_out_not[i] = x


i = 0

# for j in G2_out_not[0]:
# 	print j

while all_lines[i] != '0 0\n':
	nos = all_lines[i].split()
	x = NodeMapG2[int(nos[0])]
	y = NodeMapG2[int(nos[1])]
	EdgesG2[x][y] = 1
	AdjG2_in[y].append(x)
	AdjG2_out[x].append(y)
	# print x
	G2_out_not[x].remove(y)
	i += 1

# print "------FINAL------ \n"
# for j in G2_out_not[0]:
# 	print j

i += 1

while i < len(all_lines):
	nos = all_lines[i].split()
	x = NodeMapG1[int(nos[0])]
	y = NodeMapG1[int(nos[1])]
	EdgesG1[x][y] = 1
	AdjG1_in[y].append(x)
	AdjG1_out[x].append(y)
	i += 1

# matrices ready!!
# no vars for 

num_vars = (n1*n2)
num_const = n1 + n1*(n2*(n2-1))/2 + n2*(n1*(n1 - 1)/2) + (n1*(n1-1)*n2*(n2-1))

f = open(filename+'.satinput', 'w')
f.write('p cnf ' + str(num_vars) + ' ' + str(num_const) + '\n')

# edges in G1 consts:
# varno = 1
# for i in range(n1):
# 	for j in range(n1):
# 		if EdgesG1[i][j] == 0:
# 			f.write('-' + str(varno) + ' 0\n')
# 		else:
# 			f.write(str(varno) + ' 0\n')
# 		varno += 1

# for i in range(n2):
# 	for j in range(n2):
# 		if EdgesG2[i][j] == 0:
# 			f.write('-' + str(varno) + ' 0\n')
# 		else:
# 			f.write(str(varno) + ' 0\n')
# 		varno += 1

# n2^2 + n1^2 done.

def getvarno( j,  i):
	return str(n2*j + i + 1)




# def getvar12( x,  j,  i):
# 	if x == 1:
# 		return str(j*n1 + i + 1)
# 	else:
# 		return str(n1**2 + j*n2 + i + 1)



# put some vals of 
NotPoss = {}

for i in range(n1):
	for j in range(n2):
		if len(AdjG2_out[j]) < len(AdjG1_out[i]) or len(AdjG2_in[j]) < len(AdjG1_in[i]) :
			NotPoss[(i,j)] = True;

# now we know the ones that are not possible.
# eliminate more!
for zz in range(9*n1):
	i = zz%n1
	for j in range(n2):
		ilist = AdjG1_out[i]
		leni = len(ilist)
		jlist = AdjG2_out[j]
		lenj = len(jlist)

		if (i,j) not in NotPoss and lenj < 40 and leni <= 20:
			# still possible :p Hmmmmmmmm...
			# ith corresponds to ilist[i]
			onlyone = set()
			for x in range(leni):
				y = set()
				for m in range(lenj):
					if (ilist[x], jlist[m]) not in NotPoss and jlist[m] not in onlyone:
						y.add(jlist[m])
				if len(y) == 0:
					# print "NICE -------------- \n"
					NotPoss[(i,j)] = True
					break
				if len(y) == 1:
					onlyone.add(y.pop())
			# x = xth out of i.


for i in range(n1):
	s = ''
	for j in range(n2):
		if (i,j) not in NotPoss:
			s += ('-' + getvarno(i,j) + ' ')
	s += '0\n'
	f.write(s)

# f.flush()

for i in range(n1):
	for j in range(n2):
		for k in xrange(j+1,n2,1):
			if (i,j) not in NotPoss and (i,k) not in NotPoss:
				f.write(getvarno(i,j) + ' ' + getvarno(i,k) + ' 0\n')

# f.flush()

for i in range(n2):
	for j in range(n1):
		for k in xrange(j+1,n1,1):
			if (j,i) not in NotPoss and (k,i) not in NotPoss:
				f.write(getvarno(j,i) + ' ' + getvarno(k,i) + ' 0\n')

# f.flush()


for i in range(n1):
	for j in range(n1):
		for k in range(n2):
# print time.time() - start_time
# print "Loop for i finished"
# print i
			if (i,k) not in NotPoss:
				if EdgesG1[i][j]:
					s = ""
					s = s + getvarno(i,k) + " "
					for x in AdjG2_out[k]:
						if (j,x) not in NotPoss:
							# noclauses[x] += 1
							s+="-"+getvarno(j,x)+" "
					s+="0\n"
					f.write(s)
				else:
					for x in AdjG2_out[k]:
						if (j,x) not in NotPoss:
							# noclauses[k] += 1
							# noclauses[x] += 1
							f.write(getvarno(i,k)+" "+getvarno(j,x)+" 0\n")

# n2sorted = sorted(noclauses.items(), key=lambda x:x[1])


for x in range(n2):
	for y in G2_out_not[x]:
		if y != x:
			for i in range(n1):
				if (i,x) not in NotPoss:
					for i_adj in AdjG1_out[i]:
						if (i_adj,y) not in NotPoss:
							f.write(getvarno(i,x) + " " + getvarno(i_adj,y) + " 0\n")



for p in NotPoss:
	(x,y) = p
	f.write(getvarno(x,y)+" 0\n")

print time.time() - start_time
				# for l in range(n2):
				# 	if (k != l):
				# 			if EdgesG2[k][l] != EdgesG1[i][j] and (i,k) not in NotPoss and (j,l) not in NotPoss:
				# 				f.write(getvarno(i,k) + ' ' + getvarno(j,l) + ' 0\n')
				# f.flush()
	# print time.time() - start_time
	# print "Loop for i finished"
	# print i
