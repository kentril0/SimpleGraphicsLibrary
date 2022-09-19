/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include <SGL/opengl/Shader.h>
#include <SGL/opengl/ShaderObject.h>


namespace sgl
{
    std::shared_ptr<Shader> Shader::Create()
    {
        return std::make_shared<Shader>();
    }

    std::shared_ptr<Shader> Shader::Create(
        const std::initializer_list<std::shared_ptr<ShaderObject>>& objs)
    {
        return std::make_shared<Shader>(objs);
    }

    // =========================================================================

    Shader::Shader()
    {
        SGL_FUNCTION();

        CreateProgram();
    }

    Shader::Shader(
        const std::initializer_list<std::shared_ptr<ShaderObject>>& objs)
        : Shader()
    {
        LinkStages(objs);
    }

    Shader::~Shader()
    {
        SGL_FUNCTION();

        DeleteProgram();
    }

    void Shader::AttachStage(const std::shared_ptr<ShaderObject>& obj) const
    {
        SGL_FUNCTION();

        glAttachShader( m_ID, obj->GetID() );
    }

    void Shader::LinkStages(
        const std::initializer_list<std::shared_ptr<ShaderObject>>& objs)
    const
    {
        SGL_FUNCTION();

        for (const auto& obj : objs)
            AttachStage(obj);

        LinkProgram();

        for (const auto& obj : objs)
            glDetachShader( m_ID, obj->GetID() );
    }

    void Shader::LinkAttachedStages() const
    {
        SGL_FUNCTION();

        LinkProgram();
    }

    void Shader::CreateProgram()
    {
        SGL_FUNCTION();

        m_ID = glCreateProgram();
        SGL_ASSERT(m_ID > 0);
    }

    void Shader::DeleteProgram()
    {
        SGL_FUNCTION();

        glDeleteProgram(m_ID);  // ignores if 0
        m_ID = 0;
    }

    void Shader::LinkProgram() const
    {
        SGL_FUNCTION();

        glLinkProgram(m_ID);

        const int kSuccess = CheckLinkErrors();
        SGL_ASSERT(kSuccess == GL_TRUE);
    }

    void Shader::Use() const
    {
        glUseProgram(m_ID);
    }
    void Shader::UnUse() const
    {
        glUseProgram(0);
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniform1i(kLocation, value);
    }

    void Shader::SetIntArray(const std::string& name, int* values,
                             uint32_t count) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniform1iv(kLocation, count, values);
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniform1f(kLocation, value);
    }

    void Shader::SetFloat2(const std::string& name, const glm::vec2& value) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniform2f(kLocation, value.x, value.y);
    }

    void Shader::SetFloat3(const std::string& name, const glm::vec3& value) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniform3f(kLocation, value.x, value.y, value.z);
    }

    void Shader::SetFloat4(const std::string& name, const glm::vec4& value) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniform4f(kLocation, value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniformMatrix3fv(kLocation, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        const GLint kLocation = glGetUniformLocation(m_ID, name.c_str());
        glUniformMatrix4fv(kLocation, 1, GL_FALSE, glm::value_ptr(mat));
    }

    int Shader::CheckLinkErrors() const
    {
        SGL_FUNCTION();

        int success;
        const uint32_t kLogSize = 1024;
        char log[kLogSize];

        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_ID, kLogSize, NULL, log);
            SGL_LOG_ERR("| Error::Program: Link-time error: \n{}\n{}",
                    log,
                    "---------------------------------------------------");
        }

        return success;
    }
    
} // namespace sgl
