#include <cassert>
#include <iostream>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

void test_part1_4x4_1() {
    // Create a 4x4 chessboard
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);  // White Rook at (3, 2)
    sBoard.createChessPiece(Black, Bishop, 1, 3);  // Black Bishop at (1, 3)
    sBoard.createChessPiece(Black, Rook, 1, 1);  // Black Rook at (1, 1)
    sBoard.createChessPiece(White, Rook, 2, 3);  // White Rook at (2, 3)

    // Test that pieces are created at the correct positions
    assert(sBoard.getPiece(3, 2)->getType() == Type::Rook);
    assert(sBoard.getPiece(3, 2)->getColor() == White);
    assert(sBoard.getPiece(1, 3)->getType() == Type::Bishop);
    assert(sBoard.getPiece(1, 3)->getColor() == Black);

    // Test valid Rook movements
    assert(sBoard.isValidMove(3, 2, 3, 0)); // Move horizontally left (valid)
    assert(sBoard.isValidMove(3, 2, 0, 2)); // Move vertically up (valid)

    // Test invalid Rook movements
    assert(!sBoard.isValidMove(3, 2, 2, 1)); // Not a valid Rook move (diagonal)
    assert(!sBoard.isValidMove(3, 2, 3, 4)); // Out of board bounds

    // Test Bishop movements
    assert(sBoard.isValidMove(1, 3, 0, 2)); // Valid diagonal move (top-left)
    assert(sBoard.isValidMove(1, 3, 2, 2)); // Valid diagonal move (bottom-left)

    // Test invalid Bishop movements
    assert(!sBoard.isValidMove(1, 3, 1, 1)); // Not a diagonal move

    // Test for move to same position (invalid for all pieces)
    assert(!sBoard.isValidMove(1, 3, 1, 3));

    // Output if all tests pass
    std::cout << "All Part 1 tests passed successfully." << std::endl;
}

int main() {
    test_part1_4x4_1(); // Call the test function
    return EXIT_SUCCESS;
}
