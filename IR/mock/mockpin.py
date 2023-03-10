class MockInputPin:
    def __init__(self, on):
        self._value = 1 if on else 0
    def value(self):
        return self._value

class MockOutputPin:
    def value(self, value=None):
        pass

class MockIrReceivePin:
    data = [[ 0 , 1 ],[ 10000 , 0 ],[ 4524 , 1 ],[ 4498 , 0 ],[ 544 , 1 ],[ 1697 , 0 ],[ 565 , 1 ],[ 1669 , 0 ],[ 579 , 1 ],[ 1666 , 0 ],[ 567 , 1 ],[ 585 , 0 ],[ 539 , 1 ],[ 582 , 0 ],[ 542 , 1 ],[ 582 , 0 ],[ 548 , 1 ],[ 580 , 0 ],[ 555 , 1 ],[ 543 , 0 ],[ 548 , 1 ],[ 1694 , 0 ],[ 580 , 1 ],[ 1668 , 0 ],[ 580 , 1 ],[ 1665 , 0 ],[ 575 , 1 ],[ 545 , 0 ],[ 585 , 1 ],[ 548 , 0 ],[ 547 , 1 ],[ 583 , 0 ],[ 544 , 1 ],[ 583 , 0 ],[ 542 , 1 ],[ 581 , 0 ],[ 549 , 1 ],[ 542 , 0 ],[ 586 , 1 ],[ 1636 , 0 ],[ 576 , 1 ],[ 582 , 0 ],[ 545 , 1 ],[ 573 , 0 ],[ 547 , 1 ],[ 586 , 0 ],[ 549 , 1 ],[ 584 , 0 ],[ 547 , 1 ],[ 548 , 0 ],[ 582 , 1 ],[ 546 , 0 ],[ 545 , 1 ],[ 1673 , 0 ],[ 578 , 1 ],[ 579 , 0 ],[ 542 , 1 ],[ 1692 , 0 ],[ 543 , 1 ],[ 1702 , 0 ],[ 545 , 1 ],[ 1665 , 0 ],[ 584 , 1 ],[ 1682 , 0 ],[ 589 , 1 ],[ 1663 , 0 ],[ 569 , 1 ],[ 1679 , 0 ],[ 543 , 1 ]]
    index = 0
    current_value = 1
    time_last_change = 0
    def __init__(self, system):
        self.system = system
    def value(self, value=None):
        current_time = self.system.ticks_us()

        time_since_change = current_time - self.time_last_change

        if time_since_change >= self.data[self.index][0]:
            self.next_value()
        return self.current_value

    def next_value(self):
        self.current_value = self.data[self.index][1]
        if (self.index < len(self.data) - 1):
            self.index = self.index + 1
        self.time_last_change = self.system.ticks_us()
