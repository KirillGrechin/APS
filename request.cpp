#include "request.h"

Request::Request(double startTime, int sourceNumber, int requestNumber)
{
    this->startTime = startTime;
    this->sourceNumber = sourceNumber;
    this->requestNumber = requestNumber;
}

double Request::getStartTime()
{
    return startTime;
}

int Request::getSourceNumber()
{
    return sourceNumber;
}

int Request::getRequestNumber()
{
    return requestNumber;
}
