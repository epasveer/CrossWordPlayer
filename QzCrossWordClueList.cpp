#include "QzCrossWordClueList.h"

QzCrossWordClueList::QzCrossWordClueList ( QWidget* parent ) : QListWidget (parent) {
    _puzzle   = 0;
    _clueList = AcrossLiteClue::Unknown;

    QObject::connect (this, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(_selected(QListWidgetItem*,QListWidgetItem*)));
}

QzCrossWordClueList::QzCrossWordClueList ( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent) : QListWidget (parent) {
    _puzzle   = 0;
    _clueList = AcrossLiteClue::Unknown;

    setPuzzle (puzzle, clueList);
}

QzCrossWordClueList::~QzCrossWordClueList () {
}

void QzCrossWordClueList::setPuzzle (AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList) {

    _puzzle   = puzzle;
    _clueList = clueList;

    clear ();

    if (_clueList == AcrossLiteClue::Across) {
        AcrossLiteClues::const_iterator b = _puzzle->beginAcrossClue ();
        AcrossLiteClues::const_iterator e = _puzzle->endAcrossClue ();
        while (b != e) {
            QzCrossWordClue* clue = new QzCrossWordClue ( (*b).number(), QString((*b).clue().c_str()) );
            addItem (clue);

            b++;
        }

    }else if (_clueList == AcrossLiteClue::Down) {
        AcrossLiteClues::const_iterator b = _puzzle->beginDownClue ();
        AcrossLiteClues::const_iterator e = _puzzle->endDownClue ();
        while (b != e) {
            QzCrossWordClue* clue = new QzCrossWordClue ( (*b).number(), QString((*b).clue().c_str()) );
            addItem (clue);

            b++;
        }
    }
}

AcrossLitePuzzleBase* QzCrossWordClueList::puzzle () {
    return _puzzle;
}

AcrossLiteClue::Orientation QzCrossWordClueList::clueList () {
    return _clueList;
}

void QzCrossWordClueList::clueSelected (int n) {

    for (unsigned int i=0; i<count(); i++) {
        QzCrossWordClue* clue = (QzCrossWordClue*) item(i);
        if (clue->number() == n) {
            if (currentItem() != 0) {
                currentItem()->setSelected(false);
            }
            clue->setSelected(true);
            scrollToItem(clue);
            break;
        }
    }
}

void QzCrossWordClueList::_selected (QListWidgetItem* currItem, QListWidgetItem* prevItem) {

    QzCrossWordClue* clue = dynamic_cast<QzCrossWordClue*>(currItem);

    if (clue) {
        //cout << "QzCrossWordClueList::_selected() - ClueDirection " << clueList() << " Clue# " << clue->number() << endl;
        emit clueSelected(clueList(), clue->number());
    }
}

