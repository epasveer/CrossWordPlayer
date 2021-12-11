#include "QzCrossWordCell.h"

QzCrossWordCell::QzCrossWordCell (QWidget* parent) : QWidget(parent) {
    _colLabel   = 0;
    _rowLabel   = 0;
    _solution   = '.';
    _guess      = ' ';

    revealSolution(false);
    setShowCorrectness (false);
    setNumber(0);
    showNumber(false);
    hilite(false);
}

QzCrossWordCell::~QzCrossWordCell () {
}

QSize QzCrossWordCell::sizeHint () const {
    return QSize(25,25);
}

QSizePolicy QzCrossWordCell::sizePolicy () const {

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHeightForWidth(true);

    return sp;
}

void QzCrossWordCell::setSolution (const char letter) {
    _solution = letter;

    update();
}

void QzCrossWordCell::setColRowLabel (const int col, const int row) {
    _colLabel = col;
    _rowLabel = row;
}

int QzCrossWordCell::colLabel () const {
    return _colLabel;
}

int QzCrossWordCell::rowLabel () const {
    return _rowLabel;
}

void QzCrossWordCell::setGuess (const char letter) {

    setShowCorrectness(false);

    // Don't change guess if cell is revealed.
    if (isSolutionRevealed()) return;

    _guess = letter;

    update();
}

char QzCrossWordCell::solution () const {
    return _solution;
}

char QzCrossWordCell::guess () const {
    return _guess;
}

void QzCrossWordCell::revealSolution (const bool flag) {
    _isSolutionRevealed = flag;

    if (flag == true) {
        setShowCorrectness(false);
    }

    if (flag == false) {
        _guess = ' ';
    }else{
        _guess = solution();
    }

    update();
}

bool QzCrossWordCell::isSolutionRevealed () const {
    return _isSolutionRevealed;
}

bool QzCrossWordCell::showCorrectness () const {
    return _showCorrectness;
}

void QzCrossWordCell::setShowCorrectness (const bool flag) {
    _showCorrectness = flag;

    update ();
}

bool QzCrossWordCell::isSolutionCorrect () const {
    return (solution() == guess());
}

void QzCrossWordCell::setNumber (const int number) {
    _number = number;

    if (_number == 0) showNumber(false);

    update();
}

int QzCrossWordCell::number () const {
    return _number;
}

void QzCrossWordCell::showNumber (const bool flag) {
    if (number() == 0) {
        _isNumberShown = false;
        return;
    }

    _isNumberShown = flag;

    update();
}

bool QzCrossWordCell::isNumberShown () const {
    return _isNumberShown;
}

void QzCrossWordCell::hilite (const bool flag) {
    _isHilited = flag;

    update ();
}

bool QzCrossWordCell::isHilited () const {
    return _isHilited;
}

void QzCrossWordCell::paintEvent (QPaintEvent*) {
    QPainter p(this);
    p.setPen(QPen(QColor("black")));

    if (solution() == '.') {
        paintBlock(p);
    }else{
        if (hasFocus()) {
            p.fillRect(rect(), QColor("yellow"));
        }else{
            if (isHilited()) {
                p.fillRect(rect(), QColor(200,200,200));
            }else{
                p.fillRect(rect(), QColor("white"));
            }
        }

        paintFrame(p);

        if (isNumberShown()) {
            paintNumber(p);
        }

        paintLetter(p);
    }
}

void QzCrossWordCell::paintBlock (QPainter& p) {
    p.fillRect(rect(), QColor("black"));
}

void QzCrossWordCell::paintFrame (QPainter& p) {
    p.setPen(QPen(QColor("black"),1));
    p.drawRect(rect());
}

void QzCrossWordCell::paintNumber (QPainter& p) {
    QRect r = rect();
    r.setHeight( 12 );
    r.moveTo( 3,0 );

    // Resize the font to the size of the cell.
    QFont f = p.font();
    QFontMetrics fm (f);
    while (fm.height() < r.height()) {
        f.setPointSize( f.pointSize() + 2 );
        fm = QFontMetrics(f);
    }
    p.setFont(f);

    QString text;
    text.setNum(number());

    p.drawText(r, Qt::AlignLeft, text);
}

void QzCrossWordCell::paintLetter (QPainter& p) {
    QRect r = rect();
    int deltaY = r.height() - (int)((float)r.height() * .70);

    r.setHeight( r.height() - deltaY );
    r.moveTo( 0, deltaY );

    // Resize the font to the size of the cell.
    QFont f = p.font();
    QFontMetrics fm (f);
    while (fm.height() < r.height()) {
        f.setPointSize( f.pointSize() + 2 );
        fm = QFontMetrics(f);
    }
    p.setFont(f);

    QString letter;
    if (isSolutionRevealed() == false) {
        letter = QString(QChar(guess()));
    }else{
        letter = QString(QChar(solution()));
    }

    p.drawText(r, Qt::AlignRight, letter);

    if (showCorrectness() == true && isSolutionRevealed() == false && guess() != ' ' && isSolutionCorrect() == false) {
        p.drawLine (rect().width(),0, 0,rect().height());
    }
}

