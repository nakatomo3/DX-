

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

#include <Windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>

#include "main.h"
#include "Cube.h"
#include "Line.h"
#include "Input.h"
#include <vector>
using namespace std;

//===============================================
//������ǉ��@3D�p�ǉ��R�[�h


//3D�|���S���t�H�[�}�b�g
//#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//�v���W�F�N�V�����p�p�����[�^
#define VIEW_ANGLE (D3DXToRadian(60.0f))                             //�r���[���ʂ̎���p
#define VIEW_ASPECT ((float)SCREEN_WIDTH/ (float)SCREEN_HEIGHT)      //�r���[���ʂ̃A�X�y�N�g�l
#define VIEW_NEAR_Z (0.1f)                                          //�r���[���ʂ�NearZ
#define VIEW_FAR_Z (1000.0f)                                       //�r���[���ʂ�FarZ

//�J�����p�p�����[�^
D3DXVECTOR3 g_posCameraEye;
D3DXVECTOR3 g_posCameraAt;
D3DXVECTOR3 g_vecCameraUp;

//�v���W�F�N�V�������J�����s��
D3DXMATRIX g_mtxView;             //�r���[�}�g���N�X
D3DXMATRIX g_mtxProjectioin;     //�v���W�F�N�V�����}�g���N�X

//�T���v���|���S���̕\�����̂Ɋւ���p�����[�^
D3DXVECTOR3 g_pos; //�n�ʂ̈ʒu
D3DXVECTOR3 g_rot; //�n�ʂ̌���
D3DXVECTOR3 g_scl; //�n�ʂ̑傫��
D3DXMATRIX g_mtxWorld; //���[���h�}�g���N�X

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff; //���_�o�b�t�@	
LPDIRECT3DVERTEXBUFFER9 lineBuffer;

D3DXVECTOR3 cameraPos;
Input* input;


//�����܂�3D�p�ǉ��R�[�h
//===============================================

vector<Cube*> cubes;
vector<Line*> lines;
bool isUp = true;


/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/
#define CLASS_NAME     "GameWindow"       // �E�C���h�E�N���X�̖��O
#define WINDOW_CAPTION "�Q�[���E�B���h�E" // �E�B���h�E�̖��O


/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �Q�[���̏������֐�
// �߂�l:�������Ɏ��s�����Ƃ�false
static bool Initialize(void);
// �Q�[���̍X�V�֐�
static void Update(void);
// �Q�[���̕`��֐�
static void Draw(void);
// �Q�[���̏I������
static void Finalize(void);


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static HWND g_hWnd;             // �E�B���h�E�n���h��
static float g_Rotation = 0.0f; // �X�v���C�g��]�p�x 

/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

//#######################################################################
// ���C���֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �g�p���Ȃ��ꎞ�ϐ��𖾎�
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // �E�B���h�E�N���X�\���̂̐ݒ�
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;                          // �E�B���h�E�v���V�[�W���̎w��
    wc.lpszClassName = CLASS_NAME;                     // �N���X���̐ݒ�
    wc.hInstance = hInstance;                          // �C���X�^���X�n���h���̎w��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // �}�E�X�J�[�\�����w��
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); // �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�

    // �N���X�o�^
    RegisterClass(&wc);


    // �E�B���h�E�X�^�C��
    DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

    // ��{��`���W
    RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɐV���ȋ�`���W���v�Z
    AdjustWindowRect(&window_rect, window_style, FALSE);

    // �V����Window�̋�`���W���畝�ƍ������Z�o
    int window_width = window_rect.right - window_rect.left;
    int window_height = window_rect.bottom - window_rect.top;

    // �v���C�}�����j�^�[�̉�ʉ𑜓x�擾
    int desktop_width = GetSystemMetrics(SM_CXSCREEN);
    int desktop_height = GetSystemMetrics(SM_CYSCREEN);

    // �f�X�N�g�b�v�̐^�񒆂ɃE�B���h�E�����������悤�ɍ��W���v�Z
    // ��������������A�f�X�N�g�b�v���E�B���h�E���傫���ꍇ�͍���ɕ\��
    int window_x = max((desktop_width - window_width) / 2, 0);
    int window_y = max((desktop_height - window_height) / 2, 0);

    // �E�B���h�E�̐���
    g_hWnd = CreateWindow(
        CLASS_NAME,     // �E�B���h�E�N���X
        WINDOW_CAPTION, // �E�B���h�E�e�L�X�g
        window_style,   // �E�B���h�E�X�^�C��
        window_x,       // �E�B���h�E���Wx
        window_y,       // �E�B���h�E���Wy
        window_width,   // �E�B���h�E�̕�
        window_height,  // �E�B���h�E�̍���
        NULL,           // �e�E�B���h�E�n���h��
        NULL,           // ���j���[�n���h��
        hInstance,      // �C���X�^���X�n���h��
        NULL            // �ǉ��̃A�v���P�[�V�����f�[�^
    );

    if( g_hWnd == NULL ) {
        // �E�B���h�E�n���h�������炩�̗��R�Ő����o���Ȃ�����
        return -1;
    }

    // �w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
    ShowWindow(g_hWnd, nCmdShow);


	// �Q�[���̏�����(Direct3D�̏�����)
	if( !Initialize() ) {
        // �Q�[���̏������Ɏ��s����
		return -1;
	}

	Input::GetInstance().Init(hInstance, g_hWnd);

    // Windows�Q�[���p���C�����[�v
    MSG msg = {}; // msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            // ���b�Z�[�W������ꍇ�̓��b�Z�[�W������D��
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // �Q�[���̍X�V
			Update();
			// �Q�[���̕`��
			Draw();
        }
    }

	// �Q�[���̏I������(Direct3D�̏I������)
	Finalize();

    return (int)msg.wParam;
}

//#######################################################################
// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg ) {
        case WM_KEYDOWN:
            if( wParam == VK_ESCAPE ) {
                SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
            }
            break;

        case WM_CLOSE:
            if( MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK ) {
                DestroyWindow(hWnd); // �w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
            }
            return 0; // DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����邱�Ƃɂ���ĉ����Ȃ��������Ƃɂ���

        case WM_DESTROY: // �E�B���h�E�̔j�����b�Z�[�W
            PostQuitMessage(0); // WM_QUIT���b�Z�[�W�̑��M
            return 0;
    };

    // �ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//#######################################################################
// �Q�[���̏������֐�
bool Initialize(void)
{
    // Direct3D���b�p�[���W���[���̏�����
    if( !MyDirect3D_Initialize(g_hWnd) ) {
        return false;
    }

    // �e�N�X�`���̓ǂݍ���
    if( Texture_Load() > 0 ) {
        MessageBox(g_hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);
    }

	cameraPos = D3DXVECTOR3(0,0,-2);

	cubes.push_back(new Cube(g_hWnd));
	cubes.push_back(new Cube(g_hWnd));
	cubes.push_back(new Cube(g_hWnd));

	cubes[1]->SetPosition(D3DXVECTOR3(1, 0, 0));
	cubes[2]->SetLocalPosition(D3DXVECTOR3(-0.5f, 0, 0));

	//yoko
	for (int i = 0; i < 100; i++) {
		lines.push_back(new Line(D3DXVECTOR3(10,-0.5f,(i-50)*0.1f), D3DXVECTOR3(-10,-0.5f, (i - 50)*0.1f)));
	}
	for (int i = 0; i < 100; i++) {
		lines.push_back(new Line(D3DXVECTOR3((i - 50)*0.1f, -0.5f, -10), D3DXVECTOR3((i - 50)*0.1f, -0.5f, 10)));
	}

	//================================================================
	//������ǉ��@3D�|���S���p���_�̏���
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,
	//							D3DUSAGE_WRITEONLY,
	//							FVF_VERTEX_3D,
	//							D3DPOOL_MANAGED,
	//							&g_pD3DVtxBuff,
	//							NULL);

	////���_�o�b�t�@�̒��g�𖄂߂�
	//VERTEX_3D *pVtx;

	////���_�o�b�t�@�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//float size = 0.1f;

	////���_���W�̐ݒ�
	//pVtx[0].vtx = D3DXVECTOR3(-size, size, -size);
	//pVtx[1].vtx = D3DXVECTOR3(size, size, -size);
	//pVtx[2].vtx = D3DXVECTOR3(-size, -size, -size);
	//pVtx[3].vtx = D3DXVECTOR3(size, size, -size);
	//pVtx[4].vtx = D3DXVECTOR3(size, -size, -size);
	//pVtx[5].vtx = D3DXVECTOR3(-size, -size, -size);

	//pVtx[6].vtx = D3DXVECTOR3(size, size, size);
	//pVtx[7].vtx = D3DXVECTOR3(size, -size, size);
	//pVtx[8].vtx = D3DXVECTOR3(size, size, -size);
	//pVtx[9].vtx = D3DXVECTOR3(size, -size, size);
	//pVtx[10].vtx = D3DXVECTOR3(size, -size, -size);
	//pVtx[11].vtx = D3DXVECTOR3(size, size, -size);

	//pVtx[12].vtx = D3DXVECTOR3(-size, -size, size);
	//pVtx[13].vtx = D3DXVECTOR3(-size, size, -size);
	//pVtx[14].vtx = D3DXVECTOR3(-size, -size, -size);
	//pVtx[16].vtx = D3DXVECTOR3(-size, size, -size);
	//pVtx[15].vtx = D3DXVECTOR3(-size, size, size);
	//pVtx[17].vtx = D3DXVECTOR3(-size, -size, size);

	//pVtx[18].vtx = D3DXVECTOR3(-size, size, size);
	//pVtx[19].vtx = D3DXVECTOR3(-size, -size, size);
	//pVtx[20].vtx = D3DXVECTOR3(size, size, size);
	//pVtx[21].vtx = D3DXVECTOR3(size, size, size);
	//pVtx[22].vtx = D3DXVECTOR3(-size, -size, size);
	//pVtx[23].vtx = D3DXVECTOR3(size, -size, size);

	//pVtx[24].vtx = D3DXVECTOR3(-size, size, size);
	//pVtx[25].vtx = D3DXVECTOR3(size, size, size);
	//pVtx[26].vtx = D3DXVECTOR3(size, size, -size);
	//pVtx[27].vtx = D3DXVECTOR3(-size, size, size);
	//pVtx[28].vtx = D3DXVECTOR3(size, size, -size);
	//pVtx[29].vtx = D3DXVECTOR3(-size, size, -size);

	//pVtx[30].vtx = D3DXVECTOR3(-size, -size, size);
	//pVtx[31].vtx = D3DXVECTOR3(size, -size, -size);
	//pVtx[32].vtx = D3DXVECTOR3(size, -size, size);
	//pVtx[33].vtx = D3DXVECTOR3(-size, -size, size);
	//pVtx[34].vtx = D3DXVECTOR3(-size, -size, -size);
	//pVtx[35].vtx = D3DXVECTOR3(size, -size, -size);

	////�@���x�N�g���̐ݒ�
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f); 

	//pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[9].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[10].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[11].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//pVtx[12].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[13].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[14].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[15].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[16].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[17].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//pVtx[18].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[19].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[20].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[21].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[22].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[23].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//pVtx[24].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[25].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[26].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[27].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[28].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[29].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//pVtx[30].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[31].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[32].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[33].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[34].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[35].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	////���ˌ��̐ݒ�
	//pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//pVtx[6].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//pVtx[7].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//pVtx[8].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//pVtx[9].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//pVtx[10].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//pVtx[11].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//pVtx[12].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//pVtx[13].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//pVtx[14].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//pVtx[15].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//pVtx[16].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//pVtx[17].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	//pVtx[18].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[19].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[20].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[21].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[22].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[23].diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	//pVtx[24].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); //���F
	//pVtx[25].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[26].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[27].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[28].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[29].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	//pVtx[30].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f); //�s���N
	//pVtx[31].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[32].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[33].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[34].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[35].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

	////�e�N�X�`���̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);

	//pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[10].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);

	//pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[16].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[17].tex = D3DXVECTOR2(0.0f, 1.0f);

	//pVtx[18].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[20].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[22].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[23].tex = D3DXVECTOR2(0.0f, 1.0f);

	//pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[27].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[28].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[29].tex = D3DXVECTOR2(0.0f, 1.0f);

	//pVtx[30].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[31].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[32].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);

	//g_pD3DVtxBuff->Unlock();


	//��������\�����C���p

	/*pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&lineBuffer,
		NULL);

	VERTEX_3D *lineV;

	lineBuffer->Lock(0, 0, (void**)&lineV, 0);

	lineV[0].vtx = D3DXVECTOR3(100,0,0);
	lineV[1].vtx = D3DXVECTOR3(-100,0,0);

	lineBuffer->Unlock();*/


	//�����܂Ł@3D�|���S���p���_�̏���
	//================================================================


    return true;
}

//#######################################################################
// �Q�[���̍X�V�֐�
void Update(void)
{
    g_Rotation += 0.05f;	//�K���Ɋp�x�̑����𑝂₷

	Input::GetInstance().Update();
}

//#######################################################################
// �Q�[���̕`��֐�
void Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
    if( !pDevice ) return;
     
    // ��ʂ̃N���A
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(10, 40, 20, 255), 1.0f, 0);

    // �`��o�b�`���߂̊J�n
    pDevice->BeginScene();

	//==============================================
	//������ǉ��@�e�X�g�p�J������������
	g_posCameraEye = cameraPos;
	g_posCameraAt = cameraPos + D3DXVECTOR3(0,0,2);
	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�r���[�s��̍쐬
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCameraEye,
		&g_posCameraAt,
		&g_vecCameraUp);

	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	//==============================================
	// ������ǉ��@�e�X�g�p�v���W�F�N�V�����s��̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjectioin,
								VIEW_ANGLE,         //�r���[���ʂ̎���p
								VIEW_ASPECT,		//�r���[���ʂ̃A�X�y�N�g��
								VIEW_NEAR_Z,		//�r���[���ʂ�NearZ
								VIEW_FAR_Z         //�r���[���ʂ�FarZ
	);

	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjectioin);

	//=============================================================
	//������ǉ��@�|���S���̃��[���h�s��̍쐬
	//D3DXMATRIX mtxScl;
	//D3DXMATRIX mtxRot;
	//D3DXMATRIX mtxTrs;

	//g_pos = D3DXVECTOR3(0, 0, 0);
	//g_rot = D3DXVECTOR3(0, g_Rotation*1.4f, g_Rotation);
	//g_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	////���[���h�s���P�ʍs��֏�����
	//D3DXMatrixIdentity(&g_mtxWorld);

	////�X�P�[���s����쐬�����[���h�s��֍���
	//D3DXMatrixScaling(&mtxScl, g_scl.x, g_scl.y, g_scl.z);
	//D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	////��]�s����쐬�����[���h�s��֍���
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rot.y, g_rot.x, g_rot.z);
	//D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

	////���s�s��
	//D3DXMatrixTranslation(&mtxTrs, g_pos.x, g_pos.y, g_pos.z);
	//D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrs);

	////���[���h�}�g���N�X��ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	////�`�悵�����|���S�����_�o�b�t�@���f�[�^�X�g���[���ɃZ�b�g
	//pDevice->SetStreamSource(0, g_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	////�|���S���̕`��
	//pDevice->SetFVF(FVF_VERTEX_3D);

	////�|���S���̕`��
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	////pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KIZUNA));
	//pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 12);

	//�����܂ł�ǉ��@
	//=============================================================  

	cubes[1]->SetRotation(cubes[1]->GetRotation() + D3DXVECTOR3(0, 0.01f, 0.1f));
	cubes[2]->SetRotation(cubes[2]->GetRotation() + D3DXVECTOR3(0, 0.01f, -0.1f));

	if (isUp) {
		cubes[0]->SetPosition(cubes[0]->GetPosition() + D3DXVECTOR3(0, 0.01f, 0));
	} else {
		cubes[0]->SetPosition(cubes[0]->GetPosition() + D3DXVECTOR3(0, -0.01f, 0));
	}
	if (cubes[0]->GetPosition().y >= 1) {
		isUp = false;
	}
	if (cubes[0]->GetPosition().y <= -1) {
		isUp = true;
	}

	for each (Cube* cube in cubes) {
		cube->Draw();
	}
	for each (Line* line in lines) {
		line->Draw();
	}

	if (Input::GetInstance().GetKey(DIK_A)) {
		cameraPos.x -= 0.01f;
	}
	if (Input::GetInstance().GetKey(DIK_D)) {
		cameraPos.x += 0.01f;
	}
	if (Input::GetInstance().GetKey(DIK_W)) {
		cameraPos.z += 0.01f;
	}
	if (Input::GetInstance().GetKey(DIK_S)) {
		cameraPos.z -= 0.01f;
	}

    // �`��o�b�`���߂̏I��
    pDevice->EndScene();

    // �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
    pDevice->Present(NULL, NULL, NULL, NULL);
}

//#######################################################################
// �Q�[���̏I������
void Finalize(void)
{
    // �e�N�X�`���̉��
    Texture_Release();

    // Direct3D���b�p�[���W���[���̏I������
    MyDirect3D_Finalize();




}
