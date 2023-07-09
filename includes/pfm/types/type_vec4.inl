#include "../setup.hpp"

namespace pfm {
    // Implicit basic constructors
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>::vec(vec<4, T> const& v)
        : x(v.x), y(v.y), z(v.z), w(v.w) 
    {}

    // Explicit basic constructors
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR  vec<4,T>::vec(T scalar)
        : x(scalar), y(scalar), z(scalar), w(scalar)
    {}
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>::vec(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {}

    // Unary arithmetic operators
    template<typename T> //struct template
    template<typename U> //extern template
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator=(vec<4, U> const& v)
    {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
        this->z = static_cast<T>(v.z);
        this->w = static_cast<T>(v.w);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator+=(vec<4, U> const& v)
    {
        this->x += static_cast<T>(v.x);
        this->y += static_cast<T>(v.y);
        this->z += static_cast<T>(v.z);
        this->w += static_cast<T>(v.w);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator+=(U scalar)
    {
        this->x += static_cast<T>(scalar);
        this->y += static_cast<T>(scalar);
        this->z += static_cast<T>(scalar);
        this->w += static_cast<T>(scalar);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator-=(vec<4, U> const& v)
    {
        this->x -= static_cast<T>(v.x);
        this->y -= static_cast<T>(v.y);
        this->z -= static_cast<T>(v.z);
        this->w -= static_cast<T>(v.w);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator-=(U scalar)
    {
        this->x -= static_cast<T>(scalar);
        this->y -= static_cast<T>(scalar);
        this->z -= static_cast<T>(scalar);
        this->w -= static_cast<T>(scalar);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator*=(vec<4, U> const& v)
    {
        this->x *= static_cast<T>(v.x);
        this->y *= static_cast<T>(v.y);
        this->z *= static_cast<T>(v.z);
        this->w *= static_cast<T>(v.w);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator*=(U scalar)
    {
        this->x *= static_cast<T>(scalar);
        this->y *= static_cast<T>(scalar);
        this->z *= static_cast<T>(scalar);
        this->w *= static_cast<T>(scalar);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator/=(vec<4, U> const& v)
    {
        this->x /= static_cast<T>(v.x);
        this->y /= static_cast<T>(v.y);
        this->z /= static_cast<T>(v.z);
        this->w /= static_cast<T>(v.w);
        return *this;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& vec<4, T>::operator/=(U scalar)
    {
        this->x /= static_cast<T>(scalar);
        this->y /= static_cast<T>(scalar);
        this->z /= static_cast<T>(scalar);
        this->w /= static_cast<T>(scalar);
        return *this;
    }

    // Binary arithmetic operators
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator+(vec<4, T> const& v1, vec<4, T> const& v2)
    {
        return vec<4, T>
            (
                v1.x + v2.x,
                v1.y + v2.y,
                v1.z + v2.z,
                v1.w + v2.w
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator+(T scalar, vec<4, T> const& v)
    {
        return vec<4, T>
            (
                v.x + scalar,
                v.y + scalar,
                v.z + scalar,
                v.w + scalar
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator-(vec<4, T> const& v1, vec<4, T> const& v2)
    {
        return vec<4, T>
            (
                v1.x - v2.x,
                v1.y - v2.y,
                v1.z - v2.z,
                v1.w - v2.w
            );
    }


    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator-(T scalar, vec<4, T> const& v)
    {
        return vec<4, T>
            (
                v.x - scalar,
                v.y - scalar,
                v.z - scalar,
                v.w - scalar
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator*(vec<4, T> const& v1, vec<4, T> const& v2)
    {
        return vec<4, T>
            (
                v1.x * v2.x,
                v1.y * v2.y,
                v1.z * v2.z,
                v1.w * v2.w
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator*(T scalar, vec<4, T> const& v)
    {
        return vec<4, T>
            (
                v.x * scalar,
                v.y * scalar,
                v.z * scalar,
                v.w * scalar
            );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator/(vec<4, T> const& v1, vec<4, T> const& v2)
    {
        return vec<4, T>
        (
            v1.x / v2.x,
            v1.y / v2.y,
            v1.z / v2.z,
            v1.w / v2.w
        );
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR vec<4, T>& operator/(T scalar, vec<4, T> const& v)
    {
        return vec<4, T>
            (
                v.x / scalar,
                v.y / scalar,
                v.z / scalar,
                v.w / scalar
            );
    }

    // Boolean operators
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR bool operator==(vec<4, T> const& v1, vec<4, T> const& v2)
    {
        return
            (
                v1.x == v2.x &&
                v1.y == v2.y &&
                v1.z == v2.z &&
                v1.w == v2.w
            );
    }
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR bool operator!=(vec<4, T> const& v1, vec<4, T> const& v2)
    {
        return !(v1 == v2);
    }

}//namespace pfm