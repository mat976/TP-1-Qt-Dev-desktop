#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <QRegularExpression>
#include <QDebug>

class Lexer
{
    QString m_query;

    public:
        Lexer();
        void setQuery(const QString& query);
        bool checkActionToken();
        bool checkSearchToken();
        bool checkLastModifiedToken();
        bool checkCreatedToken();
        bool checkMaxSizeToken();
        bool checkMinSizeToken();
        bool checkSizeToken();
        bool checkExtToken();
        bool checkTypeToken();

        QString extractFilename();
        QString extractLastModified() const;
        QString extractCreated() const;
        QString extractMaxSize();
        QString extractMinSize();
        QString extractSize();
        QStringList extractExtensions();
};

#endif // LEXER_H
