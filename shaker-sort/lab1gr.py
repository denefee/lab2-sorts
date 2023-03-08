import numpy as np
import matplotlib.pyplot as plt

x = np.array([])
y = np.array([])

for i in np.arange(10, 2000, 10):
    x = np.append(x, i)

f = open('out1-3.txt')
for line in f:
    y = np.append(y, int(line))
f.close()


plt.xlabel(r'Количество данных в массиве', fontsize=14)
plt.ylabel(r'Время работы программы, $нc$', fontsize=14)
plt.title(r'График зависимости времени работы шейкерной сортировки (backward steps) от размера массива при среднем случае', fontsize=14)
plt.grid(True)
plt.errorbar(x, y, xerr=0, yerr=0, fmt='+', color='black', capsize=3)
p = np.polyfit(x, y, 2, full=True, cov=False)
print(p)
p = p[0]
yfit = np.polyval(p,x)
plt.plot(x, yfit, color="firebrick")
plt.show()