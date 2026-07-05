#pragma once

#include "../Vector.h"
#include "../Matrix.h"

#include "../Support/Trig.h"

#include <concepts>


namespace lab {

    template<std::floating_point F, std::uint8_t Dimensions> 
	requires((Dimensions > 1) && (Dimensions <= 4))
    struct Transform{};
}

