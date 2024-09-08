#include "ir_codes_repository.h"

#define NUMBER_OF_CODES 1


char CodeNametestcode[] = "testcode";
int CodeSizetestcode = 68;
int CodeTimestestcode[] = { 0, 4509, 9024, 9600, 11268, 11821, 13511, 14062, 15754, 16283, 16905, 17429, 18026, 18553, 19147, 19674, 20270, 20795, 21390, 21917, 23609, 24162, 25854, 26406, 28098, 28649, 29220, 29772, 30342, 30892, 31466, 32016, 32588, 33138, 33710, 34260, 34830, 35383, 37074, 37627, 38196, 38747, 39318, 39870, 40440, 41017, 41562, 42116, 42684, 43237, 43807, 44360, 46051, 46630, 47173, 47749, 49416, 49994, 51661, 52235, 53904, 54457, 56148, 56699, 58392, 58944, 60636, 61187 };
char CodeValuestestcode[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };



char* codeNames[NUMBER_OF_CODES] = { CodeNametestcode };
int codeCounts[NUMBER_OF_CODES] = { CodeSizetestcode };
int* codeTimes[NUMBER_OF_CODES]{ CodeTimestestcode };
char* codeValues[NUMBER_OF_CODES]{ CodeValuestestcode };


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

IrCode IrCodesRepository::First()
{
	return codes[0];
}