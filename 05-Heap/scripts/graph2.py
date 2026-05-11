import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table2.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float))
sizes = []
minheap_extractmin = []
minheap_decreasekey = []
for line in data:
    sizes.append(line[1]/1000)
    minheap_extractmin.append(line[2]*10**6)
    minheap_decreasekey.append(line[3]*10**6)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, minheap_extractmin, "s-", color="green", label="minheap_extractmin", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, minheap_decreasekey, "x-", color="blue", label="minheap_decreasekey", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

#y_ticks = [0.2, 0.4, 0.5, 0.6, 0.8, 1]
y_ticks = [0.2, 1, 4, 16, 64, 256, 1024]
plt.yticks(y_ticks, [str(y) for y in y_ticks])

# Ox
plt.xticks(sizes, [str(int(x)) for x in sizes])
plt.xlim(sizes[0], sizes[-1])

# label
plt.xlabel("Количество элементов в массиве, тыс")
plt.ylabel("Время выполнения, мкс")

# grid
plt.grid(True, which='both', linestyle='--', linewidth=0.5, color='grey', alpha=0.7)

# legend
plt.legend()

# save
plt.savefig("../out/graph2.png", dpi=175)

# display
plt.tight_layout()
plt.show()
