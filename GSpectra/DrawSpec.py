import matplotlib.pyplot as plt
import numpy as np
import inspect
import sys

if len(sys.argv)<>2:
	print 'Need a spectrum file name'
	sys.exit()
	

with open(sys.argv[1]) as f:
    polyShape = []
    for line in f:
        line = line.split() # to deal with blank 
        if line:            # lines (ie skip them)
            line = [int(i) for i in line]
            polyShape.append(line)
array = np.asarray(polyShape)
#array = array.transpose()
#lines = [int(x) for x in line.rstrip('\n') for line in open('Spectrum_temp.txt')]
print array[2:]

t = np.arange(0,array[0],array[1])
s = array[2:]
plt.plot(t, s)

plt.xlabel('Energy (keV)')
plt.ylabel('Counts per bin')
plt.title('Spectrum')
plt.grid(True)
#plt.savefig("test.png")
plt.show()

