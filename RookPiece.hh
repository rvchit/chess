#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"
#include <string>

namespace Student {
    class RookPiece : public ChessPiece {
    public:
        // Constructor
        RookPiece(ChessBoard &board, Color color, int row, int column);
        
        // Override pure virtual functions from ChessPiece
        const char *toString() override;
        bool canMoveToLocation(int toRow, int toColumn) override;
        Type getType() override;
    };
}

#endif
