package storage

import (
	"database/sql"
	"embed"
	"fmt"
	"log"
	"path/filepath"
	"strings"

	mapset "github.com/deckarep/golang-set/v2"
	_ "github.com/lib/pq"
	_ "github.com/mattn/go-sqlite3"
)

//go:embed words/*.txt
var wordsFS embed.FS

func getWords(fs *embed.FS) (map[string]string, error) {
	result := make(map[string]string)
	files, err := fs.ReadDir("words")
	if err != nil {
		return nil, err
	}
	for _, file := range files {
		fileName := file.Name()
		val, err := fs.ReadFile("words/" + fileName)
		if err != nil {
			return nil, err
		}
		content := string(val)
		nameWithoutSuffix := strings.TrimSuffix(fileName, filepath.Ext(fileName))
		result[nameWithoutSuffix] = content
	}
	return result, nil
}

type Database struct {
	db *sql.DB
}

func New() *Database {

	const file string = "words.db"
	handler, err := sql.Open("sqlite3", file)
	if err != nil {
		log.Print("Can't connect to database")
		panic(err)
	}

	err = handler.Ping()
	if err != nil {
		log.Print("Can't ping to database")
		panic(err)
	}
	database := &Database{
		db: handler,
	}
	err = database.configing()
	if err != nil {
		log.Print("Configuring error")
		panic(err)
	}
	return database
}

func (d *Database) GetWordTypes() (mapset.Set[string], error) {
	return d.requestAllTablesName()
}

func (d *Database) GetWords(wordsType string) ([]string, error) {
	queryString := fmt.Sprintf("SELECT * FROM %s;", wordsType)

	rows, err := d.db.Query(queryString)
	if err != nil {
		return nil, err
	}
	defer rows.Close()
	var result []string
	for rows.Next() {
		var word string
		err = rows.Scan(&word)
		if err != nil {
			return nil, err
		}
		result = append(result, word)
	}
	return result, nil
}

func (d *Database) configing() error {
	fmt.Println("check all data...")
	words, err := getWords(&wordsFS)
	if err != nil {
		return err
	}
	existingTable, err := d.requestAllTablesName()
	if err != nil {
		return err
	}
	for wordsType, content := range words {
		if existingTable.Contains(wordsType) {
			fmt.Printf("data %s already stored \n", wordsType)
		} else {
			fmt.Printf("store %s ... \n", wordsType)
			err := d.createTableWithContent(wordsType, strings.Fields(content))
			if err != nil {
				return err
			}
		}
	}
	return nil
}

func (d *Database) requestAllTablesName() (mapset.Set[string], error) {
	rows, err := d.db.Query("SELECT name FROM sqlite_master WHERE type='table'")
	if err != nil {
		return nil, err
	}
	defer rows.Close()
	result := mapset.NewSet[string]()
	for rows.Next() {
		var tableName string
		err = rows.Scan(&tableName)
		if err != nil {
			return nil, err
		}
		result.Add(tableName)
	}
	return result, nil
}

func (d *Database) createTableWithContent(name string, content []string) error {
	queryString := fmt.Sprintf("CREATE TABLE %s ( word TEXT PRIMARY KEY);", name)
	statement, err := d.db.Prepare(queryString)
	if err != nil {
		return err
	}
	_, err = statement.Exec()
	if err != nil {
		return err
	}
	for _, word := range content {
		queryString := fmt.Sprintf("INSERT INTO %s (word) VALUES (\"%s\")", name, word)
		statement, err := d.db.Prepare(queryString)
		if err != nil {
			return err
		}
		_, err = statement.Exec()
		if err != nil {
			return err
		}
	}
	return nil
}
