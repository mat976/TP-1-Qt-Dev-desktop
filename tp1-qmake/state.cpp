#include "state.h"

State::State()
{

}

QString State::stateName() const
{
    return this->_stateName;
}

int State::id() const {
    return this->_id;
}

void State::setStateName(const QString &newStateName)
{
    this->_stateName = newStateName;
}

void State::setId(const int newId)
{
    this->_id = newId;
}
