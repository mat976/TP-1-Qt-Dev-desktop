#ifndef STATE_H
#define STATE_H

#include "QString"
#include "qdebug.h"

class State
{
    QString _stateName;
    int _id = 0;
    static int currentIndex;
    QVector<State*> _transitions;

    public:
        State(const QString& stateName, const int id);
        void addTransition(State* targetState);

        QString getStateName() const;
        int getId() const;
        QVector<State*> getTransitions() const;

        bool operator == (const State& st1) {
            qDebug() << __FUNCTION__ << st1.getId() << getId();
            qDebug() << __FUNCTION__ << st1.getStateName() << getStateName();
            return st1._id == _id;
        }
};

#endif // STATE_H
