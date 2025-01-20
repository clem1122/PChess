import PChess as pc
b = pc.Board()

for i in range(30):
    print(i, " : ", b.valhalla_coord_to_index(b.valhalla_index_to_coord(i)))


