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
			fx.Annotate(
				datasource.NewSQLRep,
				fx.As(new(service.Repository)),
			),
			fx.Annotate(
				service.NewGameService,
				fx.As(new(web.GameService)),
			),
			fx.Annotate(
				service.NewUserService,
				fx.As(new(web.UserService)),
			),
			web.NewJwtProvider,
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
	mux.HandleFunc("POST /signup", handler.SignUp)
	mux.HandleFunc("POST /signin", handler.SignIn)
	mux.HandleFunc("POST /refresh", handler.RefreshAccessToken)
	mux.HandleFunc("POST /new/ai", handler.JwtMiddleware()(handler.CreateNewAIGame))
	mux.HandleFunc("POST /new/pvp", handler.JwtMiddleware()(handler.CreateNewPVPGame))
	mux.HandleFunc("GET /avaliable_games", handler.JwtMiddleware()(handler.GetAvaliableGames))
	mux.HandleFunc("GET /finished_games", handler.JwtMiddleware()(handler.GetFinishedGames))
	mux.HandleFunc("POST /join/{game_id}", handler.JwtMiddleware()(handler.JoinGame))
	mux.HandleFunc("GET /game/{game_id}", handler.JwtMiddleware()(handler.UpdateGame))
	mux.HandleFunc("POST /move/{game_id}", handler.JwtMiddleware()(handler.MakeTurn))
	mux.HandleFunc("GET /users/info", handler.JwtMiddleware()(handler.UserInfo))
	mux.HandleFunc("GET /leaderboard", handler.JwtMiddleware()(handler.Leaderboard))

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
