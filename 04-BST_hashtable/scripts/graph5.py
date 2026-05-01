import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table6.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float))
sizes = []
bstree_max_worst = []
bstree_max_avg = []
for line in data:
    sizes.append(line[1]/1000)
    bstree_max_worst.append(line[2]*10**6)
    bstree_max_avg.append(line[3]*10**6)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, bstree_max_worst, "s-", color="green", label="bstree_max_worst", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, bstree_max_avg, "x-", color="blue", label="bstree_max_avg", markersize=4, 
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
plt.ylabel("Время выполнения, мкс")

# grid
plt.grid(True, which='both', linestyle='--', linewidth=0.5, color='grey', alpha=0.7)

# legend
plt.legend()

# save
plt.savefig("../out/graph5.png", dpi=175)

# display
plt.tight_layout()
plt.show()
