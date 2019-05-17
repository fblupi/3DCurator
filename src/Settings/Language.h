#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QCoreApplication>
#include <QPointer>
#include <QString>
#include <QTranslator>

/**
 * @class Language
 * Class with app current language
 */
class Language {
public:
    /**
     * Constructor
     * @params locale	Language locale (es_ES, en_US...)
     */
    explicit Language(QString locale);

    /**
     * Destructor
     */
    ~Language();

    /**
     * Change language
     * @params locale	Language locale (es_ES, en_US...)
     */
    void setLocale(const QString &locale);

    /**
     * Change app language
     */
    void setAppLocale();

    /**
     * Get current locale
     * @return Current locale
     */
    QString getLocale() const;

private:
    QTranslator translator; /**< Translator */
    QString locale; /**< Locale */
};

#endif // LANGUAGE_H
