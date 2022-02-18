#include "textdisplay.h"
#include "cell.h"

TextDisplay::TextDisplay(int n): gridSize{n} {
    std::vector<char>row(n, '-');
    std::vector<std::vector<char>>all(n, row);
    theDisplay = all;
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    Info info = whoNotified.getInfo();
    if (info.colour == Colour::Black) {
        theDisplay[info.row][info.col] = 'B';
    } else if (info.colour == Colour::White) {
        theDisplay[info.row][info.col] = 'W';
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    int size = td.gridSize;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j != size - 1) {
                out << td.theDisplay[i][j];
            } else {
                out << td.theDisplay[i][j] << std::endl;
            }
        }
    }
   return out;
}

