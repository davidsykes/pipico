from irexception import IrException



class WaveAnalyser:
	def analyse(self, data):
		self.check_there_is_enough_data(data)
		self.check_first_value_is_0_0(data)
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

	def analyse2(self, data):
		self.check_there_is_enough_data(data)
		self.check_first_value_is_0_0(data)
		skip_first_pulse = data[2:len(data)]
		minimum = self.find_minimum_width(skip_first_pulse)
		data_compared_to_minimum = self.compare_data_to_minimum(skip_first_pulse, minimum)
		print(data_compared_to_minimum)
		ones = [d[0] for d in data_compared_to_minimum if d[1] == 1]
		print('ones', ones)
		zeros = [d[0] for d in data_compared_to_minimum if d[1] == 0]
		print('zeros', zeros)
		ones_value = self.convert_to_binary(ones)
		zeros_value = self.convert_to_binary(zeros)
		print('ong', ones_value, zeros_value)

		return result

	def find_minimum_width(self, data):
		minimum = data[1][0]
		for i in range(2, len(data)):
			if data[i][0] < minimum:
				minimum = data[i][0]
		return minimum

	def compare_data_to_minimum(self, data, minimum):
		factors = [ [(int)(d[0] * 10 / minimum), d[1]] for d in data]
		comp = [ [1 if d[0] > 15 else 0, d[1]] for d in factors]
		return comp

	def convert_to_binary(self, data):
		r = 0
		for i in range(0, len(data)):
			r = r * 2 + data[i]
		return r

	def check_there_is_enough_data(self, data):
		if (len(data) < 5):
			raise IrException("Insufficient data points")

	def check_first_value_is_0_0(self, data):
		if data[0] != [0,0]:
			raise IrException("Initial data value should be 0,0")

