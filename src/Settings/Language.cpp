#include "Language.h"

Language::Language(QString locale) :
    locale(std::move(locale))
{
  setAppLocale();
}

Language::~Language() = default;

void Language::setLocale(const QString &l) {
    this->locale = l;
    setAppLocale();
}

QString Language::getLocale() const {
  return locale;
}

void Language::setAppLocale() {
    qApp->removeTranslator(&translator);
    if (translator.load(":/i18n/" + locale)) {
        qApp->installTranslator(&translator);
    }
}
