#include "source.h"

#include <QtGlobal>

Source::Source (int sourceNumber, double alpha, double beta)
{
    this->sourceNumber = sourceNumber;
    this->alpha = alpha;
    this->beta = beta;
    generatedRequests = 0;
    requestTime = 0.0;
}

double Source::getRequestTime()
{
    return requestTime;
}

std::shared_ptr<Request> Source::generateRequest()
{
    requestTime += (((double)qrand() / (double)RAND_MAX) * (beta - alpha) + alpha);
    return std::shared_ptr<Request>(new Request(requestTime, sourceNumber, ++generatedRequests));
}
