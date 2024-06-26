#pragma once
#include <cstdint>

class IFlashHardware
{
public:
    virtual const uint8_t* ReadFlash() = 0;
    virtual void WriteFlash(const uint8_t*) = 0;
};

class FlashHardware : public IFlashHardware
{
    virtual const uint8_t* ReadFlash();
    virtual void WriteFlash(const uint8_t*);
};
