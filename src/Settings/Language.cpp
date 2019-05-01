#include "Language.h"

Language::Language(const QString locale) {
  setLocale(locale);
}

Language::~Language() {

}

void Language::setLocale(const QString locale) {
  this->locale = locale;
  qApp->removeTranslator(&translator);
	if (translator.load(":/i18n/" + locale)) {
		qApp->installTranslator(&translator);
	}
}

QString Language::getLocale() const {
  return locale;
}
