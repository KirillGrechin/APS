#include "buffer.h"

#include <float.h>

Buffer::Buffer(int size)
{
    this->size = size;
    freeSpace = size;
    requestVector = std::vector<std::shared_ptr<Request>>(size);
    requestVector.reserve(size);
}

void Buffer::addRequest(const std::shared_ptr<Request>& request, Step& step)
{
    for (int i = 0; i < size; i++)
    {
        if (requestVector[i] == nullptr)
        {
            requestVector[i] = request;
            step.time = request ->getStartTime();
            step.action = "Request " + std::to_string(request -> getSourceNumber() + 1) +
                    "." + std::to_string(request -> getRequestNumber()) + " added to buffer";
            step.bufferStateVector[i] = request;
            step.sourceStateVector[request->getSourceNumber()] = nullptr;
            freeSpace--;
            break;
        }
    }
}

void Buffer::removeRequest(Statistic& statistic, Step& step)
{
    int index = getRemovingPriority();

    step.action = "Request " + std::to_string(requestVector[index]->getSourceNumber() + 1) + "." +
            std::to_string(requestVector[index]->getRequestNumber()) +" rejected from buffer";
    step.bufferStateVector[index] = nullptr;
    step.rejected++;

    statistic.incrementRejected(requestVector[index]->getSourceNumber());
    statistic.addStep(step);

    requestVector[index] = nullptr;
    freeSpace++;

    sortRequestVector(index, step.bufferStateVector);
    sortRequestVector(index, requestVector);
}

std::shared_ptr<Request> Buffer::getRequest(Statistic& statistic, int sourceAmount, Step& step)
{
    if (packageVector.size() == 0)
    {
        int priority = getServicingPriority(sourceAmount);
        int index = 0;

        for (int i = 0; i < size; i++)
        {
            if (requestVector[i] != nullptr)
            {
                if (requestVector[i]->getSourceNumber() == priority)
                {
                    packageVector.push_back(i);
                    step.packageStateVector[index++] = requestVector[i];
                }
            }
        }
    }
    statistic.addStep(step);
    step.bufferStateVector[packageVector[0]] = nullptr;

    std::shared_ptr<Request> temp = requestVector[packageVector[0]];
    requestVector[packageVector[0]] = nullptr;
    freeSpace++;

    sortRequestVector(packageVector[0], step.bufferStateVector);
    sortRequestVector(packageVector[0], requestVector);

    packageVector.erase(packageVector.begin());
    sortRequestVector(0, step.packageStateVector);

    for (int i = 0; i < (int)packageVector.size(); i++)
    {
        packageVector[i]--;
    }
    return temp;
}

bool Buffer::isEmpty()
{
    return freeSpace == size;
}

bool Buffer::isFull()
{
    return freeSpace == 0;
}

int Buffer::getRemovingPriority()
{
    int max = 0, index = 0;

    for (int i = 0; i < (int) size; i++)
    {
        if (requestVector[i] != nullptr)
        {
            if (max < requestVector[i]->getSourceNumber())
            {
                max = requestVector[i]->getSourceNumber();
            }
        }
    }
    double min = DBL_MAX;

    for (int i = 0; i < size; i++)
    {
        if (requestVector[i] != nullptr)
        {
           if (requestVector[i]->getSourceNumber() == max)
           {
               if (requestVector[i]->getStartTime() < min)
               {
                   min = requestVector[i]->getStartTime();
                   index = i;
               }
           }
        }
    }
    return index;
}

int Buffer::getServicingPriority(int sourceAmount)
{
    std::vector<std::vector<int>> vector(sourceAmount);

    for (int i = 0; i < (int) vector.size(); i++)
    {
        vector[i].push_back(0);
    }
    for (int i = 0; i < size; i++)
    {
        if (requestVector[i] != nullptr)
        {
            vector[requestVector[i]->getSourceNumber()][0]++;
        }
    }
    int max = 0, index = 0;

    for (int i = 0; i < (int)vector.size(); i++)
    {
        if (vector[i][0] > max)
        {
            max = vector[i][0];
            index = i;
        }
    }
    if (max == 1)
    {
        int min = INT_MIN;

        for (int i = 0; i < (int) size; i++)
        {
            if (requestVector[i] != nullptr)
            {
                if (min > requestVector[i]->getSourceNumber())
                {
                    min = requestVector[i]->getSourceNumber();
                    index = i;
                }
            }
        }
    }
    return index;
}

void Buffer::sortRequestVector(int index, std::vector<std::shared_ptr<Request>>& vector)
{
    for (int i = index; i < size; i++)
    {
        if (i != size - 1)
        {
            vector[i] = vector[i + 1];
        }
        else
        {
            vector[i] = nullptr;
        }
    }
}
