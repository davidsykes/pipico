#pragma once

typedef struct sPulser
{
    void (*pulse)(struct sPulser* self);

    int pulse_count;

} sPulser;