import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table2.csv", delimiter=',', skip_header=1,
                     dtype=(int, int, float, float, float, float))
sizes = []
bstree_max = []
rbtree_max = []
for line in data:
    sizes.append(line[1]/1000)
    bstree_max.append(line[4]*10**6)
    rbtree_max.append(line[5]*10**6)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, bstree_max, "s-", color="green", label="bstree_max_worst", markersize=4,
         linewidth=1.5)
plt.plot(sizes, rbtree_max, "x-", color="red", label="rbtree_max_worst", markersize=4,
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [0.02, 0.05, 0.1, 0.5, 1, 5, 10, 50]
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
plt.savefig("../out/graph2-2.png", dpi=175)

# display
plt.tight_layout()
plt.show()
