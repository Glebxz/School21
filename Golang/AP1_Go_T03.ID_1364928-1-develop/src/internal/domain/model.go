package domain

import "sync"

const (
	Empty = 0
	X     = 1
	O     = 2
	Draw  = 3
)

type Board [3][3]int

type Game struct {
	UUID  string `json:"uuid"`
	Board Board  `json:"board"`

	mu sync.Mutex
}

func (g *Game) Lock() {
	g.mu.Lock()
}

func (g *Game) Unlock() {
	g.mu.Unlock()
}
