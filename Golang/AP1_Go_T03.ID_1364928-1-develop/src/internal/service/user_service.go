package service

import (
	"xo/internal/domain"

	"github.com/google/uuid"
)

type UserService struct {
	repo Repository
}

func NewUserService(repo Repository) *UserService {
	return &UserService{repo: repo}
}

func (us *UserService) Registration(login, password string) error {
	user := domain.User{
		ID:       uuid.New(),
		Login:    login,
		Password: password,
	}

	if err := us.repo.AddUser(user.Login, user.Password, user.ID); err != nil {
		return err
	}

	return nil
}

func (us *UserService) Authorization(login, password string) (uuid.UUID, error) {
	userID, err := us.repo.GetUser(login, password)
	return userID, err
}

func (us *UserService) GetUserInfo(userID uuid.UUID) (domain.UserInfo, error) {
	userInfo := us.repo.GetUserInfo(userID)
	return userInfo, nil
}
