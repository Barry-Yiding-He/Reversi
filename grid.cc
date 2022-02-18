#include "grid.h"
#include "textdisplay.h"

Grid::~Grid() {
    delete td;
    delete ob;
}

void Grid::init(size_t n) {
    //initialize theGrid
    this->theGrid.clear();
     for (int i = 0; i < n; i++) {
        std::vector<Cell>v;
        theGrid.emplace_back(v);
        for (int j = 0; j < n; j++) {
            theGrid[i].emplace_back(Cell(i,j));
        }
    }
    //initialize TextDisplay
    delete this->td;
    this->td = new TextDisplay(n);
    //attach observer
    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++){
            if (i == 0 && j == 0) {
                this->theGrid[i][j].attach(&this->theGrid[i][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j]);
            } else if (i == 0 && j == n-1) {
                this->theGrid[i][j].attach(&this->theGrid[i][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j]);
            } else if (i == n-1 && j == 0) {
                this->theGrid[i][j].attach(&this->theGrid[i][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j]);
            } else if (i == n-1 && j == n-1) {
                this->theGrid[i][j].attach(&this->theGrid[i][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j]);
            } else if (i == 0 && j != 0 && j != n-1) {
                this->theGrid[i][j].attach(&this->theGrid[i][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j+1]);
            } else if (i == n-1 && j != 0 && j != n-1) {
                this->theGrid[i][j].attach(&this->theGrid[i][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j+1]);
            } else if (j == 0 && i != 0 && i != n-1) {
                this->theGrid[i][j].attach(&this->theGrid[i-1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j+1]);
            } else if (j == n-1 && i != 0 && i != n-1) {
                this->theGrid[i][j].attach(&this->theGrid[i-1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j-1]);
            } else {
                this->theGrid[i][j].attach(&this->theGrid[i-1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i-1][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i][j+1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j-1]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j]);
                this->theGrid[i][j].attach(&this->theGrid[i+1][j+1]);
            } 
            this->theGrid[i][j].attach(td);
        }
    }
}

bool Grid::isFull() const {
    int size = this->theGrid.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Info info = theGrid[i][j].getInfo();
            if (info.colour == Colour::NoColour) {
                return false;
            }
        }
    }
    return true;
}

Colour Grid::whoWon() const {
    int size = this->theGrid.size();
    int BNum = 0;
    int WNum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Info info = theGrid[i][j].getInfo();
            if (info.colour == Colour::Black) {
                BNum += 1;
            } else {
                WNum += 1;
            }
        }
    }
    if (BNum > WNum) {
        return Colour::Black;
    } else if (WNum > BNum) {
        return Colour::White;
    } else {
        return Colour::NoColour;
    }
}

void Grid::setObserver(Observer<Info, State> *ob) {
    this->ob = ob;
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
    InvalidMove invalid;
    int size = this->theGrid.size();
    if (r>= size || r < 0 || c >= size || c < 0) {
        throw invalid;
    }
    if (this->theGrid[r][c].getInfo().colour != Colour::NoColour) {
        throw invalid;
    }
    this->theGrid[r][c].setPiece(colour);
    this->theGrid[r][c].notifyObservers();
}

void Grid::toggle(size_t r, size_t c) {
    theGrid[r][c].toggle();
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
