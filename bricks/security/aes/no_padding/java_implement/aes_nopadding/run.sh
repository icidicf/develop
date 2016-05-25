#!/bin/bash

mvn clean
mvn package 


java -cp ./target/AESNoPadding-1.0-SNAPSHOT.jar AES 



