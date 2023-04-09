import matplotlib.pyplot as plt
import json

fig, ax = plt.subplots()

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

def read_codes(file_path):
    with open(file_path, 'r') as content_file:
        content = content_file.read()
    data = json.loads(content)
    return data

def convert_code(code):
    converted = []
    for c in code:
        converted.append([c['t'],c['v']])
    return converted

def extract_code(codes, code_to_return):
    for code in codes:
        if code['code'] == code_to_return:
            return convert_code(code['waveform'])


all_codes = read_codes('codes.json')

code_0 = extract_code(all_codes, '0')
code_1 = extract_code(all_codes, '265055')


plot(code_0, 0)
plot(code_1, 1.1)
plt.show()