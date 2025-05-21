import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("results.txt")
sizes = data[:, 0]
gflops = data[:, 1]
bandwidth = data[:, 2]

# Переводим размер вектора в мегабайты (2 вектора * 8 байт)
size_MB = sizes * 2 * 8 / (1024**2)

plt.figure(figsize=(12, 8))
plt.plot(size_MB, gflops, label="GFLOPS", marker='o')
plt.plot(size_MB, bandwidth, label="Bandwidth", marker='x')

plt.xlabel("Vector Size (MB)", fontsize=18)
plt.ylabel("Performance (GFLOPS) / Bandwidth (GB/s)", fontsize=18)
plt.title("Scalar Vector Product Performance vs Vector Size", fontsize=18)
plt.legend(fontsize=18)
plt.grid(True, which="both", ls="--", linewidth=0.5)

plt.yscale("log")
plt.xscale("log")

plt.xticks(fontsize=18)
plt.yticks(fontsize=18)

plt.tight_layout()
plt.show()
