SWITCH_1_PIN = 5
SWITCH_2_PIN = 4
SWITCH_3_PIN = 3
SWITCH_4_PIN = 2

class ConfigurationSwitches:
    def __init__(self, system):
        network_switch = system.make_input_pin(SWITCH_1_PIN, False)       #   Enable network
        network_type_switch = system.make_input_pin(SWITCH_2_PIN, False)  #   0 = dumper, 1 = listener
        switch3 = system.make_input_pin(SWITCH_3_PIN, False)              #
        switch4 = system.make_input_pin(SWITCH_4_PIN, False)              #
        print('Switches', network_switch.value(), network_type_switch.value(), switch3.value(), switch4.value())

        self.is_network_enabled = network_switch.value()
        self.are_we_a_listener = network_type_switch.value()
