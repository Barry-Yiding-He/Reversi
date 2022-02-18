#include "cell.h"

Cell::Cell(size_t r, size_t c): r{r}, c{c} {}

void Cell::setPiece(Colour colour) {
    this->colour = colour;
    State state = {StateType::NewPiece, colour, Direction::W};
    this->setState(state);
}

void Cell::toggle() { // Toggles my colour.
    if (this->colour == Colour::Black) {
        this->colour = Colour::White;
    } else {
        this->colour = Colour::Black;
    }
} 

Info Cell::getInfo() const {
    Info result={this->r, this->c, this->colour};
    return result;
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    Info info = whoFrom.getInfo();
    State state = whoFrom.getState();
    int column = info.col;
    int row = info.row;
    //NEWPIECE
    if (state.type == StateType::NewPiece && colour != Colour::NoColour && info.colour != colour) {
        if (column == c && row == r - 1) {
            State temps = {StateType ::Relay, info.colour, Direction::N};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c && row == r + 1) {
            State temps = {StateType ::Relay, info.colour, Direction::S};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c - 1 && row == r) {
            State temps = {StateType ::Relay, info.colour, Direction::W};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c + 1 && row == r) {
            State temps = {StateType ::Relay, info.colour, Direction::E};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c + 1 && row == r + 1) {
            State temps = {StateType ::Relay, info.colour, Direction::SE};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c + 1 && row == r - 1) {
            State temps = {StateType ::Relay, info.colour, Direction::NE};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c - 1 && row == r + 1) {
            State temps = {StateType ::Relay, info.colour, Direction::SW};
            this->setState(temps);
            this->notifyObservers();
        } else if (column == c - 1 && row == r - 1) {
            State temps = {StateType ::Relay, info.colour, Direction::NW};
            this->setState(temps);
            this->notifyObservers();
        }
    } else if (state.type == StateType::Relay) { //RELAY
        if (column == c && row == r - 1) {
            if (state.direction == Direction::N && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::N};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::N && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::S};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c && row == r + 1) {
            if (state.direction == Direction::S && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::S};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::S && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::N};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c - 1 && row == r) {
            if (state.direction == Direction::W && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::W};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::W && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::E};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c + 1 && row == r) {
            if (state.direction == Direction::E && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::E};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::E && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::W};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c + 1 && row == r + 1) {
            if (state.direction == Direction::SE && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::SE};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::SE && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::NW};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c + 1 && row == r - 1) {
            if (state.direction == Direction::NE && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::NE};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::NE && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::SW};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c - 1 && row == r - 1) {
            if (state.direction == Direction::NW && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::NW};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::NW && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::SE};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c - 1 && row == r + 1) {
            if (state.direction == Direction::SW && info.colour == colour) {
                State temps = {StateType::Relay, info.colour, Direction::SW};
                this->setState(temps);
                this->notifyObservers();
            } else if (state.direction == Direction::SW && info.colour != colour && colour != Colour::NoColour) {
                State temps = {StateType::Reply, colour, Direction ::NE};
                this->setState(temps);
                this->notifyObservers();
            }
        }
    } else if (state.type == StateType::Reply && info.colour != colour && colour != Colour::NoColour) { // REPLY
        if  (info.col == c && info.row == r - 1) {
            if (state.direction == Direction::N) {
                this->toggle();
                State temps = {StateType::Reply, info.colour, Direction::N};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c && row == r + 1) {
            if (state.direction == Direction::S) {
                this->toggle();
                State temps = {StateType ::Reply, info.colour, Direction ::S};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c - 1 && row == r) {
            if (state.direction == Direction::W) {
                this->toggle();
                State temps = {StateType::Reply, info.colour, Direction::W};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c + 1 && row == r) {
            if (state.direction == Direction::E) {
                this->toggle();
                State temps = {StateType::Reply, info.colour, Direction::E};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c + 1 && row == r + 1) {
            if (state.direction == Direction::SE) {
                this->toggle();
                State temps = {StateType::Relay, info.colour, Direction::SE};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c + 1 && row == r - 1) {
            if (state.direction == Direction::NE) {
                this->toggle();
                State temps = {StateType::Reply, info.colour, Direction::NE};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c-1 && row == r+1) {
            if (state.direction == Direction::SW) {
                this->toggle();
                State temps = {StateType::Reply, info.colour, Direction::SW};
                this->setState(temps);
                this->notifyObservers();
            }
        } else if (column == c - 1 && row == r - 1) {
            if (state.direction == Direction::NW) {
                this->toggle();
                State temps = {StateType::Reply, info.colour, Direction::NW};
                this->setState(temps);
                this->notifyObservers();
            }
        }
    }
}

