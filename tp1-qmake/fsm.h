#ifndef FSM_H
#define FSM_H

#include "state.h"
#include <QDebug>

class Fsm
{
    State _currentState;

    public:
        Fsm();
};

#endif // FSM_H
