import matplotlib.ticker
import matplotlib.pyplot as plt
import csv

lengths = []
results = []
with open('data.csv', 'r') as data_file:
    reader = csv.reader(data_file, delimiter=',', quotechar='|')
    for row in reader:
        lengths.append(int(row[0]))
        results.append(int(row[3]) / 1000000)
plt.style.use("fivethirtyeight")
fig, ax = plt.subplots(figsize=(11, 11))
y1 = [y1 / 1000000 for y1 in lengths]
y2 = [y2 / 1000000 * 90 for y2 in lengths]
y3 = [y3 ** 2 / 1000000 for y3 in lengths]
ax.set_title('Зависимость времени подсчета\n кол-ва различных подстрок')
ax.set_xlabel('Длина строки')
ax.set_ylabel('Время в мс')
ax.xaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%d'))
ax.yaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%d'))
ax.plot(lengths, results, color='red', linestyle='-', marker='o', label='проведенные замеры')
ax.plot(lengths, y1, color='green', marker='o', label='O(n)')
ax.plot(lengths, y2, color='blue', marker='o', label='O(n) * 90')
ax.plot(lengths[:6], y3[:6], color='yellow', marker='o', label='O(n^2)')
ax.legend(loc='lower right')
fig.savefig('count-all-substr.png')
