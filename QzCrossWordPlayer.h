#ifndef QzCrossWordPlayer_H
#define QzCrossWordPlayer_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>

#include "QzCrossWord.h"

class QzCrossWordPlayer : public QMainWindow {
    Q_OBJECT

    public:
        QzCrossWordPlayer ();
       ~QzCrossWordPlayer ();

    public slots:
        void          setPuzzle         (const QString& filename);
        void          savePuzzle        (const QString& filename);
        void          launchOpenDialog  ();
        void          launchSaveDialog  ();
        void          launchAboutDialog ();
        void          revealSolution    ();
        void          revealWord        ();
        void          revealLetter      ();
        void          checkSolution     ();
        void          checkWord         ();
        void          checkLetter       ();
        void          clearSolution     ();

    private:
        QzCrossWord*  _crossWord;
        QMenu*        _fileMenu;
        QMenu*        _viewMenu;
        QMenu*        _helpMenu;
        QToolBar*     _toolBar;
};

#endif

