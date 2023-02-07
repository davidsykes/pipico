import sys
import pytest
sys.path.append('../src')
from waveanalyser import WaveAnalyser
from irexception import IrException


class TestWaveAnalyser:
    def setup_method(self, test_method):
        self.data_tv = [[ 0 , 0 ],[ 4524 , 1 ],[ 4498 , 0 ],[ 544 , 1 ],[ 1697 , 0 ],[ 565 , 1 ],[ 1669 , 0 ],[ 579 , 1 ],[ 1666 , 0 ],[ 567 , 1 ],[ 585 , 0 ],[ 539 , 1 ],[ 582 , 0 ],[ 542 , 1 ],[ 582 , 0 ],[ 548 , 1 ],[ 580 , 0 ],[ 555 , 1 ],[ 543 , 0 ],[ 548 , 1 ],[ 1694 , 0 ],[ 580 , 1 ],[ 1668 , 0 ],[ 580 , 1 ],[ 1665 , 0 ],[ 575 , 1 ],[ 545 , 0 ],[ 585 , 1 ],[ 548 , 0 ],[ 547 , 1 ],[ 583 , 0 ],[ 544 , 1 ],[ 583 , 0 ],[ 542 , 1 ],[ 581 , 0 ],[ 549 , 1 ],[ 542 , 0 ],[ 586 , 1 ],[ 1636 , 0 ],[ 576 , 1 ],[ 582 , 0 ],[ 545 , 1 ],[ 573 , 0 ],[ 547 , 1 ],[ 586 , 0 ],[ 549 , 1 ],[ 584 , 0 ],[ 547 , 1 ],[ 548 , 0 ],[ 582 , 1 ],[ 546 , 0 ],[ 545 , 1 ],[ 1673 , 0 ],[ 578 , 1 ],[ 579 , 0 ],[ 542 , 1 ],[ 1692 , 0 ],[ 543 , 1 ],[ 1702 , 0 ],[ 545 , 1 ],[ 1665 , 0 ],[ 584 , 1 ],[ 1682 , 0 ],[ 589 , 1 ],[ 1663 , 0 ],[ 569 , 1 ],[ 1679 , 0 ],[ 543 , 1 ]]
        self.data_sony = [[0, 0], [2393, 1], [561, 0], [1203, 1], [590, 0], [609, 1], [584, 0], [621, 1], [542, 0], [641, 1], [585, 0], [622, 1], [544, 0], [625, 1], [585, 0], [625, 1], [583, 0], [618, 1], [546, 0], [1251, 1], [542, 0], [664, 1], [551, 0], [1213, 1], [584, 0], [1203, 1], [584, 0], [623, 1], [554, 0], [1247, 1], [596, 0], [578, 1], [593, 0], [1234, 1], [547, 0], [1240, 1], [544, 0], [1248, 1], [581, 0], [1211, 1], [584, 0], [1199, 1]]
        self.analyser = WaveAnalyser()

    def test_first_value_must_be_at_time_0(self):
        data = [[ 1 , 0 ],[ 4524 , 1 ],[ 4498 , 0 ],[ 544 , 1 ],[ 1697 , 0 ],[ 565 , 1 ],[ 1669 , 0 ]]
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(data)

    def test_first_value_must_be_0(self):
        data = [[ 0 , 1 ],[ 4524 , 1 ],[ 4498 , 0 ],[ 544 , 1 ],[ 1697 , 0 ],[ 565 , 1 ],[ 1669 , 0 ]]
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(data)

    def test_there_must_be_at_least_4_data_points(self):
        data = [[ 0 , 1 ],[ 4524 , 1 ],[ 4498 , 0 ]]
        
        with pytest.raises(IrException) as e_info:
            result = self.analyser.analyse(data)

    def test_the_tv_return_value(self):
        result = self.analyser.analyse(self.data_tv)

        assert result == 3772793023

    def test_the_sony_return_value(self):
        result = self.analyser.analyse(self.data_sony)

        assert result == 527199