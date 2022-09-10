/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#include "SGL/pch.h"
#include "SGL/SGL.h"


namespace sgl
{
    // -------------------------------------------------------------------------
    // Function prototypes

    void InitLogging();

    // -------------------------------------------------------------------------
    
    void Init()
    {
        InitLogging();
    }

    void InitLogging()
    {
        sgl::Log::Init();
        SGL_FUNCTION();
    }


} // namespace sgl