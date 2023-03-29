#pragma once

typedef struct sInputPin
{
    int (*gpio_get)(struct sInputPin* self);

} sInputPin;