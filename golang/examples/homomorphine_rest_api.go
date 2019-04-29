package main

import (
	"flag"
	"fmt"
	"log"
	"net/http"
)

/********************************************************************************
* This example will show you how to use Homomorphine RESTful API to
* generate public/secret keys using SEAL backend, encode/encrypt
* the block of data,  do basic operations with it and decrypt the final results
********************************************************************************/
func main() {
	host := flag.String("host", "localhost", "Homomorphine host")
	port := flag.Int("port", 20888, "Homomorphine port")
	flag.Parse()

	log.Printf("Sending API queries at http://%s:%d", *host, *port)

	log.Println("Fetching private and secret key...")
	resp, err := http.Get(fmt.Sprintf("http://%s:%d/seal/bfv/keys/", *host, *port))

	log.Println(resp)
	log.Println(err)
}
