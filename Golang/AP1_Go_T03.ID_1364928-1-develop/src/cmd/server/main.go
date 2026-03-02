package main

import (
	"xo/internal/di"

	"go.uber.org/fx"
)

func main() {
	app := fx.New(di.NewApp())
	app.Run()
}
