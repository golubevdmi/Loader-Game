#include <GridGenerator/GridGenerator.h>

void TestGridGenerator::generate()
{
    if (m_width != m_height)
        return;
    int sz = m_width;
    switch (sz)
    {
    case 5:
        grid5x5();
        break;
    case 10:
        grid10x10();
        break;
    case 15:
        grid15x15();
        break;
    }
}

void TestGridGenerator::fill(int value, int count)
{}

void TestGridGenerator::grid5x5()
{
    int center = m_width / 2;
    int border = m_width - 1;

    setValue(center, center, LoaderPlayer);

    setValue(center - 1, center - 1, Cargo);
    setValue(center + 1, center + 1, Cargo);

    setValue(center - 1, center + 1, CargoDestination);
    setValue(center + 1, center - 1, CargoDestination);

    setValue(border, border, Barrier);
    setValue(0, 0, Barrier);
    setValue(0, border, Barrier);
    setValue(border, 0, Barrier);
}

void TestGridGenerator::grid10x10()
{
    int center = m_width / 2;
    int border = m_width - 1;

    setValue(center, center, LoaderPlayer);

    setValue(center - 1, center - 1, Cargo);
    setValue(center + 1, center + 1, Cargo);

    setValue(center - 1, center + 1, CargoDestination);
    setValue(center + 1, center - 1, CargoDestination);

    setValue(border, border, Barrier);
    setValue(0, 0, Barrier);
    setValue(0, border, Barrier);
    setValue(border, 0, Barrier);
}

void TestGridGenerator::grid15x15()
{
    int center = m_width / 2;
    int border = m_width - 1;

    setValue(center, center, LoaderPlayer);

    setValue(center - 1, center - 1, Cargo);
    setValue(center + 1, center + 1, Cargo);

    setValue(center - 1, center + 1, CargoDestination);
    setValue(center + 1, center - 1, CargoDestination);

    setValue(border, border, Barrier);
    setValue(0, 0, Barrier);
    setValue(0, border, Barrier);
    setValue(border, 0, Barrier);
}
