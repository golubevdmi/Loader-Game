#include "StatStorage.h"

#include <QIODevice>
#include <QFile>
#include <QDataStream>
#include <QDebug>


static const QString statisticsFilename = "statistics.txt";


QDataStream& operator <<(QDataStream &out, const Statistics &stat)
{
    out << stat.time;
    out << stat.level;
    out << stat.steps;
    out << stat.nMoves;
    return out;
}
QDataStream& operator >>(QDataStream &out, Statistics &stat)
{
    out >> stat.time;
    out >> stat.level;
    out >> stat.steps;
    out >> stat.nMoves;
    return out;
}



StatStorage::StatStorage(QObject *parent)
    : QAbstractTableModel(parent)
{
    read();
}

StatStorage::~StatStorage()
{}

QVariant StatStorage::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("Date");
        case 1:
            return tr("Level");
        case 2:
            return tr("Steps");
        case 3:
            return tr("nMoves");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

int StatStorage::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return getNumberOfLines();
}

int StatStorage::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant StatStorage::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Statistics stat = m_stats[index.row()];
    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return QVariant(stat.time);
        case 1:
            return QVariant(stat.level);
        case 2:
            return QVariant(stat.steps);
        case 3:
            return QVariant(stat.nMoves);
        }
        break;
    }
    return QVariant();
}

bool StatStorage::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

void StatStorage::read()
{
    QFile file(statisticsFilename);
    file.open(QIODevice::ReadOnly);
    if (file.isOpen())
    {
        while (!file.atEnd())
        {
            Statistics stat;
            QDataStream in(&file);
            in >> stat;
            m_stats.push_back(stat);
        }
    }
}

int StatStorage::getNumberOfLines() const
{
    QFile file(statisticsFilename);
    file.open(QIODevice::ReadOnly);
    if (file.isOpen())
    {
        int count = 0;
        while (!file.atEnd())
        {
            Statistics stat;
            QDataStream in(&file);
            in >> stat;
            ++count;
        }
        file.close();
        return count;
    }
    return 0;
}



void saveStatistics(Statistics stat)
{
    QFile file(statisticsFilename);
    file.open(QIODevice::Append);
    if (file.isOpen())
    {
        qDebug() << "Append to stat file";
        QDataStream out(&file);
        out << stat;
        file.close();
    }
    else
    {
        qDebug() << "Not append to stat file";
    }
}
