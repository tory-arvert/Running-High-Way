/// @file GraphicsManagerImplDirect3D.hpp
/// @brief �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X�pImpl - ����
/// @note DirectX�p�̕`��f�o�C�X�̏������s���B
/// @date 2012/12/18     tory

//====================================================================
//              GraphicsManagerImplDirect3D.hpp
//--------------------------------------------------------------------
//    �������e : �`��f�o�C�X�̏������Ǘ�����N���X��Impl - ����
//    �������e : 
//    �쐬�ڍ� : 2012/12/18
//    �⑫     : DirectX�p�̕`��f�o�C�X�̏������s���B
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2012/04/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_H
#define INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_H

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>              // D3DFVF_XYZRHW���̎g�p�ɕK�v

#include "IGraphicsManagerImpl.h"
#include <tiostream.h>          // tstring�^�Ȃǂ�TCHAR�g����`
#include "TemplateBaseClass.hpp"
#include "Comptr.hpp"

#include "ISpriteImpl.h"

// StaticLib�v���W�F�N�g�̃v���p�e�B����lib���Ăяo���ꍇwarning���o�邽�߁A����̑�p�@
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


namespace GameLib{
    namespace Graphics{

        using namespace std;

        /// @brief stateFlag
        /// @brief Direct3D���̏�ԃt���O�Ɋւ�����̂��W�߂��N���X
        class D3DStatesFlag{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            bool mFullScreen;           ///< @brief �t���X�N���[�����[�h�t���O
            bool mVSync;                ///< @brief ���������t���O
            bool mAntiAlias;            ///< @brief �A���`�G�C���A�X�t���O
            bool mRenderable;           ///< @brief �`��\���
            bool mVertexShaderReady;    ///< @brief ���_�V�F�[�_�̗L��
            bool mPixelShaderReady;     ///< @brief �s�N�Z���V�F�[�_�̗L��

            DWORD mVertexVersion;       ///< @brief ���_�V�F�[�_��ver
            DWORD mPixelVersion;        ///< @brief �s�N�Z���V�F�[�_��ver

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:
            
            /// @brief �R���X�g���N�^
            D3DStatesFlag(){
                mFullScreen         = false;
                mVSync              = false;
                mAntiAlias          = false;
                mRenderable         = false;
                mVertexShaderReady  = false;
                mPixelShaderReady   = false;     
                mVertexVersion      = 0;
                mPixelVersion       = 0;
            }
            
            /// @brief �f�X�g���N�^
            ~D3DStatesFlag(){}
            


            //----------------------------------------------------------
            // �����o�֐�
        public:

            //----------------------------------------
            // �A�N�Z�T
        public:

            /// @brief �t���X�N���[���t���O�l��ݒ肵�܂��B
            void setFullScreen(const bool value){
                mFullScreen = value;
            }

            /// @brief ���������t���O�l��ݒ肵�܂��B
            void setVSync(const bool value){
                mVSync = value;
            }

            /// @brief �A���e�G�C���A�X�t���O�l��ݒ肵�܂��B
            void setAntiAlias(const bool value){
                mAntiAlias = value;
            }

            /// @brief �����ݕ`��\�ȏ�Ԃ�ݒ肵�܂��B
            void setRenderable(const bool value){
                mRenderable = value;
            }

            /// @brief ���_�V�F�[�_�̗L����ݒ肵�܂��B
            void setVertexShaderReady(const bool value){
                mVertexShaderReady = value;
            }

            /// @brief �s�N�Z���V�F�[�_�̗L����ݒ肵�܂��B
            void setPixelShaderReady(const bool value){
                mPixelShaderReady = value;
            }

            /// @brief ���_�V�F�[�_�̃o�[�W�������L�^���܂��B
            void setVertexVersion(const DWORD value){
                mVertexVersion = value;
            }

            /// @brief �s�N�Z���V�F�[�_�̃o�[�W�������L�^���܂��B
            void setPixelVersion(const DWORD value){
                mPixelVersion = value;
            }

           //----------------------------------------

            /// @brief �t���X�N���[���t���O�l��Ԃ��܂��B
            const bool isFullScreen() const { return mFullScreen; }

            /// @brief ���������t���O�l��Ԃ��܂��B
            const bool isVSync() const { return mVSync; }

            /// @brief �A���e�G�C���A�X�t���O�l��Ԃ��܂��B
            const bool isAntiAlias() const { return mAntiAlias; }

            /// @brief �����ݕ`��\�ȏ�Ԃ��Ԃ��܂��B
            const bool isRenderable() const { return mRenderable;}

            /// @brief ���_�V�F�[�_�̗L����Ԃ��܂��B
            const bool isVertexShaderReady() const { return mVertexShaderReady; }

            /// @brief �s�N�Z���V�F�[�_�̗L����Ԃ��܂��B
            const bool isPixelShaderReady() const { return mPixelShaderReady; }

            /// @brief ���_�V�F�[�_�̃o�[�W������Ԃ��܂��B
            /// @param a_Major ���W���[�o�[�W����
            /// @param a_Minor �}�C�i�[�o�[�W����
            void getVertexVersion(int* a_Major, int* a_Minor) const {            
                *a_Major = ((mVertexVersion)>>8 & 0xFF);
                *a_Minor = ((mVertexVersion)>>0 & 0xFF);
            }

            /// @brief �s�N�Z���V�F�[�_�̃o�[�W������Ԃ��܂��B
            /// @param a_Major ���W���[�o�[�W����
            /// @param a_Minor �}�C�i�[�o�[�W����
            void getPixelVersion(int* a_Major, int* a_Minor) const {
                *a_Major = ((mPixelVersion)>>8 & 0xFF);
                *a_Minor = ((mPixelVersion)>>0 & 0xFF);
            }

        };


        /// @class ImplDirect3D
        /// @brief DirectX�`��f�o�C�X�̕`����Ǘ�����N���X
        class ImplDirect3D : public IGraphicsManagerImpl{

            //----------------------------------------------------------
            // �ʖ��錾

            /// @brief IDirect3D9�̃X�}�[�g�|�C���^�^
            typedef Com_ptr< IDirect3D9 >  IDirect3D9_sp;
            /// @brief IDirect3DDevice9�̃X�}�[�g�|�C���^�^
            typedef Com_ptr< IDirect3DDevice9 > IDirect3DDevice9_sp;
            /// @brief �X�v���C�g�C���^�[�t�F�C�X�̃X�}�[�g�|�C���^�^
            typedef shared_ptr< ISpriteImpl > ISpriteImpl_sp;
            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            tstring mTitle;     ///< @brief �E�B���h�E�^�C�g��
            HWND    mHandle;    ///< @brief �E�B���h�E�n���h��
            
            IDirect3D9_sp mDirect3D;        ///< @brief Direct3D9
            IDirect3DDevice9_sp mDevice;    ///< @brief �����_�����O�f�o�C�X
        
            BaseWH<int> mClient;            ///< @brief �x�[�X�N���C�A���g�̈�
            BaseWH<int> m2DClient;          ///< @brief 2D�`�掞�̊�̈�T�C�Y

            unsigned int mFrameCount;       ///< @brief ����܂ł̃t���[����

            D3DStatesFlag mStatesFlag;      ///< @brief Direct3D���̏�ԃt���O�Ɋւ�����̂��W�߂��N���X
            D3DPRESENT_PARAMETERS mPresentParams;   ///< @brief PresentParameters�\����
        public:
            /// @brief �X�v���C�g�̃C���^�[�t�F�C�X�p�C���v��
            /// @attention ����SpriteImpl��extern�Ŏg�p����d�g�݂ƂȂ��Ă���B
            ISpriteImpl_sp mSpriteImpl;     ///< @brief �X�v���C�g�̃C���^�[�t�F�C�X�C���v��

            //----------------------------------------------------------
            // ���ꃁ���o
        public:
                
            /// @brief �R���X�g���N�^
            ImplDirect3D(
                const HWND a_Handle,            // �E�B���h�E�n���h��
                const int a_Width,              // �N���C�A���gX�T�C�Y
                const int a_Height,             // �N���C�A���gY�T�C�Y
                const bool a_Fullscreen,        // �t���X�N���[���t���O
                const bool a_VSync,             // ���������t���O
                const bool a_AntiAlias,         // �A���`�G�C���A�X�t���O
                const int a_Width2D,            // 2D�`�掞�̊�̈�X�T�C�Y
                const int a_Height2D            // 2D�`�掞�̊�̈�Y�T�C�Y
                ):
            mDirect3D( NULL ),
            mDevice( NULL ),
            mFrameCount( 0 )
            {
                // ���ʃ����o������
                Init( a_Handle, a_Width, a_Height, a_Fullscreen, a_VSync, a_AntiAlias );

                // 2D�`�掞�̊�̈�T�C�Y��ݒ肷��B�����Sprite��Font�̕`�掞�ɏk�ڂ������␳���Ă����B
                // ���̃T�C�Y�͏���쐬���̂ݐݒ�\�Ƃ���B
                m2DClient.setWH( a_Width2D, a_Height2D );

                // COM�̏�����
                InitD3D9();
                // �V�F�[�_�̗L�����m�F
                isReadyShader();
                // �v���[���g�p�����[�^�̏�����
                InitPresentParams();
                // �f�o�C�X�̍쐬
                auto a_Success = CreateDevice();
                    
                // �f�o�C�X�̍쐬�ɐ���������
                if( a_Success ){ 
                
                    // �`��\��Ԃ�ݒ�
                    mStatesFlag.setRenderable( true );
                    // �e�N�X�`��0stage��SamplerState��ݒ肵�Ă����B
                    setSamplerState(0);
            
                }
            }

            /// @brief �f�X�g���N�^
            virtual ~ImplDirect3D(){}

            //----------------------------------------------------------
            // �����o�֐�


            /// @brief  �`��J�n
            void BeginDraw()
            {
                // �t���[���J�E���g
                ++mFrameCount;

                //��ʂ��N���A( �F�ŃN���A )
                mDevice->Clear( 
                    0,
                    0,
                    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                    D3DCOLOR_XRGB( 0, 0, 128 ),
                    1.0f,
                    0
                    );
                //�`��J�n��錾
                mDevice->BeginScene();
            }


            /// @brief  �`��I��
            void EndDraw()
            {
                HRESULT hr = S_OK;

                //�`��I����錾
                mDevice->EndScene();
                //�o�b�N�o�b�t�@��]������
                hr = mDevice->Present( 0, 0, 0, 0 );

                // �f�o�C�X���X�g�������ɕ��A�������s��
                if ( hr == D3DERR_DEVICELOST )
                {
                    // �`��s�\���
                    mStatesFlag.setRenderable( false );
                }
            }

            /// @brief �t���X�N���[���l�Ȃǂ̕ω��𔽉f�����邽�߂�
            /// @brief ���݂̃f�o�C�X��j����A�V���ɍč\�z���܂��B
            void RecreateDevice(){

                // ���\�[�X�j�����ɃA�N�Z�X���Ȃ��悤�ɕ`��s�ɐݒ�
                mStatesFlag.setRenderable( false );

                // ���\�[�X�̊J��
                CleanupResource();

                // �f�o�C�X�̊J��(Comptr�Ȃ̂�NULL����ɂĊJ��)
                mDevice = NULL;

                // �V�����t���O�l�̏�ԂɂȂ�悤�v���[���g�p�����[�^��������
                InitPresentParams();

                // �f�o�C�X�̍č쐬
                CreateDevice();
                
                // ���\�[�X�̍č쐬
                RecreateResource();

                // ���\�[�X�ɃA�N�Z�X�ł���悤�ɂȂ������ߕ`��\�ɐݒ�
                mStatesFlag.setRenderable( true );

            }


            /// @brief  Direct3D�f�o�C�X�̕��A�����݂܂��B
            /// @retval true ���한�A����
            /// @retval false �ُ�I��
            const bool Restore()
            {
                HRESULT hr = S_OK;

                // �f�o�C�X�����A�\�����m�F
                hr = mDevice->TestCooperativeLevel();
                switch( hr )
                {
                // ���A�\���
                case D3DERR_DEVICENOTRESET:
                    hr = mDevice->Reset( &mPresentParams );
                    if ( FAILED( hr ) )
                    {
                        // �f�o�C�X���A�͔���Ɏ��Ԃ�������Ƃ������邽�߁A���񂩌J��Ԃ��K�v������ꍇ������B
                        // ���̂��ߖ��񃁃b�Z�[�W��\������Ƃ܂����\���������B
                        // MessageBox(NULL,_T("�f�o�C�X���X�g����̕��A�Ɏ��s���܂����B"),_T("���A��ƒ��~"),MB_OK);
                        return false;
                    }
                }

                return true;
            }


            //----------------------------------------
            // �A�N�Z�T
            /// @brief  Direct3DDevice9���擾���܂��B
            /// @return Direct3DDevice9�ւ̃X�}�[�g�|�C���^
            /// @note �f�o�C�X�擾�͊O���Ɍ��J�����Aextern�ŕK�v�ȃN���X�̓����ł̂ݎg�p�ł���悤�ɂ���B
            IDirect3DDevice9_sp getDevice() const {
                return mDevice;
            }

            /// @brief ���_�V�F�[�_���g�p�\���ǂ�����Ԃ��܂��B
            /// @return bool ���_�V�F�[�_�̎g�p�̉�
            const bool getVertexShaderReady() const { return mStatesFlag.isVertexShaderReady(); }

            /// @brief �s�N�Z���V�F�[�_���g�p�\���ǂ�����Ԃ��܂��B
            /// @return bool �s�N�Z���V�F�[�_�̎g�p�̉�
            const bool getPixelShaderReady() const { return mStatesFlag.isPixelShaderReady(); }

            /// @brief 2D�p�̊�̈�T�C�Y���擾���܂��B
            /// @param a_w ��̕���Ԃ��܂��B
            /// @param a_h ��̍�����Ԃ��܂��B
            void get2DClientSize( int *a_w, int *a_h){
                *a_w = m2DClient.width();
                *a_h = m2DClient.height();
            }

            /// @brief �N���C�A���g�̈�T�C�Y���擾���܂��B
            /// @param a_w ��̕���Ԃ��܂��B
            /// @param a_h ��̍�����Ԃ��܂��B
            void getClientSize( int *a_w, int *a_h){
                *a_w = mClient.width();
                *a_h = mClient.height();
            }



            /// @brief  ����܂ł̃t���[���J�E���g���擾���܂��B
            /// @return �t���[���J�E���g
            const int getFrameCount() const{
                return mFrameCount;
            }

            /// @brief  �f�o�C�X���`��\��Ԃ����m�F���܂��B
            /// @retval true �`��\
            /// @retval false �`��s�\
            const bool isRenderable() const {
                return mStatesFlag.isRenderable();
            }

            /// @brief �t���X�N���[�����[�h�̃t���O��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setFullScreen(const bool value){
                mStatesFlag.setFullScreen( value );
            }

            /// @brief ���������̃t���O�l��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setVSync(const bool value){
                mStatesFlag.setVSync( value );
            }

            /// @brief �A���`�G�C���A�X�̃t���O�l��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setAntialias(const bool value){
                mStatesFlag.setAntiAlias( value );
            }

            /// @brief �N���C�A���g�T�C�Y��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setClientSize(const int a_Width, const int a_Height){
                mClient.setWH( a_Width, a_Height );
                RecreateDevice();
            }

            //----------------------------------------
            // �w���p�[�֐�
        protected:


            /// @brief  ���ʃ����o�����������܂��B
            /// @param  a_Handle        �`��Ώۂ̃E�B���h�E�n���h��
            /// @param  a_Width         �E�B���h�E�̍���
            /// @param  a_Height        �E�B���h�E�̕�
            /// @param  a_Fullscreen    �t���X�N���[��
            /// @param  a_VSync         ��������
            /// @param  a_AntiAlias     �A���`�G�C���A�X
            void Init(
                const HWND a_Handle,
                const int a_Width,
                const int a_Height,
                const bool a_Fullscreen,
                const bool a_VSync,
                const bool a_AntiAlias
                ){
                mHandle = a_Handle;
                mClient.setWH( a_Width, a_Height );
                mStatesFlag.setFullScreen( a_Fullscreen );
                mStatesFlag.setVSync( a_VSync );
                mStatesFlag.setAntiAlias( a_AntiAlias );

            } // end of void Init


            /// @brief DirectX���g�p�ł���悤�ɏ��������܂��B
            /// @note �R���X�g���N�^��p�w���p�[�֐�
            const bool InitD3D9(){
                mDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
                // ����Ɏ擾�ł������̃`�F�b�N
                return (mDirect3D != nullptr) ? true : false;
            }


            /// @brief  �V�F�[�_�@�\�̗L�����m�F
            /// @note �R���X�g���N�^��p�w���p�[�֐�
            const bool isReadyShader()
            {
                HRESULT hr = S_OK;

                // �n�[�h�E�F�A�����擾
                D3DCAPS9 caps;
                ZeroMemory(&caps, sizeof(caps));
                hr = mDirect3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

                // VertexShader1.1���m�F
                mStatesFlag.setVertexShaderReady( caps.VertexShaderVersion >= D3DVS_VERSION( 1, 1 ) );
                mStatesFlag.setVertexVersion(caps.VertexShaderVersion);

                // PixelShader2.2���m�F
                mStatesFlag.setPixelShaderReady( caps.PixelShaderVersion >= D3DPS_VERSION( 2, 0 ) );
                mStatesFlag.setPixelVersion( caps.PixelShaderVersion );

                return (hr == S_OK ? true : false);
            }

            /// @brief PresentParameters�̂̏����������܂��B
            /// @attention �������O��HWND�Ȃǂ̎w���Y��Ȃ����ƁB
            void InitPresentParams(){
                ZeroMemory(&mPresentParams, sizeof(mPresentParams));
                // �t���X�N���[���ƃE�B���h�E���[�h�̐ݒ�
                mPresentParams.Windowed                     = !mStatesFlag.isFullScreen();
                // �o�b�N�o�b�t�@�̃X���b�v�G�t�F�N�g = Direct3D�ɃX���b�v�G�t�F�N�g���܂�����
                mPresentParams.SwapEffect                   = D3DSWAPEFFECT_DISCARD;
                // �o�b�N�o�b�t�@�̃t�H�[�}�b�g
                SelectBackBufferFormat();
                // Direct3D�ɐ[�x�o�b�t�@�̊Ǘ����܂�����
                mPresentParams.EnableAutoDepthStencil       = true;
                // �[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
                mPresentParams.AutoDepthStencilFormat       = D3DFMT_D16;
                // �J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E�n���h��
                mPresentParams.hDeviceWindow                = mHandle;
                // �t���X�N���[�����̉�ʂ̃T�C�Y�i�o�b�N�o�b�t�@�̕�,�o�b�N�o�b�t�@�̍����j
                mPresentParams.BackBufferWidth              = mClient.width();
                mPresentParams.BackBufferHeight             = mClient.height();

                // �o�b�N�o�b�t�@�̐� = 1
                mPresentParams.BackBufferCount              = 1;
                // �}���`�T���v�����O�֘A��ݒ肷��B
                SelectMultiSample();
                // �t���O�͎g��Ȃ�
                mPresentParams.Flags                        = 0;
                // ���̃��t���b�V�����[�g�����̂܂܎g��
                SelectRefreshRateInHz();
                // ����������ݒ肷��B
                SelectVSync();
            }


            /// @brief �}���`�T���v�����O���A���`�G�C���A�X�t���O�l�ɍ��킹�Ď����Őݒ肵�܂��B
            /// @attention �A���`�G�C���A�X�t���O�l��true�̏ꍇ�A�ݒ�\�͈͓��ł̍ő�l��I�����܂��B
            /// @note InitPresentParams��p�w���p�[�֐���p�w���p�[�֐�
            void SelectMultiSample(){

                // �A���`�G�C���A�X�������ɐݒ肳��Ă����ꍇ
                if(!mStatesFlag.isAntiAlias()){
                    // �A���`�G�C���A�X���g��Ȃ��ꍇ��None�ɐݒ肷��B
                    mPresentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
                    mPresentParams.MultiSampleQuality = 0;
                    return;
                }

                // �A���`�G�C���A�X���L���ɐݒ肳��Ă����ꍇ
                HRESULT hr = E_FAIL;
                DWORD qualityBackBuffer = 0;
                DWORD qualityZBuffer = 0;
                DWORD antialiasChoiceCount = (DWORD)D3DMULTISAMPLE_16_SAMPLES;

                while( antialiasChoiceCount ){
                    //�����_�����O�^�[�Q�b�g�ŃA���`�G�C���A�V���O���T�|�[�g����Ă��邩���`�F�b�N
                    hr = mDirect3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
                                                                D3DDEVTYPE_HAL,
                                                                mPresentParams.BackBufferFormat,
                                                                mPresentParams.Windowed,
                                                                (D3DMULTISAMPLE_TYPE)antialiasChoiceCount,
                                                                &qualityBackBuffer );
                    if( SUCCEEDED(hr) ){
                        //�[�x�X�e���V�� �T�[�t�F�C�X�ŃA���`�G�C���A�X���T�|�[�g����Ă��邩���`�F�b�N
                        hr = mDirect3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
                                                                    D3DDEVTYPE_HAL,
                                                                    mPresentParams.AutoDepthStencilFormat,
                                                                    mPresentParams.Windowed,
                                                                    (D3DMULTISAMPLE_TYPE)antialiasChoiceCount,
                                                                    &qualityZBuffer );
                        if( SUCCEEDED(hr) ){
                            // �A���`�G�C���A�X���g�p�ł���̂�D3DPRESENT_PARAMETERS�Ƀ^�C�v���Z�b�g����B
                            mPresentParams.MultiSampleType = (D3DMULTISAMPLE_TYPE)antialiasChoiceCount;
            
                            // QualityBackBuffer��QualityZBuffer�ŏ��������̒l��L���ɂ���B
                            // �ǂ�ȃp�^�[���Œl���Ԃ�̂��킩��Ȃ����߁A���̂悤�ȏ����ɂ��Ă���B
                            ( qualityBackBuffer < qualityZBuffer ) ?
                                mPresentParams.MultiSampleQuality = qualityBackBuffer - 1 :
                                mPresentParams.MultiSampleQuality = qualityZBuffer - 1;
                            break;
                        }
                    }
      
                //���݂̃^�C�v�ŃA���`�G�C���A�X���g�p�ł��Ȃ��̂ŁA�P�i�K�Ⴂ�^�C�v�ōă`�F�b�N����B
                --antialiasChoiceCount;
                }

            }




            /// @brief �o�b�N�o�b�t�@�̃t�H�[�}�b�g�������őI�����܂��B
            /// @note InitPresentParams��p�w���p�[�֐�
            void SelectBackBufferFormat(){

                // �E�B���h�E���[�h�̂Ƃ�
                if(mPresentParams.Windowed){
                   mPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
                } 

                // �t���X�N���[�����[�h�̂Ƃ�
                // ���݂̃v���C�}���f�B�X�v���C�A�_�v�^�̃��[�h���擾����
                // �f�B�X�v���C���[�h�̏������߂�
                D3DDISPLAYMODE displayMode;
                ZeroMemory(&displayMode, sizeof(displayMode));

                if(FAILED( mDirect3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &displayMode )))
                {
                    MessageBox(NULL, _T("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���"), _T("DirectX"),MB_OK | MB_ICONSTOP);
                    mPresentParams.BackBufferFormat = D3DFMT_UNKNOWN; 
                    return;
                }

                mPresentParams.BackBufferFormat = displayMode.Format;
            }

            /// @brief ���t���b�V�����[�g�������őI��ݒ肵�܂��B
            /// @note InitPresentParams��p�w���p�[�֐�
            void SelectRefreshRateInHz(){

                // �E�B���h�E���[�h����0���g�p
                if( mPresentParams.Windowed ){
                    mPresentParams.FullScreen_RefreshRateInHz = 0;
                    return;
                }

                // �t���X�N���[�����[�h��
                // ���̃��t���b�V�����[�g�����̂܂܎g��
                mPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

            }

            /// @brief �t���O�l�̐ݒ�ɂ���Đ��������������Őݒ肵�܂��B
            /// @attention ���������̓t���X�N���[�����łȂ��ƗL���ɂȂ�܂���B
            /// @note InitPresentParams��p�w���p�[�֐�
            void SelectVSync(){

                if(mStatesFlag.isVSync() & mStatesFlag.isFullScreen()){ 
                    mPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
                    return;
                }
                mPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
                return;
            }



            /// @brief Direct3D�f�o�C�X���쐬���܂��B
            const bool CreateDevice(){

                HRESULT hr = S_OK;

                // �n�[�h�E�F�A�f�o�C�X�̍쐬( VertexShader1.1���L���� )
                if ( mStatesFlag.isVertexShaderReady() ){

                    hr = mDirect3D->CreateDevice(
                                        D3DADAPTER_DEFAULT,
                                        // �n�[�h�E�F�A�`�揈��
                                        D3DDEVTYPE_HAL,
                                        mHandle,
                                        // HARDWARE���_���� | ���x�͎኱�����邪������{���x�ɂ���B
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                        &mPresentParams,
                                        mDevice.ToCreator()
                                    );
                } else {
                    hr = D3DERR_INVALIDDEVICE;
                }

                // (���_)�\�t�g�E�F�A�f�o�C�X�̍쐬( VertexShader1.1��Ή� or �쐬���s�� )
                if ( FAILED( hr ) )
                {
                    hr = mDirect3D->CreateDevice(
                                        D3DADAPTER_DEFAULT,
                                        // �n�[�h�E�F�A�`�揈��
                                        D3DDEVTYPE_HAL,
                                        mHandle,
                                        // SOFTWARE���_���� | ���x�͎኱�����邪������{���x�ɂ���B
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                        &mPresentParams,
                                        mDevice.ToCreator()
                                    );
                }

                // �\�t�g�E�F�A�f�o�C�X�̍쐬( ����ɍ쐬���s���A�������x�͖ڂ����Ă��Ȃ��c )
                if ( FAILED( hr ) )
                {
                    hr = mDirect3D->CreateDevice(
                                        D3DADAPTER_DEFAULT,
                                        // �\�t�g�t�F�A�G�~�����[�V�����`�揈��
                                        D3DDEVTYPE_REF,
                                        mHandle,
                                        // SOFTWARE���_���� | ���x�͎኱�����邪������{���x�ɂ���B
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                        &mPresentParams,
                                        mDevice.ToCreator()
                                    );
                }



                // �ǂ̃f�o�C�X�쐬�ɂ����s�����ꍇ
                // ��O�R���e�i��throw����
                if ( FAILED( hr ) )
                {
                    MessageBox(NULL,_T("DirectX�f�o�C�X�̍쐬�Ɏ��s���܂����B\n�O���t�B�b�N�{�[�h���Ή����Ă��܂���B"), _T("Direct3D"),MB_OK);
                    return false;
                }

                return true;
            }

            /// @brief �e�N�X�`����samplerState��ݒ肵�܂��B
            void setSamplerState(const int a_No){
                // �g�厞�̃t�B���^�[
                mDevice->SetSamplerState(a_No, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
                // �k�����̃t�B���^�[
                mDevice->SetSamplerState(a_No, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
                // �~�b�v�}�b�v ���x���Ԃ̃t�B���^�[
                mDevice->SetSamplerState(a_No, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
            }

            /// @brief  ���������\�[�X�̑S������s���܂��B
            void CleanupResource()
            {
                // �����Ƀ��\�[�X��������郁�\�b�h���L�q
            
                // ������Ȃ���΂Ȃ�Ȃ���
                // - �����_�����O�^�[�Q�b�g
                // - �[�x�X�e���V���T�[�t�F�C�X
                // - �ǉ��X���b�v�`�F�[��
                // - �X�e�[�g�u���b�N
                // - D3DPOOL_DEFAULT���\�[�X
            }

            /// @brief  ���������\�[�X�̍č쐬���s���܂��B
            void RecreateResource()
            {
                // �����Ƀ��\�[�X���č쐬���郁�\�b�h���L�q
            
                // ������Ȃ���΂Ȃ�Ȃ���
                // - �����_�����O�^�[�Q�b�g
                // - �[�x�X�e���V���T�[�t�F�C�X
                // - �ǉ��X���b�v�`�F�[��
                // - �X�e�[�g�u���b�N
                // - D3DPOOL_DEFAULT���\�[�X
            }



        }; // end of class GraphicsManager

    } // end of namespace Graphics
} // end of namespace GameLib


#endif