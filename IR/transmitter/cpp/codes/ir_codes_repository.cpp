#include "ir_codes_repository.h"

#define NUMBER_OF_CODES 3


char CodeNametestcode[] = "testcode";
int CodeSizetestcode = 68;
int CodeTimestestcode[] = { 0, 4509, 9024, 9600, 11268, 11821, 13511, 14062, 15754, 16283, 16905, 17429, 18026, 18553, 19147, 19674, 20270, 20795, 21390, 21917, 23609, 24162, 25854, 26406, 28098, 28649, 29220, 29772, 30342, 30892, 31466, 32016, 32588, 33138, 33710, 34260, 34830, 35383, 37074, 37627, 38196, 38747, 39318, 39870, 40440, 41017, 41562, 42116, 42684, 43237, 43807, 44360, 46051, 46630, 47173, 47749, 49416, 49994, 51661, 52235, 53904, 54457, 56148, 56699, 58392, 58944, 60636, 61187 };
char CodeValuestestcode[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameOnOff[] = "SamsungOnOff";
int CodeSizeOnOff = 68;
int CodeTimesOnOff[] = { 0, 4538, 9026, 9597, 11270, 11848, 13514, 14089, 15758, 16329, 16880, 17455, 18028, 18580, 19150, 19706, 20272, 20821, 21394, 21946, 23612, 24187, 25856, 26437, 28100, 28678, 29248, 29803, 30370, 30918, 31493, 32043, 32615, 33169, 33737, 34284, 34859, 35409, 37076, 37649, 38224, 38775, 39346, 39900, 40468, 41015, 41591, 42141, 42713, 43266, 43835, 44382, 46053, 46632, 47201, 47747, 49419, 49998, 51663, 52238, 53907, 54489, 56152, 56729, 58396, 58970, 60640, 61221 };
char CodeValuesOnOff[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameSonyForward[] = "SonyForward";
int CodeSizeSonyForward = 126;
int CodeTimesSonyForward[] = { 0, 2422, 2984, 3611, 4178, 4810, 5373, 6599, 7165, 7798, 8360, 9586, 10152, 10785, 11346, 11974, 12541, 13173, 13736, 14962, 15528, 16161, 16722, 17949, 18514, 19748, 20307, 21536, 22099, 23325, 23890, 24524, 25085, 26313, 26877, 27512, 28072, 28700, 29266, 29899, 30461, 31088, 44859, 47288, 47846, 48476, 49040, 49675, 50235, 51464, 52027, 52663, 53222, 54451, 55014, 55650, 56208, 56839, 57403, 58038, 58598, 59827, 60390, 61026, 61584, 62814, 63377, 64603, 65168, 66402, 66961, 68190, 68753, 69378, 69947, 71177, 71739, 72366, 72933, 73566, 74128, 74765, 75323, 75953, 89720, 92143, 92708, 93342, 93902, 94583, 95097, 96330, 96889, 97518, 98083, 99317, 99876, 100506, 101070, 101705, 102265, 102894, 103460, 104693, 105252, 105881, 106446, 107670, 108238, 109469, 110030, 111257, 111822, 113056, 113614, 114245, 114809, 116044, 116601, 117232, 117795, 118432, 118990, 119620, 120185, 120820 };
char CodeValuesSonyForward[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };


char* codeNames[NUMBER_OF_CODES] = { CodeNametestcode, CodeNameOnOff, CodeNameSonyForward };
int codeCounts[NUMBER_OF_CODES] = { CodeSizetestcode, CodeSizeOnOff, CodeSizeSonyForward };
int* codeTimes[NUMBER_OF_CODES]{ CodeTimestestcode, CodeTimesOnOff, CodeTimesSonyForward };
char* codeValues[NUMBER_OF_CODES]{ CodeValuestestcode, CodeValuesOnOff, CodeValuesSonyForward };


IrCodesRepository::IrCodesRepository(IMessageLogger& messageLogger) : messageLogger(messageLogger)
{
	for (int i = 0; i < NUMBER_OF_CODES; ++i)
	{
		IrCode code;
		codes.push_back(std::move(code));
		IrCode& last = codes.back();
		last.Name = codeNames[i];
		last.Count = codeCounts[i];
		int* times = codeTimes[i];
		for (int j = 0; j < last.Count; ++j)
		{
			last.Times.push_back(times[j]);
		}
		char* values = codeValues[i];
		for (int j = 0; j < last.Count; ++j)
		{
			last.Values.push_back(values[j]);
		}
	}
}

IrCode* IrCodesRepository::GetCode(const std::string& name)
{
	for (int i = 0; i < codes.size(); ++i)
	{
		if (codes[i].Name == name)
		{
			return &codes[i];
		}
	}

	messageLogger.Log("Code '" + name + "' not found.");

	return 0;
}