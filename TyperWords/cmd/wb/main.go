package main

import (
	"os"
	"words_backend/internal/handler"

	"github.com/gin-gonic/gin"
)

func main() {
	h := handler.New()
	r := gin.Default()
	r.GET("/ping", h.Ping)
	r.GET("/words/:type", h.Words)
	r.GET("/supported", h.SupportedTypes)

	port := os.Getenv("PORT")
	if port == "" {
		port = "8080"
	}
	r.Run("localhost:" + port)
}
