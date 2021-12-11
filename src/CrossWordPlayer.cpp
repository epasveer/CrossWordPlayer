#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>

#include "CrossWordPlayer.h"

static const char* fileopen_xpm[] = {
    "16 13 5 1",
    ". c #040404",
    "# c #808304",
    "a c None",
    "b c #f3f704",
    "c c #f3f7f3",
    "aaaaaaaaa...aaaa",
    "aaaaaaaa.aaa.a.a",
    "aaaaaaaaaaaaa..a",
    "a...aaaaaaaa...a",
    ".bcb.......aaaaa",
    ".cbcbcbcbc.aaaaa",
    ".bcbcbcbcb.aaaaa",
    ".cbcb...........",
    ".bcb.#########.a",
    ".cb.#########.aa",
    ".b.#########.aaa",
    "..#########.aaaa",
    "...........aaaaa"
};


static const char* solution_xpm[]={
    "16 16 4 1",
    ". c None",
    "# c #000000",
    "b c #0000ff",
    "a c #ffffff",
    "................",
    "................",
    "################",
    "#aaaa###########",
    "#aaaa###########",
    "#aaaa###########",
    "#aaaa###########",
    "b###############",
    "baaaa#aaaa#aaaa#",
    "bbaaa#aaaa#aaaa#",
    "bbbaa#aaaa#aaaa#",
    "bbbbb#aaaa#aaaa#",
    "bbbbbbbbb##aaaa#",
    "bbbbbbbbbbb#####",
    "bbbbbbbbbbbbbbbb",
    "bbbbbbbbbbbbbbbb"};


static const char* word_xpm[]={
    "16 16 3 1",
    ". c None",
    "# c #000000",
    "a c #0000ff",
    "................",
    "................",
    "................",
    "####..#########.",
    "####..#########.",
    ".##...##........",
    ".##...##........",
    ".##...########..",
    ".##...########..",
    "a##...##........",
    "aa#...##........",
    "aaaaaaaaa######.",
    "aaaaaaaaaaaaaa#.",
    "aaaaaaaaaaaaaaa.",
    "aaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaa"};


static const char* letter_xpm[]={
    "16 16 3 1",
    ". c None",
    "# c #000000",
    "a c #0000ff",
    "................",
    "................",
    "................",
    "....#########...",
    "....#########...",
    "....##..........",
    "....##..........",
    "....########....",
    "....########....",
    "aa..##..........",
    "aaaa##..........",
    "aaaaaaa######...",
    "aaaaaaaaaaaa#...",
    "aaaaaaaaaaaaaa..",
    "aaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaa"};

static const char* check_solution_xpm[]={
"16 16 5 1",
". c None",
"b c #000000",
"# c #00c000",
"a c #00ff00",
"c c #ffffff",
"............#a#.",
"...........#aaa#",
"bbbbbbbbbb#aaaaa",
"bccccbbbbbb#aaa#",
"bccccbbbbbbb#a#b",
"bccccbbbbbbbb#bb",
"bccccbbbbbbbbbbb",
"bbbbbbbbbbbbbbbb",
"bccccbccccbccccb",
"bccccbccccbccccb",
"bccccbccccbccccb",
"bccccbccccbccccb",
"bccccbccccbccccb",
"bbbbbbbbbbbbbbbb",
"bbbbbbbbbbbbbbbb",
"bbbbbbbbbbbbbbbb"};


static const char* check_word_xpm[]={
"16 16 4 1",
". c None",
"b c #000000",
"# c #00c000",
"a c #00ff00",
"............#a#.",
"...........#aaa#",
"..........#aaaaa",
"bbbb..bbbbb#aaa#",
"bbbb..bbbbbb#a#.",
".bb...bb.....#..",
".bb...bb........",
".bb...bbbbbbbb..",
".bb...bbbbbbbb..",
".bb...bb........",
".bb...bb........",
"bbbb..bbbbbbbbb.",
"bbbb..bbbbbbbbb.",
"................",
"................",
"................"};


static const char* check_letter_xpm[]={
"16 16 4 1",
". c None",
"b c #000000",
"# c #00c000",
"a c #00ff00",
"............#a#.",
"...........#aaa#",
"..........#aaaaa",
"....bbbbbbb#aaa#",
"....bbbbbbbb#a#.",
"....bb.......#..",
"....bb..........",
"....bbbbbbbb....",
"....bbbbbbbb....",
"....bb..........",
"....bb..........",
"....bbbbbbbbb...",
"....bbbbbbbbb...",
"................",
"................",
"................"};


static const char* crossword_xpm[] = {
    "24 24 7 1",
    "  c #FC0404",
    ". c #FCFCFC",
    "X c #3C0404",
    "o c #DCDCDC",
    "O c #240404",
    "+ c #040404",
    "@ c None",
    "oooooooooooooooooooooooo",
    "oooooooooooooooooooooooo",
    "oo+++++++++++++++++ooooo",
    "oo+...+...+++++...+ooooo",
    "oo+.+++++++++++++++++ooo",
    "oo+.+...+...+++++...+ooo",
    "oo+++.OOOOXOOOO++++++++o",
    "oo+.+.O   X   O++++...+o",
    "oo+.++O   X   O++++...+o",
    "oo+.+.O   X   O++++...+o",
    "oo+++.OOOOXOOOO++++++++o",
    "oo+++.+...+...+...+++++o",
    "oo+++++...+...+...+++++o",
    "oo+++++...+...+...+++++o",
    "oo+++++++++++++++++++++o",
    "oo+.+++++++...+...+...+o",
    "oo+.+++++++...+...+...+o",
    "oo+.+.+++++...+...+...+o",
    "oo+++.+++++++++++++++++o",
    "oooo+.+...+++++...+...+o",
    "oooo+++...+++++...+...+o",
    "oooooo+...+++++...+...+o",
    "oooooo+++++++++++++++++o",
    "oooooooooooooooooooooooo"
};

CrossWordPlayer::CrossWordPlayer () : QMainWindow () {

    _crossWord = new QzCrossWord(this);

    menuBar();
    statusBar();
    setCentralWidget (_crossWord);

    _fileMenu = new QMenu("&File", this);
    _fileMenu->addAction(QPixmap(fileopen_xpm),       "&Open...",        this, SLOT(launchOpenDialog()) );
    _fileMenu->addAction(QPixmap(fileopen_xpm),       "&Save...",        this, SLOT(launchSaveDialog()) );
    _fileMenu->addAction(                             "&Exit",           qApp, SLOT(quit()) );

    _viewMenu = new QMenu("&View", this);
    _viewMenu->addAction(QPixmap(solution_xpm),       "Reveal Puzzle",   this, SLOT(revealSolution()) );
    _viewMenu->addAction(QPixmap(word_xpm),           "Reveal Word",     this, SLOT(revealWord())     );
    _viewMenu->addAction(QPixmap(letter_xpm),         "Reveal Letter",   this, SLOT(revealLetter())   );
    _viewMenu->addSeparator();
    _viewMenu->addAction(QPixmap(check_solution_xpm), "Check Puzzle",    this, SLOT(checkSolution())  );
    _viewMenu->addAction(QPixmap(check_word_xpm),     "Check Word",      this, SLOT(checkWord())      );
    _viewMenu->addAction(QPixmap(check_letter_xpm),   "Check Letter",    this, SLOT(checkLetter())    );
    _viewMenu->addSeparator();
    _viewMenu->addAction(                             "Clear",           this, SLOT(clearSolution())  );

    _helpMenu = new QMenu("&Help", this);
    _helpMenu->addAction("About...",                                     this, SLOT(launchAboutDialog()) );

    menuBar()->addMenu(_fileMenu);
    menuBar()->addMenu(_viewMenu);
    menuBar()->addMenu(_helpMenu);

    // Tool Bar.
    _toolBar = addToolBar("Puzzle Operations");

    QAction* openAction           = _toolBar->addAction (QPixmap(fileopen_xpm), "");
    _toolBar->addSeparator();

    QAction* revealSolutionAction = _toolBar->addAction (QPixmap(solution_xpm), "");
    QAction* revealWordAction     = _toolBar->addAction (QPixmap(word_xpm), "");
    QAction* revealLetterAction   = _toolBar->addAction (QPixmap(letter_xpm), "");
    _toolBar->addSeparator();

    QAction* checkSolutionAction  = _toolBar->addAction (QPixmap(check_solution_xpm), "");
    QAction* checkWordAction      = _toolBar->addAction (QPixmap(check_word_xpm), "");
    QAction* checkLetterAction    = _toolBar->addAction (QPixmap(check_letter_xpm), "");

    openAction->setToolTip("Open Puzzle");

    revealSolutionAction->setToolTip("Reveal Puzzle");
    revealWordAction->setToolTip("Reveal Word");
    revealLetterAction->setToolTip("Reveal Letter");

    checkSolutionAction->setToolTip("Check Puzzle");
    checkWordAction->setToolTip("Check Word");
    checkLetterAction->setToolTip("Check Letter");

    QObject::connect (openAction,           SIGNAL(triggered()), this, SLOT(launchOpenDialog()));

    QObject::connect (revealSolutionAction, SIGNAL(triggered()), this, SLOT(revealSolution()));
    QObject::connect (revealWordAction,     SIGNAL(triggered()), this, SLOT(revealWord()));
    QObject::connect (revealLetterAction,   SIGNAL(triggered()), this, SLOT(revealLetter()));

    QObject::connect (checkSolutionAction,  SIGNAL(triggered()), this, SLOT(checkSolution()));
    QObject::connect (checkWordAction,      SIGNAL(triggered()), this, SLOT(checkWord()));
    QObject::connect (checkLetterAction,    SIGNAL(triggered()), this, SLOT(checkLetter()));

    statusBar()->showMessage ("Enjoy!", 5000);
}

/**
  General Method description

  \param    X    Description of X
  \return        Description of return value
 */
CrossWordPlayer::~CrossWordPlayer () {
}

/**
  General Method description

  \param    X    Description of X
  \return        Description of return value
 */
void CrossWordPlayer::launchOpenDialog() {

    QString filename = QFileDialog::getOpenFileName(this, QString::null, "*.puz *.txt");

    setPuzzle (filename);
}

void CrossWordPlayer::launchSaveDialog() {

    QString filename = QFileDialog::getSaveFileName(this, QString::null, "*.puz");

    savePuzzle (filename);
}

void CrossWordPlayer::setPuzzle (const QString& filename) {

    if (filename.isNull() == false) {
        _crossWord->setPuzzle(filename);
    }
}

void CrossWordPlayer::savePuzzle (const QString& filename) {

    if (filename.isNull() == false) {
        _crossWord->savePuzzle(filename);
    }
}

void CrossWordPlayer::revealSolution () {
    _crossWord->revealSolution(true);
}

void CrossWordPlayer::revealWord () {
    _crossWord->revealWord(true);
}

void CrossWordPlayer::revealLetter () {
    _crossWord->revealLetter(true);
}

void CrossWordPlayer::checkSolution () {
    _crossWord->checkSolution();
}

void CrossWordPlayer::checkWord () {
    _crossWord->checkWord();
}

void CrossWordPlayer::checkLetter () {
    _crossWord->checkLetter();
}

void CrossWordPlayer::clearSolution () {
    _crossWord->clearSolution();
}

void CrossWordPlayer::launchAboutDialog() {

    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle ("CrossWordPlayer");
    message->setText ("CrossWordPlayer (ver. 3.1)\nOctober, 2018\nErnie Pasveer (epasveer@att.net)\nReleased under the GPL");
    message->setIconPixmap (QPixmap(crossword_xpm));
    message->addButton (QMessageBox::Ok);

    message->exec();

    delete message;
}

int main (int argc, char* argv[]) {

    QApplication app (argc, argv);

    CrossWordPlayer mainWindow;
    if (argc == 2) {
        mainWindow.setPuzzle(QString(argv[1]));
    }

    mainWindow.show();

    return app.exec ();
}

