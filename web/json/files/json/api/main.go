package main

import (
	"io/ioutil"
	"os"

	"github.com/buger/jsonparser"
	"github.com/gin-gonic/gin"
)

func main() {
	r := gin.Default()

	r.POST("/", func(c *gin.Context) {
		body, err := ioutil.ReadAll(c.Request.Body)
		if err != nil {
			c.String(400, "Failed to read body")
			return
		}

		id, err := jsonparser.GetInt(body, "id")
		if err != nil {
			c.String(400, "Failed to parse json")
			return
		}

		if id == 0 {
			c.String(200, "The quick brown fox jumps over the lazy dog.")
			return
		}
		if id == 1 {
			c.String(200, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.")
			return
		}
		if id == 2 {
			// Flag!!!
			flag := os.Getenv("FLAG")
			c.String(200, flag)
			return
		}

		c.String(400, "No data")
	})

	if err := r.Run(":8000"); err != nil {
		panic("server is not started")
	}
}
