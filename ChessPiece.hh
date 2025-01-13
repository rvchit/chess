#ifndef _CHESSPIECE_H__
#define _CHESSPIECE_H__

#include "Chess.h"

namespace Student {
    class ChessBoard;

    class ChessPiece {
    protected:
        ChessBoard &board;  // Reference to the board to which the piece belongs
        Color color;        // Color of the piece (White or Black)
        int row;            // Current row of the piece
        int column;         // Current column of the piece

    public:
        /**
         * @brief
         * Constructor for ChessPiece.
         * @param board
         * The board to which the piece belongs.
         * @param color
         * The colour of the piece.
         * @param row
         * Starting row of the piece.
         * @param column
         * Starting column of the piece.
         */
        ChessPiece(ChessBoard &board, Color color, int row, int column);

        /**
         * @brief
         * Default destructor for ChessPiece.
         * Does nothing special.
         */
        virtual ~ChessPiece() {}

        /**
         * @return
         * Colour of piece.
         */
        Color getColor();

        /**
         * @return
         * Type of piece.
         */
        virtual Type getType();

        /**
         * @return
         * Current row number of piece.
         */
        int getRow();

        /**
         * @return
         * Current column number of piece.
         */
        int getColumn();

        /**
         * @brief Sets row and column numbers of piece.
         * @param row
         * The new row number of the piece.
         * @param column
         * The new column number of the piece.
         */
        virtual void setPosition(int row, int column);

        /**
         * @brief
         * A pure virtual method to be implemented in the derived classes.
         * Determines if movement from current position to new position is valid.
         * @param toRow
         * The row of the destination position.
         * @param toColumn
         * The column of the destination position.
         * @return
         * A boolean indicating if a move from current to destination is valid.
         */
        virtual bool canMoveToLocation(int toRow, int toColumn) = 0;

        /**
         * @brief
         * A pure virtual method to be implemented in the derived classes.
         * Returns a unicode string representation of the piece.
         * Refer to this link https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
         * for more information on unicode representation of chess piece.
         * @return
         * A unicode representation of the piece.
         */
        virtual const char *toString() = 0;
    };
}

#endif
