#pragma once

#include "setup.hpp"

namespace pfm {
    template<typename T>
    struct vec<3, T>
    {
        // Typedefs
        typedef T value_type
        typedef vec<3, T> type;

        // Implicit basic constructors
        PFM_FUNC_DECL PFM_CONSTEXPR vec() PFM_DEFAULT;
        PFM_FUNC_DECL PFM_CONSTEXPR vec(vec const& v) PFM_DEFAULT;
        PFM_FUNC_DECL PFM_CONSTEXPR vec(vec<3, T> const& v);

        // Explicit basic constructors
        PFM_FUNC_DECL PFM_CONSTEXPR PFM_EXPLICIT vec(T scalar);
        PFM_FUNC_DECL PFM_CONSTEXPR vec(T x, T y, T z);

        // Unary arithmetic operators
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator=(vec<3, T> const& v) PFM_DEFAULT;
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator=(vec<3, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator+=(vec<3, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator+=(U scalar);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator-=(vec<3, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator-=(U scalar);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator*=(vec<3, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator*=(U scalar);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator/=(vec<3, U> const& v);
        template<typename U>
        PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator/=(U scalar);


    };// struct vec<3, T>

    // Binary arithmetic operators
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator+(vec<3, T> const& v1, vec<3, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator+(T scalar, vec<3, T> const& v);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator-(vec<3, T> const& v1, vec<3, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator-(T scalar, vec<3, T> const& v);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator*(vec<3, T> const& v1, vec<3, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator*(T scalar, vec<3, T> const& v);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator/(vec<3, T> const& v1, vec<3, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR vec<3, T>& operator/(T scalar, vec<3, T> const& v);

    // Boolean operators
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR bool operator==(vec<3, T> const& v1, vec<3, T> const& v2);
    template<typename T>
    PFM_FUNC_DECL PFM_CONSTEXPR bool operator!=(vec<3, T> const& v1, vec<3, T> const& v2);

}//namespace pfm

#include "type_vec3.inl"