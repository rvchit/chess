#ifndef _KINGPIECE_H__
#define _KINGPIECE_H__

#include "ChessPiece.hh"
#include <string>

namespace Student {
    class KingPiece : public ChessPiece {
    public:
        // Constructor
        KingPiece(ChessBoard &board, Color color, int row, int column);

        // Override pure virtual functions from ChessPiece
        const char *toString() override;
        bool canMoveToLocation(int toRow, int toColumn) override;
        Type getType() override;
    };
}

#endif
