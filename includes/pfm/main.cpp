#include "pfm.hpp"

int main()
{
    pfm::mat4 m1 = {
        111.f, 2.f, 3.f, 4.f,
        1.f, 18.f, 22.f, 4.f,
        .111f, .2f, .3f, .4f,
        820.f, 222.f, 333.f, 444.f
    };

    pfm::mat4 m2 = {
        484.f, 1102.f, 2.f, 7.f,
        484.f, 1102.f, 2.f, 7.f,
        484.f, 1102.f, 2.f, 7.f,
        484.f, 1102.f, 2.f, 7.f
    };

    std::cout << m2 * m1 << std::endl;
    return (0);
}