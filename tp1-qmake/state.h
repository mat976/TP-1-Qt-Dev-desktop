#ifndef STATE_H
#define STATE_H

#include "QString"
#include "qdebug.h"

class State
{
    QString _stateName;
    int _id = 0;
    static int currentIndex;

    public:
        State();
        QString stateName() const;
        int id() const;
        void setStateName(const QString &newStateName);
        void setId(const int newId);

        bool operator == (const State& st1) {
            qDebug() << __FUNCTION__ << st1.id() << id();
            qDebug() << __FUNCTION__ << st1.stateName() << stateName();
            return st1._id == _id;
        }
};

#endif // STATE_H
