import sys
sys.path.append('../src/io')
from pinwatcher import PinWatcher

class MockPin:
    _index = 0
    def __init__(self, system, timings):
        self._system = system
        self._timings = timings
    def value(self):
        if (self._index >= len(self._timings) - 1):
            return self._timings[self._index][1]
        atime = self._system.ticks_us()
        if (atime >= self._timings[self._index+1][0]):
            self._index = self._index + 1
        return self._timings[self._index][1]

class MockSystem:
    _time = -1

    def ticks_us(self):
        self._time = self._time + 1
        return self._time

def test_wait_for_change_with_timeout_that_doesnt_time_out():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[10,1]])

    watcher = PinWatcher(system, pin_to_watch)

    val = watcher.wait_for_change(100)

    assert(val == 1)

def test_wait_for_change_with_timeout_that_does_time_out():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[1000,1]])

    watcher = PinWatcher(system, pin_to_watch)

    val = watcher.wait_for_change(100)

    assert(val == None)

def test_wait_for_change_with_no_timeout():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[10,1]])

    watcher = PinWatcher(system, pin_to_watch)

    val = watcher.wait_for_change()

    assert(val == 1)

def test_get_time_of_change():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[10,1]])

    watcher = PinWatcher(system, pin_to_watch)

    t = watcher.get_time_of_change()

    assert(t == 10)

def test_get_time_of_change_with_timeout():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[10,1]])

    watcher = PinWatcher(system, pin_to_watch)

    t = watcher.get_time_of_change(5)

    assert(t == None)

def test_value():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[4,1]])

    watcher = PinWatcher(system, pin_to_watch)

    assert(pin_to_watch.value() == 0)
    assert(pin_to_watch.value() == 0)
    assert(pin_to_watch.value() == 1)
    assert(pin_to_watch.value() == 1)

def test_get_time_of_change_gets_time_since_last_change_not_since_the_routine_was_called():
    system = MockSystem()
    pin_to_watch = MockPin(system, [[0,0],[10,1],[20,0]])

    watcher = PinWatcher(system, pin_to_watch)

    assert(watcher.get_time_of_change() == 10)
    system.ticks_us()
    system.ticks_us()
    system.ticks_us()
    assert(watcher.get_time_of_change() == 10)

