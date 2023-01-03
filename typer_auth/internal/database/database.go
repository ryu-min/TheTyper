package database

import (
	"database/sql"
	_ "github.com/lib/pq"
	"typer_auth/internal/auth_config"
)

type Database struct {
	config    *auth_config.Config
	DbHandler *sql.DB
}

func New(config *auth_config.Config) *Database {
	return &Database{
		config: config,
	}
}

func (db *Database) OpenConnection() error {
	handler, err := sql.Open("postgres", db.config.DatabaseURL)
	if err != nil {
		return err
	}

	err = handler.Ping()
	if err != nil {
		return err
	}

	db.DbHandler = handler
	return nil
}

func (db *Database) CloseConnection() {
	db.DbHandler.Close()
}
