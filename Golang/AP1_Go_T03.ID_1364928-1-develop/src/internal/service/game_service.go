package service

import (
	"errors"
	"time"
	"xo/internal/domain"

	"github.com/google/uuid"
)

var (
	ErrNoAcces  = errors.New("you are not a host of this game")
	ErrNoGame   = errors.New("game with this uuid does not exist")
	ErrGameFull = errors.New("game already full")
)

type GameService struct {
	repo Repository
}

func NewGameService(repo Repository) *GameService {
	return &GameService{repo: repo}
}

func (gs *GameService) AddNewGame(userID uuid.UUID, isAI bool) domain.Game {
	newGame := domain.Game{
		GameID: uuid.New(),

		IsAI: isAI,

		PlayerXID: userID,

		CurrentTurn: domain.X,
		State:       domain.InProgress,
		Winner:      uuid.Nil,
		StartTime:   time.Now(),
	}

	gs.repo.AddNewGame(newGame)

	return newGame
}

func (gs *GameService) GetAvaliableGames() []domain.Game {
	return gs.repo.GetAvaliableGames()
}

func (gs *GameService) GetFinishedGames(userID uuid.UUID) []domain.Game {
	return gs.repo.GetFinishedGames(userID)
}

func (gs *GameService) AddPlayerToGame(userID, gameID uuid.UUID) (domain.Game, error) {
	game, ok := gs.repo.GetGame(gameID)

	if !ok {
		return game, ErrNoGame
	}

	if game.PlayerOID != uuid.Nil || game.IsAI {
		return domain.Game{}, ErrGameFull
	}

	game.PlayerOID = userID
	gs.repo.SaveGame(game)
	return game, nil
}

func (gs *GameService) MakeTurn(userID, gameID uuid.UUID, i, j int) error {
	game, ok := gs.repo.GetGame(gameID)

	if !ok {
		return ErrNoGame
	}

	curPlayer := userID

	if curPlayer != game.PlayerXID && curPlayer != game.PlayerOID {
		return ErrNoAcces
	}

	err := game.MakeMove(i, j, curPlayer)
	if err != nil {
		return err
	}

	if game.IsAI && game.State == domain.InProgress {
		game.Board, _ = minMax(game.Board, domain.O)
		game.CurrentTurn = -game.CurrentTurn
		game.State = game.Board.CheckGameState()
		game.UpdateWinner()
	}

	gs.repo.SaveGame(game)
	return err
}

func (gs *GameService) RefreshGame(gameID uuid.UUID) (domain.Game, error) {
	game, ok := gs.repo.GetGame(gameID)

	if !ok {
		return game, ErrNoGame
	}

	return game, nil
}

func (gs *GameService) GetLeaderboard(n int) []struct {
	PlayerID uuid.UUID
	Ratio    float32
} {
	return gs.repo.GetLeaderboard(n)
}
