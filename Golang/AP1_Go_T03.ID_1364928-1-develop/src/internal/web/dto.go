package web

import (
	"xo/internal/domain"
)

type Response struct {
	Board   [3][3]int `json:"board"`
	Message string    `json:"message"`
}

func fromDomainToJSON(board domain.Board, msg string) Response {
	return Response{
		Board:   board,
		Message: msg,
	}
}
