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

        return mat<4, 4, T>(
            x.x,    x.y,    x.z,    -dot(x, eye),
            y.x,    y.y,    y.z,    -dot(y, eye),
           -z.x,   -z.y,    -z.z,    dot(z, eye),
            0.f,    0.f,    0.f,    1.f
        );
    }

}