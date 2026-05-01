import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table7.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, int, float, int))
sizes = []
KR_collisions = []
jenkins_collisions = []
for line in data:
    sizes.append(line[1]/1000)
    KR_collisions.append(line[3])
    jenkins_collisions.append(line[5])

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, KR_collisions, "s-", color="red", label="KR_collisions", markersize=4, 
         linewidth=1.5, alpha=0.7)
plt.plot(sizes, jenkins_collisions, "x-", color="blue", label="jenkins_collisions", markersize=4, 
         linewidth=1.5, alpha=0.5)

# Oy
plt.yscale('log')

y_ticks = [4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288]
plt.yticks(y_ticks, [str(y) for y in y_ticks])

# Ox
plt.xticks(sizes, [str(int(x)) for x in sizes])
plt.xlim(sizes[0], sizes[-1])

# label
plt.xlabel("Количество элементов в массиве, тыс")
plt.ylabel("Число коллизий")

# grid
plt.grid(True, which='both', linestyle='--', linewidth=0.5, color='grey', alpha=0.7)

# legend
plt.legend()

# save
plt.savefig("../out/graph6-2.png", dpi=175)

# display
plt.tight_layout()
plt.show()
