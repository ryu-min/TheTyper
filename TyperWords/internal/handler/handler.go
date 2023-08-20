package handler

import (
	"fmt"
	"net/http"
	"strconv"
	"strings"
	"words_backend/internal/storage"

	"github.com/gin-gonic/gin"
)

type Handler struct {
	db *storage.Database
}

func New() *Handler {
	db := storage.New()
	return &Handler{db: db}
}

func (e *Handler) Ping(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "pong",
	})
}

func (e *Handler) Words(c *gin.Context) {
	wordsType := c.Param("type")
	fmt.Println("request " + wordsType)
	limit := c.Query("limit")
	if len(limit) > 0 {
		_, err := strconv.Atoi(limit)
		if err != nil {
			c.String(http.StatusBadRequest, "request format error, param limit should be converted to int")
			return
		}
	}

	wordsTypes, err := e.db.GetWordTypes()
	if err != nil {
		c.String(http.StatusBadRequest, "typer words service not configuring")
		return
	}

	if wordsTypes.Contains(wordsType) {
		words, err := e.db.GetWords(wordsType)
		if err != nil {
			c.String(http.StatusBadRequest, "type '%s' not supported", wordsType)
		} else {
			joinedString := strings.Join(words, " ")
			c.JSON(http.StatusOK, gin.H{
				"words": joinedString,
			})
		}
	} else {
		c.String(http.StatusBadRequest, "type '%s' not supported", wordsType)
		return
	}
}

func (e *Handler) SupportedTypes(c *gin.Context) {
	wordsTypes, err := e.db.GetWordTypes()
	if err != nil {
		c.String(http.StatusBadRequest, "words service not configuring")
		return
	}
	joinedString := strings.Join(wordsTypes.ToSlice(), " ")
	c.JSON(http.StatusOK, gin.H{
		"types": joinedString,
	})
}
