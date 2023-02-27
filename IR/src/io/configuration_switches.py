SWITCH_1_PIN = 5
SWITCH_2_PIN = 4
SWITCH_3_PIN = 3
SWITCH_4_PIN = 2

class ConfigurationSwitches:
    def __init__(self, system, service_access):
        self.system = system
        self.service_access = service_access
        temp_or_ir_function = system.make_input_pin(SWITCH_1_PIN, False)
        network_type_switch = system.make_input_pin(SWITCH_2_PIN, False)  #   0 = dumper, 1 = listener
        switch3 = system.make_input_pin(SWITCH_3_PIN, False)              #
        switch4 = system.make_input_pin(SWITCH_4_PIN, False)              #

        self.be_a_temperature_sensor = temp_or_ir_function.value()
        self.are_we_a_listener = network_type_switch.value()
        self.dump_raw_ir_codes = switch3.value()
        self.string_format = ','.join([str(temp_or_ir_function.value()), str(network_type_switch.value()), str(switch3.value()), str(switch4.value())])

        self.are_we_a_listener = self.check_for_option('ir_transmitter', self.are_we_a_listener)
        self.be_a_temperature_sensor = self.check_for_option('temperature', self.be_a_temperature_sensor)

    def check_for_option(self, name, original_value):
        option_name = self.system.id + '.' + name
        opt = self.service_access.get_option(option_name)
        print('"' + opt + '"')
        if len(opt) > 0:
            if opt == '1':
                return True
            return False
        return original_value