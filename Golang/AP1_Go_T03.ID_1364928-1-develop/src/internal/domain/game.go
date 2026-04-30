package domain

import (
	"errors"
	"time"

	"github.com/google/uuid"
)

var (
	ErrInvalidTurn      = errors.New("invalid turn")
	ErrCellOccupied     = errors.New("cell is already occupied")
	ErrGameOver         = errors.New("game already finished")
	ErrWrongPlayerTurn  = errors.New("not your turn")
	ErrWaitSecondPlayer = errors.New("no second player")
)

type Cell int

const (
	Empty Cell = 0
	X     Cell = 1
	O     Cell = -1
)

type GameState int

const (
	InProgress GameState = iota
	WinX
	WinO
	Draw
)

type Board [3][3]Cell

type Game struct {
	GameID uuid.UUID
	Board  Board

	IsAI bool

	PlayerXID uuid.UUID
	PlayerOID uuid.UUID

	CurrentTurn Cell
	State       GameState
	Winner      uuid.UUID
	StartTime   time.Time
}

func (game *Game) MakeMove(i, j int, player uuid.UUID) error {
	if i < 0 || i > 2 || j < 0 || j > 2 {
		return ErrInvalidTurn
	}

	if game.State == WinX || game.State == WinO || game.State == Draw {
		return ErrGameOver
	}

	if player != game.PlayerXID && player != game.PlayerOID {
		return ErrWrongPlayerTurn
	}

	if player == game.PlayerXID && game.CurrentTurn != X {
		return ErrWrongPlayerTurn
	}

	if player == game.PlayerOID && game.CurrentTurn != O {
		return ErrWrongPlayerTurn
	}

	if game.Board[i][j] != Empty {
		return ErrCellOccupied
	}

	game.Board[i][j] = game.CurrentTurn
	game.CurrentTurn = -game.CurrentTurn

	game.State = game.Board.CheckGameState()
	game.UpdateWinner()

	return nil
}

func (board Board) CheckGameState() GameState {
	for i := range board {
		if board[i][0] != Empty && board[i][0] == board[i][1] && board[i][0] == board[i][2] {
			if board[i][0] == X {
				return WinX
			} else {
				return WinO
			}
		}
	}

	for j := range board[0] {
		if board[0][j] != Empty && board[0][j] == board[1][j] && board[0][j] == board[2][j] {
			if board[0][j] == X {
				return WinX
			} else {
				return WinO
			}
		}
	}

	if board[0][0] != Empty && board[0][0] == board[1][1] && board[0][0] == board[2][2] {
		if board[0][0] == X {
			return WinX
		} else {
			return WinO
		}
	}

	if board[0][2] != Empty && board[0][2] == board[1][1] && board[0][2] == board[2][0] {
		if board[0][2] == X {
			return WinX
		} else {
			return WinO
		}
	}

	for i := range board {
		for j := range board[i] {
			if board[i][j] == Empty {
				return InProgress
			}
		}
	}

	return Draw
}

func (game *Game) UpdateWinner() {
	if game.State == WinX {
		game.Winner = game.PlayerXID
	}
	if game.State == WinO {
		game.Winner = game.PlayerOID
	}
	if game.State == Draw {
		game.Winner = uuid.Nil
	}
}
