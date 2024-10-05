#include "ir_codes_repository.h"

char CodeNametestcode[] = "testcode";
int CodeSizetestcode = 8;
int CodeTimestestcode[] = { 0, 4000, 8000, 12000, 16000, 20000, 24000, 28000 };
char CodeValuestestcode[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameOnOff[] = "SamsungOnOff";
int CodeSizeOnOff = 68;
int CodeTimesOnOff[] = { 0, 4538, 9026, 9597, 11270, 11848, 13514, 14089, 15758, 16329, 16880, 17455, 18028, 18580, 19150, 19706, 20272, 20821, 21394, 21946, 23612, 24187, 25856, 26437, 28100, 28678, 29248, 29803, 30370, 30918, 31493, 32043, 32615, 33169, 33737, 34284, 34859, 35409, 37076, 37649, 38224, 38775, 39346, 39900, 40468, 41015, 41591, 42141, 42713, 43266, 43835, 44382, 46053, 46632, 47201, 47747, 49419, 49998, 51663, 52238, 53907, 54489, 56152, 56729, 58396, 58970, 60640, 61221 };
char CodeValuesOnOff[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameSonyForward[] = "SonyForward";
int CodeSizeSonyForward = 126;
int CodeTimesSonyForward[] = { 0, 2422, 2984, 3611, 4178, 4810, 5373, 6599, 7165, 7798, 8360, 9586, 10152, 10785, 11346, 11974, 12541, 13173, 13736, 14962, 15528, 16161, 16722, 17949, 18514, 19748, 20307, 21536, 22099, 23325, 23890, 24524, 25085, 26313, 26877, 27512, 28072, 28700, 29266, 29899, 30461, 31088, 44859, 47288, 47846, 48476, 49040, 49675, 50235, 51464, 52027, 52663, 53222, 54451, 55014, 55650, 56208, 56839, 57403, 58038, 58598, 59827, 60390, 61026, 61584, 62814, 63377, 64603, 65168, 66402, 66961, 68190, 68753, 69378, 69947, 71177, 71739, 72366, 72933, 73566, 74128, 74765, 75323, 75953, 89720, 92143, 92708, 93342, 93902, 94583, 95097, 96330, 96889, 97518, 98083, 99317, 99876, 100506, 101070, 101705, 102265, 102894, 103460, 104693, 105252, 105881, 106446, 107670, 108238, 109469, 110030, 111257, 111822, 113056, 113614, 114245, 114809, 116044, 116601, 117232, 117795, 118432, 118990, 119620, 120185, 120820 };
char CodeValuesSonyForward[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameSamsungVolumeDown[] = "SamsungVolumeDown";
int CodeSizeSamsungVolumeDown = 68;
int CodeTimesSamsungVolumeDown[] = { 0, 4533, 9028, 9603, 11273, 11844, 13517, 14096, 15762, 16337, 16884, 17462, 18007, 18588, 19129, 19703, 20251, 20829, 21373, 21955, 23618, 24196, 25862, 26436, 28107, 28688, 29229, 29804, 30351, 30929, 31473, 32055, 32596, 33170, 33718, 34296, 35963, 36537, 38207, 38788, 39330, 39903, 41574, 42154, 42697, 43270, 43819, 44396, 44941, 45522, 46064, 46637, 47186, 47763, 48309, 48888, 50553, 51129, 51676, 52255, 53920, 54496, 56165, 56737, 58409, 58988, 60654, 61229 };
char CodeValuesSamsungVolumeDown[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNameSamsungVolumeUp[] = "SamsungVolumeUp";
int CodeSizeSamsungVolumeUp = 68;
int CodeTimesSamsungVolumeUp[] = { 0, 4585, 9026, 9605, 11270, 11847, 13513, 14088, 15757, 16330, 16879, 17457, 18001, 18583, 19123, 19698, 20245, 20877, 21368, 21940, 23612, 24192, 25856, 26434, 28100, 28676, 29222, 29802, 30344, 30918, 31466, 32044, 32588, 33223, 33711, 34286, 35955, 36528, 38199, 38780, 40443, 41022, 41565, 42138, 42687, 43264, 43809, 44390, 44931, 45505, 46054, 46632, 47176, 47758, 48298, 48873, 49420, 50000, 51664, 52241, 53908, 54483, 56152, 56725, 58395, 58977, 60639, 61219 };
char CodeValuesSamsungVolumeUp[] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };

char CodeNamePause[] = "Pause";
int CodeSizePause = 2;
int CodeTimesPause[] = { 0, 500000 };
char CodeValuesPause[] = { 0, 0 };

IrCodesRepository::IrCodesRepository(IMessageLogger& messageLogger) : messageLogger(messageLogger)
{
	AddCode(CodeNameOnOff, CodeSizeOnOff, CodeTimesOnOff, CodeValuesOnOff);
	AddCode(CodeNameSonyForward, CodeSizeSonyForward, CodeTimesSonyForward, CodeValuesSonyForward);
	AddCode(CodeNameSamsungVolumeDown, CodeSizeSamsungVolumeDown, CodeTimesSamsungVolumeDown, CodeValuesSamsungVolumeDown);
	AddCode(CodeNameSamsungVolumeUp, CodeSizeSamsungVolumeUp, CodeTimesSamsungVolumeUp, CodeValuesSamsungVolumeUp);
	AddCode(CodeNamePause, CodeSizePause, CodeTimesPause, CodeValuesPause);
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

void IrCodesRepository::AddCode(const char* name, int dataSize, int* times, char* values)
{
	IrCode code;
	codes.push_back(std::move(code));
	IrCode& last = codes.back();
	last.Name = name;
	last.Count = dataSize;
	for (int j = 0; j < last.Count; ++j)
	{
		last.Times.push_back(times[j]);
	}
	for (int j = 0; j < last.Count; ++j)
	{
		last.Values.push_back(values[j]);
	}
}