#ifndef FSM_H
#define FSM_H

#include "state.h"
#include "lexer.h"
#include <QDebug>

class Fsm
{
    State _currentState;
    Lexer _lexer;
    QString m_query;

    public:
        Fsm();
        void run();
        bool checkState(State& src, const State& target, bool cond);
};

#endif // FSM_H
