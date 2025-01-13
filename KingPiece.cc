#include "KingPiece.hh"
#include "ChessBoard.hh"
#include <cmath>  // For std::abs

namespace Student {

    // Constructor
    KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {}

    // Returns a Unicode character for a King
    const char *KingPiece::toString() {
        return (getColor() == White) ? "\u2654" : "\u265A";  // Unicode for white or black king
    }

    // Defines the movement rules for a King
    bool KingPiece::canMoveToLocation(int toRow, int toColumn) {
        int currentRow = getRow();
        int currentColumn = getColumn();

        // A king can move exactly one square in any direction.
        int rowDifference = std::abs(currentRow - toRow);
        int columnDifference = std::abs(currentColumn - toColumn);

        // Check if the move is within a single square in any direction
        if ((rowDifference <= 1) && (columnDifference <= 1)) {
            // Check if the destination square is empty or contains an opponent's piece.
            ChessPiece *targetPiece = board.getPiece(toRow, toColumn);
            if (targetPiece == nullptr || targetPiece->getColor() != getColor()) {
                return true;
            }
        }

        return false;
    }

    // Returns the type of the piece (King)
    Type KingPiece::getType() {
        return Type::King;
    }
}
