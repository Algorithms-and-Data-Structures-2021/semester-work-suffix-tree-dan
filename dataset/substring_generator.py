import random
import string
import csv
import os


def main():
    folders = ["data/has_substr/1/", "data/has_substr/2/", "data/has_substr/3/", "data/has_substr/4/",
               "data/has_substr/5/",
               "data/has_substr/6/", "data/has_substr/7/", "data/has_substr/8/", "data/has_substr/9/",
               "data/has_substr/10/"]
    files = ['100.csv', '500.csv', '1000.csv', '5000.csv', '10000.csv', '25000.csv', '50000.csv', '100000.csv',
             '250000.csv', '500000.csv', '750000.csv', '1000000.csv']
    test_string = ''.join(random.choice(string.ascii_lowercase) for i in range(1001000))

    for folder in folders:
        for file in files:
            samples_count = int(file.split('.')[0])
            filename = folder + file
            os.makedirs(os.path.dirname(filename), exist_ok=True)
            with open(filename, 'w') as csv_file:
                writer = csv.writer(csv_file, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
                substr_index = random.randint(0, len(test_string) - samples_count)
                writer.writerow([test_string[substr_index:(substr_index + samples_count)]])
            csv_file.close()
    str_file = open("data/has_substr/test-string.csv", 'w')
    str_file.write(test_string)
    str_file.close()


if __name__ == '__main__':
    main()
