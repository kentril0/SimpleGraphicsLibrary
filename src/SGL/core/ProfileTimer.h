/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_PROFILE_TIMER_H_
#define SGL_CORE_PROFILE_TIMER_H_

#include <chrono>

#define MILLIS_TO_SECONDS 0.001f


namespace sgl 
{
    struct ProfileRecord
    {
        const char* name;
        float duration;
    };

    template<typename Fn>
    class ProfileTimer 
    {
    public:
        /**
         * @param name Name of the timed event
         * @param func Called when stopped with parameter of type ProfileRecord
         */
        ProfileTimer(const char* name, Fn&& func)
            : m_Name(name), m_Stopped(false), m_Func(func)
        {
            Start();
        }

        ~ProfileTimer()
        {
            if (!m_Stopped)
                Stop();
        }
    private:
        inline void Start()
        {
            m_Start = std::chrono::high_resolution_clock::now();
        }

        void Stop()
        {
            m_Stopped = true;
            m_Func({ m_Name, Elapsed() });
        }

        inline float ElapsedMillis() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - m_Start).count();
        }

        inline float Elapsed() const
        {
            return ElapsedMillis() * MILLIS_TO_SECONDS; 
        }

    private:
        const char* m_Name;
        bool m_Stopped;
        Fn m_Func;

        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };

} // namespace sgl 

#endif // SGL_CORE_PROFILE_TIMER_H_
