#include "../setup.hpp"

namespace pfm {
    // Implicit basic constructors
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>::vec(vec<3, T> const& v)
        : x(v.x), y(v.y), z(v.z) 
    {}

    // Explicit basic constructors
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR  vec<3,T>::vec(T scalar)
        : x(scalar), y(scalar), z(scalar)
    {}
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>::vec(T x, T y, T z)
        : x(x), y(y), z(z)
    {}

    // Unary arithmetic operators
    template<typename T> //struct template
    template<typename U> //extern template
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator=(vec<3, U> const& v)
    {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
        this->z = static_cast<T>(v.z);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator+=(vec<3, U> const& v)
    {
        this->x += static_cast<T>(v.x);
        this->y += static_cast<T>(v.y);
        this->z += static_cast<T>(v.z);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator+=(U scalar)
    {
        this->x += static_cast<T>(scalar);
        this->y += static_cast<T>(scalar);
        this->z += static_cast<T>(scalar);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator-=(vec<3, U> const& v)
    {
        this->x -= static_cast<T>(v.x);
        this->y -= static_cast<T>(v.y);
        this->z -= static_cast<T>(v.z);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator-=(U scalar)
    {
        this->x -= static_cast<T>(scalar);
        this->y -= static_cast<T>(scalar);
        this->z -= static_cast<T>(scalar);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator*=(vec<3, U> const& v)
    {
        this->x *= static_cast<T>(v.x);
        this->y *= static_cast<T>(v.y);
        this->z *= static_cast<T>(v.z);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator*=(U scalar)
    {
        this->x *= static_cast<T>(scalar);
        this->y *= static_cast<T>(scalar);
        this->z *= static_cast<T>(scalar);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator/=(vec<3, U> const& v)
    {
        this->x /= static_cast<T>(v.x);
        this->y /= static_cast<T>(v.y);
        this->z /= static_cast<T>(v.z);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& vec<3, T>::operator/=(U scalar)
    {
        this->x /= static_cast<T>(scalar);
        this->y /= static_cast<T>(scalar);
        this->z /= static_cast<T>(scalar);
        return *this;
    }

    // Binary arithmetic operators
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator+(vec<3, T> const& v1, vec<3, T> const& v2)
    {
        return vec<3, T>
            (
                v1.x + v2.x,
                v1.y + v2.y,
                v1.z + v2.z
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator+(T scalar, vec<3, T> const& v)
    {
        return vec<3, T>
            (
                v.x + scalar,
                v.y + scalar,
                v.z + scalar
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator-(vec<3, T> const& v1, vec<3, T> const& v2)
    {
        return vec<3, T>
            (
                v1.x - v2.x,
                v1.y - v2.y,
                v1.z - v2.z
            );
    }


    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator-(T scalar, vec<3, T> const& v)
    {
        return vec<3, T>
            (
                v.x - scalar,
                v.y - scalar,
                v.z - scalar
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator*(vec<3, T> const& v1, vec<3, T> const& v2)
    {
        return vec<3, T>
            (
                v1.x * v2.x,
                v1.y * v2.y,
                v1.z * v2.z
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator*(T scalar, vec<3, T> const& v)
    {
        return vec<3, T>
            (
                v.x * scalar,
                v.y * scalar,
                v.z * scalar
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator/(vec<3, T> const& v1, vec<3, T> const& v2)
    {
        return vec<3, T>
        (
            v1.x / v2.x,
            v1.y / v2.y,
            v1.z / v2.z
        );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<3, T>& operator/(T scalar, vec<3, T> const& v)
    {
        return vec<3, T>
            (
                v.x / scalar,
                v.y / scalar,
                v.z / scalar
            );
    }

    // Boolean operators
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR bool operator==(vec<3, T> const& v1, vec<3, T> const& v2)
    {
        return
            (
                v1.x == v2.x &&
                v1.y == v2.y &&
                v1.z == v2.z
            );
    }
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR bool operator!=(vec<3, T> const& v1, vec<3, T> const& v2)
    {
        return !(v1 == v2);
    }

}//namespace pfm