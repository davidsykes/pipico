#pragma once
#include "iwidget.h"
#include "../../tools/message_logger.h"

class LogDisplayWidget : public IWidget
{
	IMessageLogger& messageLogger;

	virtual std::string RenderWidget();

public:
	LogDisplayWidget(IMessageLogger& messageLogger) : messageLogger(messageLogger) {}
};
