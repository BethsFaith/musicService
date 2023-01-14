#ifndef BASESCREENSFACTORY_H
#define BASESCREENSFACTORY_H

#include "basefragment.h"
#include "QString"

class BaseScreensFactory
{
public:
    BaseScreensFactory() = default;

    virtual ~BaseScreensFactory() = default;

    virtual BaseFragment *create(QString tag) = 0;

    virtual QString createStart() = 0;
};

#endif // BASESCREENSFACTORY_H
