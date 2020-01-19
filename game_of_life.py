from scipy import signal

INPUT = 'input_files/input_second.txt'


def load_file():
    with open(INPUT, 'r') as f:
        matrix = [[int(num) for num in line.split(' ')] for line in f]
    return matrix


def evaluate_cell(matrix):
    count_matrix = []
    for index_x, row in enumerate(matrix):
        tmp_list = []
        for index_y in range(len(row)):
            tmp_list.append(count_neighbors(matrix, index_x, index_y))
        count_matrix.append(tmp_list)
    return count_matrix


def count_neighbors(matrix, y, x):
    live_count = 0

    try:
        if x - 1 >= 0 and y - 1 >= 0 and matrix[y - 1][x - 1] == 1:
            live_count += 1
    except:
        pass
    try:
        if x >= 0 and y - 1 >= 0 and matrix[y - 1][x] == 1:
            live_count += 1
    except:
        pass
    try:
        if x + 1 >= 0 and y - 1 >= 0 and matrix[y - 1][x + 1] == 1:
            live_count += 1
    except:
        pass
    try:
        if x - 1 >= 0 and y >= 0 and matrix[y][x - 1] == 1:
            live_count += 1
    except:
        pass
    try:
        if x + 1 >= 0 and y >= 0 and matrix[y][x + 1] == 1:
            live_count += 1
    except:
        pass
    try:
        if x - 1 >= 0 and y + 1 >= 0 and matrix[y + 1][x - 1] == 1:
            live_count += 1
    except:
        pass
    try:
        if x >= 0 and y + 1 >= 0 and matrix[y + 1][x] == 1:
            live_count += 1
    except:
        pass
    try:
        if x + 1 >= 0 and y + 1 >= 0 and matrix[y + 1][x + 1] == 1:
            live_count += 1
    except:
        pass

    return live_count


def next_generation(count_matrix, matrix):
    for index_x, row in enumerate(count_matrix):
        for index_y, item in enumerate(row):
            if item < 2:
                matrix[index_x][index_y] = 0
            elif item == 2 or item == 3:
                matrix[index_x][index_y] = 1
            elif item > 3:
                matrix[index_x][index_y] = 0
    return matrix


if __name__ == "__main__":
    matrix = load_file()
    while True:
        [print(row) for row in matrix]
        print("")
        count_matrix = evaluate_cell(matrix)
        # [print(row) for row in count_matrix]
        # print("")
        matrix = next_generation(count_matrix, matrix)
        [print(row) for row in matrix]
        print("")
