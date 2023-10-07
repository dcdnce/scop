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

}
