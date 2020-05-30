#ifndef _GRID_H_
#define _GRID_H_

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>

#include <FieldFlags.h>

using GridType = QVector<int>;


class QFile;

class GridGenerator
{
public:
    GridGenerator();
    virtual ~GridGenerator() {}

    virtual void init() = 0;

    virtual bool loadLevel(int lvlNumber = 0) = 0;
    virtual bool loadNextLvl() = 0;
    virtual bool loadPrevLvl() = 0;

    size_t size_grid() const;

    void setWidth(int width);
    void setHeight(int height);

    int getWidth() const;
    int getHeight() const;
    int getCurrentLvl() const;
    int getLvls() const;
    int getNumberOfElements(int role) const;
    GridType getGrid() const;

protected:
    int m_width;
    int m_height;
    int m_currLvl;
    int m_nLvls;
    GridType m_grid;

    void setValue(int row, int column, int value);
    int getValue(int row, int column) const;
};

class GridFromFile : public GridGenerator
{
public:
    GridFromFile(QString filename);
    ~GridFromFile();

    void init() override;

    bool loadLevel(int lvlNumber = 0) override;
    bool loadNextLvl() override;
    bool loadPrevLvl() override;

private:
    QFile *m_pFile;

    bool readLvl(int lvlNumber);
    void readFileArray(QJsonArray &array);
    void readLvlSize(const QJsonObject &object, int &width, int &height);
    void fillGrid(const QJsonArray &gridArray);
    int getNLvlsFromFile();
};

#endif // !_GRID_H_

