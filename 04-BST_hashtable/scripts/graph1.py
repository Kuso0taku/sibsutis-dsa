import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table2.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float))
sizes = []
bstree_lookup = []
hashtable_lookup = []
for line in data:
    sizes.append(line[1]/1000)
    bstree_lookup.append(line[2]*10**6)
    hashtable_lookup.append(line[3]*10**6)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, bstree_lookup, "s-", color="green", label="bstree_lookup", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, hashtable_lookup, "x-", color="blue", label="hashtable_lookup", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [0.03, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14]
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
