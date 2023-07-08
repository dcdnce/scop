#pragma once

#define PFM_FUNC_DECL
#define PFM_CONSTEXPR constexpr
#define PFM_EXPLICIT explicit
#define PFM_DEFAULT = default

namespace pfm {
    // Typedefs
    typedef int length_t;

    // Objects templates
    template<length_t L, typename T> struct vec;
    template<length_t C, length_t R, typename T> struct mat;
}