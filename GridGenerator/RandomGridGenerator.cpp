#include <GridGenerator/GridGenerator.h>

#include <random>

// PRNG
int random(int min, int max)
{
    Q_ASSERT(min <= max);
    if (min == max)
        return min;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}


void RandomGridGenerator::fill(int value, int count, GridType &grid)
{
    Q_ASSERT(value != FieldValue::Undefined && value != FieldValue::Empty);

    // Number of free fields
    auto nFree = std::count(grid.begin(), grid.end(), FieldValue::Empty);
    nFree += std::count(grid.begin(), grid.end(), FieldValue::Undefined);

    if (count > nFree)
        return;

    // Fill
    int counter = 0;
    while (counter < count)
    {
        int index = random(0, grid.size() - 1);
        if (grid.at(index) == FieldValue::Undefined || grid.at(index) == FieldValue::Empty)
        {
            grid[index] = value;
            ++counter;
        }
    }
}
