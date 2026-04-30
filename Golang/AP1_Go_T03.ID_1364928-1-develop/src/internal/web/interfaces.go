package web

import (
	"xo/internal/domain"

	"github.com/google/uuid"
)

type GameService interface {
	AddNewGame(userID uuid.UUID, isAI bool) domain.Game
	GetAvaliableGames() []domain.Game
	GetFinishedGames(userID uuid.UUID) []domain.Game
	AddPlayerToGame(userID, gameID uuid.UUID) (domain.Game, error)
	MakeTurn(userID, gameID uuid.UUID, i, j int) error
	RefreshGame(gameID uuid.UUID) (domain.Game, error)
	GetLeaderboard(n int) []struct {
		PlayerID uuid.UUID
		Ratio    float32
	}
}

type UserService interface {
	Registration(login, password string) error
	Authorization(login, password string) (uuid.UUID, error)
	GetUserInfo(userID uuid.UUID) (domain.UserInfo, error)
}
