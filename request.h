#ifndef REQUEST_H
#define REQUEST_H

class Request
{
public:
    Request(double, int, int);

    double getStartTime();

    int getSourceNumber();
    int getRequestNumber();

private:
    double startTime;
    int requestNumber;
    int sourceNumber;
};

#endif
