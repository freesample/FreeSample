import numpy as np
import matplotlib.pyplot as plt

def LoadAndPlot(filename):
  data = np.loadtxt(filename)
  x = data[:,0]
  y = data[:,1]
  plt.plot(x, y, 'r-')
  plt.ylim([0.0,1.0])
  plt.show()

  return x,y

def Histogram(filename):
  data = np.loadtxt(filename)
  y = data[:,1]
  plt.hist(y)
  plt.show()
