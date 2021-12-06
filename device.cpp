#include "device.h"

#include <QtGlobal>
#include <cmath>

Device::Device(int deviceNumber, double lambda)
{
    this->deviceNumber = deviceNumber;
    this->lambda = lambda;
    requestStartTime = 0.0;
    requestStopTime = 0.0;
    currentRequest = nullptr;
}

void Device::addRequest(const std::shared_ptr<Request>& request, Step& step)
{
    currentRequest = request;

    if ((requestStartTime == 0.0) || (requestStartTime < request->getStartTime()))
    {
        requestStartTime = request->getStartTime();
    }
    requestStopTime = requestStartTime + (-1 / lambda * std::log((double)qrand() / (double)RAND_MAX));

    step.time = requestStartTime;
    step.action = "Request " + std::to_string(currentRequest->getSourceNumber() + 1) + "." +
            std::to_string(currentRequest->getRequestNumber())+ " is on device " +
            std::to_string(deviceNumber + 1);
    step.deviceStateVector[deviceNumber] = request;
}

void Device::setAvailable(Statistic& statistic, Step& step)
{
    if (currentRequest == nullptr)
    {
        return;
    }
    fillStatistic(statistic, step);
    currentRequest = nullptr;
    requestStartTime = requestStopTime;
}

void Device::setStartTime(double startTime)
{
    requestStartTime = startTime;
}

int Device::getDeviceNumber()
{
    return deviceNumber;
}

double Device::getStartTime()
{
    return requestStartTime;
}

double Device::getStopTime()
{
    return requestStopTime;
}

bool Device::isAvailable(double requestTime)
{
    if (currentRequest == nullptr || requestStopTime < requestTime)
    {
        return true;
    }
    return false;
}

void Device::fillStatistic(Statistic& statistic, Step& step)
{
    step.time = requestStopTime;
    step.action = "Request " + std::to_string(currentRequest->getSourceNumber() + 1) + "." +
            std::to_string(currentRequest->getRequestNumber()) + " processed. Device " +
            std::to_string(deviceNumber + 1) + " is free";
    step.deviceStateVector[deviceNumber] = nullptr;
    step.processed++;

    statistic.addStep(step);
    statistic.incrementProcessed(currentRequest->getSourceNumber());
    statistic.addWaitingTime(currentRequest->getSourceNumber(), requestStartTime - currentRequest->getStartTime());
    statistic.addServicingTime(currentRequest->getSourceNumber(), requestStopTime - requestStartTime);
    statistic.addSimulationTime(currentRequest->getSourceNumber(), requestStopTime - currentRequest->getStartTime());
    statistic.addDeviceWorkingTime(deviceNumber, requestStopTime - requestStartTime);
    statistic.setTotalSimulationTime(requestStopTime);
}
