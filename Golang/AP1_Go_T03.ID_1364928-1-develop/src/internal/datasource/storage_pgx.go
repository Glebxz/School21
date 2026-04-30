package datasource

import (
	"context"
	"encoding/json"
	"os"
	"xo/internal/domain"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5/pgxpool"
)

type PostgreDB struct {
	dbpool *pgxpool.Pool
}

func NewSQLRep() *PostgreDB {
	dbpool, err := pgxpool.New(context.Background(), "postgres://postgres:0000@localhost:5432/xo")
	if err != nil {
		panic(err)
	}

	file, errF := os.ReadFile("./internal/datasource/init.sql")
	if errF != nil {
		panic(errF)
	}
	initApply := string(file)

	_, errE := dbpool.Exec(context.Background(), initApply)
	if errE != nil {
		panic(errE)
	}

	return &PostgreDB{
		dbpool: dbpool,
	}
}

func (db *PostgreDB) AddNewGame(game domain.Game) error {
	board, errJ := json.Marshal(game.Board)
	if errJ != nil {
		return errJ
	}
	_, err := db.dbpool.Exec(context.Background(), `
	INSERT INTO games (
	game_uuid,
    board,
    is_ai,
    player_x,
    player_o,
    current_turn,
    current_state,
    winner,
	start_time
	)
	VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9)`, game.GameID, board, game.IsAI, game.PlayerXID, game.PlayerOID, game.CurrentTurn, game.State, game.Winner, game.StartTime)

	if err != nil {
		return err
	}

	return nil
}

func (db *PostgreDB) SaveGame(game domain.Game) error {
	board, errJ := json.Marshal(game.Board)
	if errJ != nil {
		return errJ
	}

	_, err := db.dbpool.Exec(context.Background(), `
	UPDATE games SET
    	board = $1,
    	is_ai = $2,
    	player_x = $3,
	    player_o = $4,
    	current_turn = $5,
    	current_state = $6,
    	winner = $7
	WHERE game_uuid = $8
	`,
		board,
		game.IsAI,
		game.PlayerXID,
		game.PlayerOID,
		game.CurrentTurn,
		game.State,
		game.Winner,
		game.GameID,
	)
	if err != nil {
		return err
	}

	return nil
}

func (db *PostgreDB) GetGame(gameID uuid.UUID) (domain.Game, bool) {
	var game domain.Game
	var board []byte
	result := true

	err := db.dbpool.QueryRow(context.Background(), `
        SELECT game_uuid, board, is_ai, player_x, player_o, current_turn, current_state, winner, start_time
        FROM games
        WHERE game_uuid = $1
    `, gameID).Scan(
		&game.GameID,
		&board,
		&game.IsAI,
		&game.PlayerXID,
		&game.PlayerOID,
		&game.CurrentTurn,
		&game.State,
		&game.Winner,
		&game.StartTime,
	)

	if err != nil {
		return game, false
	}

	json.Unmarshal(board, &game.Board)

	return game, result
}

func (db *PostgreDB) GetAvaliableGames() []domain.Game {
	rows, _ := db.dbpool.Query(context.Background(), `
	SELECT *
	FROM games
	WHERE player_o = '00000000-0000-0000-0000-000000000000' AND is_ai = false`)
	defer rows.Close()

	games := make([]domain.Game, 0)
	for rows.Next() {
		var game domain.Game
		var board []byte
		rows.Scan(&game.GameID,
			&board,
			&game.IsAI,
			&game.PlayerXID,
			&game.PlayerOID,
			&game.CurrentTurn,
			&game.State,
			&game.Winner,
			&game.StartTime)
		json.Unmarshal(board, &game.Board)
		games = append(games, game)
	}

	return games
}

func (db *PostgreDB) GetFinishedGames(userID uuid.UUID) []domain.Game {
	rows, _ := db.dbpool.Query(context.Background(), `
	SELECT *
	FROM games
	WHERE (player_x = $1 OR player_o = $1) AND (current_state = $2 OR current_state = $3 OR current_state = $4)
	`, userID, domain.WinX, domain.WinO, domain.Draw)
	defer rows.Close()

	games := make([]domain.Game, 0)
	for rows.Next() {
		var game domain.Game
		var board []byte
		rows.Scan(&game.GameID,
			&board,
			&game.IsAI,
			&game.PlayerXID,
			&game.PlayerOID,
			&game.CurrentTurn,
			&game.State,
			&game.Winner,
			&game.StartTime)
		json.Unmarshal(board, &game.Board)
		games = append(games, game)
	}

	return games
}

func (db *PostgreDB) AddUser(login, password string, userID uuid.UUID) error {
	_, err := db.dbpool.Exec(context.Background(), `
	INSERT INTO users (
	uuid,
	login,
	password
	)
	VALUES ($1, $2, $3)`, userID, login, password)

	if err != nil {
		return err
	}

	return nil
}

func (db *PostgreDB) GetUser(login, password string) (uuid.UUID, error) {
	var userID uuid.UUID

	err := db.dbpool.QueryRow(context.Background(), `
	SELECT uuid FROM users WHERE login = $1 AND password = $2`, login, password).Scan(&userID)

	if err != nil {
		return uuid.Nil, err
	}
	return userID, nil
}

func (db *PostgreDB) GetUserInfo(userID uuid.UUID) domain.UserInfo {
	var userInfo domain.UserInfo
	userInfo.ID = userID

	rows, _ := db.dbpool.Query(context.Background(), `
	SELECT games.game_uuid
	FROM users INNER JOIN games ON users.uuid = games.player_x OR users.uuid = games.player_o
	WHERE users.uuid = $1`, userID)
	defer rows.Close()

	for rows.Next() {
		var gameID uuid.UUID
		rows.Scan(&gameID)
		userInfo.CurrentGames = append(userInfo.CurrentGames, gameID)
	}

	return userInfo
}

func (db *PostgreDB) GetLeaderboard(n int) []struct {
	PlayerID uuid.UUID
	Ratio    float32
} {
	result := make([]struct {
		PlayerID uuid.UUID
		Ratio    float32
	}, 0)

	rows, _ := db.dbpool.Query(context.Background(), `
	SELECT 
    u.uuid,
    COALESCE(
        ROUND(
            100.0 * COUNT(g.game_uuid) FILTER (WHERE g.winner = u.uuid)
            /
            NULLIF(COUNT(g.game_uuid), 0),
            2
        ),
        0
    ) AS winrate
FROM users u
LEFT JOIN games g 
    ON u.uuid = g.player_x OR u.uuid = g.player_o
GROUP BY u.uuid
ORDER BY winrate DESC
LIMIT $1;`, n)
	defer rows.Close()

	for rows.Next() {
		var row struct {
			PlayerID uuid.UUID
			Ratio    float32
		}
		rows.Scan(&row.PlayerID, &row.Ratio)
		result = append(result, row)
	}

	return result
}
