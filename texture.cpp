


#include <d3dx9.h>
#include "debug_Printf.h"
#include "mydirect3d.h"
#include "texture.h"


/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/
#define TEXTURE_FILENAME_MAX (64) // テクスチャファイル名最大文字数（パス、NULL文字含む）

// テクスチャファイル管理構造体
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX]; // テクスチャファイル名
	int width;  // テクスチャ解像度横幅
	int height; // テクスチャ解像度縦幅
} TextureFile;


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
// 読み込みテクスチャ情報
static const TextureFile g_TextureFiles[] = {
	{ "asset/texture/airou.png",           256,  256 },
    { "asset/texture/KIZUNA.jpg", 225, 225 }
};
// 読み込みテクスチャ数
static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// 読み込みテクスチャ数とテクスチャ管理番号列挙数に差があった場合コンパイルエラーとする
static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");


/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {}; // テクスチャインターフェース管理配列


/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

// テクスチャの読み込み
int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

// テクスチャの解放
void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

// テクスチャインターフェースの取得
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

// テクスチャ解像度幅の取得
int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].width;
}

// テクスチャ解像度高さの取得
int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].height;
}
