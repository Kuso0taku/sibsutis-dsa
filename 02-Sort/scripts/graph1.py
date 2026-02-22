import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table1.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float, float, float))
sizes = []
radix = []
merge = []
heap = []
select = []
for line in data:
    sizes.append(line[1]/1000)
    radix.append(line[2])
    merge.append(line[3])
    heap.append(line[4])
    select.append(line[5])

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, radix, "^-", color="red", label="Radix Sort", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, merge, "o-", color="blue", label="Merge Sort", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, heap, "s-", color="green", label="Heap Sort", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, select, "x-", color="black", label="Selection Sort", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [0.2, 1, 4, 16, 64, 256, 1024]
plt.yticks(y_ticks, [str(y) for y in y_ticks])

# Ox
plt.xticks(sizes, [str(int(x)) for x in sizes])
plt.xlim(sizes[0], sizes[-1])

# label
plt.xlabel("Количество элементов в массиве, тыс")
plt.ylabel("Время выполнения, с")

# grid
plt.grid(True, which='both', linestyle='--', linewidth=0.5, color='grey', alpha=0.7)

# legend
plt.legend()

# save
plt.savefig("../out/graph1.png", dpi=175)

# display
plt.tight_layout()
plt.show()
