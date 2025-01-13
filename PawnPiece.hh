#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {
    public:
        // Constructor
        PawnPiece(ChessBoard &board, Color color, int row, int column);
        
        // Override pure virtual functions from ChessPiece
        const char *toString() override;
        bool canMoveToLocation(int toRow, int toColumn) override;
        Type getType() override;
    };
}

#endif
