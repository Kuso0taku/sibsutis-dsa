import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table1.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float, float, float))
sizes = []
radix = []
merge = []
heap = []
for line in data:
    sizes.append(line[1]/1000)
    radix.append(line[2]*10**3)
    merge.append(line[3]*10**3)
    heap.append(line[4]*10**3)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, radix, "^-", color="red", label="Radix Sort", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, merge, "o-", color="blue", label="Merge Sort", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, heap, "s-", color="green", label="Heap Sort", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [1, 4, 16, 64, 256, 512]
plt.yticks(y_ticks, [str(y) for y in y_ticks])
plt.ylim(1, 512)

# Ox
plt.xticks(sizes, [str(int(x)) for x in sizes])
plt.xlim(sizes[0], sizes[-1])

plt.xlabel("Количество элементов в массиве, тыс")
plt.ylabel("Время выполнения, мс")

# grid
plt.grid(True, which='both', linestyle='--', linewidth=0.5, color='grey', alpha=0.7)

# legend
plt.legend()

# save
plt.savefig("../out/graph2.png", dpi=175)

# display
plt.tight_layout()
plt.show()
