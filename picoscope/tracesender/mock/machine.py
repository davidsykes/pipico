class Pin:
    OUT = 1
    def __init__(self, name, direction):
        self.name = name
    def value(self, val):
        if self.name == 'LED':
            print('LED ', 'on' if val == 1 else 'off')
        else:
            raise Exception(''.join(['Invalid pin "', self.name, '"']))