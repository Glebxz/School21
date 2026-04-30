package web

import (
	"encoding/json"
	"net/http"

	"github.com/google/uuid"
)

type contextKey string

const UserIDKey contextKey = "userID"

type GameHandler struct {
	gameService GameService
	userService UserService
	jwtProvider JwtProvider
}

func NewGameHandler(gameService GameService, userService UserService, jwtProvider *JwtProvider) *GameHandler {
	return &GameHandler{
		gameService: gameService,
		userService: userService,
		jwtProvider: *jwtProvider,
	}
}

func buildResponse(w http.ResponseWriter, status int, data any) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(status)
	json.NewEncoder(w).Encode(data)
}

func (gh *GameHandler) SignUp(w http.ResponseWriter, r *http.Request) {
	var newUser SignUpRequest

	if err := json.NewDecoder(r.Body).Decode(&newUser); err != nil {
		buildResponse(w, http.StatusBadRequest, err.Error())
		return
	}

	if err := gh.userService.Registration(newUser.Login, newUser.Password); err != nil {
		buildResponse(w, http.StatusConflict, err.Error())
		return
	}

	buildResponse(w, http.StatusCreated, map[string]string{"status": "New user created"})
}

func (gh *GameHandler) SignIn(w http.ResponseWriter, r *http.Request) {
	var user SignUpRequest
	if err := json.NewDecoder(r.Body).Decode(&user); err != nil {
		buildResponse(w, http.StatusBadRequest, err.Error())
		return
	}

	userID, err := gh.userService.Authorization(user.Login, user.Password)
	if err != nil {
		buildResponse(w, http.StatusUnauthorized, err.Error())
		return
	}

	at, _ := gh.jwtProvider.GenerateAccessToken(userID)
	rt, _ := gh.jwtProvider.GenerateRefreshToken(userID)
	jwtr := JwtResponse{
		Type:         "Bearer",
		AccessToken:  at,
		RefreshToken: rt,
	}

	buildResponse(w, http.StatusOK, jwtr)
}

func (gh *GameHandler) RefreshAccessToken(w http.ResponseWriter, r *http.Request) {
	var refreshJwtRequest RefreshJwtRequest
	if err := json.NewDecoder(r.Body).Decode(&refreshJwtRequest); err != nil {
		buildResponse(w, http.StatusBadRequest, err.Error())
		return
	}

	userIDstring, err := gh.jwtProvider.ValidateRefreshToken(refreshJwtRequest.RefreshToken)
	if err != nil {
		buildResponse(w, http.StatusBadRequest, err.Error())
	}

	userID, _ := uuid.Parse(userIDstring)
	tokenString, _ := gh.jwtProvider.GenerateAccessToken(userID)
	jwtr := JwtResponse{
		Type:         "Bearer",
		AccessToken:  tokenString,
		RefreshToken: refreshJwtRequest.RefreshToken,
	}
	buildResponse(w, http.StatusOK, jwtr)
}

func (gh *GameHandler) CreateNewAIGame(w http.ResponseWriter, r *http.Request) {
	gh.CreateNewGame(w, r, true)
}

func (gh *GameHandler) CreateNewPVPGame(w http.ResponseWriter, r *http.Request) {
	gh.CreateNewGame(w, r, false)
}

func (gh *GameHandler) CreateNewGame(w http.ResponseWriter, r *http.Request, isAI bool) {
	newGame := gh.gameService.AddNewGame(r.Context().Value(UserIDKey).(uuid.UUID), isAI)
	buildResponse(w, http.StatusCreated, gameToJSON(newGame))
}

func (gh *GameHandler) GetAvaliableGames(w http.ResponseWriter, r *http.Request) {
	buildResponse(w, http.StatusOK, gamesToJSON(gh.gameService.GetAvaliableGames()))
}

func (gh *GameHandler) GetFinishedGames(w http.ResponseWriter, r *http.Request) {
	buildResponse(w, http.StatusOK, gamesToJSON(gh.gameService.GetFinishedGames(r.Context().Value(UserIDKey).(uuid.UUID))))
}

func (gh *GameHandler) JoinGame(w http.ResponseWriter, r *http.Request) {
	gameID, err1 := uuid.Parse(r.PathValue("game_id"))
	if err1 != nil {
		buildResponse(w, http.StatusBadRequest, map[string]string{"error": err1.Error()})
		return
	}

	game, err2 := gh.gameService.AddPlayerToGame(r.Context().Value(UserIDKey).(uuid.UUID), gameID)
	if err2 != nil {
		buildResponse(w, http.StatusConflict, map[string]string{"error": err2.Error()})
		return
	}

	buildResponse(w, http.StatusOK, gameToJSON(game))
}

func (gh *GameHandler) UpdateGame(w http.ResponseWriter, r *http.Request) {
	gameID, err1 := uuid.Parse(r.PathValue("game_id"))
	if err1 != nil {
		buildResponse(w, http.StatusBadRequest, map[string]string{"error": err1.Error()})
		return
	}

	game, err2 := gh.gameService.RefreshGame(gameID)
	if err2 != nil {
		buildResponse(w, http.StatusConflict, map[string]string{"error": err2.Error()})
		return
	}

	buildResponse(w, http.StatusOK, gameToJSON(game))
}

func (gh *GameHandler) MakeTurn(w http.ResponseWriter, r *http.Request) {
	gameID, err1 := uuid.Parse(r.PathValue("game_id"))

	if err1 != nil {
		buildResponse(w, http.StatusBadRequest, map[string]string{"error": err1.Error()})
		return
	}

	var newTurn NewTurn
	if err := json.NewDecoder(r.Body).Decode(&newTurn); err != nil {
		buildResponse(w, http.StatusBadRequest, map[string]string{"error": err.Error()})
		return
	}

	if err := gh.gameService.MakeTurn(r.Context().Value(UserIDKey).(uuid.UUID), gameID, newTurn.I, newTurn.J); err != nil {
		buildResponse(w, http.StatusConflict, map[string]string{"error": err.Error()})
		return
	}

	buildResponse(w, http.StatusOK, struct{}{})
}

func (gh *GameHandler) UserInfo(w http.ResponseWriter, r *http.Request) {
	userID := r.Context().Value(UserIDKey).(uuid.UUID)
	userInfo, err2 := gh.userService.GetUserInfo(userID)

	if err2 != nil {
		buildResponse(w, http.StatusConflict, map[string]string{"error": err2.Error()})
		return
	}

	buildResponse(w, http.StatusOK, map[string]UserInfo{"user info": userInfoToJSON(userInfo)})
}

func (gh *GameHandler) Leaderboard(w http.ResponseWriter, r *http.Request) {
	var n int
	if err := json.NewDecoder(r.Body).Decode(&n); err != nil {
		buildResponse(w, http.StatusBadRequest, map[string]string{"error": err.Error()})
	}

	leads := gh.gameService.GetLeaderboard(n)
	leaderboard := Leaderboard{
		Lines: make([]struct {
			PlayerID string  `json:"playerID"`
			Ratio    float32 `json:"ratio"`
		}, len(leads)),
	}

	for i := range leads {
		leaderboard.Lines[i].PlayerID = leads[i].PlayerID.String()
		leaderboard.Lines[i].Ratio = leads[i].Ratio
	}

	buildResponse(w, http.StatusOK, leaderboard)
}
