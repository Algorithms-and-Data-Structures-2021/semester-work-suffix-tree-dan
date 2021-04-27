import matplotlib.ticker
import matplotlib.pyplot as plt
import csv

lengths = []
results = []
with open('data.csv', 'r') as data_file:
    reader = csv.reader(data_file, delimiter=',', quotechar='|')
    for row in reader:
        lengths.append(int(row[0]))
        results.append(int(row[2]) / 1000000)
plt.style.use("fivethirtyeight")
fig, ax = plt.subplots(figsize=(11, 11))

y1 = [y1 / 1000000 for y1 in lengths]
y2 = [y2 / 1000000 * 8 for y2 in lengths]
ax.set_title('Зависимость времени проверки наличия\n подстроки от её длины')
ax.set_xlabel('Длина подстроки')
ax.set_ylabel('Время в мс')
ax.xaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%d'))
ax.yaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%d'))
ax.plot(lengths, results, color='red', linestyle='-', marker='o', label='проведенные замеры')
ax.plot(lengths, y1, color='green', marker='o', label='O(n)')
ax.plot(lengths, y2, color='blue', marker='o', label='O(n) * 8')
ax.legend(loc='lower right')
fig.savefig('has-substr.png')
