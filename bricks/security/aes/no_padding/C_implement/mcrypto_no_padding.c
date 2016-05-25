#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  * MCrypt API available online:
 *   * http://linux.die.net/man/3/mcrypt
 *    */
#include <mcrypt.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

int encrypt(
        void* buffer,
        int buffer_len, /* Because the plaintext could include null bytes*/
        char* IV, 
        char* key,
        int key_len 
        ){
    MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
    int blocksize = mcrypt_enc_get_block_size(td);
    if( buffer_len % blocksize != 0 ){return 1;}

    mcrypt_generic_init(td, key, key_len, IV);
    mcrypt_generic(td, buffer, buffer_len);
    mcrypt_generic_deinit (td);
    mcrypt_module_close(td);

    return 0;
}

int decrypt(
        void* buffer,
        int buffer_len,
        char* IV, 
        char* key,
        int key_len 
        ){
    MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
    int blocksize = mcrypt_enc_get_block_size(td);
    if( buffer_len % blocksize != 0 ){return 1;}

    mcrypt_generic_init(td, key, key_len, IV);
    mdecrypt_generic(td, buffer, buffer_len);
    mcrypt_generic_deinit (td);
    mcrypt_module_close(td);

    return 0;
}

void display(char* ciphertext, int len){
    int v;
    for (v=0; v<len; v++){
        printf("%d ", ciphertext[v]);
    }
    printf("\n");
}

void print_data(const char *tittle, const void* data, int len)                   
{                                                                                
        printf("%s : ",tittle);                                                      
            const unsigned char * p = (const unsigned char*)data;                        
                int i = 0;                                                                   
                                                                                                 
                    for (; i<len; ++i)                                                           
                                printf("%02X ", *p++);                                                   
                                                                                                     
                        printf("\n");                                                                
} 
int main()
{
//    MCRYPT td, td2;
    //char plaintext[] = {0x0,0x1,0x2,0x3,0x4,0x5};

    /*
    char * plaintext = "test text 123";
   char key[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x00};
   char IV[] ={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
   */

    char * plaintext = "test text 123";
    char* IV = "AAAAAAAAAAAAAAAA";
    char *key = "0123456789abcdef";

    int keysize = 16; /* 128 bits */
    char* buffer;
    int buffer_len = 16;

    buffer = calloc(1, buffer_len);
    strncpy(buffer, plaintext, buffer_len);

    printf("==C==\n");
    printf("plain:   %s\n", plaintext);
    print_data("\n openssl plain ", plaintext, buffer_len);
    encrypt(buffer, buffer_len, IV, key, keysize); 
    printf("\n cipher:  "); 
    display(buffer , buffer_len);
    print_data("\n openssl cipher  ", buffer, buffer_len);
    decrypt(buffer, buffer_len, IV, key, keysize);
    printf("\n decrypt: %s\n", buffer);
    print_data("\n openssl decrypt ", buffer, buffer_len);

    return 0;
}
