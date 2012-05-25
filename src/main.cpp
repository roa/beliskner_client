#include <iostream>

#include "BaseRoot.hpp"

using namespace Beliskner;

int main(int argc, char **argv)
{
    new BaseRoot();

    BaseRoot *base = BaseRoot::getSingletonPtr();

    base->runTest();

    return 0;
}
