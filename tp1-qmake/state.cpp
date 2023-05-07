#include "state.h"

State::State(const QString& stateName, const int id)
{
    this->_stateName = stateName;
    this->_id = id;

    qDebug() << _stateName;
    qDebug() << _id;
}

QString State::getStateName() const
{
    return _stateName;
}

int State::getId() const {
    return _id;
}

QVector<State*> State::getTransitions() const
{
    return _transitions;
}

void State::addTransition(State* targetState)
{
    _transitions.append(targetState);
}
