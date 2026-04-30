package web

import (
	"time"

	"github.com/golang-jwt/jwt/v5"
	"github.com/google/uuid"
)

type JwtRequest struct {
	Login    string `json:"login"`
	Password string `json:"password"`
}

type JwtResponse struct {
	Type         string `json:"type"`         // Обычно "Bearer"
	AccessToken  string `json:"accessToken"`  // Короткоживущий JWT
	RefreshToken string `json:"refreshToken"` // Длинноживущий токен
}

type RefreshJwtRequest struct {
	RefreshToken string `json:"refreshToken"`
}

type JwtProvider struct {
	UserService   UserService
	AccessSecret  []byte
	RefreshSecret []byte
	AccessTTL     time.Duration
	RefreshTTL    time.Duration
}

func NewJwtProvider(userService UserService /*, accessSecret, refreshSecret []byte, accessTTL, refreshTTL time.Duration*/) *JwtProvider {
	jwtProvider := &JwtProvider{
		UserService:   userService,
		AccessSecret:  []byte("access"),
		RefreshSecret: []byte("refresh"),
		AccessTTL:     time.Minute * 3,
		RefreshTTL:    time.Minute * 30,
	}

	return jwtProvider
}

func (jp *JwtProvider) GenerateAccessToken(userID uuid.UUID) (string, error) {
	claims := jwt.RegisteredClaims{
		Subject:   userID.String(),
		ExpiresAt: jwt.NewNumericDate(time.Now().Add(jp.AccessTTL)),
		IssuedAt:  jwt.NewNumericDate(time.Now()),
	}

	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	return token.SignedString(jp.AccessSecret)
}

func (jp *JwtProvider) GenerateRefreshToken(userID uuid.UUID) (string, error) {
	claims := jwt.RegisteredClaims{
		Subject:   userID.String(),
		ExpiresAt: jwt.NewNumericDate(time.Now().Add(jp.RefreshTTL)),
		IssuedAt:  jwt.NewNumericDate(time.Now()),
		ID:        uuid.NewString(),
	}

	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	return token.SignedString(jp.RefreshSecret)
}

func (jp *JwtProvider) ValidateAccessToken(tokenString string) (string, error) {
	claims := &jwt.RegisteredClaims{}
	parser := jwt.NewParser(jwt.WithValidMethods([]string{"HS256"}))
	token, err := parser.ParseWithClaims(tokenString, claims, func(token *jwt.Token) (any, error) {
		return jp.AccessSecret, nil
	})
	if err != nil {
		return "", err
	}

	return token.Claims.GetSubject()
}

func (jp *JwtProvider) ValidateRefreshToken(tokenString string) (string, error) {
	claims := &jwt.RegisteredClaims{}
	parser := jwt.NewParser(jwt.WithValidMethods([]string{"HS256"}))
	token, err := parser.ParseWithClaims(tokenString, claims, func(token *jwt.Token) (any, error) {
		return jp.RefreshSecret, nil
	})
	if err != nil {
		return "", err
	}

	return token.Claims.GetSubject()
}
