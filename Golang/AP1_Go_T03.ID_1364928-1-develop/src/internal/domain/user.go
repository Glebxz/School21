package domain

import "github.com/google/uuid"

type User struct {
	ID       uuid.UUID
	Login    string
	Password string
}

type UserInfo struct {
	ID           uuid.UUID
	CurrentGames []uuid.UUID
}
