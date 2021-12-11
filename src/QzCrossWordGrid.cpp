#include <QtWidgets/QMessageBox>
#include "QzCrossWordGrid.h"

QzCrossWordGrid::QzCrossWordGrid (QWidget* parent) : QWidget (parent) {
    _gridLayout       = 0;
    _puzzle           = 0;
    _focusOrientation = FocusHorizontal;

    // set white background
    QPalette pal = palette();

    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

QzCrossWordGrid::QzCrossWordGrid (AcrossLitePuzzleBase* puzzle, QWidget* parent) : QWidget (parent) {
    _gridLayout       = 0;
    _puzzle           = 0;
    _focusOrientation = FocusHorizontal;

    // set white background
    QPalette pal = palette();

    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    setPuzzle (puzzle);
}

QzCrossWordGrid::~QzCrossWordGrid () {
}

void QzCrossWordGrid::setPuzzle (AcrossLitePuzzleBase* puzzle) {

    if (_gridLayout) {
        delete _gridLayout;
        _gridLayout = 0;
    }

    while (_cells.size() > 0) {
        QzCrossWordCell* w = _cells.back();
        delete w;
        _cells.pop_back();
    }

    _gridLayout       = new QGridLayout(this);
    _puzzle           = puzzle;
    _focusOrientation = FocusHorizontal;

    for (int r = 0; r<_puzzle->nRows(); r++) {
        for (int c = 0; c<_puzzle->nColumns(); c++) {
            QzCrossWordCell* w = new QzCrossWordCell(this);
            w->setColRowLabel(c,r);
            w->setSolution(_puzzle->solutionCell(c,r));
            w->setShowCorrectness (false);
            // w->setGuess(' ');
            w->setGuess(_puzzle->diagramCell(c,r));
            w->setNumber(_puzzle->cellNumber(c,r));
            w->showNumber(true);
            w->setFocusPolicy(Qt::ClickFocus);
            w->show();

            w->installEventFilter( this ); // then install filter

            _gridLayout->addWidget(w,r,c);

            _cells.push_back(w);
        }
    }

    _gridLayout->activate();
};

AcrossLitePuzzleBase* QzCrossWordGrid::puzzle () {
    return _puzzle;
}

void QzCrossWordGrid::savePuzzle (const QString& filename) {
    if (_puzzle == 0) return;

    QString f = filename;

    if (f.contains('.') == false) {
        f += ".puz";
    }

    int indx = f.lastIndexOf('.');

    QString sub = f.mid(indx);

    if (sub != QString(".puz")) {
        QMessageBox::warning (this, "KrossWordPlayer", "Trying to save to a file with a '" + sub + "' extension\nwhen it should be a '.puz' extension.");
        return;
    }

    AcrossLitePuzPuzzle puz;
    puz.copy(*_puzzle);

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->solution() != '.') {
            int letter = cell->guess();
            puz.setDiagramCell(cell->colLabel(), cell->rowLabel(), letter);
        }

        ++i;
    }


    puz.save(f.toStdString());
}

void QzCrossWordGrid::revealSolution (const bool flag) {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        cell->revealSolution(flag);
        ++i;
    }
}

void QzCrossWordGrid::revealWord (const bool flag) {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->isHilited()) {
            cell->revealSolution(flag);
        }
        ++i;
    }
}

void QzCrossWordGrid::revealLetter (const bool flag) {

    QzCrossWordCell* cell = focusCell();

    if (cell != 0 && cell->isHilited()) {
        cell->revealSolution(flag);
    }
}

void QzCrossWordGrid::uncheckSolution () {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        cell->setShowCorrectness(false);
        ++i;
    }
}

void QzCrossWordGrid::checkSolution () {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        cell->setShowCorrectness(true);
        ++i;
    }
}

void QzCrossWordGrid::checkWord () {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->isHilited()) {
            cell->setShowCorrectness(true);
        }
        ++i;
    }
}

void QzCrossWordGrid::checkLetter () {

    QzCrossWordCell* cell = focusCell();
    if (cell != 0 && cell->isHilited()) {
        cell->setShowCorrectness(true);
    }
}

QSize QzCrossWordGrid::sizeHint () const {
    return QSize(25,25);
}

QSizePolicy QzCrossWordGrid::sizePolicy () const {
    return QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QSize QzCrossWordGrid::minimumSizeHint () const {
    return QSize(25,25);
}

void QzCrossWordGrid::keyPressEvent (QKeyEvent* e) {

    QString letter = e->text().toUpper();

    //cout << "Grid - Key pressed: " << letter.toStdString() << endl;

    QzCrossWordCell* cell = focusCell();

    //cout << "Grid - Has focus cell : " << ( cell != 0 ? "yes" : "no" ) << endl;

    if (cell) {
        if (e->key() == Qt::Key_Right) {
            if (focusOrientation() == QzCrossWordGrid::FocusHorizontal) {
                setFocusCell(cell->colLabel()+1, cell->rowLabel());
            }else{
                setFocusOrientation(QzCrossWordGrid::FocusHorizontal);
            }

        }else if (e->key() == Qt::Key_Left) {
            if (focusOrientation() == QzCrossWordGrid::FocusHorizontal) {
                setFocusCell(cell->colLabel()-1, cell->rowLabel());
            }else{
                setFocusOrientation(QzCrossWordGrid::FocusHorizontal);
            }

        }else if (e->key() == Qt::Key_Up) {
            if (focusOrientation() == QzCrossWordGrid::FocusVertical) {
                setFocusCell(cell->colLabel(), cell->rowLabel()-1);
            }else{
                setFocusOrientation(QzCrossWordGrid::FocusVertical);
            }

        }else if (e->key() == Qt::Key_Down) {
            if (focusOrientation() == QzCrossWordGrid::FocusVertical) {
                setFocusCell(cell->colLabel(), cell->rowLabel()+1);
            }else{
                setFocusOrientation(QzCrossWordGrid::FocusVertical);
            }

        }else if (e->key() >= Qt::Key_A && e->key() <= Qt::Key_Z) {
            cell->setGuess (letter.toStdString()[0]);

            advanceFocusCell();

        }else if (e->key() == Qt::Key_Space) {
            cell->setGuess (' ');

            advanceFocusCell();

        }else if (e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace) {
            cell->setGuess (' ');

            advanceFocusCell(-1);
        }
    }
}

void QzCrossWordGrid::mousePressEvent (QMouseEvent* e) {

    hiliteFullSolution(false);

    if (e->button() == Qt::RightButton) {
        if (focusOrientation() == QzCrossWordGrid::FocusHorizontal) {
            setFocusOrientation(QzCrossWordGrid::FocusVertical);
        }else if (focusOrientation() == QzCrossWordGrid::FocusVertical) {
            setFocusOrientation(QzCrossWordGrid::FocusHorizontal);
        }
    }

    hiliteSolution(true);
}

bool QzCrossWordGrid::eventFilter( QObject* o, QEvent* e ) {

    if ( e->type() == QEvent::KeyPress ) {  // key press

        QKeyEvent* k = (QKeyEvent*)e;

        switch (k->key()) {
            case Qt::Key_Left:
            case Qt::Key_Right:
            case Qt::Key_Up:
            case Qt::Key_Down:
            case Qt::Key_Delete:
            case Qt::Key_Backspace:
                keyPressEvent(k);
                return true;  // eat event
                break;
            default:
                if (k->key() >= Qt::Key_A && k->key() <= Qt::Key_Z) {
                    keyPressEvent(k);
                    return true;
                }
                break;
        }

    }else if ( e->type() == QEvent::MouseButtonPress ) {  // mouse press

        QMouseEvent* m = (QMouseEvent*)e;

        switch(m->button()) {
            case Qt::RightButton:
            case Qt::LeftButton:
                {
                    mousePressEvent(m);

                    QzCrossWordCell* cell = focusCell();
                    if (cell) {
                        setFocusCell (cell->colLabel(), cell->rowLabel());
                    }

                    return true; // eat event
                }

                break;

            default:
                break;
        }
    }

    return QWidget::eventFilter( o, e );    // standard event processing
}

QzCrossWordCell* QzCrossWordGrid::focusCell () {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->hasFocus()) {
            return cell;
        }
        ++i;
    }

    return 0;
}

QzCrossWordCell* QzCrossWordGrid::cell (const int col, const int row) {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->colLabel() == col && cell->rowLabel() == row) {
            return cell;
        }
        ++i;
    }

    return 0;
}

QzCrossWordCell* QzCrossWordGrid::cell (const int number) {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->number() == number) {
            return cell;
        }
        ++i;
    }

    return 0;
}


void QzCrossWordGrid::setFocusCell (const int col, const int row) {

    hiliteSolution(false);

    QzCrossWordCell* c = cell(col, row);

    if (c) {
        c->setFocus();

        hiliteSolution(true);

        emit colFocused(col);
        emit rowFocused(row);
        emit colRowFocused(col,row);
    }
}

void QzCrossWordGrid::setFocusCell (AcrossLiteClue::Orientation o, int number) {

    //cout << "QzCrossWordGrid::setFocusCell() - " << number << endl;

    hiliteFullSolution(false);

    QzCrossWordCell* c = cell(number);

    if (c) {

        //cout << "QzCrossWordGrid::setFocusCell() - " << c->colLabel() << " " << c->rowLabel() << endl;

        setFocusCell(c->colLabel(), c->rowLabel());

        if (o == AcrossLiteClue::Across) {
            setFocusOrientation (QzCrossWordGrid::FocusHorizontal);
        }else if (o == AcrossLiteClue::Down) {
            setFocusOrientation (QzCrossWordGrid::FocusVertical);
        }else{
            setFocusOrientation (QzCrossWordGrid::FocusUnknown);
        }

        hiliteSolution(true);
    }
}

void QzCrossWordGrid::advanceFocusCell(const int count) {

    QzCrossWordCell* c = focusCell();
    if (c == 0) return;

    int col = c->colLabel();
    int row = c->rowLabel();

    if (focusOrientation() == QzCrossWordGrid::FocusVertical) {
        QzCrossWordCell* cx = cell(col, row+count);
        if (cx == 0) return;
        if (cx->solution() == '.') return;

        setFocusCell (col, row+count);

    }else if (focusOrientation() == QzCrossWordGrid::FocusHorizontal) {
        QzCrossWordCell* cx = cell(col+count, row);
        if (cx == 0) return;
        if (cx->solution() == '.') return;

        setFocusCell (col+count, row);
    }
}

void QzCrossWordGrid::setFocusOrientation (const QzCrossWordGrid::FocusOrientation orientation) {

    hiliteSolution(false);

    _focusOrientation = orientation;

    hiliteSolution(true);
}

QzCrossWordGrid::FocusOrientation QzCrossWordGrid::focusOrientation () const {
    return _focusOrientation;
}

void QzCrossWordGrid::hiliteSolution (const bool flag) {

    QzCrossWordCell* c = focusCell();
    if (c == 0) return;

    int col = c->colLabel(); // Get current col/row.
    int row = c->rowLabel();

    if (focusOrientation() == QzCrossWordGrid::FocusVertical) {
        // Current to top.
        for (int r = row; ; r--) {
            QzCrossWordCell* cx = cell(col, r);
            if (cx == 0) break;
            if (cx->solution() == '.') break;

            cx->hilite(flag);
        }

        // Current to bottom.
        for (int r = row; ; r++) {
            QzCrossWordCell* cx = cell(col, r);
            if (cx == 0) break;
            if (cx->solution() == '.') break;

            cx->hilite(flag);
        }

    }else if (focusOrientation() == QzCrossWordGrid::FocusHorizontal) {
        // Current to left.
        for (int c = col; ; c--) {
            QzCrossWordCell* cx = cell(c, row);
            if (cx == 0) break;
            if (cx->solution() == '.') break;

            cx->hilite(flag);
        }

        // Current to right.
        for (int c = col; ; c++) {
            QzCrossWordCell* cx = cell(c, row);
            if (cx == 0) break;
            if (cx->solution() == '.') break;

            cx->hilite(flag);
        }
    }
}

void QzCrossWordGrid::hiliteFullSolution (const bool flag) {

    auto i = _cells.begin();

    while ( i != _cells.end()) {
        QzCrossWordCell* cell = *i;
        if (cell->isHilited() != flag) {
            cell->hilite(flag);
        }
        ++i;
    }
}

void QzCrossWordGrid::colRowToDownAcross (const int col, const int row,  int& down, int& across) {

    down = across = -1;

    // Find nearest down solution number.
    int r = row;
    QzCrossWordCell* downCell = cell(col, r);
    while (downCell) {
        if (downCell->solution() == '.') break;

        down = downCell->number();

        downCell = cell(col, --r);
    }

    // Find nearest across solution number.
    int c = col;
    QzCrossWordCell* acrossCell = cell(c, row);
    while (acrossCell) {
        if (acrossCell->solution() == '.') break;

        across = acrossCell->number();

        acrossCell = cell(--c, row);
    }
}

