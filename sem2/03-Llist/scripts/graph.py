import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table.csv", delimiter=',', skip_header=1, 
                     dtype=(int, float, float))
sizes = []
add_tail = []
lookup = []
for line in data:
    sizes.append(line[0]/1000)
    add_tail.append(line[1]*10**6)
    lookup.append(line[2]*10**6)

print(data)
plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, add_tail, "s-", color="green", label="list_add_tail", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, lookup, "x-", color="black", label="list_lookup", markersize=4, 
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
plt.savefig("../out/graph.png", dpi=175)

# display
plt.tight_layout()
plt.show()
