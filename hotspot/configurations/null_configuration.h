#ifndef NullConfiguration_H
#define NullConfiguration_H

#include "configuration.h"

class NullConfiguration : public Configuration
{
    public:
        NullConfiguration();
        virtual std::string process_request(const char *request, const char *params);
};


#endif
