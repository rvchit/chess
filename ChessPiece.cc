#include "ChessPiece.hh"
#include "ChessBoard.hh"

#include "Chess.h"

namespace Student {

    // Constructor: Initializes the chess piece with its board reference, color, and starting position.
    ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column)
        : board(board), color(color), row(row), column(column) {}

    // Returns the color of the piece (either White or Black).
    Color ChessPiece::getColor() {
        return color;
    }

    // Returns the current row of the piece.
    int ChessPiece::getRow() {
        return row;
    }

    // Returns the current column of the piece.
    int ChessPiece::getColumn() {
        return column;
    }

    // Sets the position of the piece to a new row and column.
    void ChessPiece::setPosition(int newRow, int newColumn) {
        row = newRow;
        column = newColumn;
    }

    // The getType() method returns a generic type.
    // Derived classes should override this method to return their specific type.
    Type ChessPiece::getType() {
        return Type::Pawn; // pawn fallback
    }
}
