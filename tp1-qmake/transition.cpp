#include "transition.h"

Transition::Transition(State* sourceState, State* targetState, bool condition)
    : _sourceState(sourceState), _targetState(targetState), _condition(condition)
{

}

bool Transition::canTransition() const
{
    return _condition;
}

State* Transition::targetState() const
{
    return _targetState;
}
