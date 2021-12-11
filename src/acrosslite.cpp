#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "acrosslite.h"


AcrossLiteClue::AcrossLiteClue () {
    _number = 0;
    _clue   = "";
}

AcrossLiteClue::AcrossLiteClue (const int number, const string& clue) {
    _number = 0;
    _clue   = "";

    set (number, clue);
}

AcrossLiteClue::AcrossLiteClue (const AcrossLiteClue& src) {
    _number = 0;
    _clue   = "";

    *this = src;
}

AcrossLiteClue::~AcrossLiteClue () {
}

AcrossLiteClue& AcrossLiteClue::operator= (const AcrossLiteClue& rhs) {
    set (rhs.number(), rhs.clue());

    return *this;
}

bool AcrossLiteClue::operator< (const AcrossLiteClue& rhs) {
    return (number() < rhs.number());
}

bool AcrossLiteClue::operator== (const AcrossLiteClue& rhs) {
    return (number() == rhs.number());
}

ostream& operator<< (ostream& os, const AcrossLiteClue& rhs) {
    os << rhs.number() << ") " << rhs.clue();

    return os;
}

void AcrossLiteClue::set (const int number, const string& clue) {
    _number = number;
    _clue   = clue;
}

int AcrossLiteClue::number () const {
    return _number;
}

const string& AcrossLiteClue::clue () const {
    return _clue;
}



AcrossLiteGrid::AcrossLiteGrid () {
    resize (0,0);
}

AcrossLiteGrid::AcrossLiteGrid (const int nColumns, const int nRows) {
    resize(nColumns, nRows);
}

AcrossLiteGrid::AcrossLiteGrid (const AcrossLiteGrid& src) {
    *this = src;
}

AcrossLiteGrid::~AcrossLiteGrid () {
}

AcrossLiteGrid& AcrossLiteGrid::operator= (const AcrossLiteGrid& rhs) {
    _nColumns = rhs._nColumns;
    _nRows    = rhs._nRows;
    _cells    = rhs._cells;

    return *this;
}

ostream& operator<< (ostream& os, const AcrossLiteGrid& rhs) {
    for (int r = 0; r<rhs.nRows(); r++) {
        for (int c = 0; c<rhs.nColumns(); c++) {
            os << (char)rhs.cell(c,r);
        }
        os << endl;
    }


    return os;
}

void AcrossLiteGrid::resize (const int nColumns, const int nRows) {
    _nColumns = nColumns;
    _nRows    = nRows;

    _cells.resize(_nColumns * _nRows);
}

int AcrossLiteGrid::nColumns () const {
    return _nColumns;
}

int AcrossLiteGrid::nRows () const {
    return _nRows;
}

int AcrossLiteGrid::cell (const int column, const int row) const {
    int i = index (column, row);

    return _cells[i];
}

void AcrossLiteGrid::setCell (const int column, const int row, const int letter) {
    int i = index (column, row);

    _cells[i] = letter;
}

int AcrossLiteGrid::index (const int column, const int row) const {
    int i = column + (row * nColumns());

    return i;
}




AcrossLitePuzzleBase::AcrossLitePuzzleBase () {
}

AcrossLitePuzzleBase::~AcrossLitePuzzleBase () {
}

ostream& operator<< (ostream& os, const AcrossLitePuzzleBase& rhs) {
    os << "N Columns = "  << rhs.nColumns() << endl;
    os << "N Rows    = "  << rhs.nRows()    << endl << endl;
    os << "Diagram Grid"  << endl << rhs._diagram   << endl;
    os << "Solution Grid" << endl << rhs._solution  << endl;

    return os;
}

void AcrossLitePuzzleBase::load (const string& /*filename*/) {
}

void AcrossLitePuzzleBase::save (const string& /*filename*/) {
}

int AcrossLitePuzzleBase::nColumns () const {
    return _diagram.nColumns();
}

int AcrossLitePuzzleBase::nRows () const {
    return _diagram.nRows();
}

int AcrossLitePuzzleBase::diagramCell (const int column, const int row) const {
    return _diagram.cell(column, row);
}

int AcrossLitePuzzleBase::solutionCell (const int column, const int row) const {
    return _solution.cell(column, row);
}

int AcrossLitePuzzleBase::cellNumber (const int column, const int row) const {
    return (int)_numbers.cell(column, row);
}

int AcrossLitePuzzleBase::index (const int column, const int row) const {
    int i = column + (row * nColumns());

    return i;
}

void AcrossLitePuzzleBase::setDiagramCell (const int column, const int row, const int letter) {
    _diagram.setCell(column, row, letter);
}


AcrossLiteClues::const_iterator AcrossLitePuzzleBase::beginAcrossClue () const {
    return _acrossClues.begin();
}

AcrossLiteClues::const_iterator AcrossLitePuzzleBase::endAcrossClue () const {
    return _acrossClues.end();
}

AcrossLiteClues::const_iterator AcrossLitePuzzleBase::beginDownClue () const {
    return _downClues.begin();
}

AcrossLiteClues::const_iterator AcrossLitePuzzleBase::endDownClue () const {
    return _downClues.end();
}

const string& AcrossLitePuzzleBase::puzzleName () const {
    return _puzzleName;
}

const string& AcrossLitePuzzleBase::authorName () const {
    return _authorName;
}

const string& AcrossLitePuzzleBase::copyright () const {
    return _copyright;
}

const AcrossLiteGrid& AcrossLitePuzzleBase::diagram () const {
    return _diagram;
}

const AcrossLiteGrid& AcrossLitePuzzleBase::solution () const {
    return _solution;
}

const AcrossLiteGrid& AcrossLitePuzzleBase::numbers () const {
    return _numbers;
}

const AcrossLiteClues& AcrossLitePuzzleBase::acrossClues () const {
    return _acrossClues;
}

const AcrossLiteClues& AcrossLitePuzzleBase::downClues () const {
    return _downClues;
}


AcrossLitePuzPuzzle::AcrossLitePuzPuzzle () : AcrossLitePuzzleBase() {
}

AcrossLitePuzPuzzle::AcrossLitePuzPuzzle (const string& filename) : AcrossLitePuzzleBase() {
    load (filename);
}

AcrossLitePuzPuzzle::~AcrossLitePuzPuzzle () {
}

void AcrossLitePuzPuzzle::load (const string& filename) {

    _init ();

    //
    // Open the file.
    //
    int fh = ::open (filename.c_str(), O_RDONLY);
    if (fh < 0) {
        return;
    }

    //
    // Read the header.
    //
    int stat = ::read (fh, &_header, sizeof(AcrossLitePuzHeader));
    if (stat != sizeof(AcrossLitePuzHeader)) {
        return;
    }

    _solution.resize(_header._nColumns, _header._nRows);
    _diagram.resize(_header._nColumns, _header._nRows);
    _numbers.resize(_header._nColumns, _header._nRows);

    if (nColumns() < 1 || nColumns() > 25) {
        return;
    }

    if (nRows() < 1 || nRows() > 25) {
        return;
    }

    //
    // Read the the Solution and populate the Solution grid.
    //
    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            char letter;
            stat = ::read (fh, &letter, 1);
            if (stat != 1) {
                return;
            }

            _solution.setCell(c,r,letter);
        }
    }

    //
    // Read the the Diagram and populate the Diagram grid.
    //
    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            char letter;
            stat = ::read (fh, &letter, 1);
            if (stat != 1) {
                return;
            }

            if (letter == '-') letter = ' ';

            _diagram.setCell(c,r,letter);
        }
    }

    //
    // Calculate the cell numbers.
    //
    _calculateCellNumbers();

    //
    // Read puzzle name, author, and copyright.
    //
    _puzzleName = _readString(fh);
    _authorName = _readString(fh);
    _copyright  = _readString(fh);

    //
    // Read the clues.
    //
    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            int number = cellNumber (c,r);
            if (number == 0) continue;

            // Try an 'across'
            if (c == 0 || diagramCell(c-1,r) == '.') {
                string clueText = _readString(fh);
                if (clueText.size() == 0) {
                    cout << "Unexepected EOF while reading clues." << endl;
                }

                AcrossLiteClue c(number, clueText);
                _acrossClues.push_back(c);
            }

            // Try a 'down'
            if (r == 0 || diagramCell(c,r-1) == '.') {
                string clueText = _readString(fh);
                if (clueText.size() == 0) {
                    cout << "Unexepected EOF while reading clues." << endl;
                }

                AcrossLiteClue c(number, clueText);
                _downClues.push_back(c);
            }
        }
    }

    //
    // Close the file.
    //
    stat = ::close (fh);
    if (stat < 0) {
        return;
    }
}

void AcrossLitePuzPuzzle::save (const string& filename) {

    // Create the file.
    int fh = ::creat (filename.c_str(), 0666);
    if (fh < 0) {
        return;
    }

    // Write the header.
    int stat = ::write (fh, &_header, sizeof(AcrossLitePuzHeader));
    if (stat != sizeof(AcrossLitePuzHeader)) {
        return;
    }

    // Write the the Solution.
    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {

            char letter = _solution.cell(c,r);

            stat = ::write (fh, &letter, 1);
            if (stat != 1) {
                return;
            }
        }
    }

    // Write the the Diagram.
    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {

            char letter = _diagram.cell(c,r);

            if (letter == ' ') letter = '-';

            stat = ::write (fh, &letter, 1);
            if (stat != 1) {
                return;
            }
        }
    }

    // Write the puzzle name, author, and copyright.
    _writeString(fh, _puzzleName);
    _writeString(fh, _authorName);
    _writeString(fh, _copyright);

    // Write the clues.
    int acrossIndex = 0;
    int downIndex   = 0;
    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            int number = cellNumber (c,r);
            if (number == 0) continue;

            // Try an 'across'
            if (c == 0 || diagramCell(c-1,r) == '.') {
                string clueText = _acrossClues[acrossIndex].clue();
                _writeString(fh, clueText);
                acrossIndex++;
            }

            // Try a 'down'
            if (r == 0 || diagramCell(c,r-1) == '.') {
                string clueText = _downClues[downIndex].clue();
                _writeString(fh, clueText);
                downIndex++;
            }
        }
    }

    // Close the file.
    stat = ::close (fh);
    if (stat < 0) {
        return;
    }
}

void AcrossLitePuzPuzzle::copy (const AcrossLitePuzzleBase& rhs) {
    _diagram        = rhs.diagram();
    _solution       = rhs.solution();
    _numbers        = rhs.numbers();
    _acrossClues    = rhs.acrossClues();
    _downClues      = rhs.downClues();

    _puzzleName     = rhs.puzzleName();
    _authorName     = rhs.authorName();
    _copyright      = rhs.copyright();

    _header._nColumns = rhs.nColumns();
    _header._nRows    = rhs.nRows();
}


void AcrossLitePuzPuzzle::_init () {
    memset (&_header, 0, sizeof(AcrossLitePuzHeader));

    _diagram.resize(0,0);
    _solution.resize(0,0);
    _numbers.resize(0,0);

    _acrossClues.resize(0);
    _downClues.resize(0);

    _puzzleName = "";
    _authorName = "";
    _copyright  = "";
}


void AcrossLitePuzPuzzle::_calculateCellNumbers() {
    _numbers.resize(nColumns(), nRows());

    int number = 1;

    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            if (diagramCell(c,r) == '.') continue;

            if (r == 0 || c == 0) {
                _numbers.setCell(c,r,number++);

            }else if (diagramCell(c,r-1) == '.') {
                _numbers.setCell(c,r,number++);

            }else if (diagramCell(c-1,r) == '.') {
                _numbers.setCell(c,r,number++);

            }else{
                _numbers.setCell(c,r,0);
            }
        }
    }
}

string AcrossLitePuzPuzzle::_readString (int fh) {
    string s;

    while (1) {
        char letter;
        int  stat = ::read (fh, &letter, 1);
        if (stat   != 1) break;
        if (letter == 0) break;

        s += letter;
    }

    return s;
}

void AcrossLitePuzPuzzle::_writeString (int fh, const string& text) {

    char letter;

    for (unsigned int i=0; i<text.length(); i++) {
        letter = text[i];
        int  stat = ::write (fh, &letter, 1);
        if (stat   != 1) break;
    }

    letter = '\0';
    ::write (fh, &letter, 1);
}




AcrossLiteTxtPuzzle::AcrossLiteTxtPuzzle () : AcrossLitePuzzleBase() {
}

AcrossLiteTxtPuzzle::AcrossLiteTxtPuzzle (const string& filename) : AcrossLitePuzzleBase() {
    load (filename);
}

AcrossLiteTxtPuzzle::~AcrossLiteTxtPuzzle () {
}

void AcrossLiteTxtPuzzle::load (const string& filename) {

    _init ();

    // Open the file.
    int fh = ::open (filename.c_str(), O_RDONLY);
    if (fh < 0) {
        return;
    }

    // Read 'header' line.
    string str = _readString(fh);

    if (str.find("<ACROSS PUZZLE>") != 0) {
        return;
    }

    // Read 'title' line.
    str = _readString(fh);

    if (str.find("<TITLE>") != 0) {
        return;
    }

    _puzzleName = _readString(fh);

    // Read 'author' line.
    str = _readString(fh);

    if (str.find("<AUTHOR>") != 0) {
        return;
    }

    _authorName = _readString(fh);


    // Read 'copyright' line.
    str = _readString(fh);

    if (str.find("<COPYRIGHT>") != 0) {
        return;
    }

    _copyright  = _readString(fh);

    // Read 'size' line.
    str = _readString(fh);
    if (str.find("<SIZE>") != 0) {
        return;
    }

    int nr = 0;
    int nc = 0;

    str = _readString(fh);
    (void)sscanf (str.c_str(), "%dx%d", &nr, &nc);
    if (nr == 0 || nc == 0) {
        return;
    }

    _diagram.resize(nc,nr);
    _solution.resize(nc,nr);
    _numbers.resize(nc,nr);

    if (nColumns() < 1 || nColumns() > 25) {
        return;
    }

    if (nRows() < 1 || nRows() > 25) {
        return;
    }

    // Read the the Solution and populate the Solution grid.
    str = _readString(fh);
    if (str.find("<GRID>") != 0) {
        return;
    }

    for (int r=0; r<nRows(); r++) {
        str = _readString(fh);
        for (int c=0; c<nColumns(); c++) {
            char letter = str[c];

            _solution.setCell(c,r,letter);

            if (letter == '.') {
                _diagram.setCell(c,r, '.');
            }else{
                _diagram.setCell(c,r, ' ');
            }
        }
    }

    // Calculate the cell numbers.
    _calculateCellNumbers();

    // Read the 'across' clues.
    str = _readString(fh);
    if (str.find("<ACROSS>") != 0) {
        return;
    }

    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            int number = cellNumber (c,r);
            if (number == 0) continue;

            // Try an 'across'
            if (c == 0 || diagramCell(c-1,r) == '.') {
                string clueText = _readString(fh);
                if (clueText.size() == 0) {
                    cout << "Unexepected EOF while reading clues." << endl;
                }

                AcrossLiteClue c(number, clueText);
                _acrossClues.push_back(c);
            }
        }
    }

    // Read the 'down' clues.
    str = _readString(fh);
    if (str.find("<DOWN>") != 0) {
        return;
    }

    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            int number = cellNumber (c,r);
            if (number == 0) continue;

            // Try a 'down'
            if (r == 0 || diagramCell(c,r-1) == '.') {
                string clueText = _readString(fh);
                if (clueText.size() == 0) {
                    cout << "Unexepected EOF while reading clues." << endl;
                }

                AcrossLiteClue c(number, clueText);
                _downClues.push_back(c);
            }
        }
    }

    // Close the file.
    int stat = ::close (fh);
    if (stat < 0) {
        return;
    }
}

void AcrossLiteTxtPuzzle::save (const string& /*filename*/) {
    cout << "Sorry, saving to .txt format is not implemented yet." << endl;
}

void AcrossLiteTxtPuzzle::copy (const AcrossLitePuzzleBase& /*rhs*/) {
    cout << "Sorry, copying to .txt format is not implemented yet." << endl;
}

void AcrossLiteTxtPuzzle::_init () {
    _diagram.resize(0,0);
    _solution.resize(0,0);
    _numbers.resize(0,0);

    _acrossClues.resize(0);
    _downClues.resize(0);

    _puzzleName = "";
    _authorName = "";
    _copyright  = "";
}


void AcrossLiteTxtPuzzle::_calculateCellNumbers() {
    _numbers.resize(nColumns(), nRows());

    int number = 1;

    for (int r=0; r<nRows(); r++) {
        for (int c=0; c<nColumns(); c++) {
            if (diagramCell(c,r) == '.') continue;

            if (r == 0 || c == 0) {
                _numbers.setCell(c,r,number++);

            }else if (diagramCell(c,r-1) == '.') {
                _numbers.setCell(c,r,number++);

            }else if (diagramCell(c-1,r) == '.') {
                _numbers.setCell(c,r,number++);

            }else{
                _numbers.setCell(c,r,0);
            }
        }
    }
}

string AcrossLiteTxtPuzzle::_readString (int fh) {
    string s;

    while (1) {
        char letter;
        int  stat = ::read (fh, &letter, 1);
        if (stat   !=    1) break;
        if (letter ==    0) break;
        if (letter == '\n') break;
        if (letter == '\t') continue;

        s += letter;
    }

    return s;
}

