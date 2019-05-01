#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QCoreApplication>
#include <QPointer>
#include <QString>
#include <QTranslator>

/**
 * @class Sculpture
 * Class with app current language
 */
class Language {
public:
  /**
   * Constructor
   * @params locale	Language locale (es_ES, en_US...)
   */
  Language(const QString locale);

  /**
   * Destructor
   */
  ~Language();

  /**
   * Change language
   * @params locale	Language locale (es_ES, en_US...)
   */
  void setLocale(const QString locale);

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
