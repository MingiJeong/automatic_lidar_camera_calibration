import numpy as np

data = np.loadtxt("0.pcd", skiprows=11)
np.savetxt("0r.pcd", data, fmt="%.3f", delimiter=" ")
