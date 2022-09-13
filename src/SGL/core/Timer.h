/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_TIMER_H_
#define SGL_CORE_TIMER_H_

#include <chrono>

#define MILLIS_TO_SECONDS 0.001f


namespace sgl 
{
    class Timer
    {
    public:
        Timer()
        {
            Start();
        }

        inline void Start()
        {
            m_Start = std::chrono::high_resolution_clock::now();
        }

        /** @return Time elapsed in seconds */
        inline operator float() const { return Elapsed(); }

        inline float ElapsedMillis() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - m_Start).count();
        }

        inline float ElapsedMicro() const
        {
            return std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::high_resolution_clock::now() - m_Start).count();
        }

        // @return Time elapsed in seconds
        inline float Elapsed() const
        {
            return ElapsedMillis() * MILLIS_TO_SECONDS; 
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };

} // namespace sgl 

#endif // SGL_CORE_TIMER_H_
