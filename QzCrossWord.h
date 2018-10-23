#ifndef QzCrossWord_H
#define QzCrossWord_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtCore/QString>

#include "QzCrossWordGrid.h"
#include "QzCrossWordClueList.h"
#include "acrosslite.h"

class QzCrossWord : public QWidget {
    Q_OBJECT

    public:
        QzCrossWord (QWidget* parent=0);
       ~QzCrossWord ();

        void                                setPuzzle               (const QString& filename);
        void                                savePuzzle              (const QString& filename);

        void                                clearSolution           ();
        void                                revealSolution          (const bool flag);
        void                                revealWord              (const bool flag);
        void                                revealLetter            (const bool flag);
        void                                checkSolution           ();
        void                                checkWord               ();
        void                                checkLetter             ();

    public slots:
        void                                handleNewColRowFocused  (int newCol, int newRow);

    private:
       AcrossLitePuzzleBase*                _puzzle;
       QGroupBox*                           _puzzleGroupBox;
       QzCrossWordGrid*                     _grid;
       QzCrossWordClueList*                 _acrossClues;
       QzCrossWordClueList*                 _downClues;
};

#endif

