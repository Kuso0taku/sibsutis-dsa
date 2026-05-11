import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table1.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float))
sizes = []
minheap_insert = []
build_minheap = []
for line in data:
    sizes.append(line[1]/1000)
    minheap_insert.append(line[2]*10**3)
    build_minheap.append(line[3]*10**3)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, minheap_insert, "s-", color="green", label="minheap_insert", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, build_minheap, "x-", color="blue", label="build_minheap", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [1, 4, 16]
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
plt.savefig("../out/graph1.png", dpi=175)

# display
plt.tight_layout()
plt.show()
