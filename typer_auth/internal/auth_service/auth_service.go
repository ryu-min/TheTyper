package auth_service

import (
	"fmt"
	"github.com/dgrijalva/jwt-go"
	"github.com/gorilla/mux"
	"net/http"
	"typer_auth/internal/auth_config"
	"typer_auth/internal/database"
)

type AuthService struct {
	config   *auth_config.Config
	router   *mux.Router
	database *database.Database
}

func New(config *auth_config.Config) *AuthService {
	return &AuthService{
		config:   config,
		router:   mux.NewRouter(),
		database: database.New(config),
	}
}

func (s *AuthService) Start() error {
	err := s.database.OpenConnection()
	if err != nil {
		return err
	}
	s.ConfigureRouter()
	return http.ListenAndServe(s.config.BinAddr, s.router)
}

func (s *AuthService) ConfigureRouter() {

	// todo GET -> POST
	s.router.HandleFunc("/register", s.register()).Methods("GET")
	s.router.HandleFunc("/auth", s.auth()).Methods("GET")
}

func (s *AuthService) register() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		userName := r.URL.Query().Get("user_name")
		userPassword := r.URL.Query().Get("user_password")

		fmt.Println("user name is" + userName)
		fmt.Println("user pass is" + userPassword)

		if userName != "" && userPassword != "" {
			fmt.Fprintf(w, "Hello %s, %s", userName, userPassword)
			err := s.database.DbHandler.QueryRow("insert into users values($1, $2)", userName, userPassword)
			if err != nil {
				fmt.Println("add user" + userName)
			} else {
				fmt.Println(err)
			}
		} else {
			fmt.Print(w, "need user name and password")
		}
	}
}
func (s *AuthService) auth() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {

		userName := r.URL.Query().Get("user_name")
		userPassword := r.URL.Query().Get("user_password")

		fmt.Println("user name is" + userName)
		fmt.Println("user pass is" + userPassword)

		dbUserPassword := ""
		err := s.database.DbHandler.QueryRow("select user_password from users where user_name = $1 ", userName).Scan(&dbUserPassword)

		if err == nil {
			println("db pass" + dbUserPassword)
			if dbUserPassword == userPassword {
				w.Header().Set("Access-Control-Allow-Origin", "*")
				w.Header().Set("Content-Type", "application/json")
				jwtToken, jwtErr := GenerateJWT(userName)
				if jwtErr != nil {
					println(jwtErr)
					fmt.Fprintf(w, "error")
				} else {
					fmt.Fprintf(w, jwtToken)
				}
			}
		} else {
			println(err)
			fmt.Fprintf(w, "error")
			println(err)
		}
	}
}

func GenerateJWT(userName string) (string, error) {
	token := jwt.New(jwt.SigningMethodHS256)

	var mySigningKey = []byte("johenews")

	claims := token.Claims.(jwt.MapClaims)

	claims["authorized"] = true
	claims["user"] = userName
	//claims["exp"] = time.Now().Add(time.Hour * 2160).Unix()

	tokenString, err := token.SignedString(mySigningKey)

	if err != nil {
		fmt.Errorf("Something went wrong: %s", err.Error())
	}

	return tokenString, nil
}
