namespace pfm {

    template<typename T>
    PFM_INLINE mat<4, 4, T> translate(mat<4, 4, T> const& m, vec<3, T> const& v)
    {
        mat<4, 4, T> ret(m);
        ret[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3]; 
        return (ret);
    }

    template<typename T>
    PFM_INLINE mat<4, 4, T> lookAt(vec<3, T> const& eye, vec<3, T> const& target, vec<3, T> const& up)
    {
        vec<3, T> z = normalize(target - eye);
        vec<3, T> x = normalize(cross(z, up));
        vec<3, T> y = normalize(cross(x, z));

        mat<4, 4, T> ret;

		ret[0][0] = x.x;
		ret[1][0] = x.y;
		ret[2][0] = x.z;
		ret[3][0] = -dot(x, eye);

		ret[0][1] = y.x;
		ret[1][1] = y.y;
		ret[2][1] = y.z;
		ret[3][1] = -dot(y, eye);

		ret[0][2] = -z.x;
		ret[1][2] = -z.y;
		ret[2][2] = -z.z;
		ret[3][2] = dot(z, eye);

		ret[0][3] = 0.f;
		ret[1][3] = 0.f;
		ret[2][3] = 0.f;
		ret[3][3] = 1.0f;

		return ret;
    }

	template<typename T>
    PFM_FUNC_DECL mat<4, 4, T> perspective(T const& fovy, T const& ar,  T const& znear, T const& zfar)
	{
		assert(ar > static_cast<T>(0));

		T const tanThetaHalf = tan(fovy / 2.f);

		mat<4, 4, T> ret(0.f);

		ret[0][0] = 1.f / (ar * tanThetaHalf);
		ret[1][1] = 1.f / tanThetaHalf; 
		ret[2][2] = - zfar / (zfar - znear);
		ret[2][3] = - 1.f;
		ret[3][2] = (-zfar * znear) / (zfar - znear);

		return (ret);
	}
}

