#ifndef _STAT_STORAGE_H_
#define _STAT_STORAGE_H_

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

struct Statistics
{
    QString time;
    int level = 0;
    int steps = 0;
    int nMoves = 0;
};


void saveStatistics(Statistics stat);


class StatStorage : public QAbstractTableModel
{
    Q_OBJECT
public:
    StatStorage(QObject *parent = nullptr);
    ~StatStorage();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    int m_nLines;
    QVector<Statistics> m_stats;

    void read();
    int getNumberOfLines() const;
    Statistics getStat(int row) const;
};

#endif // !_STAT_STORAGE_H_
