#include "QzCrossWord.h"

QzCrossWord::QzCrossWord (QWidget* parent) : QWidget (parent) {

    _puzzle      = 0;
    _grid        = 0;
    _acrossClues = 0;
    _downClues   = 0;

    // Create Grid widget
    _puzzleGroupBox = new QGroupBox("Puzzle");
    _puzzleGroupBox->setFlat(false);
    _grid = new QzCrossWordGrid (_puzzleGroupBox);
    _grid->setMinimumSize(500,500);

    QVBoxLayout* puzzleGroupBoxLayout = new QVBoxLayout;
    puzzleGroupBoxLayout->addWidget(_grid);
    _puzzleGroupBox->setLayout(puzzleGroupBoxLayout);

    // Create Across Clues widget
    QGroupBox* acrossGroupBox = new QGroupBox("Across");
    _acrossClues = new QzCrossWordClueList;
    _acrossClues->setMinimumWidth(300);

    QVBoxLayout* acrossGroupBoxLayout = new QVBoxLayout;
    acrossGroupBoxLayout->addWidget(_acrossClues);
    acrossGroupBox->setLayout(acrossGroupBoxLayout);

    // Create Down Clues widget
    QGroupBox* downGroupBox = new QGroupBox("Down");
    _downClues = new QzCrossWordClueList;
    _downClues->setMinimumWidth(300);

    QVBoxLayout* downGroupBoxLayout = new QVBoxLayout;
    downGroupBoxLayout->addWidget(_downClues);
    downGroupBox->setLayout(downGroupBoxLayout);

    // Create Layouts
    QVBoxLayout* cluesBoxLayout = new QVBoxLayout;
    cluesBoxLayout->addWidget(acrossGroupBox);
    cluesBoxLayout->addWidget(downGroupBox);

    QBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(_puzzleGroupBox,100);
    topLayout->addLayout(cluesBoxLayout,0);

    setLayout(topLayout);

    QObject::connect (_acrossClues, SIGNAL(clueSelected(AcrossLiteClue::Orientation, int)), _grid,        SLOT(setFocusCell(AcrossLiteClue::Orientation, int)));
    QObject::connect (_downClues,   SIGNAL(clueSelected(AcrossLiteClue::Orientation, int)), _grid,        SLOT(setFocusCell(AcrossLiteClue::Orientation, int)));
    QObject::connect (_grid,        SIGNAL(colRowFocused(int, int)),                        this,         SLOT(handleNewColRowFocused(int, int)));
}

QzCrossWord::~QzCrossWord () {
    if (_puzzle) {
        delete _puzzle;
        _puzzle = 0;
    }
}

void QzCrossWord::setPuzzle (const QString& filename) {
    if (_puzzle) {
        delete _puzzle;
        _puzzle = 0;
    }

    if (filename.right(4) == QString(".puz")) {
        _puzzle = new AcrossLitePuzPuzzle(filename.toStdString());

    }else if (filename.right(4) == QString(".txt")) {
        _puzzle = new AcrossLiteTxtPuzzle(filename.toStdString());
    }

    _grid->setPuzzle (_puzzle);
    _acrossClues->setPuzzle (_puzzle, AcrossLiteClue::Across);
    _downClues->setPuzzle (_puzzle, AcrossLiteClue::Down);

    _puzzleGroupBox->setTitle(QString(_puzzle->puzzleName().c_str()));
}

void QzCrossWord::savePuzzle (const QString& filename) {
    _grid->savePuzzle(filename);
}

void QzCrossWord::clearSolution () {
    _grid->revealSolution (false);
    _grid->uncheckSolution ();
}

void QzCrossWord::revealSolution (const bool flag) {
    _grid->revealSolution (flag);
}

void QzCrossWord::revealWord (const bool flag) {
    _grid->revealWord (flag);
}

void QzCrossWord::revealLetter (const bool flag) {
    _grid->revealLetter (flag);
}

void QzCrossWord::checkSolution () {
    _grid->checkSolution ();
}

void QzCrossWord::checkWord () {
    _grid->checkWord ();
}

void QzCrossWord::checkLetter () {
    _grid->checkLetter ();
}

void QzCrossWord::handleNewColRowFocused (int newCol, int newRow) {
    int down, across;

    _grid->colRowToDownAcross (newCol, newRow, down, across);

    if (down != -1) {
        _downClues->clueSelected (down);
    }

    if (across != -1) {
        _acrossClues->clueSelected (across);
    }
}

