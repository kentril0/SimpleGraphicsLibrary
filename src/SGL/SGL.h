/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_SGL_H_
#define SGL_SGL_H_

#include <memory>

#include <glad/glad.h>

#include "SGL/core/Base.h"
#include "SGL/core/Log.h"
#include "SGL/core/Assert.h"
#include "SGL/core/Utils.h"
#include "SGL/core/Window.h"
#include "SGL/core/Application.h"

#include "SGL/opengl/VertexBuffer.h"
#include "SGL/opengl/IndexBuffer.h"
#include "SGL/opengl/VertexArray.h"

#include "SGL/opengl/ShaderObject.h"
#include "SGL/opengl/Shader.h"

#include "SGL/opengl/Texture2D.h"
#include "SGL/opengl/CubeMapTexture.h"
#include "SGL/opengl/Texture2DArray.h"


namespace sgl
{
    void Init();

} // namespace sgl


#endif // SGL_SGL_H_
