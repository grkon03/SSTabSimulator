#include "includes/SSTabSimulatorAllIncludes.hpp"

using namespace SSTabSim;

int main()
{
    // sample programs

    SSTab s1 = TableauxShape{
        {10, 8, 6, 3, 3, 1},
        {5, 4, 3, 2, 1},
        {3, 3, 1, 1}};

    SSTab s2 = TableauxShape{
        {12, 11, 4, 2},
        {8, 8, 3, 1},
        {7, 4, 2},
        {5},
        {4}};

    SSTab s3 = TableauxShape{
        {5, 3, 3, 3, 3, 3, 2},
        {4, 2, 2, 2},
        {2, 1}};

    std::cout << "s1:" << std::endl
              << s1 << std::endl;
    std::cout << "s2:" << std::endl
              << s2 << std::endl;
    std::cout << "s3:" << std::endl
              << s3 << std::endl;

    std::cout << "(s1 * s2) * s3 time lapse" << std::endl;

    SSTab r1 = SSTab::multiplicationTimeLapse(
        SSTab::multiplicationTimeLapse(s1, s2), s3);

    std::cout << "(s1 * s2) * s3: " << std::endl
              << r1 << std::endl;
    std::cout << "s1 * (s2 * s3): " << std::endl
              << s1 * (s2 * s3) << std::endl;

    std::cout << "wow, same shape!!" << std::endl;
}