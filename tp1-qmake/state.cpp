#include "state.h"

State::State(const QString& stateName, const int id)
{
    this->_stateName = stateName;
    this->_id = id;
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

bool State::isTransitionPossible(const State& target) const {
    for (State* transition : _transitions) {
        if (*transition == target) {
            return true;
        }
    }
    return false;
}

void State::addTransition(State* targetState)
{
    _transitions.append(targetState);
}
