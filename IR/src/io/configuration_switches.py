SWITCH_1_PIN = 5
SWITCH_2_PIN = 4
SWITCH_3_PIN = 3
SWITCH_4_PIN = 2

class ConfigurationSwitches:
    def __init__(self, system, service_access):
        self.system = system
        self.service_access = service_access
        switch1 = system.make_input_pin(SWITCH_1_PIN, False)              #
        ir_type_switch = system.make_input_pin(SWITCH_2_PIN, False)  # 0 = ir recorder, 1 = if transmitter
        switch3 = system.make_input_pin(SWITCH_3_PIN, False)              #
        switch4 = system.make_input_pin(SWITCH_4_PIN, False)              #

        self.are_we_ir_transmitter = ir_type_switch.value()
        self.dump_raw_ir_codes = switch3.value()
        self.string_format = ','.join([str(switch1.value()), str(ir_type_switch.value()), str(switch3.value()), str(switch4.value())])

        function = self.get_option('function')
        if function == 'irtransmitter':
            self.are_we_ir_transmitter = True
        elif function == 'irreceiver':
            self.are_we_ir_transmitter = False

    def get_option(self, name):
        option_name = self.system.id + '.' + name
        opt = self.service_access.get_option(option_name)
        self.service_access.log(''.join(['Option ', option_name, '="', opt, '"']))
        return opt

    def check_for_option(self, name, original_value):
        opt = self.get_option(name)
        if len(opt) > 0:
            if opt == '1':
                return True
            return False
        return original_value