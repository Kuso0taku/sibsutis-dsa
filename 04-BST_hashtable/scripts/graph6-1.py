import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table7.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, int, float, int))
sizes = []
KR_lookup = []
jenkins_lookup = []
for line in data:
    sizes.append(line[1]/1000)
    KR_lookup.append(line[2]*10**6)
    jenkins_lookup.append(line[4]*10**6)

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, KR_lookup, "s-", color="red", label="KR_lookup", markersize=4, 
         linewidth=1.5, alpha=0.7)
plt.plot(sizes, jenkins_lookup, "x-", color="blue", label="jenkins_lookup", markersize=4, 
         linewidth=1.5, alpha=0.5)

# Oy
plt.yscale('log')

y_ticks = [0.02, 0.03, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14]
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
plt.savefig("../out/graph6-1.png", dpi=175)

# display
plt.tight_layout()
plt.show()
