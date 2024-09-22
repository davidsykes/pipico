#include "ir_codes_repository.h"

#define NUMBER_OF_CODES 2


char CodeNametestcode[] = "testcode";
int CodeSizetestcode = 68;
int CodeTimestestcode[] = { 0, 4509, 9024, 9600, 11268, 11821, 13511, 14062, 15754, 16283, 16905, 17429, 18026, 18553, 19147, 19674, 20270, 20795, 21390, 21917, 23609, 24162, 25854, 26406, 28098, 28649, 29220, 29772, 30342, 30892, 31466, 32016, 32588, 33138, 33710, 34260, 34830, 35383, 37074, 37627, 38196, 38747, 39318, 39870, 40440, 41017, 41562, 42116, 42684, 43237, 43807, 44360, 46051, 46630, 47173, 47749, 49416, 49994, 51661, 52235, 53904, 54457, 56148, 56699, 58392, 58944, 60636, 61187 };
char CodeValuestestcode[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameOnOff[] = "OnOff";
int CodeSizeOnOff = 68;
int CodeTimesOnOff[] = { 0, 4538, 9026, 9597, 11270, 11848, 13514, 14089, 15758, 16329, 16880, 17455, 18028, 18580, 19150, 19706, 20272, 20821, 21394, 21946, 23612, 24187, 25856, 26437, 28100, 28678, 29248, 29803, 30370, 30918, 31493, 32043, 32615, 33169, 33737, 34284, 34859, 35409, 37076, 37649, 38224, 38775, 39346, 39900, 40468, 41015, 41591, 42141, 42713, 43266, 43835, 44382, 46053, 46632, 47201, 47747, 49419, 49998, 51663, 52238, 53907, 54489, 56152, 56729, 58396, 58970, 60640, 61221 };
char CodeValuesOnOff[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };


char* codeNames[NUMBER_OF_CODES] = { CodeNametestcode, CodeNameOnOff };
int codeCounts[NUMBER_OF_CODES] = { CodeSizetestcode, CodeSizeOnOff };
int* codeTimes[NUMBER_OF_CODES]{ CodeTimestestcode, CodeTimesOnOff };
char* codeValues[NUMBER_OF_CODES]{ CodeValuestestcode, CodeValuesOnOff };


IrCodesRepository::IrCodesRepository()
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

	return 0;
}