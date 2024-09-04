#pragma once
#include "iapi_action.h"
#include "../../pico_scope/pico_scope_recorder.h"

class RecordIrAction : public IApiAction
{
	IPicoScopeRecorder& irRecorder;

	virtual std::string ApiAction();

public:
	RecordIrAction(IPicoScopeRecorder& irRecorder) : irRecorder(irRecorder) {}
};
