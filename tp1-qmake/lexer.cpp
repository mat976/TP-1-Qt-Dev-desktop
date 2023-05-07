#include "lexer.h"

Lexer::Lexer(){

}

void Lexer::setQuery(const QString& query){
    m_query = query;
}

bool Lexer::checkActionToken()
{
    QStringList actionTokens = {"INDEXER", "GET", "ADD", "PUSH", "CLEAR", "SEARCH"};

    QString regexPattern = QString("(%1)").arg(actionTokens.join("|"));
    QRegularExpression regexAction(regexPattern);
    QRegularExpressionMatch matchAction = regexAction.match(m_query);
    qDebug() << __FUNCTION__ << matchAction.hasMatch();
    return matchAction.hasMatch();
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
    QRegularExpression regexCreated("CREATED:\\s*((?:\\d{1,2}/\\d{1,2}/\\d{2,4})|(?:\\d{1,2}/\\d{2,4})|(?:\\d{4})|(?:\\d{2})|SINCE LAST\\s+\\d+\\s+(?:MINUTES|HOURS|DAYS|MONTHS|YEAR)|\\d+\\s+(?:MINUTES|HOURS|DAYS|MONTHS|YEAR) AGO|BETWEEN\\s+(?:(?:\\d{1,2}/\\d{1,2}/\\d{2,4})|(?:\\d{1,2}/\\d{2,4})|(?:\\d{4}))\\s+AND\\s+(?:(?:\\d{1,2}/\\d{1,2}/\\d{2,4})|(?:\\d{1,2}/\\d{2,4})|(?:\\d{4})))");
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

QString Lexer::extractFilename()
{
    QString filename;
    QRegularExpression regex("SEARCH '\\s*(.*?)\\s*'");
    QRegularExpressionMatch match = regex.match(m_query);

    if (match.hasMatch()) {
        filename = match.captured(1);
    }

    qDebug() << __FUNCTION__ << filename;
    return filename;
}
QString Lexer::extractLastModified() const {
    QRegularExpression regex("LAST_MODIFIED:\\s*(\\d{2}/\\d{2}/\\d{4}|\\d{2}/\\d{4}|\\d{4}|\\d{2})");
    QRegularExpressionMatch match = regex.match(m_query);

    if (match.hasMatch()) {
        QString dateSpec = match.captured(1);
        return dateSpec; // retourner la date spécifiée
    } else {
        return QString(); // retourner une chaîne vide si aucune correspondance n'est trouvée
    }
}

QString Lexer::extractCreated() const {
    QRegularExpression regex("CREATED:\\s*(\\d{2}/\\d{2}/\\d{4}|\\d{2}/\\d{4}|\\d{4}|\\d{2})");
    QRegularExpressionMatch match = regex.match(m_query);

    if (match.hasMatch()) {
        QString dateSpec = match.captured(1);
        return dateSpec; // retourner la date spécifiée
    } else {
        return QString(); // retourner une chaîne vide si aucune correspondance n'est trouvée
    }
}

QString Lexer::extractMaxSize()
{
    QRegularExpression regexMaxSize("MAX_SIZE:(\\d+)([KMG])");
    QRegularExpressionMatch matchMaxSize = regexMaxSize.match(m_query);

    if (matchMaxSize.hasMatch()) {
        QString sizeValue = matchMaxSize.captured(1);
        QString sizeUnit = matchMaxSize.captured(2);

        double sizeInBytes = sizeValue.toDouble();
        if (sizeUnit == "K") {
            sizeInBytes *= 1024; // Conversion en octets
        } else if (sizeUnit == "M") {
            sizeInBytes *= 1024 * 1024; // Conversion en octets
        } else if (sizeUnit == "G") {
            sizeInBytes *= 1024 * 1024 * 1024; // Conversion en octets
        }

        return QString::number(sizeInBytes, 'f', 0);
    }

    return "";
}

QString Lexer::extractMinSize()
{
    QRegularExpression regexMinSize("MIN_SIZE:(\\d+)([KMG])");
    QRegularExpressionMatch matchMinSize = regexMinSize.match(m_query);

    if (matchMinSize.hasMatch()) {
        QString sizeValue = matchMinSize.captured(1);
        QString sizeUnit = matchMinSize.captured(2);

        double sizeInBytes = sizeValue.toDouble();
        if (sizeUnit == "K") {
            sizeInBytes *= 1024; // Conversion en octets
        } else if (sizeUnit == "M") {
            sizeInBytes *= 1024 * 1024; // Conversion en octets
        } else if (sizeUnit == "G") {
            sizeInBytes *= 1024 * 1024 * 1024; // Conversion en octets
        }

        return QString::number(sizeInBytes, 'f', 0);
    }

    return "";
}

QString Lexer::extractSize()
{
    QRegularExpression regexSize("SIZE:(BETWEEN )?(\\d+)([KMG])?( AND (\\d+)([KMG]))?");
    QRegularExpressionMatch matchSize = regexSize.match(m_query);

    if (matchSize.hasMatch()) {
        QString sizeValue1 = matchSize.captured(2);
        QString sizeUnit1 = matchSize.captured(3);

        QString sizeValue2 = matchSize.captured(5);
        QString sizeUnit2 = matchSize.captured(6);

        double sizeInBytes1 = sizeValue1.toDouble();
        double sizeInBytes2 = sizeValue2.toDouble();

        if (sizeUnit1 == "K") {
            sizeInBytes1 *= 1024; // Conversion en octets
        } else if (sizeUnit1 == "M") {
            sizeInBytes1 *= 1024 * 1024; // Conversion en octets
        } else if (sizeUnit1 == "G") {
            sizeInBytes1 *= 1024 * 1024 * 1024; // Conversion en octets
        }

        if (sizeUnit2 == "K") {
            sizeInBytes2 *= 1024; // Conversion en octets
        } else if (sizeUnit2 == "M") {
            sizeInBytes2 *= 1024 * 1024; // Conversion en octets
        } else if (sizeUnit2 == "G") {
            sizeInBytes2 *= 1024 * 1024 * 1024; // Conversion en octets
        }

        if (matchSize.captured(1) == "BETWEEN ") {
            // Format SIZE:BETWEEN <size_spec> AND <size_spec>
            return QString::number(sizeInBytes1, 'f', 0) + "-" + QString::number(sizeInBytes2, 'f', 0);
        } else {
            // Format SIZE:<size_spec>
            return QString::number(sizeInBytes1, 'f', 0);
        }
    }

    return "";
}

QStringList Lexer::extractExtensions()
{
    QRegularExpression regexExtensions("EXT:([a-zA-Z0-9]+(?:,|\\s+OR\\s+)[a-zA-Z0-9]+(?:,|\\s+OR\\s+)*)");
    QRegularExpressionMatch matchExtensions = regexExtensions.match(m_query);

    if (matchExtensions.hasMatch()) {
        QString extensions = matchExtensions.captured(1);
        QStringList extensionList = extensions.split(",", Qt::SkipEmptyParts);
        return extensionList;
    }

    return QStringList();
}
