#include <iostream>

#include "BaseRoot.hpp"

using namespace Beliskner;

int main(int argc, char **argv)
{
    new BaseRoot();

    BaseRoot *base = BaseRoot::getSingletonPtr();
    base->initOgre();
    base->run();

    return 0;
}
