#include "tower_sim.hpp"
#include "Point.hpp"
#include "geometry.hpp"

// static void test_generic_points()
// {
//     Point<2, int> p1;
//     Point<2, int> p2;
//     auto p3 = p1 + p2;
//     p1 += p2;
//     p1 *= 3;
//     p3 = p3;

//     //Point<2,int> pp {1 ,2, 3};
//     //Point3D ppp{1,2};
//     //Point<6, int> pop {1,2,3,4,5,6};
// }

// int main()
// {
//     test_generic_points();
// }

int main(int argc, char** argv)
{
    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}