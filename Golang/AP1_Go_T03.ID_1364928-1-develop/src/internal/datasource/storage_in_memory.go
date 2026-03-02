package datasource

import (
	"sync"
	"xo/internal/domain"
	"xo/internal/interfaces"
)

type StorageInMem struct {
	Games sync.Map
}

func NewStorageInMem() interfaces.Repository {
	return &StorageInMem{}
}

func (s *StorageInMem) Save(game *domain.Game) {
	s.Games.Store(game.UUID, game)
}

func (s *StorageInMem) Get(uuid string) (*domain.Game, bool) {
	val, ok := s.Games.Load(uuid)
	if !ok {
		return nil, false
	}
	return val.(*domain.Game), true
}
