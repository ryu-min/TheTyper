package main

import (
	"flag"
    "github.com/gin-gonic/gin"
    _ "net/http"
    "fmt"

    //	"fmt"
//	"github.com/BurntSushi/toml"
//	"log"
//	"typer_auth/internal/auth_config"
//	"typer_auth/internal/auth_service"
)

var (
	configPath string
)

func init() {
	flag.StringVar(&configPath, "config-path", "configs/config.toml", "path to config file")
}

func main() {
	flag.Parse()

    r := gin.Default()

    r.GET("/test", func(c *gin.Context) {

        first := c.Query("first")
        if len(first) > 0 {
            fmt.Println("recieve first param " + first)
        } else {
            fmt.Println("do not recieve first param")
        }

        second := c.Query("second")
        if len(second) > 0 {
            fmt.Println("recieve second param " + second)
        } else {
            fmt.Println("do not recieve second param")
        }
    })


    r.Run(":8080")


//	conf := auth_config.NewConfig()
//	_, err := toml.DecodeFile(configPath, conf)
//	if err != nil {
//		log.Fatal(err)
//	} else {
//		fmt.Println(conf.BinAddr)
//		fmt.Println(conf.DatabaseURL)
//		service := auth_service.New(conf)
//		err = service.Start()
//		if err != nil {
//			log.Fatal(err)
//		}
//	}
}