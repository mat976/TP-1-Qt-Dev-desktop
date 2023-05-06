#include "state.h"

State::State(const QString& stateName, const int id)
{
    this->_stateName = stateName;
    this->_id = id;

    qDebug() << _stateName;
    qDebug() << _id;
}

QString State::stateName() const
{
    return this->_stateName;
}

int State::id() const {
    return this->_id;
}

void State::addTransition(Transition *transition)
{
    _transitions.append(transition);
}

