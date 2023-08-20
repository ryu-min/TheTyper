package main

import (
	_ "embed"
	"words_backend/internal/handler"

	"github.com/gin-gonic/gin"
	_ "github.com/mattn/go-sqlite3"
)

func main() {
	h := handler.New()
	r := gin.Default()
	r.GET("/ping", h.Ping)
	r.GET("/words/:type", h.Words)
	r.GET("/supported", h.SupportedTypes)
	r.Run("localhost:5050")
}
