#pragma once
#include "pico_scope.h"


class IPicoScopeCaptureAndPost
{
public:
	virtual void CaptureAndPost() = 0;
};

class PicoScopeCaptureAndPost : public IPicoScopeCaptureAndPost
{
	IHardwareInterface& hw_if;
	IPicoScope& pico_scope;

	virtual void CaptureAndPost();
public:
	PicoScopeCaptureAndPost(
		IHardwareInterface& hw_if,
		IPicoScope& pico_scope
	)
		: hw_if(hw_if),
		pico_scope(pico_scope)
	{}
};

//class IPicoScopeRecordAndPost
//{
//public:
//    virtual std::string RecordAndPostTrace() = 0;
//};
//
//class PicoScopeRecordAndPost : public IPicoScopeRecordAndPost
//{
//    IHardwareInterface& hw_if;
//    PicoScopeConfiguration& config;
//    IRestHandler& restHandler;
//
//    virtual std::string RecordAndPostTrace();
//
//public:
//    PicoScopeRecordAndPost(IHardwareInterface& hw_if,
//                            PicoScopeConfiguration& config,
//                            IRestHandler& restHandler)
//                            : hw_if(hw_if), config(config), restHandler(restHandler) {}
//};
//
//
//void RunScope(IHardwareInterface& hw_if);
//void run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config, IRestHandler& restHandler);
