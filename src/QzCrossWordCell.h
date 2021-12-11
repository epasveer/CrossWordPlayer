#ifndef QzCrossWordCell_H
#define QzCrossWordCell_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QSizePolicy>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/QSize>

class QzCrossWordCell : public QWidget {
    Q_OBJECT

    public:
        QzCrossWordCell (QWidget* parent=0);
       ~QzCrossWordCell ();

        void                                setColRowLabel      (const int col, const int row);
        int                                 colLabel            () const;
        int                                 rowLabel            () const;
        void                                setSolution         (const char letter);
        void                                setGuess            (const char letter);
        char                                solution            () const;
        char                                guess               () const;
        void                                revealSolution      (const bool flag);
        bool                                isSolutionRevealed  () const;
        void                                setShowCorrectness  (const bool flag);
        bool                                showCorrectness     () const;
        bool                                isSolutionCorrect   () const;
        void                                setNumber           (const int number = 0);
        int                                 number              () const;
        void                                showNumber          (const bool flag);
        bool                                isNumberShown       () const;
        void                                hilite              (const bool flag);
        bool                                isHilited           () const;

        virtual QSize                       sizeHint            () const;
        virtual QSizePolicy                 sizePolicy          () const;
        virtual void                        paintEvent          (QPaintEvent* e);
        virtual void                        paintNumber         (QPainter& p);
        virtual void                        paintFrame          (QPainter& p);
        virtual void                        paintLetter         (QPainter& p);
        virtual void                        paintBlock          (QPainter& p);

    private:
        QzCrossWordCell ();

        int                                 _colLabel;
        int                                 _rowLabel;
        char                                _solution;
        char                                _guess;
        bool                                _isSolutionRevealed;
        bool                                _showCorrectness;
        int                                 _number;
        bool                                _isNumberShown;
        bool                                _isHilited;
};

#endif

