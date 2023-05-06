#include "fsm.h"

Fsm::Fsm()
{
    this->_lexer.setQuery(this->m_query);
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
}

bool Fsm::checkState(State& src, const State& target, bool cond){
   qDebug() << __FUNCTION__ << _currentState.stateName() << _currentState.id();
   if (src == _currentState && cond) {
       qDebug() << _currentState.stateName();
       _currentState = target;

       /*if (callback != nullptr) {
           callback();
       }*/

       return true;
   }

   return false;
}
