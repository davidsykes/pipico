#ifndef NullConfiguration_H
#define NullConfiguration_H

#include "../logic/requests/configuration.h"

class NullConfiguration : public Configuration
{
    public:
        NullConfiguration();
        virtual std::string process_request(const char *request, const char *params);
};


#endif
