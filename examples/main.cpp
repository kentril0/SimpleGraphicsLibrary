

#include <SGL/SGL.h>
#include "HelloTriangle/HelloTriangle.h"


int main()
{
    sgl::Init();

    auto app = HelloTriangle();
    app.Run();

    return 0;
}