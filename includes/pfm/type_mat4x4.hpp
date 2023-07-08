#pragma once

#include "setup.hpp"

namespace pfm {
    template<typename T>
    struct mat<4, 4, T>
    {
        typedef vec<4, T> col_type;
        typedef vec<4, T> row_type;
        typedef T value_type;
        typedef mat<4, 4, T> type;

        // Data
        col_type value[4];

        // Implicit basic constructors
        PFM_FUNC_DECL PFM_CONSTEXPR mat() PFM_DEFAULT;
        PFM_FUNC_DECL PFM_CONSTEXPR mat(mat<4, 4, T> const& m);

        // Explicit basic constructors
        PFM_FUNC_DECL PFM_CONSTEXPR PFM_EXPLICIT mat(T scalar);
		PFM_FUNC_DECL PFM_CONSTEXPR mat(
			T const& x0, T const& y0, T const& z0, T const& w0,
			T const& x1, T const& y1, T const& z1, T const& w1,
			T const& x2, T const& y2, T const& z2, T const& w2,
			T const& x3, T const& y3, T const& z3, T const& w3);
        PFM_FUNC_DECL PFM_CONSTEXPR mat(
            col_type const& v0,
            col_type const& v1,
            col_type const& v2,
            col_type const& v3);

        // Unary arithmetic operations

    };
}