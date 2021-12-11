#include "QzCrossWordClue.h"

QzCrossWordClue::QzCrossWordClue (const int n, QListWidget* listWidget, const QString& text) : QListWidgetItem ("", listWidget) {
    _number = n;

    setText (QString::number(number()) + QString(". ") + text);
}

QzCrossWordClue::QzCrossWordClue (const int n, const QString& text) : QListWidgetItem ("") {
    _number = n;

    setText (QString::number(number()) + QString(". ") + text);
}

QzCrossWordClue::~QzCrossWordClue () {
}


int QzCrossWordClue::number () const {
    return _number;
}

