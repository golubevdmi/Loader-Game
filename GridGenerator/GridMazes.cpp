#include <GridGenerator/GridGenerator.h>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

GridMazes::GridMazes(QString filename)
    : m_pFile(new QFile(filename))
    , m_currMaze(0)
{}

GridMazes::~GridMazes()
{
    if (m_pFile)
        delete m_pFile;
}

void GridMazes::init()
{
    Q_ASSERT(m_pFile);
    if (!m_pFile->isOpen())
    {
        m_pFile->open(QIODevice::ReadOnly);
    }
}

void GridMazes::generate()
{
    Q_ASSERT(m_currMaze >= 0);

    if (!readGrid(m_currMaze))
    {
        qDebug() << "grid not open";
    }
    m_pFile->close();
    ++m_currMaze;
}

void GridMazes::next()
{

}

void GridMazes::previous()
{

}

void GridMazes::fill(int value, int count)
{
    Q_UNUSED(value);
    Q_UNUSED(count);
}

bool GridMazes::readGrid(int mazeNumber)
{
    if (!m_pFile || !m_pFile->isOpen())
        return false;

    QByteArray fileData = m_pFile->readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(fileData));
    QJsonObject mazeObject = loadDoc.array()[mazeNumber].toObject();

    if (!mazeObject.isEmpty())
    {
        QString key = mazeObject.keys()[0];
        QJsonObject params = mazeObject[key].toObject();

        qDebug() << "Maze number " + QString::number(mazeNumber);

        int szWidth = params["Size X"].toString().toInt();
        int szHeight = params["Size Y"].toString().toInt();

        m_grid.resize(szWidth * szHeight);
        setWidth(szWidth);
        setHeight(szHeight);
        std::fill(m_grid.begin(), m_grid.end(), FieldValue::Empty);

        qDebug() << szWidth << ", " << szHeight;
        qDebug() << params.size();
        QJsonArray gridArray = params["Grid"].toArray();
        Q_ASSERT(gridArray.size() == szHeight);
        for (int i = 0; i < gridArray.size(); ++i)
        {
            QString str = gridArray[i].toString();
            Q_ASSERT(str.size() == szWidth);
            for (int j = 0; j < str.size(); ++j)
            {
                setValue(i, j, symbolToValue(str[j]));
            }
        }
        return true;
    }
    return false;
}

int GridMazes::symbolToValue(QChar symbol)
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
