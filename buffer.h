#ifndef BUFFER_H
#define BUFFER_H

#include "step.h"
#include "request.h"
#include "statistic.h"

#include <memory>
#include <vector>

class Buffer
{
public:
    Buffer(int);

    void addRequest(const std::shared_ptr<Request>&, Step&);
    void removeRequest(Statistic&, Step&);

    std::shared_ptr<Request> getRequest(Statistic&, int, Step&);

    bool isEmpty();
    bool isFull();

private:
    int size;
    int freeSpace;

    std::vector<std::shared_ptr<Request>> requestVector;
    std::vector<int> packageVector;

    int getRemovingPriority();
    int getServicingPriority(int);
    void sortRequestVector(int, std::vector<std::shared_ptr<Request>>&);
};

#endif
