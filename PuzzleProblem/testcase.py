import random
for i in range(20000):
	num=range(9)
	random.shuffle(num)
	array=''
	c = 0
	for x in num:
		c += 1
		array=array+str(x) + " "
		if not c % 3:
			array += "\n"
	print array
	#raw_input()
