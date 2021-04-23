import argparse
import csv
import os
import random
import string

DEFAULT_DESCRIPTION = 'CSV dataset generator script demo.'
DEFAULT_SAMPLES = 100


# To create data you have to execute this script using console command 'python generate_csv_dataset.py' in needed dir


def parse_args():
    """
    Парсинг аргументов командной строки (CLI).
    :return интерфейс для работы с аргументами.

    Больше информации на https://docs.python.org/3.7/howto/argparse.html
    """

    # parser = argparse.ArgumentParser(description=DEFAULT_DESCRIPTION)

    # parser.add_argument('output',
    #                     type=str,
    #                     help='output CSV file, e.g. data/output.csv')

    # parser.add_argument('--samples',
    #                     type=int,
    #                     default=DEFAULT_SAMPLES,
    #                     help='number of samples to generate (default: {})'.format(DEFAULT_SAMPLES))

    # return parser.parse_args()


def main():
    folders = ["data/tree_creation/1/", "data/tree_creation/2/", "data/tree_creation/3/", "data/tree_creation/4/", "data/tree_creation/5/",
               "data/tree_creation/6/", "data/tree_creation/7/", "data/tree_creation/8/", "data/tree_creation/9/", "data/tree_creation/10/"]
    files = ['100.csv', '500.csv', '1000.csv', '5000.csv', '10000.csv', '25000.csv', '50000.csv', '100000.csv',
             '250000.csv', '500000.csv', '750000.csv', '1000000.csv']
    for folder in folders:
        for file in files:
            samples_count = int(file.split('.')[0])
            filename = folder + file
            os.makedirs(os.path.dirname(filename), exist_ok=True)
            with open(filename, 'w') as csv_file:
                writer = csv.writer(csv_file, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
                writer.writerow([''.join(random.choice(string.ascii_lowercase) for i in range(samples_count))])


if __name__ == '__main__':
    # args = parse_args()

    # # валидация аргументов
    # if args.samples < 0:
    #     raise ValueError('Number of samples must be greater than 0.')

    # # запись данных в файл
    # with open(args.output, 'w') as file:
    #     for i in range(args.samples - 1):
    #         file.write('{},'.format(i))
    #     file.write(str(args.samples - 1))
    main()
