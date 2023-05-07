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
    READING_PARAMS.addTransition(&READING_PARAMS);

    SEARCH.addTransition(&READING_FILENAME);

    READING_FILENAME.addTransition(&READING_OPTIONS);
    READING_OPTIONS.addTransition(&READING_OPTIONS);

    READING_PARAMS.addTransition(&FINISHED);
    READING_OPTIONS.addTransition(&FINISHED);
}

void Fsm::setQuery(const QString& query){
    this->_lexer.setQuery(query);
}

bool Fsm::checkState(State& src, const State& target, bool cond, std::function<void()> callback){
    qDebug() << "Src state name: " << src.getStateName() << "Current state state name : " <<_currentState.getStateName();
    qDebug() << "checkSearchToken" << cond;
    qDebug() << "transition possible ? : " << src.isTransitionPossible(target);

    if (src == _currentState && cond && src.isTransitionPossible(target)) {
        _currentState = target;
        if (callback) callback();
        return true;
    }

   return false;
}

void Fsm::run()
{
    _currentState = START;

    checkState(_currentState, READING_ACTION, _lexer.checkActionToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
    });

    checkState(_currentState, SEARCH, _lexer.checkSearchToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        this->SQLQuery += "SELECT path, filename, extension, size FROM files WHERE ";
    });

    checkState(_currentState, READING_FILENAME, true, [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do somthing with _lexer.extractFilename();
        this->SQLQuery += "filename='" + _lexer.extractFilename() + "' ";
    });

    checkState(_currentState, READING_OPTIONS, _lexer.checkLastModifiedToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do something with _lexer.extractLastModified();
        QString date = _lexer.extractLastModified().replace('/', '-');
        QRegularExpression regex("(\\d{2}-\\d{2}-\\d{4})|(\\d{2}-\\d{4})|(\\d{4})");
        QRegularExpressionMatch match = regex.match(date);
        if (match.hasMatch()) {
            if(match.captured(1).isEmpty()){
                if(match.captured(2).isEmpty()){
                    this->SQLQuery += "AND lastModified=STR_TO_DATE('" + date + "', '%Y') ";
                } else {
                    this->SQLQuery += "AND lastModified=STR_TO_DATE('" + date + "', '%m-%y') ";
                }
            } else {
                this->SQLQuery += "AND lastModified='" + date + "' ";
            }
        }
    });

    checkState(_currentState, READING_OPTIONS, _lexer.checkCreatedToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do something with _lexer.extractCreated();
        QString date = _lexer.extractCreated().replace('/', '-');
        QRegularExpression regex("(\\d{2}-\\d{2}-\\d{4})|(\\d{2}-\\d{4})|(\\d{4})");
        QRegularExpressionMatch match = regex.match(date);
        if (match.hasMatch()) {
            if(match.captured(1).isEmpty()){
                if(match.captured(2).isEmpty()){
                    this->SQLQuery += "AND creationDate=STR_TO_DATE('" + date + "', '%Y') ";
                } else {
                    this->SQLQuery += "AND creationDate=STR_TO_DATE('" + date + "', '%m-%y') ";
                }
            } else {
                this->SQLQuery += "AND creationDate='" + date + "' ";
            }
        }
    });

    checkState(_currentState, READING_OPTIONS, _lexer.checkMaxSizeToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do something with _lexer.extractMaxSize();
        this->SQLQuery += "AND size<=" + _lexer.extractMaxSize() + " ";
    });

    checkState(_currentState, READING_OPTIONS, _lexer.checkMinSizeToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do something with _lexer.extractMinSize();
        this->SQLQuery += "AND size>=" + _lexer.extractMaxSize() + " ";
    });

    checkState(_currentState, READING_OPTIONS, _lexer.checkSizeToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do something with _lexer.extractSize();
        this->SQLQuery += "AND size=" + _lexer.extractSize() + " ";
    });

    /*TODO
     * checkState(_currentState, READING_OPTIONS, _lexer.checkExtToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // do something with _lexer.extractExtensions();
    });

    checkState(_currentState, READING_OPTIONS, _lexer.checkTypeToken(), [this](){
        qDebug() << "Current State is : " << _currentState.getStateName();
        // faire dans le lexer la fonction pour get le token type
    });
    */

    qDebug() << SQLQuery;
}
