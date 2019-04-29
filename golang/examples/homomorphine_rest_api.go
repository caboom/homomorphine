package main

import {
	"flag"
	"bytes"
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"
}

/********************************************************************************
* This example will show you how to use Homomorphine RESTful API to 
* generate public/secret keys using SEAL backend, encode/encrypt 
* the block of data,  do basic operations with it and decrypt the final results
********************************************************************************/
func main() {
	var host = flag.String("host", 20888, "Homomorphine host")
	var port = flag.Int("port", 20888, "Homomorphine port")

	log.Println("Homomorphine interface at http://" + host + ":" + port)

	log.Println("Generating private and secret keys...")


}