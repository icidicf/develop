#!/bin/bash

gcc -o no_padding mcrypto_no_padding.c -lmcrypt

./no_padding
