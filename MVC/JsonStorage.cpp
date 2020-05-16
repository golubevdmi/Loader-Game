#include <MVC/JsonStorage.h>

#include <QFile>
#include <QVariant>
#include <QModelIndex>

JsonStorage::JsonStorage()
    : _pFile(new QFile("storage.json"))
{
    _pFile->open(QIODevice::ReadWrite);
}

JsonStorage::~JsonStorage()
{
    if (_pFile)
    {
        if (_pFile->isOpen())
            _pFile->close();
        delete _pFile;
    }
}


bool JsonStorage::read()
{
    return false;
}

bool JsonStorage::write()
{
    return false;
}
