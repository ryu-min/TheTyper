package main

import (
	"flag"
	"fmt"
	"github.com/BurntSushi/toml"
	"log"
	"typer_auth/internal/auth_config"
	"typer_auth/internal/auth_service"
)

var (
	configPath string
)

func init() {
	flag.StringVar(&configPath, "config-path", "configs/config.toml", "path to config file")
}

func main() {
	flag.Parse()

	conf := auth_config.NewConfig()
	_, err := toml.DecodeFile(configPath, conf)
	if err != nil {
		log.Fatal(err)
	} else {
		fmt.Println(conf.BinAddr)
		fmt.Println(conf.DatabaseURL)
		service := auth_service.New(conf)
		err = service.Start()
		if err != nil {
			log.Fatal(err)
		}
	}
}