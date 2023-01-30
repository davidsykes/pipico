import sys
import pytest
sys.path.append('../src')
from waveanalyser import WaveAnalyser
from irexception import IrException

def convert():
    data = [[ 0 , 1 ],[ 4455 , 0 ],[ 8838 , 1 ],[ 9340 , 0 ],[ 10917 , 1 ],[ 11410 , 0 ],[ 12974 , 1 ],[ 13466 , 0 ],[ 15033 , 1 ],[ 15523 , 0 ],[ 15974 , 1 ],[ 16422 , 0 ],[ 16911 , 1 ],[ 17396 , 0 ],[ 17851 , 1 ],[ 18303 , 0 ],[ 18796 , 1 ],[ 19286 , 0 ],[ 19693 , 1 ],[ 20188 , 0 ],[ 21761 , 1 ],[ 22251 , 0 ],[ 23869 , 1 ],[ 24364 , 0 ],[ 25929 , 1 ],[ 26419 , 0 ],[ 26866 , 1 ],[ 27361 , 0 ],[ 27809 , 1 ],[ 28301 , 0 ],[ 28759 , 1 ],[ 29251 , 0 ],[ 29709 , 1 ],[ 30206 , 0 ],[ 30617 , 1 ],[ 31110 , 0 ],[ 31555 , 1 ],[ 32051 , 0 ],[ 33618 , 1 ],[ 34119 , 0 ],[ 34568 , 1 ],[ 35069 , 0 ],[ 35516 , 1 ],[ 36004 , 0 ],[ 36456 , 1 ],[ 36943 , 0 ],[ 37430 , 1 ],[ 37892 , 0 ],[ 38344 , 1 ],[ 38832 , 0 ],[ 39323 , 1 ],[ 39857 , 0 ],[ 41394 , 1 ],[ 41893 , 0 ],[ 42349 , 1 ],[ 42805 , 0 ],[ 44409 , 1 ],[ 44901 , 0 ],[ 46471 , 1 ],[ 46964 , 0 ],[ 48528 , 1 ],[ 49020 , 0 ],[ 50597 , 1 ],[ 51092 , 0 ],[ 52667 , 1 ],[ 53156 , 0 ],[ 54684 , 1 ]]
    t = 0
    i = 0
    d2 = []
    while (i < len(data)):
        d3 = []
        d3.append(data[i][0] - t)
        d3.append(data[i][1])
        d2.append(d3)
        t = data[i][0]
        i = i + 1
    print(d2)

class Test:
    data = []

    def setup_method(self, test_method):
        self.data = [[ 0 , 0 ],[ 4524 , 1 ],[ 4498 , 0 ],[ 544 , 1 ],[ 1697 , 0 ],[ 565 , 1 ],[ 1669 , 0 ],[ 579 , 1 ],[ 1666 , 0 ],[ 567 , 1 ],[ 585 , 0 ],[ 539 , 1 ],[ 582 , 0 ],[ 542 , 1 ],[ 582 , 0 ],[ 548 , 1 ],[ 580 , 0 ],[ 555 , 1 ],[ 543 , 0 ],[ 548 , 1 ],[ 1694 , 0 ],[ 580 , 1 ],[ 1668 , 0 ],[ 580 , 1 ],[ 1665 , 0 ],[ 575 , 1 ],[ 545 , 0 ],[ 585 , 1 ],[ 548 , 0 ],[ 547 , 1 ],[ 583 , 0 ],[ 544 , 1 ],[ 583 , 0 ],[ 542 , 1 ],[ 581 , 0 ],[ 549 , 1 ],[ 542 , 0 ],[ 586 , 1 ],[ 1636 , 0 ],[ 576 , 1 ],[ 582 , 0 ],[ 545 , 1 ],[ 573 , 0 ],[ 547 , 1 ],[ 586 , 0 ],[ 549 , 1 ],[ 584 , 0 ],[ 547 , 1 ],[ 548 , 0 ],[ 582 , 1 ],[ 546 , 0 ],[ 545 , 1 ],[ 1673 , 0 ],[ 578 , 1 ],[ 579 , 0 ],[ 542 , 1 ],[ 1692 , 0 ],[ 543 , 1 ],[ 1702 , 0 ],[ 545 , 1 ],[ 1665 , 0 ],[ 584 , 1 ],[ 1682 , 0 ],[ 589 , 1 ],[ 1663 , 0 ],[ 569 , 1 ],[ 1679 , 0 ],[ 543 , 1 ]]
        self.analyser = WaveAnalyser()

    def test_first_value_must_be_at_time_0(self):
        self.data[0][0] = 1
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(self.data)

    def test_first_value_must_be_0(self):
        self.data[0][1] = 1
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(self.data)

    def test_first_width_must_be_over_4000(self):
        self.data[1][0] = 3999
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(self.data)

    def test_second_width_must_be_over_4000(self):
        self.data[2][0] = 3999
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(self.data)

    def test_there_must_be_at_least_4_data_points(self):
        data2 = self.data[0:4]
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(data2)

    def test_the_return_value(self):
        result = self.analyser.analyse(self.data)

        assert result == 3772793023