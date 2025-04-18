import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("results.txt")
sizes = data[:, 0]
gflops = data[:, 1]
bandwidth = data[:, 2]

# Переводим размер вектора в мегабайты (2 вектора * 8 байт)
size_MB = sizes * 2 * 8 / (1024**2)

plt.plot(size_MB, gflops, label="GFLOPS")
plt.plot(size_MB, bandwidth, label="Bandwidth (GB/s)")
plt.xlabel("Vector Size (MB)")
plt.ylabel("Performance")
plt.legend()
plt.grid()
plt.title("Performance vs Vector Size")
plt.tight_layout()
plt.show()