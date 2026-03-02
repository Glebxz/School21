package service

import (
	"xo/internal/domain"
)

type move struct {
	i, j int
}

func minMax(board domain.Board, turn int) (domain.Board, int) {
	check := checkGameOver(board)
	if check == domain.O {
		return board, 1
	} else if check == domain.X {
		return board, -1
	} else if check == domain.Draw {
		return board, 0
	}

	moves := getMoves(board)
	var bestBoard domain.Board

	if turn == domain.O {
		bestScore := -100
		for _, move := range moves {
			curBoard := board
			curBoard[move.i][move.j] = domain.O

			_, curScore := minMax(curBoard, domain.X)

			if curScore > bestScore {
				bestScore = curScore
				bestBoard = curBoard
			}
		}
		return bestBoard, bestScore

	} else {
		bestScore := 100
		for _, move := range moves {
			curBoard := board
			curBoard[move.i][move.j] = domain.X

			_, curScore := minMax(curBoard, domain.O)

			if curScore < bestScore {
				bestScore = curScore
				bestBoard = curBoard

			}
		}
		return bestBoard, bestScore
	}
}

func getMoves(board domain.Board) []move {
	moves := []move{}
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if board[i][j] == domain.Empty {
				moves = append(moves, move{i, j})
			}
		}
	}
	return moves
}
