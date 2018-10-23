#ifndef AcrossLite_H
#define AcrossLite_H

using namespace std;

#include <vector>
#include <string>
#include <iostream>

class AcrossLiteClue {
    public:
        enum Orientation {
               Unknown = 0,
               Across  = 1,
               Down    = 2
        };

        AcrossLiteClue ();
        AcrossLiteClue (const int number, const string& clue);
        AcrossLiteClue (const AcrossLiteClue& src);
       ~AcrossLiteClue ();

        AcrossLiteClue& operator=  (const AcrossLiteClue& rhs);
        bool            operator<  (const AcrossLiteClue& rhs);
        bool            operator== (const AcrossLiteClue& rhs);
        friend ostream& operator<< (ostream& os, const AcrossLiteClue& rhs);

        void            set        (const int number, const string& clue);
        int             number     () const;
        const string&   clue       () const;

    private:
        int             _number;
        string          _clue;
};

typedef vector<AcrossLiteClue> AcrossLiteClues;

class AcrossLiteGrid {
    public:
        AcrossLiteGrid ();
        AcrossLiteGrid (const int nColumns, const int nRows);
        AcrossLiteGrid (const AcrossLiteGrid& src);
       ~AcrossLiteGrid ();

        AcrossLiteGrid& operator=  (const AcrossLiteGrid& rhs);
        friend ostream& operator<< (ostream& os, const AcrossLiteGrid& rhs);

        void            resize     (const int nColumns, const int nRows);
        int             nColumns   () const;
        int             nRows      () const;

        int             cell       (const int column, const int row) const;
        void            setCell    (const int column, const int row, const int letter);
        int             index      (const int column, const int row) const;

    private:
        int             _nColumns;
        int             _nRows;
        vector<int>     _cells;
};

class AcrossLitePuzzleBase {
    public:
        AcrossLitePuzzleBase ();
        virtual ~AcrossLitePuzzleBase ();

        friend ostream&         operator<<      (ostream& os, const AcrossLitePuzzleBase& rhs);

        virtual void                        load            (const string& filename);
        virtual void                        save            (const string& filename);

        int                                 nColumns        () const;
        int                                 nRows           () const;

        int                                 diagramCell     (const int column, const int row) const;
        int                                 solutionCell    (const int column, const int row) const;
        int                                 cellNumber      (const int column, const int row) const;
        int                                 index           (const int column, const int row) const;
        void                                setDiagramCell  (const int column, const int row, const int letter);

        AcrossLiteClues::const_iterator     beginAcrossClue () const;
        AcrossLiteClues::const_iterator     endAcrossClue   () const;

        AcrossLiteClues::const_iterator     beginDownClue   () const;
        AcrossLiteClues::const_iterator     endDownClue     () const;

        const string&                       puzzleName      () const;
        const string&                       authorName      () const;
        const string&                       copyright       () const;

        const AcrossLiteGrid&               diagram         () const;
        const AcrossLiteGrid&               solution        () const;
        const AcrossLiteGrid&               numbers         () const;
        const AcrossLiteClues&              acrossClues     () const;
        const AcrossLiteClues&              downClues       () const;

    protected:
        AcrossLiteGrid      _diagram;
        AcrossLiteGrid      _solution;
        AcrossLiteGrid      _numbers;
        AcrossLiteClues     _acrossClues;
        AcrossLiteClues     _downClues;

        string              _puzzleName;
        string              _authorName;
        string              _copyright;
};

struct AcrossLitePuzHeader {
    char                _junk1[44];
    unsigned char       _nColumns;
    unsigned char       _nRows;
    char                _junk2[6];
};

class AcrossLitePuzPuzzle : public AcrossLitePuzzleBase {
    public:
        AcrossLitePuzPuzzle ();
        AcrossLitePuzPuzzle (const string& filename);
       ~AcrossLitePuzPuzzle ();

        void                load                  (const string& filename);
        void                save                  (const string& filename);
        void                copy                  (const AcrossLitePuzzleBase& puzzle);

    private:
        void                _init                 ();
        void                _calculateCellNumbers ();
        string              _readString           (int fh);
        void                _writeString          (int fh, const string& text);

        AcrossLitePuzHeader _header;
};

class AcrossLiteTxtPuzzle : public AcrossLitePuzzleBase {
    public:
        AcrossLiteTxtPuzzle ();
        AcrossLiteTxtPuzzle (const string& filename);
       ~AcrossLiteTxtPuzzle ();

        void                load                  (const string& filename);
        void                save                  (const string& filename);
        void                copy                  (const AcrossLitePuzzleBase& puzzle);

    private:
        void                _init                 ();
        void                _calculateCellNumbers ();
        string              _readString           (int fh);

};

#endif

