#include "fsm.h"

Fsm::Fsm()
    : _currentState("UNKNOWN", 0)
    , START("START", 1)
    , READING_ACTION("READING_ACTION", 2)
    , INDEXER("INDEXER", 3)
    , GET("GET", 4)
    , ADD("ADD", 5)
    , CLEAR("CLEAR", 6)
    , PUSH("PUSH", 7)
    , SEARCH("SEARCH", 8)
    , READING_PARAMS("READING_PARAMS", 9)
    , READING_FILENAME("READING_FILENAME", 10)
    , READING_OPTIONS("READING_OPTIONS", 11)
    , FINISHED("FINISHED", 12)
{
    START.addTransition(&READING_ACTION);

    READING_ACTION.addTransition(&INDEXER);
    READING_ACTION.addTransition(&GET);
    READING_ACTION.addTransition(&ADD);
    READING_ACTION.addTransition(&CLEAR);
    READING_ACTION.addTransition(&PUSH);
    READING_ACTION.addTransition(&SEARCH);

    INDEXER.addTransition(&READING_PARAMS);
    GET.addTransition(&READING_PARAMS);
    ADD.addTransition(&READING_PARAMS);
    CLEAR.addTransition(&READING_PARAMS);
    PUSH.addTransition(&READING_PARAMS);

    SEARCH.addTransition(&READING_FILENAME);

    READING_FILENAME.addTransition(&READING_OPTIONS);

    READING_PARAMS.addTransition(&FINISHED);
    READING_OPTIONS.addTransition(&FINISHED);
}

void Fsm::setQuery(const QString& query){
    this->_lexer.setQuery(query);
}

void Fsm::run()
{
    _lexer.checkSearchToken();
    _lexer.checkLastModifiedToken();
    _lexer.checkCreatedToken();
    _lexer.checkMaxSizeToken();
    _lexer.checkMinSizeToken();
    _lexer.checkSizeToken();
    _lexer.checkExtToken();
    _lexer.checkTypeToken();

    qDebug() << SEARCH.getTransitions();
}

bool Fsm::checkState(State& src, const State& target, bool cond){
   qDebug() << __FUNCTION__ << _currentState.getStateName() << _currentState.getId();
   if (src == _currentState && cond) {
       qDebug() << _currentState.getStateName();
       _currentState = target;

       /*if (callback != nullptr) {
           callback();
       }*/

       return true;
   }

   return false;
}
