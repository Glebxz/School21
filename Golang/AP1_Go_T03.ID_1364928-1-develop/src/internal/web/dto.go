package web

import (
	"xo/internal/domain"

	"github.com/golang-jwt/jwt/v5"
)

type SignUpRequest struct {
	Login    string `json:"login"`
	Password string `json:"password"`
}

type NewTurn struct {
	I int `json:"i"`
	J int `json:"j"`
}

type Game struct {
	GameID string       `json:"gameID"`
	Board  domain.Board `json:"board"`

	IsAI bool `json:"IsAI"`

	PlayerXID string `json:"playerXID"`
	PlayerOID string `json:"playerOID"`

	CurrentTurn domain.Cell     `json:"currentTurn"`
	GameState   string          `json:"gameState"`
	Winner      string          `json:"winner"`
	StartTime   jwt.NumericDate `json:"startTime"`
}

type UserInfo struct {
	ID           string   `json:"id"`
	CurrentGames []string `json:"currentGames"`
}

type Leaderboard struct {
	Lines []struct {
		PlayerID string  `json:"playerID"`
		Ratio    float32 `json:"ratio"`
	}
}

func gameToJSON(game domain.Game) Game {
	var gs string
	switch game.State {
	case domain.InProgress:
		gs = "Game in progress"
	case domain.WinX:
		gs = "X won"
	case domain.WinO:
		gs = "O won"
	case domain.Draw:
		gs = "Draw"
	}

	return Game{
		GameID: game.GameID.String(),
		Board:  game.Board,

		IsAI: game.IsAI,

		PlayerXID: game.PlayerXID.String(),
		PlayerOID: game.PlayerOID.String(),

		CurrentTurn: game.CurrentTurn,
		GameState:   gs,
		Winner:      game.Winner.String(),
		StartTime:   *jwt.NewNumericDate(game.StartTime),
	}
}

func gamesToJSON(games []domain.Game) []Game {
	gamesJSON := make([]Game, 0)
	for i := range games {
		gamesJSON = append(gamesJSON, gameToJSON(games[i]))
	}
	return gamesJSON
}

func userInfoToJSON(userInfo domain.UserInfo) UserInfo {
	cg := make([]string, len(userInfo.CurrentGames))

	for i := range cg {
		cg[i] = string(userInfo.CurrentGames[i].String())
	}

	return UserInfo{
		ID:           userInfo.ID.String(),
		CurrentGames: cg,
	}
}
