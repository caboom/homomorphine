package main

import (
	"bytes"
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"net/http"
	"os"
)

type Encrypt struct {
	PublicKey string `json:"public_key"`
	Value     int    `json:"value"`
}

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

	//
	// get the generated public and secret key
	//
	log.Println("Fetching public and secret key...")
	keys_resp, err := http.Get(fmt.Sprintf("http://%s:%d/seal/bfv/keys/", *host, *port))

	if err != nil {
		fmt.Errorf("Error: %s", err)
		os.Exit(1)
	}

	var keys map[string]interface{}
	json.NewDecoder(keys_resp.Body).Decode(&keys)

	//
	// encrypt the random integer using public key
	//
	encrypt := &Encrypt{
		PublicKey: keys["public_key"].(string),
		Value:     100}

	encrypt_request, err := json.Marshal(encrypt)
	if err != nil {
		fmt.Errorf("Error: %s", err)
		os.Exit(1)
	}

	encrypt_resp, err := http.Post(fmt.Sprintf("http://%s:%d/seal/bfv/keys/", *host, *port), "application/json", bytes.NewBuffer(encrypt_request))
	if err != nil {
		fmt.Errorf("Error: %s", err)
		os.Exit(1)
	}

	log.Println(encrypt_resp)
}
