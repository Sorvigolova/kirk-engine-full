/*
	Draan proudly presents:
	
	With huge help from community:
	coyotebean, Davee, hitchhikr, kgsws, liquidzigong, Mathieulh, Proxima, SilverSpring
	
	******************** KIRK-ENGINE ********************
	An Open-Source implementation of KIRK (PSP crypto engine) algorithms and keys.
	Includes also additional routines for hash forging.
	
	********************
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KIRK_ENGINE
#define KIRK_ENGINE
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;

//Kirk return values
#define KIRK_OPERATION_SUCCESS 0
#define KIRK_NOT_ENABLED 1
#define KIRK_INVALID_MODE 2
#define KIRK_HEADER_HASH_INVALID 3
#define KIRK_DATA_HASH_INVALID 4
#define KIRK_SIG_CHECK_INVALID 5
#define KIRK_UNK_1 6
#define KIRK_UNK_2 7
#define KIRK_UNK_3 8
#define KIRK_UNK_4 9
#define KIRK_UNK_5 0xA
#define KIRK_UNK_6 0xB
#define KIRK_NOT_INITIALIZED 0xC
#define KIRK_INVALID_OPERATION 0xD
#define KIRK_INVALID_SEED_CODE 0xE
#define KIRK_INVALID_SIZE 0xF
#define KIRK_DATA_SIZE_ZERO 0x10

typedef struct 
{
        u8 cmac[0x10];  //0x0
        u16 length;     //0x10
} KIRK_KBOOTI_HEADER;   //0x12

typedef struct
{
	int mode;    //0
	int unk_4;   //4
	int unk_8;   //8
	int keyseed; //C
	int data_size;   //10
} KIRK_AES128CBC_HEADER; //0x14

typedef struct
{
	int mode;    //0
	int unk_4;   //4
	int unk_8;   //8
	int keyseed; //C
	int data_size;   //10
	u8 userkey[0x10]; //14
} KIRK_AES128CBC_USER_HEADER; //0x24

typedef struct
{
	u8  AES_key[16];            //0
	u8  CMAC_key[16];           //10
	u8  CMAC_header_hash[16];   //20
	u8  CMAC_data_hash[16];     //30
	u8  unused[32];             //40
	u32 mode;                   //60
	u8  ecdsa_hash;             //64
	u8  unk3[11];               //65
	u32 data_size;              //70
	u32 data_offset;            //74  
	u8  unk4[8];                //78
	u8  unk5[16];               //80
} KIRK_CMD1_HEADER; //0x90

typedef struct
{
	u8  AES_key[16];            //0
	u8  header_sig_r[20];           //10
	u8  header_sig_s[20];   //24
	u8  data_sig_r[20];     //38
	u8  data_sig_s[20];     //4C
	u32 mode;                   //60
	u8  ecdsa_hash;             //64
	u8  unk3[11];               //65
	u32 data_size;              //70
	u32 data_offset;            //74  
	u8  unk4[8];                //78
	u8  unk5[16];               //80
} KIRK_CMD1_ECDSA_HEADER; //0x90


typedef struct
{
	u8 r[0x14];
	u8 s[0x14];
} ECDSA_SIG; //0x28
typedef struct
{
	u8 x[0x14];
	u8 y[0x14];
} ECDSA_POINT; //0x28

typedef struct
{
    u32 data_size;             //0     
} KIRK_SHA1_HEADER;            //4

typedef struct
{
	u8 private_key[0x14];
	ECDSA_POINT public_key;
} KIRK_CMD12_BUFFER;

typedef struct
{
	u8 multiplier[0x14];
	ECDSA_POINT public_key;
} KIRK_CMD13_BUFFER;


typedef struct
{
	u8 enc_private[0x20];					//0
	u8 message_hash[0x14];				//20
} KIRK_CMD16_BUFFER;//0x34

typedef struct
{
	ECDSA_POINT public_key;					//0
	u8 message_hash[0x14];				//28
	ECDSA_SIG signature;					//3C
} KIRK_CMD17_BUFFER;//0x64

//mode passed to sceUtilsBufferCopyWithRange
#define KIRK_CMD_0_DEVKIT_DECRYPT 0
#define KIRK_CMD_1_DECRYPT_VERIFY 1
#define KIRK_CMD_2 2
#define KIRK_CMD_3_DECRYPT_VERIFY 3
#define KIRK_CMD_ENCRYPT_IV_0 4
#define KIRK_CMD_ENCRYPT_IV_FUSE 5
#define KIRK_CMD_ENCRYPT_IV_USER 6
#define KIRK_CMD_DECRYPT_IV_0 7
#define KIRK_CMD_DECRYPT_IV_FUSE 8
#define KIRK_CMD_DECRYPT_IV_USER 9
#define KIRK_CMD_PRIV_SIGN_CHECK 10
#define KIRK_CMD_SHA1_HASH 11
#define KIRK_CMD_ECDSA_GEN_KEYS 12
#define KIRK_CMD_ECDSA_MULTIPLY_POINT 13
#define KIRK_CMD_PRNG 14
#define KIRK_CMD_15 15
#define KIRK_CMD_ECDSA_SIGN 16
#define KIRK_CMD_ECDSA_VERIFY 17
#define KIRK_CMD_CERT_VERIFY 18

// These are custom found here only for encrypting data
#define KIRK_CMD_1_ENCRYPT 19
#define KIRK_CMD_3_ENCRYPT 20


//"mode" in header
#define KIRK_MODE_CMD1 1
#define KIRK_MODE_CMD2 2
#define KIRK_MODE_CMD3 3
#define KIRK_MODE_ENCRYPT_CBC 4
#define KIRK_MODE_DECRYPT_CBC 5

//sceUtilsBufferCopyWithRange errors
#define SUBCWR_NOT_16_ALGINED 0x90A
#define SUBCWR_HEADER_HASH_INVALID 0x920
#define SUBCWR_BUFFER_TOO_SMALL 0x1000

/*
      // Private Sig + Cipher
      0x01: Regular (non-superduper) decrpytion and verify of PRX or IPL blocks
      0x02: Decrypt and verify Secure payload and re-encrypt per console
      0x03: Regular (non-superduper) decrpytion of per console (could be gen from 0x2)

      // Cipher
      0x04: Encrypt Operation (inverse of 0x07) (IV=0)
      0x05: Encrypt Operation (inverse of 0x08) (IV=0 Key FUSEID Derived)
      0x06: Encrypt Operation (inverse of 0x09) (IV=0 Random Key Encrypted with UserDefined )
      0x07: Decrypt Operation (inverse of 0x04)
      0x08: Decrypt Operation (inverse of 0x05)
      0x09: Decrypt Operation (inverse of 0x06)
	  
      // Sig Gens
      0x0A: Private Signature Check (checks for private SCE sig)
      0x0B: SHA1 Hash
      0x0C: Generate an ECDSA Key pair
      0x0D: Point Multiplication
      0x0E: Random Number Gen
      0x0F: (PRNG SEED)
      0x10: Signature Gen
      // Sig Checks
      0x11: Signature Check (checks for generated sigs)
      0x12: Certificate Check (idstorage signatures)
*/

//kirk-like funcs
int kirk_CMD0(u8* outbuff, u8* inbuff);
int kirk_CMD1(u8* outbuff, u8* inbuff);
int kirk_CMD3(u8* outbuff, u8* inbuff);

int kirk_CMD4(u8* outbuff, u8* inbuff);
int kirk_CMD5(u8* outbuff, u8* inbuff);
int kirk_CMD6(u8* outbuff, u8* inbuff);
int kirk_CMD7(u8* outbuff, u8* inbuff);
int kirk_CMD8(u8* outbuff, u8* inbuff);
int kirk_CMD9(u8* outbuff, u8* inbuff);
int kirk_CMD10(u8* inbuff);
int kirk_CMD11(u8* outbuff, u8* inbuff);
int kirk_CMD12(u8* outbuff);
int kirk_CMD13(u8* outbuff,u8* inbuff);
int kirk_CMD14(u8* outbuff);
int kirk_CMD16(u8* outbuff,u8* inbuff);
int kirk_CMD17(u8* inbuff);
int kirk_CMD18(u8* inbuff);
int kirk_CMD1ENC(u8* outbuff, u8* inbuff, int size, int generate_trash);
int kirk_CMD3ENC(u8* outbuff, u8* inbuff, int size, int generate_trash);

int kirk_init(); 
int kirk_init2(u8 *, u32, u32, u32);

//helper funcs
u8* kirk_4_7_get_key(int key_type);
void hex_dump(char* str, u8* buf, int size);

//sce-like funcs
int sceUtilsBufferCopyWithRange(u8* outbuff, int outsize, u8* inbuff, int insize, int cmd);
void decrypt_kirk16_private(u8 *dA_out, u8 *dA_enc);
void encrypt_kirk16_private(u8 *dA_out, u8 *dA_dec);
void init_mesh(void);
void generate_key_from_mesh(u8 * key, int param);

#define		round_up(x,n)	(-(-(x) & -(n)))

#define		array_size(x)	(sizeof(x) / sizeof(*(x)))
#endif
