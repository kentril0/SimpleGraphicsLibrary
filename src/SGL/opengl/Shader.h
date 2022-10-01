/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_OPENGL_SHADER_H_
#define SGL_OPENGL_SHADER_H_

#include <cstdint>
#include <string>
#include <memory>

#include <glm/glm.hpp>


namespace sgl
{
/*
Workflow to use a shader:
    1. load shader source code into "shader object"
    2. compile shader object
    - corresponds to stage in the rendering pipeline
    (1.b load pre-compiled shader binary code)
    3. 1+ shader objects are attached to a "program object"
    4. llinked -> executable code
    (3.b load pre-compiled program binary code into program obj.)
    - unified program object
    - separable program object

TODO shader library
    
*/
    class ShaderObject;

    /**
     * @brief Abstraction of GL "program object"
     *  Links shader objects
     */
    class Shader
    {
    public:
        static std::shared_ptr<Shader> Create();

        static std::shared_ptr<Shader> Create(
            const std::initializer_list<std::shared_ptr<ShaderObject>>& objs);

    public:
        Shader();

        /**
         * @brief Creates the shader program, and links the "objs"
         */
        Shader(const std::initializer_list<std::shared_ptr<ShaderObject>>& objs);

        ~Shader();

        /**
         * @brief Attach shader object to the program; may be attached
         *  before loading source code into the object, or before compilation
         *  or specialization. Multiple shader objects of the same type may be
         *  attached to the program. 
         */
        void AttachStage(const std::shared_ptr<ShaderObject>& obj) const;

        /**
         * @brief After linking, detaches the shader objects "objs"
         */
        void LinkStages(
            const std::initializer_list<std::shared_ptr<ShaderObject>>& objs)
        const;

        /** 
         * @brief Links previously attached shader objects using "AttachStage"
         *  After linking keeps the shader objects attached
         */
        void LinkAttachedStages() const;

        void Use() const;
        void UnUse() const;
        
        void SetInt(const std::string& name, int value) const;
        void SetIntArray(const std::string& name, const int* values,
                         uint32_t count) const;

        void SetFloat(const std::string& name, float value) const;
        void SetFloatArray(const std::string& name, const float* values,
                           uint32_t count) const;

        void SetFloat2(const std::string& name, const glm::vec2& value) const;

        void SetFloat3(const std::string& name, const glm::vec3& value) const;
        void SetFloat3Array(const std::string& name, const glm::vec3* values,
                            uint32_t count) const;

        void SetFloat4(const std::string& name, const glm::vec4& value) const;
        void SetFloat4Array(const std::string& name, const glm::vec4* values,
                            uint32_t count) const;

        void SetMat3(const std::string& name, const glm::mat3& mat) const;
        void SetMat4(const std::string& name, const glm::mat4& mat) const;

    private:
        void CreateProgram();

        /**
         * @brief Flagged for deletion if in use. When deleted, all attached
         *  shader objects are detached 
         */
        void DeleteProgram();

        void LinkProgram() const;

        int CheckLinkErrors() const;

    private:
        uint32_t m_ID{ 0 };
    };
    
} // namespace sgl


#endif // SGL_OPENGL_SHADER_H_
