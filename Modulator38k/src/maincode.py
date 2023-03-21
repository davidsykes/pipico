IR_RECEIVE_PIN = 15
IR_TRANSMIT_PIN = 14

class MainCode:
    def maincode(self, system):
        self.system = system
        self.pin_in = self.system.make_input_pin(IR_RECEIVE_PIN)
        self.pin_out = self.system.make_output_pin(IR_TRANSMIT_PIN)
        self.led = self.system.make_output_pin("LED")
        self.timer = self.system.make_timer()
        self.system.init_timer(self.timer, 5, self.blink)
        
    def blink(self, timer):
        self.pin_out.toggle()
        self.led.toggle()

