import matplotlib.pyplot as plt
import numpy as np

# handle data
data = np.genfromtxt("../out/table1.csv", delimiter=',', skip_header=1, 
                     dtype=(int, int, float, float, float))
sizes = []
linear = []
binary = []
exp = []
for line in data:
    sizes.append(line[1]/1000)
    linear.append(line[2]*(10**6))
    binary.append(line[3]*(10**6))
    exp.append(line[4]*(10**6))

plt.figure(figsize=(10, 6))

# curves
plt.plot(sizes, linear, "^-", color="red", label="Linear", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, binary, "o-", color="blue", label="Binary", markersize=4, 
         linewidth=1.5)
plt.plot(sizes, exp, "s-", color="green", label="Exponential", markersize=4, 
         linewidth=1.5)

# Oy
plt.yscale('log')

y_ticks = [0.1, 0.2, 1.0, 4.0, 16.0, 64.0, 256.0, 1024.0, 4096.0]
plt.yticks(y_ticks, [str(y) for y in y_ticks])
#plt.ylim(0.1, 5000)

# Ox
plt.xticks(sizes, [str(int(x)) for x in sizes])
plt.xlim(250, 5000)
plt.xlabel("Количество элементов в массиве, тыс")
plt.ylabel("Время выполнения, мкс")

# grid
plt.grid(True, which='both', linestyle='--', linewidth=0.5, color='grey', alpha=0.7)

# legend
plt.legend()

# title
#plt.title('Рисунок 1. Зависимость времени выполнения алгоритмов поиска элемента в массиве от количества элементов в массиве')

# save
plt.savefig("../out/graph1.png", dpi=175)

# display
plt.tight_layout()
plt.show()
