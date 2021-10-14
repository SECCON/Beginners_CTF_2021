package main

import (
	"bytes"
	"encoding/json"
	"io/ioutil"
	"net"
	"net/http"

	"github.com/gin-gonic/gin"
)

type Info struct {
	ID int `json:"id" binding:"required"`
}

// check if the accessed user is in the local network (192.168.111.0/24)
func checkLocal() gin.HandlerFunc {
	return func(c *gin.Context) {
		clientIP := c.ClientIP()
		ip := net.ParseIP(clientIP).To4()
		if ip[0] != byte(192) || ip[1] != byte(168) || ip[2] != byte(111) {
			c.HTML(200, "error.tmpl", gin.H{
				"ip": clientIP,
			})
			c.Abort()
			return
		}
	}
}

func main() {
	r := gin.Default()
	r.Use(checkLocal())
	r.LoadHTMLGlob("templates/*")

	r.GET("/", func(c *gin.Context) {
		c.HTML(200, "index.html", nil)
	})

	r.POST("/", func(c *gin.Context) {
		// get request body
		body, err := ioutil.ReadAll(c.Request.Body)
		if err != nil {
			c.JSON(400, gin.H{"error": "Failed to read body."})
			return
		}

		// parse json
		var info Info
		if err := json.Unmarshal(body, &info); err != nil {
			c.JSON(400, gin.H{"error": "Invalid parameter."})
			return
		}

		// validation
		if info.ID < 0 || info.ID > 2 {
			c.JSON(400, gin.H{"error": "ID must be an integer between 0 and 2."})
			return
		}

		if info.ID == 2 {
			c.JSON(400, gin.H{"error": "It is forbidden to retrieve Flag from this BFF server."})
			return
		}

		// get data from api server
		req, err := http.NewRequest("POST", "http://api:8000", bytes.NewReader(body))
		if err != nil {
			c.JSON(400, gin.H{"error": "Failed to request API."})
			return
		}
		req.Header.Set("Content-Type", "application/json")
		client := new(http.Client)
		resp, err := client.Do(req)
		if err != nil {
			c.JSON(400, gin.H{"error": "Failed to request API."})
			return
		}
		defer resp.Body.Close()
		result, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			c.JSON(400, gin.H{"error": "Failed to request API."})
			return
		}

		c.JSON(200, gin.H{"result": string(result)})
	})

	if err := r.Run(":8080"); err != nil {
		panic("server is not started")
	}
}
