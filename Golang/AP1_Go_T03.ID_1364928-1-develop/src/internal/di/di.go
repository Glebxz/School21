package di

import (
	"context"
	"xo/internal/datasource"
	"xo/internal/service"
	"xo/internal/web"

	"fmt"
	"net/http"

	"go.uber.org/fx"
)

func NewApp() fx.Option {
	return fx.Options(
		fx.Provide(
			datasource.NewStorageInMem,
			service.NewDefaultService,
			web.NewGameHandler,
		),
		fx.Invoke(
			StartServer,
			func(graph fx.DotGraph) {
				fmt.Println(graph)
			},
		),
	)
}

func StartServer(lc fx.Lifecycle, handler *web.GameHandler) {
	mux := http.NewServeMux()
	mux.HandleFunc("POST /new/{uuid}", handler.CreateNewGame)
	mux.HandleFunc("POST /game/{uuid}", handler.NextStep)

	server := http.Server{
		Addr:    "localhost:8080",
		Handler: mux,
	}

	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
			go func() {
				if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
					fmt.Printf("server error: %v\n", err)
				}
			}()
			return nil
		},
		OnStop: func(ctx context.Context) error {
			return server.Shutdown(ctx)
		},
	})
}
