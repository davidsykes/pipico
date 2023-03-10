import matplotlib.pyplot as plt

fig, ax = plt.subplots()

data_tv = [[0, 0], [4510, 1], [4495, 0], [582, 1], [1664, 0], [586, 1], [1672, 0], [551, 1], [1668, 0], [605, 1], [546, 0], [587, 1], [542, 0], [550, 1], [587, 0], [543, 1], [585, 0], [545, 1], [582, 0], [544, 1], [1671, 0], [621, 1], [1621, 0], [582, 1], [1632, 0], [620, 1], [549, 0], [545, 1], [582, 0], [538, 1], [583, 0], [546, 1], [581, 0], [562, 1], [541, 0], [547, 1], [582, 0], [552, 1], [587, 0], [537, 1], [1663, 0], [592, 1], [575, 0], [545, 1], [555, 0], [549, 1], [579, 0], [545, 1], [585, 0], [550, 1], [553, 0], [585, 1], [1630, 0], [584, 1], [1665, 0], [585, 1], [581, 0], [543, 1], [1666, 0], [587, 1], [1663, 0], [588, 1], [1668, 0], [581, 1], [1667, 0], [574, 1], [1661, 0], [580, 1]]
data_sony = [[0, 0], [2393, 1], [561, 0], [1203, 1], [590, 0], [609, 1], [584, 0], [621, 1], [542, 0], [641, 1], [585, 0], [622, 1], [544, 0], [625, 1], [585, 0], [625, 1], [583, 0], [618, 1], [546, 0], [1251, 1], [542, 0], [664, 1], [551, 0], [1213, 1], [584, 0], [1203, 1], [584, 0], [623, 1], [554, 0], [1247, 1], [596, 0], [578, 1], [593, 0], [1234, 1], [547, 0], [1240, 1], [544, 0], [1248, 1], [581, 0], [1211, 1], [584, 0], [1199, 1], [12569, 0]] #, [2430, 1], [591, 0], [1197, 1], [588, 0], [622, 1], [543, 0], [617, 1], [582, 0], [625, 1], [547, 0], [658, 1], [543, 0], [629, 1], [588, 0], [627, 1], [549, 0], [622, 1], [580, 0], [1245, 1], [545, 0], [619, 1], [584, 0], [1229, 1], [581, 0], [1209, 1], [542, 0], [630, 1], [588, 0], [1212, 1], [585, 0], [628, 1], [589, 0], [1201, 1], [542, 0], [1252, 1], [556, 0], [1240, 1], [548, 0], [1245, 1], [545, 0], [1231, 1], [12590, 0]]#, [2400, 1], [586, 0], [1234, 1], [582, 0], [599, 1], [546, 0], [628, 1], [561, 0], [660, 1], [553, 0], [622, 1], [586, 0], [620, 1], [543, 0], [626, 1], [581, 0], [625, 1], [584, 0], [1207, 1], [586, 0], [625, 1], [551, 0], [1243, 1], [550, 0], [1246, 1], [553, 0], [619, 1], [584, 0], [1216, 1], [551, 0], [663, 1], [544, 0], [1245, 1], [547, 0], [1243, 1], [554, 0], [1246, 1], [545, 0], [1241, 1], [544, 0], [1239, 1], [12582, 0], [2405, 1], [580, 0], [1236, 1], [543, 0], [621, 1], [590, 0], [620, 1], [552, 0], [623, 1], [579, 0], [628, 1], [548, 0], [670, 1], [541, 0], [623, 1], [587, 0], [619, 1], [548, 0], [1241, 1], [583, 0], [622, 1], [546, 0], [1237, 1], [583, 0], [1201, 1], [553, 0], [663, 1], [545, 0], [1243, 1], [548, 0], [654, 1], [545, 0], [1242, 1], [547, 0], [1236, 1], [548, 0], [1246, 1], [542, 0], [1235, 1], [582, 0], [1239, 1], [12568, 0], [2408, 1], [578, 0], [1208, 1], [581, 0], [620, 1], [584, 0], [621, 1], [578, 0], [592, 1], [587, 0], [609, 1], [579, 0], [623, 1], [589, 0], [629, 1], [539, 0], [633, 1], [556, 0], [1244, 1], [584, 0], [593, 1], [621, 0], [1171, 1], [588, 0], [1209, 1], [620, 0], [586, 1], [590, 0], [1200, 1], [592, 0], [588, 1], [598, 0], [1192, 1], [589, 0], [1207, 1], [621, 0], [1197, 1], [588, 0], [1196, 1], [587, 0], [1208, 1]]


def convert(data):
    data2 = []
    ltime = 0
    for d in data:
        ctime = ltime + d[0]
        d[0] = ctime
        data2.append(d)
        ltime = ctime
    return data2

def plot(data, position):
    i = 0
    x = []
    y = []
    while (i < len(data)):
        if (i > 0):
            x.append(data[i][0]-1)
            y.append(data[i-1][1] + position)
        x.append(data[i][0])
        y.append(data[i][1] + position)
        i = i + 1

    ax.plot(x,y)

def analyse(data):
    minval = data[1][0]
    i = 2
    while (i < len(data)):
        if (data[i][0] < minval):
            minval = data[i][0]
        i = i + 1

analyse(data_tv)
analyse(data_sony)

plot(convert(data_tv), 0)
plot(convert(data_sony), 1.1)
plt.show()