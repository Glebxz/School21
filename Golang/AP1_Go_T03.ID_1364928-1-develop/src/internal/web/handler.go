package web

import (
	"encoding/json"
	"net/http"
	"xo/internal/domain"
	"xo/internal/interfaces"
)

type GameHandler struct {
	service interfaces.Service
}

func NewGameHandler(service interfaces.Service) *GameHandler {
	return &GameHandler{service: service}
}

func (gh *GameHandler) CreateNewGame(w http.ResponseWriter, r *http.Request) {
	uuid := r.PathValue("uuid")

	if err := gh.service.AddNewGame(uuid); err != nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusConflict)
		json.NewEncoder(w).Encode(err.Error())
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusCreated)
	rsp := fromDomainToJSON(domain.Board{}, "New game was created")
	json.NewEncoder(w).Encode(rsp)
}

func (gh *GameHandler) NextStep(w http.ResponseWriter, r *http.Request) {
	uuid := r.PathValue("uuid")
	var newBoard domain.Board

	if err := json.NewDecoder(r.Body).Decode(&newBoard); err != nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusBadRequest)
		json.NewEncoder(w).Encode("Not valid JSON")
		return
	}

	newBoard, err := gh.service.GetNextTurn(uuid, newBoard)
	if err != nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusInternalServerError)
		rsp := fromDomainToJSON(newBoard, err.Error())
		json.NewEncoder(w).Encode(rsp)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	rsp := fromDomainToJSON(newBoard, "OK")
	json.NewEncoder(w).Encode(rsp)
}
