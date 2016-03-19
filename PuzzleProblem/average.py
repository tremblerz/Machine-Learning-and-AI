from math import sqrt

def main():

    total = 0.0
    length = 0.0
    average = 0.0

    try:
        #Get the name of a file
	#filename = raw_input('Enter a file name: ')
	filename = "timeBFS.txt"
        #Open the file
        infile = open(filename, 'r')  
	
        #Read values from file and compute average
        for line in infile:
            #print line.rstrip("\n")
            amount = float(line.rstrip("\n"))
            total += amount
            length = length + 1

	infile.close()
        average = float(total) / float(length)
	sum = 0
        infile = open(filename, 'r')  
	for line in infile:
		sum += pow( (float( line.rstrip("\n") ) - average) , 2)
	sum = sqrt( float(sum) / float(length) )
        #Close the file
        infile.close()

        #Print the amount of numbers in file and average
        #print 'There were', length, 'numbers in the file.'
	#print total
        print "Mean value for BFS",format(average, ',.8f')
	print "Standard deviation is",format(sum , ',.8f')
    except IOError:
        print 'An error occurred trying to read the file.'

    except ValueError:
        print 'Non-numeric data found in the file'

    except:
        print('An error has occurred')

    try:
        #Get the name of a file
        #filename = raw_input('Enter a file name: ')
	total=0
        filename = "timeDFS.txt"
        #Open the file
        infile = open(filename, 'r')

        #Read values from file and compute average
        for line in infile:
            #print line.rstrip("\n")
            amount = float(line.rstrip("\n"))
            total += amount
            length = length + 1


        average = float(total) / float(length)
        infile.close()
        average = float(total) / float(length)
        sum = 0
        infile = open(filename, 'r')
        for line in infile:
                sum += pow( (float( line.rstrip("\n") ) - average) , 2)
        sum = sqrt( float(sum) / float(length) )
        #Close the file
        infile.close()
        #Close the file
        infile.close()

        #Print the amount of numbers in file and average
        #print 'There were', length, 'numbers in the file.'
        #print total
	print "Mean value for DFS",format(average , ',.8f')
	print "Standard deviation is",format(sum , ',.8f')
    except IOError:
        print 'An error occurred trying to read the file.' 

    except ValueError:
        print 'Non-numeric data found in the file'

    except:
        print('An error has occurred')

main()
