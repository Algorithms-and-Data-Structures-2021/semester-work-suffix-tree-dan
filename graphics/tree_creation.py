import matplotlib.ticker
import matplotlib.pyplot as plt
import csv

lengths = []
results = []
with open('data.csv', 'r') as data_file:
    reader = csv.reader(data_file, delimiter=',', quotechar='|')
    for row in reader:
        lengths.append(int(row[0]))
        results.append(int(row[1]) / 1000000)
plt.style.use("fivethirtyeight")
fig, ax = plt.subplots(figsize=(11, 11))
y1 = [y1 ** 2 / 1000000 for y1 in lengths]
ax.set_title('Зависимость времени построения дерева\n от длины строки')
ax.set_xlabel('Длина строки')
ax.set_ylabel('Время в мс')
ax.xaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%d'))
ax.yaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%d'))
ax.plot(lengths, results, color='red', linestyle='-', marker='o', label='проведенные замеры')
ax.plot(lengths[:7], y1[:7], color='green', marker='o', label='O(n^2)')
ax.legend(loc='lower right')
fig.savefig('tree-creation.png')
