#include <GridGenerator/GridGenerator.h>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

GridFromFile::GridFromFile(QString filename)
    : m_pFile(new QFile(filename))
{}

GridFromFile::~GridFromFile()
{
    if (m_pFile)
        delete m_pFile;
}

void GridFromFile::init()
{
    Q_ASSERT(m_pFile);
    m_nLvls = getNLvlsFromFile();
    if (m_nLvls)
        m_currLvl = 0;
}

bool GridFromFile::loadLevel(int lvlNumber)
{
    if (lvlNumber >= 0 && lvlNumber < m_nLvls)
    {
        if (readLvl(lvlNumber))
        {
            m_currLvl = lvlNumber;
            return true;
        }
    }
    return false;
}

bool GridFromFile::loadNextLvl()
{
    return loadLevel(m_currLvl + 1);
}

bool GridFromFile::loadPrevLvl()
{
    return loadLevel(m_currLvl - 1);
}

bool GridFromFile::readLvl(int lvlNumber)
{
    QJsonArray array;
    readFileArray(array);

    if (array.empty())
        return false;

    QJsonObject mazeObject = array[lvlNumber].toObject();
    if (!mazeObject.isEmpty())
    {
        QString key = mazeObject.keys()[0];
        QJsonObject params = mazeObject[key].toObject();

        int szWidth = -1, szHeight = -1;
        readLvlSize(params, szWidth, szHeight);

        qDebug() << "Maze number " << lvlNumber
                 << "Size: " << szHeight << ", " << szHeight;

        if (szWidth > 0 && szHeight > 0)
        {
            setWidth(szWidth);
            setHeight(szHeight);

            QJsonArray gridArray = params["Grid"].toArray();
            fillGrid(gridArray);
            return true;
        }
    }
    return false;
}

void GridFromFile::readFileArray(QJsonArray &array)
{
    if (m_pFile)
    {
        if (!m_pFile->isOpen())
            m_pFile->open(QIODevice::ReadOnly);
        if (m_pFile->isOpen())
        {
            QByteArray fileData = m_pFile->readAll();
            m_pFile->close();
            QJsonDocument loadDoc(QJsonDocument::fromJson(fileData));
            array = loadDoc.array();
        }
    }
}

void GridFromFile::readLvlSize(const QJsonObject &object, int &width, int &height)
{
    QString strWidth = object["Size X"].toString();
    QString strHeight = object["Size Y"].toString();
    if (!strWidth.isEmpty() && !strHeight.isEmpty())
    {
        width = strWidth.toInt();
        height = strHeight.toInt();
        return;
    }
}

static int symbolToValue(QChar symbol)
{
    switch (symbol.unicode())
    {
    case '@':
        return FieldValue::LoaderPlayer;
    case 'X':
        return FieldValue::Barrier;
    case '.':
        return FieldValue::CargoDestination;
    case '*':
        return FieldValue::Cargo;
    default:
        return FieldValue::Empty;
    }
}

void GridFromFile::fillGrid(const QJsonArray &gridArray)
{
    m_grid.resize(getWidth() * getHeight());

    Q_ASSERT(gridArray.size() == getHeight());
    std::fill(m_grid.begin(), m_grid.end(), FieldValue::Empty);

    for (int i = 0; i < gridArray.size(); ++i)
    {
        QString str = gridArray[i].toString();

        Q_ASSERT(str.size() == getWidth());
        for (int j = 0; j < str.size(); ++j)
        {
            setValue(i, j, symbolToValue(str[j]));
        }
    }
}

int GridFromFile::getNLvlsFromFile()
{
    QJsonArray array;
    readFileArray(array);
    return array.size();
}
