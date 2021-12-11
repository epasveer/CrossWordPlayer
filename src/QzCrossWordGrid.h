#ifndef QzCrossWordGrid_H
#define QzCrossWordGrid_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSizePolicy>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QSize>
#include <QtCore/QObject>
#include <QtCore/QEvent>

#include "QzCrossWordCell.h"
#include "acrosslite.h"

class QzCrossWordGrid : public QWidget {
    Q_OBJECT

    public:

        enum FocusOrientation {
            FocusUnknown    = 0,
            FocusHorizontal = 1,
            FocusVertical   = 2
        };

        QzCrossWordGrid (QWidget* parent=0);
        QzCrossWordGrid (AcrossLitePuzzleBase* puzzle, QWidget* parent=0);
       ~QzCrossWordGrid ();

        void                                setPuzzle           (AcrossLitePuzzleBase* puzzle);
        AcrossLitePuzzleBase*               puzzle              ();
        void                                savePuzzle          (const QString& filename);

        void                                revealSolution      (const bool flag);
        void                                revealWord          (const bool flag);
        void                                revealLetter        (const bool flag);
        void                                uncheckSolution     ();
        void                                checkSolution       ();
        void                                checkWord           ();
        void                                checkLetter         ();

        QzCrossWordCell*                    focusCell           ();
        QzCrossWordCell*                    cell                (const int col, const int row);
        QzCrossWordCell*                    cell                (const int number);
        void                                setFocusCell        (const int col, const int row);
        void                                retreatFocusCell    ();
        void                                advanceFocusCell    (const int count=1);
        void                                setFocusOrientation (const QzCrossWordGrid::FocusOrientation orientation);
        QzCrossWordGrid::FocusOrientation   focusOrientation    () const;

        void                                hiliteSolution      (const bool flag);
        void                                hiliteFullSolution  (const bool flag);

        void                                colRowToDownAcross  (const int col, const int row, int& down, int& across);

        virtual QSize                       minimumSizeHint     () const;
        virtual QSize                       sizeHint            () const;
        virtual QSizePolicy                 sizePolicy          () const;
        virtual void                        keyPressEvent       (QKeyEvent*   e);
        virtual void                        mousePressEvent     (QMouseEvent* e);
        virtual bool                        eventFilter         (QObject* o, QEvent *e);

    public slots:
        void                                setFocusCell        (AcrossLiteClue::Orientation o, int number);

    signals:
        void                                rowFocused          (int row);
        void                                colFocused          (int col);
        void                                colRowFocused       (int col, int row);

    private:
        QzCrossWordGrid ();

        AcrossLitePuzzleBase*               _puzzle;
        QGridLayout*                        _gridLayout;
        FocusOrientation                    _focusOrientation;
        QVector<QzCrossWordCell*>           _cells;
};

#endif

