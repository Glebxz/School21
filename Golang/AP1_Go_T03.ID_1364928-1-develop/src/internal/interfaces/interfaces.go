package interfaces

import (
	"xo/internal/domain"
)

type Repository interface {
	Save(game *domain.Game)
	Get(uuid string) (*domain.Game, bool)
}

type Service interface {
	AddNewGame(uuid string) error
	ValidateBoard(uuid string, newBoard domain.Board) bool
	CheckGameOver(uuid string) int
	GetNextTurn(uuid string, newBoard domain.Board) (domain.Board, error)
}
