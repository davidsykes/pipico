#include "MockCredentialsHandler.h"

void MockCredentialsHandler::HandleCredentials(std::string credentials)
{
	HandledCredentials = credentials;
}