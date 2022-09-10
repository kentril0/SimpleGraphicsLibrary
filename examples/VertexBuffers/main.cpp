

#include <SGL/SGL.h>
#include "VertexBuffers.h"


int main()
{
    sgl::Init();

    auto app = VertexBuffers();
    app.Run();

    return 0;
}