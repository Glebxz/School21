package service

import (
	"xo/internal/domain"

	"github.com/google/uuid"
)

type Repository interface {
	AddNewGame(game domain.Game) error
	SaveGame(game domain.Game) error
	GetGame(gameID uuid.UUID) (domain.Game, bool)
	GetAvaliableGames() []domain.Game
	GetFinishedGames(userID uuid.UUID) []domain.Game
	AddUser(login, password string, userID uuid.UUID) error
	GetUser(login, password string) (uuid.UUID, error)
	GetUserInfo(userID uuid.UUID) domain.UserInfo
	GetLeaderboard(n int) []struct {
		PlayerID uuid.UUID
		Ratio    float32
	}
}
