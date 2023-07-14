namespace pfm {
    template<typename T>
    PFM_FUNC_DECL float radians(T const& degrees)
    {
        return (degrees * 0.01745329251994329576923690768489);
    }
}