import pytest
import sys
sys.path.append('../src')
sys.path.append('../logic')
sys.path.append('../Mock')
from waveforms_manager import WaveformsManager
from ir_exception import IrException

class MockNetwork:
    def __init__(self, test_codes, test_sequences):
        self.test_codes = test_codes
        self.test_sequences = test_sequences
        self.get_urls = []
    def network_api_get(self, url):
        self.get_urls.append(url)
        if url == 'codes':
            return self.test_codes
        elif url == 'sequences':
            return self.test_sequences
        else:
            assert False, ''.join(['Url ', url, ' not recognised'])

class TestWaveformsManager:
    def setup_method(self, test_method):
        self.mock_network = MockNetwork(self.get_test_codes_data(), self.get_test_sequences_data())
        self.manager = WaveformsManager(self.mock_network)

    def test_on_initialising_the_sequences_are_retrieved(self):
        assert(self.mock_network.get_urls[0] == "sequences")

    def test_on_initialising_the_codes_are_retrieved(self):
        assert(self.mock_network.get_urls[1] == "codes")

    def test_the_sequence_names_can_be_retreieved(self):
        names = self.manager.get_sequence_names()
        assert(len(names) == 2)
        assert(names[0] == 'Sequence 1')
        assert(names[1] == 'Sequence 2')

    def test_a_sequence_of_codes_can_be_retrieved(self):
        sequence = self.manager.get_sequence("Sequence 1")

        assert(sequence == ['Code 1', 'Code 2'])

    def test_a_missing_sequence_throws_an_exception(self):
        with pytest.raises(IrException):
            self.manager.get_sequence("Sequence 9")

    def test_a_code_can_be_retrieved(self):
        code = self.manager.get_code('527199')

        assert(len(code.points) == 42)

    def test_a_missing_code_throws_an_exception(self):
        with pytest.raises(IrException):
            self.manager.get_code("Code 9")



    def get_test_sequences_data(self):
        return '{"sequences":[{"name":"Sequence 1","codes":["Code 1","Code 2"]},{"name":"Sequence 2","codes":["Code 2","Code 1"]}]}'

    def get_test_codes_data(self):
        return '[{"code":527199,"waveform":[{"t":0,"v":0},{"t":2382,"v":1},{"t":2981,"v":0},{"t":4181,"v":1},{"t":4759,"v":0},{"t":5372,"v":1},{"t":5954,"v":0},{"t":6581,"v":1},{"t":7162,"v":0},{"t":7775,"v":1},{"t":8318,"v":0},{"t":8982,"v":1},{"t":9571,"v":0},{"t":10160,"v":1},{"t":10735,"v":0},{"t":11357,"v":1},{"t":11940,"v":0},{"t":12559,"v":1},{"t":13151,"v":0},{"t":14355,"v":1},{"t":14937,"v":0},{"t":15523,"v":1},{"t":16108,"v":0},{"t":17314,"v":1},{"t":17899,"v":0},{"t":19138,"v":1},{"t":19690,"v":0},{"t":20318,"v":1},{"t":20905,"v":0},{"t":22114,"v":1},{"t":22697,"v":0},{"t":23320,"v":1},{"t":23872,"v":0},{"t":25105,"v":1},{"t":25689,"v":0},{"t":26894,"v":1},{"t":27489,"v":0},{"t":28695,"v":1},{"t":29277,"v":0},{"t":30482,"v":1},{"t":31066,"v":0},{"t":32273,"v":1}]},{"code":2911,"waveform":[{"t":0,"v":0},{"t":2416,"v":1},{"t":2973,"v":0},{"t":3599,"v":1},{"t":4145,"v":0},{"t":4790,"v":1},{"t":5335,"v":0},{"t":5991,"v":1},{"t":6533,"v":0},{"t":7175,"v":1},{"t":7722,"v":0},{"t":8385,"v":1},{"t":8965,"v":0},{"t":9543,"v":1},{"t":10127,"v":0},{"t":10748,"v":1},{"t":11337,"v":0},{"t":11951,"v":1},{"t":12499,"v":0},{"t":13735,"v":1},{"t":14321,"v":0},{"t":14941,"v":1},{"t":15519,"v":0},{"t":16728,"v":1},{"t":17313,"v":0},{"t":18521,"v":1},{"t":19103,"v":0},{"t":19726,"v":1},{"t":20271,"v":0},{"t":21511,"v":1},{"t":22093,"v":0},{"t":22714,"v":1},{"t":23255,"v":0},{"t":24482,"v":1},{"t":25070,"v":0},{"t":26280,"v":1},{"t":26859,"v":0},{"t":28099,"v":1},{"t":28640,"v":0},{"t":29871,"v":1},{"t":30456,"v":0},{"t":31660,"v":1}]}]'