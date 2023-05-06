#ifndef FSM_H
#define FSM_H

#include "state.h"
#include "lexer.h"
#include <QDebug>

class Fsm
{
    State _currentState;
    Lexer _lexer;
    bool checkState(State& src, const State& target, bool cond);

    public:
        Fsm();
        void run();
        void setQuery(const QString& query);
};

#endif // FSM_H
