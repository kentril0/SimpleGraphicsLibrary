#ifndef SGL_SGL_H_
#define SGL_SGL_H_

#include <memory>

#define SGL_DEBUG
#define SGL_ENABLE_ASSERTS

#include <glad/glad.h>

#include "SGL/core/Base.h"
#include "SGL/core/Log.h"
#include "SGL/core/Window.h"
#include "SGL/core/Application.h"


namespace sgl
{
    void Init();


} // namespace sgl



#endif // SGL_SGL_H_
