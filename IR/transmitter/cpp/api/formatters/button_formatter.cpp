#include "button_formatter.h"

std::string button_head = "<a href=\"";
std::string button_mid = "\"><button>";
std::string button_foot = "</button></a>";

std::string ButtonFormatter::FormatButton(const std::string& text, const std::string& link)
{
	return button_head + link + button_mid + text + button_foot;
}