from irexception import IrException



class WaveAnalyser:
	def analyse(self, data):
		self.check_there_is_enough_data(data)
		self.check_first_value_is_0_0(data)
		self.check_width_sufficient(data[1])
		self.check_width_sufficient(data[2])
		i = 3
		result = 0
		while (i < len(data)):
			datum = data[i]
			value = datum[1]
			width = datum[0]
			if (value == 0):
				bit = 1 if (width >= 1000) else 0
				result = result * 2 + bit

			i = i + 1
		return result

	def check_there_is_enough_data(self, data):
		if (len(data) < 5):
			raise IrException("Insufficient data points")

	def check_first_value_is_0_0(self, data):
		if data[0] != [0,0]:
			raise IrException("Initial data value should be 0,0")

	def check_width_sufficient(self, data):
		if data[0] < 4000:
			raise IrException("Initial frame is missing")
