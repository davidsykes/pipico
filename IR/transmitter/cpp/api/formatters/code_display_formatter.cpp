#include <sstream>
#include "code_display_formatter.h"

std::string CodeDisplayFormatter::FormatCode(const IrCode& code)
{
    std::ostringstream s;

    s << "<a href=\"http://";
    s << ip_address;
    s << "/sendcode/";
    s << code.Name;
    s << "\">Code " << code.Name << "</a>";
    return s.str();
}