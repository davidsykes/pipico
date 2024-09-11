#pragma once
#include "api_action.h"
#include "../../pico_scope/pico_scope_recorder.h"

class RecordIrAction : public ApiAction
{
	IPicoScopeRecorder& irRecorder;

	virtual std::string Action() { return irRecorder.RecordTrace(); }

public:
	RecordIrAction(IPicoScopeRecorder& irRecorder) : irRecorder(irRecorder) {}
};
