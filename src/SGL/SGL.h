#ifndef SGL_SGL_H_
#define SGL_SGL_H_

#include <memory>

#include "SGL/core/Log.h"
#include "SGL/Application/Window.h"
#include "SGL/Application/Application.h"


namespace sgl
{
    void Init(bool debugGL = false);

    std::unique_ptr<sgl::Window> CreateWindow();
    


} // namespace sgl



#endif // SGL_SGL_H_
