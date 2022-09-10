#ifndef SGL_OPENGL_SHADER_STAGE_H_
#define SGL_OPENGL_SHADER_STAGE_H_

#include <memory>


namespace sgl
{

    enum class ShaderStage
    {
        Vertex = 0,
        TessControl,
        TessEval,
        Geometry,
        Fragment,
        Compute
    };

    /**
     * @brief Abstraction of GL "shader object"
     * Maybe shared between shader programs
     * 
     */
    class ShaderObject
    {
    public:
        static std::shared_ptr<ShaderObject> Create(const ShaderStage& stage);
        static std::shared_ptr<ShaderObject> Create(const ShaderStage& stage,
                                                    const std::string& src);

    public:
        ShaderObject(const ShaderStage& stage);
        /**
         * @brief Creates shader object of stage "stage",
         *  sets its shader source to "src", and compiles it
         */
        ShaderObject(const ShaderStage& stage, const std::string& src);

        ~ShaderObject();
        
        void SetSource(const std::string& src);
        void Compile() const;
        
        uint32_t GetID() const { return m_ID; }

    private:
        void CreateShader();

        /**
         * @brief Deleted immediately if not attached to any program, else
         *  is flagged for deletion later.
         */
        void DeleteShader();

        void CheckCompilationErrors() const;

    private:
        uint32_t m_ID{ 0 };
        uint32_t m_Stage{ 0 };
    };

} // namespace sgl


#endif // SGL_OPENGL_SHADER_STAGE_H_
