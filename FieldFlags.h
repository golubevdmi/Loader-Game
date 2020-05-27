#ifndef _FIELD_FLAGS_H_
#define _FIELD_FLAGS_H_

#include <QAbstractItemModel>

enum FieldValue
{
    Empty = Qt::UserRole,
    LoaderPlayer,
    Cargo,
    CargoDestination,
    Barrier
};

#endif // !_FIELD_FLAGS_H_
