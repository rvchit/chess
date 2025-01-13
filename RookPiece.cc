#include "RookPiece.hh"
#include "ChessBoard.hh"

namespace Student {

    RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {}

    const char* RookPiece::toString() {
        return (getColor() == White) ? "\u2656" : "\u265C";  // Unicode for white or black rook
    }

    bool RookPiece::canMoveToLocation(int toRow, int toColumn) {
        int currentRow = getRow();
        int currentColumn = getColumn();

        // Rooks move either horizontally or vertically.  either row or column has to be the same 
        if (currentRow != toRow && currentColumn != toColumn) {
            return false;  // Not a valid rook move.
        }

        // Check for obstacles in the path (not jumping over other pieces).
        int rowStep = (toRow - currentRow) != 0 ? (toRow - currentRow) / std::abs(toRow - currentRow) : 0;
        int colStep = (toColumn - currentColumn) != 0 ? (toColumn - currentColumn) / std::abs(toColumn - currentColumn) : 0;

        int checkRow = currentRow + rowStep;
        int checkCol = currentColumn + colStep;

        // Traverse along the path to check for obstacles.
        while (checkRow != toRow || checkCol != toColumn) {
            if (board.getPiece(checkRow, checkCol) != nullptr) {
                return false;  // Obstacle in the path.
            }
            checkRow += rowStep;
            checkCol += colStep;
        }

        return true;
    }

    Type RookPiece::getType() {
        return Rook;
    }
}
