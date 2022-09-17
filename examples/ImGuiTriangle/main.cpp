/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include <SGL/SGL.h>
#include "ImGuiTriangle.h"


int main()
{
    sgl::Init();

    auto app = ImGuiTriangle();
    app.Run();

    return 0;
}
