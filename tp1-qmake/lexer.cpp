#include "lexer.h"

Lexer::Lexer(){

}

void Lexer::setQuery(const QString& query){
    m_query = query;
}

bool Lexer::checkSearchToken() {
    QRegularExpression regexSearch("SEARCH\\s+'([^']+)'");
    QRegularExpressionMatch match = regexSearch.match(m_query);

    if (match.hasMatch()) {
        QString filenamePart = match.captured(1);
        qDebug() << __FUNCTION__ << true;

        return true;
    }

    qDebug() << __FUNCTION__ << false;
    return false;
}

bool Lexer::checkLastModifiedToken() {
    QRegularExpression regexLastModified("LAST_MODIFIED:\\s*((?:\\d{1,2}/\\d{1,2}/\\d{2,4})|(?:\\d{1,2}/\\d{2,4})|(?:\\d{4})|(?:\\d{2})|SINCE LAST\\s+\\d+\\s+(?:MINUTES|HOURS|DAYS|MONTHS|YEAR)|\\d+\\s+(?:MINUTES|HOURS|DAYS|MONTHS|YEAR) AGO|BETWEEN\\s+(?:(?:\\d{1,2}/\\d{1,2}/\\d{2,4})|(?:\\d{1,2}/\\d{2,4})|(?:\\d{4}))\\s+AND\\s+(?:(?:\\d{1,2}/\\d{1,2}/\\d{2,4})|(?:\\d{1,2}/\\d{2,4})|(?:\\d{4})))");
    QRegularExpressionMatch match = regexLastModified.match(m_query);
    bool isMatch = match.hasMatch();
    qDebug() << __FUNCTION__ << isMatch;
    return isMatch;
}

bool Lexer::checkCreatedToken()
{
    QRegularExpression regexCreated("CREATED:(\\d{2}/\\d{2}/\\d{4})");
    QRegularExpressionMatch matchCreated = regexCreated.match(m_query);
    qDebug() << __FUNCTION__ << matchCreated.hasMatch();
    return matchCreated.hasMatch();
}

bool Lexer::checkMaxSizeToken()
{
    QRegularExpression regexMaxSize("MAX_SIZE:\\s*(\\d+)([KMG]?)");
    QRegularExpressionMatch matchMaxSize = regexMaxSize.match(m_query);
    qDebug() << __FUNCTION__ << matchMaxSize.hasMatch();
    return matchMaxSize.hasMatch();
}

bool Lexer::checkMinSizeToken()
{
    QRegularExpression regexMinSize("MIN_SIZE:\\s*(\\d+)([KMG]?)");
    QRegularExpressionMatch matchMinSize = regexMinSize.match(m_query);
    qDebug() << __FUNCTION__ << matchMinSize.hasMatch();
    return matchMinSize.hasMatch();
}

bool Lexer::checkSizeToken()
{
    QRegularExpression regexSize("SIZE:\\s*(\\d+)([KMG]?)");
    QRegularExpressionMatch matchSize = regexSize.match(m_query);
    qDebug() << __FUNCTION__ << matchSize.hasMatch();
    return matchSize.hasMatch();
}

bool Lexer::checkExtToken()
{
    QRegularExpression regexExt("EXT:\\s*\\S+");
    QRegularExpressionMatch matchExt = regexExt.match(m_query);
    qDebug() << __FUNCTION__ << matchExt.hasMatch();
    return matchExt.hasMatch();
}

bool Lexer::checkTypeToken()
{
    QRegularExpression regexType("TYPE:\\s*((?:\\w+(?:,\\s*)?)+)");
    QRegularExpressionMatch matchType = regexType.match(m_query);
    qDebug() << __FUNCTION__ << matchType.hasMatch();
    return matchType.hasMatch();
}
