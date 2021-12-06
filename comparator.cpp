#include "comparator.h"

bool Comparator::operator() (const std::shared_ptr<Request>& first, const std::shared_ptr<Request>& second)
{
    return first->getStartTime() < second->getStartTime();
}

bool Comparator::operator() (Source& first, Source& second)
{
    return first.getRequestTime() < second.getRequestTime();
}

bool Comparator::operator() (Device& first, Device &second)
{
    return first.getStopTime() < second.getStopTime();
}
