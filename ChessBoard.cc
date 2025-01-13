#include "ChessBoard.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include "PawnPiece.hh"
#include <iostream>

using namespace Student;

// constructor
// Initialization List: The constructor uses an initialization list to set up numRows, numCols, and board.
// The board is initialized as a 2D vector of size numRow x numCol, with each cell set to nullptr.
ChessBoard::ChessBoard(int numRow, int numCol)
    : numRows(numRow), numCols(numCol), 
      board(numRow, std::vector<ChessPiece*>(numCol, nullptr)) {
    std::cout << "ChessBoard created with " << numRow << " rows and " << numCol << " columns.\n";
}


// Destructor
ChessBoard::~ChessBoard() {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            delete board[row][col];  // Delete each piece if it exists
        }
    }
    std::cout << "ChessBoard destroyed and memory cleaned up.\n";
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
    // Check if the position is within bounds
    if (startRow < 0 || startRow >= numRows || startColumn < 0 || startColumn >= numCols) {
        std::cerr << "Error: Invalid position (" << startRow << ", " << startColumn << ").\n";
        return;
    }

    // Delete any existing piece at the specified position to avoid memory leaks
    delete board[startRow][startColumn];
    board[startRow][startColumn] = nullptr;

    // Create a new piece based on the type
    ChessPiece* piece = nullptr;
    switch (ty) {
        case Rook:
            piece = new RookPiece(*this, col, startRow, startColumn);
            break;
        case Bishop:
            piece = new BishopPiece(*this, col, startRow, startColumn);
            break;
        case King:
            piece = new KingPiece(*this, col, startRow, startColumn);
            break;
        case Pawn:
            piece = new PawnPiece(*this, col, startRow, startColumn);
            break;
        default:
            std::cerr << "Error: Unknown piece type.\n";
            return;
    }

    // Place the newly created piece on the board
    board[startRow][startColumn] = piece;
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    // Bounds checking
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols ||
        toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) {
        return false;
    }

    ChessPiece* piece = board[fromRow][fromColumn];
    if (piece && piece->getColor() == turn && isValidMove(fromRow, fromColumn, toRow, toColumn)) {
        // Check if the target position has an enemy piece
        if (isPieceUnderThreat(toRow, toColumn)) {
            // Delete the threatened piece to capture it
            delete board[toRow][toColumn];
            board[toRow][toColumn] = nullptr;
        }

        // Move the piece
        board[toRow][toColumn] = piece;
        board[fromRow][fromColumn] = nullptr;
        piece->setPosition(toRow, toColumn);

        // Toggle turn
        turn = (turn == White) ? Black : White;
        return true;
    }
    return false;
}
    //    return (not "Color" turn yet)



// Function to validate a move from (fromRow, fromColumn) to (toRow, toColumn)
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    // Step 1: Check if from/to coordinates are within board boundaries.
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols ||
        toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) {
        return false;
    }

    // Step 2: Check if the destination is the same as the starting position.
    if (fromRow == toRow && fromColumn == toColumn) {
        return false;
    }


    // Step 3: Check if there is a piece at the starting location.
    ChessPiece* piece = board[fromRow][fromColumn];
    if (piece == nullptr) {
        return false;
    }


    // Step 4: Check if the move is valid for the piece type.
    if (!piece->canMoveToLocation(toRow, toColumn)) {
        return false;
    }

    // Step 5: Check if the destination square is occupied by a piece of the same color.
    ChessPiece* targetPiece = board[toRow][toColumn];
    if (targetPiece != nullptr && targetPiece->getColor() == piece->getColor()) {
        return false;
    }

    // step 6:  Simulate the move to check if it puts the King in check
    board[toRow][toColumn] = piece;
    board[fromRow][fromColumn] = nullptr;
    piece->setPosition(toRow, toColumn);

    bool inCheck = isKingInCheck(piece->getColor());

    // Revert the move
    board[fromRow][fromColumn] = piece;
    board[toRow][toColumn] = targetPiece;
    piece->setPosition(fromRow, fromColumn);

    // Return false if the move puts the King in check
    return !inCheck;

}

bool ChessBoard::isPieceUnderThreat(int row, int column) {

    // Bounds checking
    if (row < 0 || row >= numRows || column < 0 || column >= numCols) {
        return false;
    }

    // Check if the piece at (row, column) exists
    if (!board[row][column]) {
        return false;
    }

    Color targetColor = board[row][column]->getColor();

    // Iterate over all board positions to check if any opposing piece can move to (row, column)
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece* piece = board[r][c];
            if (piece && piece->getColor() != targetColor) {
                // Check if this piece can move to the given (row, column)
                if (piece->canMoveToLocation(row, column)) {
                    return true; // A piece is threatening the target location
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isKingInCheck(Color color) {
    // Find the King of the given color
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece && piece->getType() == Type::King && piece->getColor() == color) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1) {
        std::cerr << "Error: King not found on the board.\n";
        return false;
    }

    // Check if any opposing piece can move to the King's position
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            ChessPiece* piece = board[row][col];
            if (piece && piece->getColor() != color && piece->canMoveToLocation(kingRow, kingCol)) {
                return true;
            }
        }
    }
    return false;
}


std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}


