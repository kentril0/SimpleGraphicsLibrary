/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "HelloTriangle.h"


int main()
{
    sgl::Init();

    auto app = HelloTriangle();
    app.Run();

    return 0;
}
