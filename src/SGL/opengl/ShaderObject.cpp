/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include <SGL/opengl/ShaderObject.h>


namespace sgl
{
    static GLenum ToGLStage(ShaderStage s)
    {
        switch(s)
        {
            case ShaderStage::Vertex:        return GL_VERTEX_SHADER;
            case ShaderStage::TessControl:   return GL_TESS_CONTROL_SHADER;
            case ShaderStage::TessEval:      return GL_TESS_EVALUATION_SHADER;
            case ShaderStage::Geometry:      return GL_GEOMETRY_SHADER;
            case ShaderStage::Fragment:      return GL_FRAGMENT_SHADER;
            case ShaderStage::Compute:       return GL_COMPUTE_SHADER;
        }
        SGL_ASSERT_MSG(false, "Unknown shader stage type");
        return 0;
    }

    std::shared_ptr<ShaderObject> ShaderObject::Create(const ShaderStage& stage)
    {
        return std::make_shared<ShaderObject>(stage);
    }

    std::shared_ptr<ShaderObject> ShaderObject::Create(const ShaderStage& stage,
                                                       const std::string& src)
    {
        return std::make_shared<ShaderObject>(stage, src);
    }

    // =========================================================================

    ShaderObject::ShaderObject(const ShaderStage& stage)
        : m_Stage( ::sgl::ToGLStage(stage) )
    {
        SGL_FUNCTION();

        CreateShader();
    }

    ShaderObject::ShaderObject(const ShaderStage& stage, const std::string& src)
        : ShaderObject(stage)
    {
        SGL_FUNCTION();

        CreateShader();        
        SetSource(src);
        Compile();
    }

    ShaderObject::~ShaderObject()
    {
        SGL_FUNCTION();

        DeleteShader();
    }

    void ShaderObject::SetSource(const std::string& src)
    {
        SGL_FUNCTION();

        const uint32_t kStringCount = 1;
        const char* kSource = src.c_str();
        const int32_t kSourceLength = src.length();

        glShaderSource(m_ID, 
                       kStringCount, &kSource, &kSourceLength);
    }

    void ShaderObject::CreateShader()
    {
        SGL_FUNCTION();

        m_ID = glCreateShader(m_Stage);
        SGL_ASSERT(m_ID > 0);
    }

    void ShaderObject::Compile() const
    {
        SGL_FUNCTION();

        {
            const Timer compileTime;

            glCompileShader(m_ID);

            SGL_LOG_INFO("Compilation took: {} ms", compileTime.ElapsedMillis());
        }

        const int kSuccess = CheckCompilationErrors();
        SGL_ASSERT(kSuccess == GL_TRUE);
    }

    void ShaderObject::DeleteShader()
    {
        SGL_FUNCTION();

        glDeleteShader(m_ID);   // will ignore deletion of '0'
        m_ID = 0;
    }

    int ShaderObject::CheckCompilationErrors() const
    {
        SGL_FUNCTION();

        int success;
        const uint32_t kLogSize = 1024;
        char log[kLogSize];

        glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(m_ID, kLogSize, NULL, log);
            SGL_LOG_ERR("| Error::Shader: Compile-time error: \n{}\n{}", 
                    log,
                    "---------------------------------------------------");
        }

        return success;
    }

} // namespace sgl
