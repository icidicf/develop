#!/bin/bash

mvn clean
mvn package 

java -cp ./target/AESPaddingTest-1.0-SNAPSHOT.jar AES




