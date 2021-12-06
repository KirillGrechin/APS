#ifndef SOURCE_H
#define SOURCE_H

#include "request.h"

#include <memory>

class Source
{
public:
    Source(int, double, double);

    double getRequestTime();

    std::shared_ptr<Request> generateRequest();

private:
    int sourceNumber;
    int generatedRequests;
    double requestTime;
    double alpha;
    double beta;
};

#endif
