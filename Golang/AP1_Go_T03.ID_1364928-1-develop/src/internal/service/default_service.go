package service

import (
	"errors"
	"sync"
	"xo/internal/domain"
	"xo/internal/interfaces"
)

type DefaultService struct {
	repo interfaces.Repository
	mu   sync.Mutex
}

func NewDefaultService(repo interfaces.Repository) interfaces.Service {
	return &DefaultService{repo: repo}
}

func (ds *DefaultService) AddNewGame(uuid string) error {
	ds.mu.Lock()
	defer ds.mu.Unlock()

	if _, ok := ds.repo.Get(uuid); ok {
		return errors.New("Game with that UUID already exist")
	}

	newGame := domain.Game{
		UUID: uuid,
	}

	ds.repo.Save(&newGame)

	return nil
}

func (ds *DefaultService) GetNextTurn(uuid string, newBoard domain.Board) (domain.Board, error) {
	game, ok := ds.repo.Get(uuid)
	if !ok {
		return domain.Board{}, errors.New("UUID not found")
	}

	game.Lock()
	defer game.Unlock()

	if !validateBoard(game.Board, newBoard) {
		return game.Board, errors.New("Previous turns was edited")
	}

	game.Board = newBoard
	ds.repo.Save(game)

	if checkGameOver(game.Board) != 0 {
		return game.Board, nil
	}

	game.Board, _ = minMax(game.Board, domain.O)

	ds.repo.Save(game)
	return game.Board, nil
}

func (ds *DefaultService) ValidateBoard(uuid string, newBoard domain.Board) bool {
	curBoard, ok := ds.repo.Get(uuid)
	if !ok {
		return false
	}
	return validateBoard(curBoard.Board, newBoard)
}

func validateBoard(curBoard domain.Board, newBoard domain.Board) bool {
	changed := false
	for i := range curBoard {
		for j := range curBoard[i] {
			if curBoard[i][j] != newBoard[i][j] {
				if curBoard[i][j] != domain.Empty || changed {
					return false
				}
				changed = true
			}
		}
	}
	return true
}

func (ds *DefaultService) CheckGameOver(uuid string) int {
	curBoard, ok := ds.repo.Get(uuid)
	if !ok {
		return domain.Empty
	}
	return checkGameOver(curBoard.Board)
}

func checkGameOver(board domain.Board) int {
	for i := range board {
		if board[i][0] != domain.Empty && board[i][0] == board[i][1] && board[i][0] == board[i][2] {
			return board[i][0]
		}
	}

	for j := range board[0] {
		if board[0][j] != domain.Empty && board[0][j] == board[1][j] && board[0][j] == board[2][j] {
			return board[0][j]
		}
	}

	if board[0][0] != domain.Empty && board[0][0] == board[1][1] && board[0][0] == board[2][2] {
		return board[0][0]
	}

	if board[0][2] != domain.Empty && board[0][2] == board[1][1] && board[0][2] == board[2][0] {
		return board[0][2]
	}

	for i := range board {
		for j := range board[i] {
			if board[i][j] == domain.Empty {
				return domain.Empty
			}
		}
	}

	return domain.Draw
}
