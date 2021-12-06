#ifndef DEVICE_H
#define DEVICE_H

#include "request.h"
#include "statistic.h"
#include "step.h"

#include <memory>

class Device
{
public:
    Device(int, double);

    void addRequest(const std::shared_ptr<Request>&, Step&);
    void setAvailable(Statistic&, Step&);
    void setStartTime(double startTime);

    int getDeviceNumber();

    double getStartTime();
    double getStopTime();

    bool isAvailable(double requestTime);

private:
    int deviceNumber;
    double requestStartTime;
    double requestStopTime;
    double lambda;

    std::shared_ptr<Request> currentRequest;

    void fillStatistic(Statistic&, Step&);
};

#endif
