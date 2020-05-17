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


void RandomGridGenerator::fill(int value, int count)
{
    Q_ASSERT(value != FieldValue::Undefined && value != FieldValue::Empty);

    // Number of free fields
    auto nFree = std::count(_grid.begin(), _grid.end(), FieldValue::Empty);
    nFree += std::count(_grid.begin(), _grid.end(), FieldValue::Undefined);

    if (count > nFree)
        return;

    // Fill
    int counter = 0;
    while (counter < count)
    {
        int row = random(0, _height - 1);
        int column = random(0, _width - 1);
        if (getValue(row, column) == FieldValue::Undefined || getValue(row, column) == FieldValue::Empty)
        {
            setValue(row, column, value);
            ++counter;
        }
    }
}
