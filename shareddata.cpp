#include "shareddata.h"
#include "time.h"
#include "cstdlib"
#include "math.h"

SharedData::SharedData()
{
    //Seed rand().
    srand((unsigned)time(NULL));
}

//Generates pseudo random numbers.
//period 2^96-1
unsigned long xorshf96(void)
{
static unsigned long x = (unsigned)time(NULL), y = (unsigned)time(NULL), z = (unsigned)time(NULL);
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

void SharedData::generateValues(int numberOfValues, double xMin, double xMax, double yMin, double yMax)
{
    this->randomXValues = new double[numberOfValues];
    this->randomYValues = new double[numberOfValues];
    this->numberOfValues = numberOfValues;

    double rawRangeX = abs(xMax - xMin);
    double rawRangeY = abs(yMax - yMin);

    for(int i = 0; i < numberOfValues; i++)
    {
        randomXValues[i] = (xorshf96()/((double)0.425849 * 10000000000) * rawRangeX) + xMin;
        randomYValues[i] = (xorshf96()/((double)0.425849 * 10000000000) * rawRangeY) + yMin;
    }
}

double *SharedData::getXValues()
{
    return this->randomXValues;
}

double *SharedData::getYValues()
{
    return this->randomYValues;
}

int SharedData::getNumberOfVal()
{
    return this->numberOfValues;
}

void SharedData::setGenerate(bool generate)
{
    this->generate = generate;
}

bool SharedData::getGenerate()
{
    return this->generate;
}
