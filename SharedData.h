#ifndef SHAREDDATA_H
#define SHAREDDATA_H


class SharedData
{
private:
    double *randomXValues;
    double *randomYValues;
    int numberOfValues;
    bool generate = false;
public:
    SharedData();
    void generateValues(int numberOfValues, double xMin, double xMax, double yMin, double yMax);
    double *getXValues();
    double *getYValues();
    int getNumberOfVal();
    void setGenerate(bool generate);
    bool getGenerate();
};

#endif // SHAREDDATA_H
