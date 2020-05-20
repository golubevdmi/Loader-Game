#include <GridGenerator/GridGenerator.h>

#include <random>
#include <QRandomGenerator>

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

#include <QDebug>
void RandomGridGenerator::fill(int value, int count)
{
    Q_ASSERT(value != FieldValue::Empty);

    // Number of free fields
    auto nFree = std::count(m_grid.begin(), m_grid.end(), FieldValue::Empty);

    if (count > nFree)
        return;

    // Fill
    int counter = 0;
    while (counter < count)
    {
        //int row = random(0, m_height - 1);
        //int column = random(0, m_width - 1);
        int row = QRandomGenerator::global()->bounded(m_width);
        int column = QRandomGenerator::global()->bounded(m_height);
        if (getValue(row, column) == FieldValue::Empty)
        {
            setValue(row, column, value);
            ++counter;
        }
    }
}
