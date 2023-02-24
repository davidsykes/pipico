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

        self.are_we_a_listener = network_type_switch.value()
        self.dump_raw_ir_codes = switch3.value()
        self.string_format = ','.join([str(network_switch.value()), str(network_type_switch.value()), str(switch3.value()), str(switch4.value())])
        print('Switches', self.string_format)
