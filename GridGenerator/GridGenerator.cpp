#include <GridGenerator/GridGenerator.h>


int getNumberOfElements(const GridType &grid, int value)
{
    auto n = std::count(grid.begin(), grid.end(), value);
    return n;
}


GridGenerator::GridGenerator()
    : m_width(0)
    , m_height(0)
    , m_nLoaderPlayers(0)
    , m_nCargos(0)
    , m_nCargosDst(0)
    , m_nBarriers(0)
{}

// Initial GridGenerator on width and height
void GridGenerator::init()
{
    m_grid.clear();
    m_grid.resize(m_width * m_height);
    std::fill(m_grid.begin(), m_grid.end(), FieldValue::Empty);
}

// Generate GridGenerator
void GridGenerator::generate()
{
    Q_ASSERT(m_nLoaderPlayers > 0 && m_nCargos > 0 && m_nCargosDst > 0 && m_nBarriers >= 0);
    Q_ASSERT(size_grid());
    Q_ASSERT(size_elements() < size_grid());

    fill(FieldValue::LoaderPlayer, m_nLoaderPlayers);
    fill(FieldValue::Cargo, m_nCargos);
    fill(FieldValue::CargoDestination, m_nCargosDst);
    fill(FieldValue::Barrier, m_nBarriers);
}

size_t GridGenerator::size_grid() const
{
    return m_grid.size();
}

size_t GridGenerator::size_elements() const
{
    return static_cast<size_t>(m_nLoaderPlayers + m_nCargos + m_nCargosDst + m_nBarriers);
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

void GridGenerator::setLoaderPlayers(int LoaderPlayers)
{
    Q_ASSERT(LoaderPlayers > 0);
    m_nLoaderPlayers = LoaderPlayers;
}

void GridGenerator::setCargos(int cargos)
{
    Q_ASSERT(cargos > 0);
    m_nCargos = cargos;
}

void GridGenerator::setCargosDestination(int cargosDst)
{
    Q_ASSERT(cargosDst > 0);
    m_nCargosDst = cargosDst;
}

void GridGenerator::setBarriers(int barriers)
{
    Q_ASSERT(barriers >= 0);
    m_nBarriers = barriers;
}

int GridGenerator::getWidth() const
{
    return m_width;
}

int GridGenerator::getHeight() const
{
    return m_height;
}

int GridGenerator::getEmpty() const
{
    return getNumberOfElements(m_grid, FieldValue::Empty);
}

int GridGenerator::getLoaderPlayers() const
{
    return getNumberOfElements(m_grid, FieldValue::LoaderPlayer);
    //return m_nLoaderPlayers;
}

int GridGenerator::getCargos() const
{
    return getNumberOfElements(m_grid, FieldValue::Cargo);
    //return m_nCargos;
}

int GridGenerator::getCargosDestination() const
{
    return getNumberOfElements(m_grid, FieldValue::CargoDestination);
    //return m_nCargosDst;
}

int GridGenerator::getBarriers() const
{
    return getNumberOfElements(m_grid, FieldValue::Barrier);
    //return m_nBarriers;
}

GridType GridGenerator::getGrid() const
{
    return m_grid;
}

void GridGenerator::setValue(int row, int column, int value)
{
    Q_ASSERT(size_grid());
    Q_ASSERT(m_height > 0);
    m_grid[row * m_height + column] = value;
}

int GridGenerator::getValue(int row, int column) const
{
    Q_ASSERT(size_grid());
    Q_ASSERT(m_height > 0);
    return m_grid.at(row * m_height + column);
}
