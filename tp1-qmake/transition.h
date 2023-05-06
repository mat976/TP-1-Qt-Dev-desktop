#ifndef TRANSITION_H
#define TRANSITION_H

class State;

class Transition
{
    State* _sourceState;
    State* _targetState;
    bool _condition;

    public:
        Transition(State* sourceState, State* targetState, bool condition);
        bool canTransition() const;
        State* targetState() const;
};

#endif // TRANSITION_H
