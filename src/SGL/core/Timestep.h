#ifndef SGL_CORE_TIMESTEP_H_
#define SGL_CORE_TIMESTEP_H_


namespace sgl 
{
    class Timestep
    {
    public:
        Timestep(float t) : m_Step(t) {}

        /** @return Time in seconds */
        inline constexpr operator float() const { return m_Step; }

        inline constexpr float Seconds() const { return m_Step; }
        inline constexpr float Millis() const { return m_Step * 1000.0f; }

    private:
        float m_Step;
    };
    
} // namespace sgl 

#endif // SGL_CORE_TIMESTEP_H_