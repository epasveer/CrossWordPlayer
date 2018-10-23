#ifndef QzCrossWordClueList_H
#define QzCrossWordClueList_H

#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QWidget>

#include "acrosslite.h"
#include "QzCrossWordClue.h"

class QzCrossWordClueList : public QListWidget {
    Q_OBJECT

    public:
        QzCrossWordClueList ( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent=0);
        QzCrossWordClueList ( QWidget* parent=0);
       ~QzCrossWordClueList ();

        void                                setPuzzle           (AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList);
        AcrossLitePuzzleBase*               puzzle              ();
        AcrossLiteClue::Orientation         clueList            ();

    signals:
        void                                clueSelected        (AcrossLiteClue::Orientation o, int number);

    public slots:
        void                                clueSelected        (int number);

    private slots:
        void                                _selected           (QListWidgetItem* currItem, QListWidgetItem* prevItem);

    private:
        AcrossLitePuzzleBase*               _puzzle;
        AcrossLiteClue::Orientation         _clueList;
};

#endif

