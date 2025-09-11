def generate_map_dict(rows=15, cols=20):
    mapping = {}
    num = 1
    for row in range(1, rows + 1):
        for col in range(1, cols + 1):
            mapping[num] = (row, col)
            num += 1
    return mapping

map = generate_map_dict()