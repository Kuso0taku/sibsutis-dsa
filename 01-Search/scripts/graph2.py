import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table1.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float, float))
sizes = []
binary = []
exp = []
for line in data:
    sizes.append(line[1]/1000)
    binary.append(line[3]*(10**6))
    exp.append(line[4]*(10**6))

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, binary, "^-", color="red", label="Binary", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, exp, "o-", color="blue", label="Exponential", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [i/100 for i in range(6, 16)]
plt.yticks(y_ticks, [str(y) for y in y_ticks])

# Ox
plt.xticks(sizes, [str(int(x)) for x in sizes])
plt.xlim(250, 5000)

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
