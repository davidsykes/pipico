#include "record_ir_action.h"
#include <sstream>



std::string RecordIrAction::ApiAction()
{
	return irRecorder.RecordTrace();
}