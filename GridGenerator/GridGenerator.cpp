#include <GridGenerator/GridGenerator.h>


GridGenerator::GridGenerator()
    : m_width(0)
    , m_height(0)
    , m_currLvl(-1)
    , m_nLvls(-1)
{}

size_t GridGenerator::size_grid() const
{
    return m_grid.size();
}

void GridGenerator::setWidth(int width)
{
    Q_ASSERT(width > 0);
    m_width = width;
}

void GridGenerator::setHeight(int height)
{
    Q_ASSERT(height > 0);
    m_height = height;
}

int GridGenerator::getWidth() const
{
    return m_width;
}

int GridGenerator::getHeight() const
{
    return m_height;
}

int GridGenerator::getCurrentLvl() const
{
    return m_currLvl;
}

int GridGenerator::getLvls() const
{
    return m_nLvls;
}

GridType GridGenerator::getGrid() const
{
    return m_grid;
}

void GridGenerator::setValue(int row, int column, int value)
{
    Q_ASSERT(size_grid());
    Q_ASSERT(row >= 0 && column >= 0);
    Q_ASSERT(row < getHeight() && column < getWidth());
    m_grid[row * m_width + column] = value;
}

int GridGenerator::getValue(int row, int column) const
{
    Q_ASSERT(size_grid());
    Q_ASSERT(row >= 0 && column >= 0);
    Q_ASSERT(row < getHeight() && column < getWidth());
    return m_grid.at(row * m_width + column);
}

int GridGenerator::getNumberOfElements(int role) const
{
    return std::count(m_grid.begin(), m_grid.end(), role);
}
