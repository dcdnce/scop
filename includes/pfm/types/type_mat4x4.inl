#pragma once

#include "../setup/setup.hpp"

namespace pfm {
    // Implicit basic constructors
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR mat<4, 4, T>::mat(mat<4, 4, T> const& m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
    {}

    // Explicit basic constructors
    template<typename T>
    PFM_INLINE PFM_CONSTEXPR mat<4, 4, T>::mat(T scalar)
		: value{col_type(scalar, 0, 0, 0), col_type(0, scalar, 0, 0), col_type(0, 0, scalar, 0), col_type(0, 0, 0, scalar)}
    {}

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR mat<4, 4, T>::mat
    (
        T const& x0, T const& y0, T const& z0, T const& w0,
        T const& x1, T const& y1, T const& z1, T const& w1,
        T const& x2, T const& y2, T const& z2, T const& w2,
        T const& x3, T const& y3, T const& z3, T const& w3
    )
        : value{
            col_type(x0, y0, z0, w0),
            col_type(x1, y1, z1, w1),
            col_type(x2, y2, z2, w2),
            col_type(x3, y3, z3, w3)}
    {}

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR mat<4, 4, T>::mat
    (
        col_type const& v0,
        col_type const& v1,
        col_type const& v2,
        col_type const& v3
    )
        : value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
    {}

    // Accesses
    template<typename T>
    PFM_INLINE typename mat<4, 4, T>::col_type& mat<4, 4, T>::operator[](length_t i) noexcept
    {
        assert(i >= 0 && i < 4);
        return this->value[i];
    }

    template<typename T>
    PFM_INLINE PFM_CONSTEXPR typename mat<4, 4, T>::col_type const& mat<4, 4, T>::operator[](length_t i) const noexcept
    {
        assert(i >= 0 && i < 4);
        return this->value[i];
    }


    // Unary arithmetic operations
    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator=(mat<4, 4, U> const& m)
    {
        value[0] = m[0];
        value[1] = m[1];
        value[2] = m[2];
        value[3] = m[3];
    }

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator+=(U scalar)
    {
        value[0] += scalar;
        value[1] += scalar;
        value[2] += scalar;
        value[3] += scalar;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator+=(mat<4, 4, U> const& m)
    {
        value[0] += m[0];
        value[1] += m[1];
        value[2] += m[2];
        value[3] += m[3];
    }

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator-=(U scalar)
    {
        value[0] -= scalar;
        value[1] -= scalar;
        value[2] -= scalar;
        value[3] -= scalar;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator-=(mat<4, 4, U> const& m)
    {
        value[0] -= m[0];
        value[1] -= m[1];
        value[2] -= m[2];
        value[3] -= m[3];
    } 

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator*=(U scalar)
    {
        value[0] *= scalar;
        value[1] *= scalar;
        value[2] *= scalar;
        value[3] *= scalar;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator*=(mat<4, 4, U> const& m)
    {
        value[0] *= m[0];
        value[1] *= m[1];
        value[2] *= m[2];
        value[3] *= m[3];
    } 

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator/=(U scalar)
    {
        value[0] /= scalar;
        value[1] /= scalar;
        value[2] /= scalar;
        value[3] /= scalar;
    }

    template<typename T>
    template<typename U>
    PFM_INLINE mat<4, 4, T> & mat<4, 4, T>::operator/=(mat<4, 4, U> const& m)
    {
        value[0] /= m[0];
        value[1] /= m[1];
        value[2] /= m[2];
        value[3] /= m[3];
    }

    // Binary arithmetic operators
    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator+(mat<4, 4, T> const& m1, mat<4, 4, T> const& m2)
    {
        return mat<4, 4, T>
        (
            m1[0] + m2[0],
            m1[1] + m2[1],
            m1[2] + m2[2],
            m1[3] + m2[3]
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator+(mat<4, 4, T> const& m, T scalar)
    {
        return mat<4, 4, T>
        (
            m[0] + scalar,
            m[1] + scalar,
            m[2] + scalar,
            m[3] + scalar
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator-(mat<4, 4, T> const& m1, mat<4, 4, T> const& m2)
    {
        return mat<4, 4, T>
        (
            m1[0] - m2[0],
            m1[1] - m2[1],
            m1[2] - m2[2],
            m1[3] - m2[3]
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator-(mat<4, 4, T> const& m, T scalar)
    {
        return mat<4, 4, T>
        (
            m[0] - scalar,
            m[1] - scalar,
            m[2] - scalar,
            m[3] - scalar
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator*(mat<4, 4, T> const& m1, mat<4, 4, T> const& m2)
    {
        return mat<4, 4, T>
        (
            m1[0] * m2[0],
            m1[1] * m2[1],
            m1[2] * m2[2],
            m1[3] * m2[3]
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator*(mat<4, 4, T> const& m, T scalar)
    {
        return mat<4, 4, T>
        (
            m[0] * scalar,
            m[1] * scalar,
            m[2] * scalar,
            m[3] * scalar
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator/(mat<4, 4, T> const& m1, mat<4, 4, T> const& m2)
    {
        return mat<4, 4, T>
        (
            m1[0] / m2[0],
            m1[1] / m2[1],
            m1[2] / m2[2],
            m1[3] / m2[3]
        );
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T>& operator/(mat<4, 4, T> const& m, T scalar)
    {
        return mat<4, 4, T>
        (
            m[0] / scalar,
            m[1] / scalar,
            m[2] / scalar,
            m[3] / scalar
        );
    }

    // Boolean operators
	template<typename T>
	PFM_INLINE bool operator==(mat<4, 4, T> const& m1, mat<4, 4, T> const& m2)
    {
        return
        (
            m1[0] == m2[0] &&
            m1[1] == m2[1] &&
            m1[2] == m2[2] &&
            m1[3] == m2[3]
        );
    }

	template<typename T>
	PFM_INLINE bool operator!=(mat<4, 4, T> const& m1, mat<4, 4, T> const& m2)
    {
        return !(m1 == m2);
    }
}