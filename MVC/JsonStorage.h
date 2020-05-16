#ifndef _JSONSTORAGE_H_
#define _JSONSTORAGE_H_

#include <QModelIndex>

class QFile;
class QVariant;

class JsonStorage
{
public:
    JsonStorage();
    ~JsonStorage();

    bool read();
    bool write();

private:
    QFile *_pFile;
    int _currStep;

    struct Storage
    {
        QVariant prevValue;
        QVariant currValue;
        int row;
        int column;
    };
};

#endif // !_JSONSTORAGE_H_
