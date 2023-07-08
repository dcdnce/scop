#pragma once

#include "setup.hpp"

namespace pfm {
    template<typename T>
    struct vec<4, T>
    {
        // Typedefs
        typedef T value_type
        typedef vec<4, T> type;

        // Data
        union { T x, r };
        union { T y, g };
        union { T z, b };
        union { T w, a };


        // Implicit basic constructors
        PFM_FUNC_DECL PFM_CONSTEXPR vec() PFM_DEFAULT;
        PFM_FUNC_DECL PFM_CONSTEXPR vec(vec const& v) PFM_DEFAULT;
        PFM_FUNC_DECL PFM_CONSTEXPR vec(vec<4, T> const& v);

        // Explicit basic constructors
        PFM_FUNC_DECL PFM_CONSTEXPR PFM_EXPLICIT vec(T scalar);
        PFM_FUNC_DECL PFM_CONSTEXPR vec(T x, T y, T z, T w);

        // Unary arithmetic operators
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator=(vec<4, T> const& v) PFM_DEFAULT;
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator=(vec<4, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator+=(vec<4, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator+=(U scalar);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator-=(vec<4, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator-=(U scalar);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator*=(vec<4, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator*=(U scalar);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator/=(vec<4, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator/=(U scalar);


    };// struct vec<4, T>

    // Binary arithmetic operators
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator+(vec<4, T> const& v1, vec<4, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator+(T scalar, vec<4, T> const& v);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator-(vec<4, T> const& v1, vec<4, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator-(T scalar, vec<4, T> const& v);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator*(vec<4, T> const& v1, vec<4, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator*(T scalar, vec<4, T> const& v);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator/(vec<4, T> const& v1, vec<4, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<4, T>& operator/(T scalar, vec<4, T> const& v);


    // Boolean operators
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR bool operator==(vec<4, T> const& v1, vec<4, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR bool operator!=(vec<4, T> const& v1, vec<4, T> const& v2);

}//namespace pfm

#include "type_vec4.inl"