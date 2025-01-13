#include "BishopPiece.hh"
#include "ChessBoard.hh"
#include "Chess.h"
#include <cmath>  // For std::abs

namespace Student {

    BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, row, column) {}

    const char* BishopPiece::toString() {
        return (getColor() == White) ? "\u2657" : "\u265D";  // Unicode for white or black bishop
    }

    bool BishopPiece::canMoveToLocation(int toRow, int toColumn) {
        int currentRow = getRow();
        int currentColumn = getColumn();

        // Bishops move diagonally.
        if (std::abs(currentRow - toRow) != std::abs(currentColumn - toColumn)) {
            return false;  // Not a valid diagonal move.
        }

        // Check for obstacles in the path (not jumping over other pieces).
        int rowStep = (toRow - currentRow) / std::abs(toRow - currentRow);
        int colStep = (toColumn - currentColumn) / std::abs(toColumn - currentColumn);

        int checkRow = currentRow + rowStep;
        int checkCol = currentColumn + colStep;

        // Traverse along the diagonal to check for obstacles.
        while (checkRow != toRow || checkCol != toColumn) {
            if (board.getPiece(checkRow, checkCol) != nullptr) {
                return false;  // Obstacle in the path.
            }
            checkRow += rowStep;
            checkCol += colStep;
        }

        // Check the target square for capture.
        ChessPiece* targetPiece = board.getPiece(toRow, toColumn);
        if (targetPiece == nullptr) {
            return true;  // The square is empty, valid move.
        } else if (targetPiece->getColor() != getColor()) {
            return true;  // The square contains an opponent's piece, valid capture.
        }

        return false;  // The square contains a piece of the same color, invalid move.
    }


    Type BishopPiece::getType() {
        return Type::Bishop;
    }
}
