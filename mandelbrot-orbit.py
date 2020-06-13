import matplotlib.pyplot as plt
from numpy import loadtxt

filename = "./output/mandelbrot-orbit"

# Source
data = loadtxt(filename + ".txt")

# Columns: iteration real-part imaginary-part
iteration, re, im = data[:,0], data[:,1], data[:,2]

# Plot real and imaginary parts
plt.plot(iteration, im, color="blue", linewidth=1.5)
plt.plot(iteration, re, color="orange", linewidth=1.5)

# Show grid
plt.grid(True)

# Image size
plt.gcf().set_size_inches(12, 4)

# x axis
plt.xlim([0,100])

# Save image
plt.savefig(filename + ".png", bbox_inches="tight")