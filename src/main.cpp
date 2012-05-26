#include <iostream>

#include "BaseRoot.hpp"
#include "DemoScene.hpp"

using namespace Beliskner;

int main(int argc, char **argv)
{
    new BaseRoot();

    DemoScene app;

    app.run();

    return 0;
}
