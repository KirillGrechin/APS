#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "request.h"
#include "source.h"
#include "device.h"
#include "step.h"

class Comparator
{
public:
    bool operator() (const std::shared_ptr<Request>&, const std::shared_ptr<Request>&);
    bool operator() (Source&, Source&);
    bool operator() (Device&, Device&);
};

#endif
