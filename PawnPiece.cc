#include "PawnPiece.hh"
#include "ChessBoard.hh"
#include <cmath>  // For std::abs

namespace Student {

    PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {}

    const char* PawnPiece::toString() {
        return (getColor() == White) ? "\u2659" : "\u265F";  // Unicode for white or black pawn
    }

    bool PawnPiece::canMoveToLocation(int toRow, int toColumn) {
        int currentRow = getRow();
        int currentColumn = getColumn();
        int rowDirection = (getColor() == White) ? -1 : 1;  // White moves down, black moves up.
        int homeRow = (getColor() == White) ? board.getNumRows() - 2 : 1;

        // Check for forward move.
        if (toColumn == currentColumn) {
            // Move forward one square if empty.
            if (toRow == currentRow + rowDirection && board.getPiece(toRow, toColumn) == nullptr) {
                return true;
            }

            // Move forward two squares from home row.
            if (currentRow == homeRow && toRow == currentRow + 2 * rowDirection &&
                board.getPiece(toRow, toColumn) == nullptr &&
                board.getPiece(currentRow + rowDirection, toColumn) == nullptr) {
                return true;
            }
        }

        // Check for diagonal capture.
        if (std::abs(toColumn - currentColumn) == 1 && toRow == currentRow + rowDirection) {
            ChessPiece* targetPiece = board.getPiece(toRow, toColumn);
            if (targetPiece != nullptr && targetPiece->getColor() != getColor()) {
                return true;  // Capture opponent's piece.
            }
        }

        return false;
    }


    Type PawnPiece::getType() {
        return Pawn;
    }
}
