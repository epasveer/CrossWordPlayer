#ifndef QzCrossWordClue_H
#define QzCrossWordClue_H

#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtCore/QString>

class QzCrossWordClue : public QListWidgetItem {
    public:
       QzCrossWordClue (const int number, QListWidget* listWidget, const QString& text = QString());
       QzCrossWordClue (const int number, const QString& text=QString());
      ~QzCrossWordClue ();

       int                                  number               () const;

    private:
       int                                  _number;
};

#endif

