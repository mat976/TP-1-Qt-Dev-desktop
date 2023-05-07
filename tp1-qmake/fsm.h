#ifndef FSM_H
#define FSM_H

#include "state.h"
#include "lexer.h"
#include <QDebug>

class Fsm
{
    State _currentState;
    State START;
    State READING_ACTION;
    State INDEXER;
    State GET;
    State ADD;
    State CLEAR;
    State PUSH;
    State SEARCH;
    State READING_PARAMS;
    State READING_FILENAME;
    State READING_OPTIONS;
    State FINISHED;

    Lexer _lexer;
    bool checkState(State& src, const State& target, bool cond, std::function<void()> callback);

    public:
        Fsm();
        void run();
        void setQuery(const QString& query);
};

#endif // FSM_H
