package auth_service

import (
	"github.com/gorilla/mux"
	"io"
	"net/http"
	"typer_auth/internal/auth_config"
)

type AuthService struct {
	config *auth_config.Config
	router *mux.Router
}

func New(config *auth_config.Config) *AuthService {
	return &AuthService{
		config: config,
		router: mux.NewRouter(),
	}
}

func (s *AuthService) Start() error {
	s.ConfigureRouter()
	return http.ListenAndServe(s.config.BinAddr, s.router)
}

func (s *AuthService) ConfigureRouter() {
	s.router.HandleFunc("/test", s.handleHello())
}

func (s *AuthService) handleHello() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		io.WriteString(w, "Hello")
	}
}
