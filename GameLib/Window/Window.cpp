/// @file window.cpp
/// @brief �E�B���h�E���쐬���鏈���N���X - ����
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              window.cpp
//--------------------------------------------------------------------
//    �������e : �E�B���h�E���쐬���鏈�� - ����
//    �������e : 
//    �쐬�ڍ� : 2011/09/01
//    �⑫     : 
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/09/01     tory
//         
//====================================================================


#include <Windows.h>                        // MessageBeep��E�B���h�E�v���V�[�W���Ȃǂ̊�{�ɕK�{
#include <memory>                           // unique_ptr�ȂǂɕK�v
#include <tiostream.h>                      // tstring�^�Ȃǂ�TCHAR�g����`

#include "window.h"


using namespace std;
using namespace GameLib::Window;


// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


// �����l�[���X�y�[�X��`
namespace{

    //----------------------------------------------------------
    // �萔��`

    /// @brief �E�B���h�E�^�C�g��
    const tstring WND_TITLE("GameApplication");
    /// @brief �E�B���h�E�N���X�l�[��
    const tstring WND_CLASSNAME("GameApplication");
    /// @brief �K��̃E�B���h�E�X�^�C��
    const DWORD WND_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    /// @class Impl
    /// @brief ���̃N���X
    class Impl
    {
        //----------------------------------------------------------
    public: // �����o�ϐ�

        tstring mTitle;      ///< @brief �E�B���h�E�^�C�g��
        tstring mClassName;  ///< @brief �N���X�l�[��
        int mIconID;        ///< @brief �A�C�R��ID
        int mClientWidth;   ///< @brief �`��̈扡��
        int mClientHeight;  ///< @brief �`��̈�c��
        int mWidth;         ///< @brief �E�B���h�E����
        int mHeight;        ///< @brief �E�B���h�E�c��
        bool mActive;       ///< @brief �E�B���h�E�̃A�N�e�B�u
        bool mFullScreen;   ///< @brief �t���X�N���[�����[�h
        int mPositionX;     ///< @brief X�ʒu
        int mPositionY;     ///< @brief Y�ʒu
        bool mMinimized;    ///< @brief �ŏ����t���O
        bool mEndRequested; ///< @brief �E�B���h�E�I���t���O
        HWND mHandle;       ///< @brief �E�B���h�E�n���h��
        bool mReady;        ///< @brief ���������t���O
        DWORD mStyle;       ///< @brief �E�B���h�E�X�^�C��

        //----------------------------------------------------------
    public: // ���ꃁ���o

        /// @brief �R���X�g���N�^
        Impl() :
            mTitle( WND_TITLE ),
            mClassName( WND_CLASSNAME ),
            mClientWidth( 1280 ),
            mClientHeight( 720 ),
            mWidth( 0 ),
            mHeight( 0 ),
            mIconID( 101 ),
            mActive( false ),
            mFullScreen( false ),
            mPositionX( 0 ),
            mPositionY( 0 ),
            mMinimized( false ),
            mEndRequested( false ),
            mHandle( NULL ),
            mReady( false ),
            mStyle( 0x0000 )
        {};



        /// @brief �f�X�g���N�^
        virtual ~Impl(){};


        //----------------------------------------------------------
    public: // �����o�֐�
        
        /// @brief �E�B���h�E��\�����܂��B
        /// @attention ����������Ă��Ȃ��ꍇ�A������init�֐����R�[������܂��B
        void Show()
        {
            // �񏉊�������init���R�[��
            if ( !mReady ){ 
                Init();
            }

            // �v���O�����J�n���̎w������Ƃɕ\��
            STARTUPINFO info;
            GetStartupInfo( &info );
            ShowWindow( mHandle, info.wShowWindow );
            UpdateWindow( mHandle );
        }



        /// @brief �f�B�X�v���C���[�h��؂�ւ��܂��B
        /// @param a_Flag true�Ńt���X�N���[���Afalse�ŃE�B���h�E�ł��B
        void EnableFullScreen( bool a_Flag ){

            // ����ݒ肷��l
            DWORD style = WS_VISIBLE;
            int px = 0;
            int py = 0;
            int w = 0;
            int h = 0;

            // �t���O���t���X�N���[��ON�ɐ؂�ւ��̏ꍇ�E�E�E
            if( a_Flag ){
                // ���݂̃E�B���h�E�ʒu���L�^���Ă���
                RECT rect;
                GetWindowRect( mHandle, &rect );
                mPositionX = rect.left;
                mPositionY = rect.top;

                // �t���X�N���[�����[�h���̐ݒ�
                px = 0;
                py = 0;
                style |= WS_POPUP;
            }
            else
            {
                // �E�B���h�E���[�h���̈ʒu�𕜋A
                px = mPositionX;
                py = mPositionY;
                // �E�B���h�E���[�h���̐ݒ�
                // const DWORD WND_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
                style |= WND_STYLE;
            }

            // �E�B���h�E�X�^�C���ƃT�C�Y���Đݒ�
            mStyle = style;
            SetWindowSize( mStyle, mWidth, mHeight );

            // �E�B���h�E�X�^�C�����C��
            SetWindowLong( mHandle, GWL_STYLE, mStyle );

            // �ʒu���ړ�
            SetWindowPos( mHandle, HWND_NOTOPMOST, px, py, mWidth, mHeight, SWP_SHOWWINDOW );

            // �E�B���h�E���X�V
            UpdateWindow( mHandle );

            // �t���O���Đݒ�
            mFullScreen = a_Flag;
        }



        /// @brief �E�B���h�E�̏I����ʒm���܂��B
        void EndRequest(){
            mEndRequested = true;
        }



        /// @brief �E�B���h�E���b�Z�[�W���������܂��B
        /// @note ���t���[����������K�v������܂�
        void Update()
        {
            MSG msg;

            // �E�B���h�E���b�Z�[�W���������ꍇ�������������
            if( PeekMessage( &msg, 0, 0, 0, PM_NOREMOVE ) ){
                if( GetMessage( &msg, 0, 0, 0 ) ){
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                } else {
                    // ���b�Z�[�W�̎擾�Ɏ��s������v���O�������I������
                    // ESC�₻�̑��̃��b�Z�[�W�ȂǂŃE�B���h�E���������ꍇ
                    mEndRequested = true;
                }
            }
        }



        /// @brief ���[�J���E�B���h�E�v���V�[�W��
        /// @param hWnd �E�B���h�E�n���h��
        /// @param msg ���b�Z�[�W�t���O
        /// @param wparam �p�����[�^�P
        /// @param lparam �p�����[�^�Q
        /// @return LRESULT ��������
        /// @note �E�B���h�E���b�Z�[�W���������܂��B
        LRESULT LocalWndProc( HWND hWnd, UINT msg, DWORD wParam, DWORD lParam )
        {
            // �e���b�Z�[�W�ɑΉ������������s��
            switch ( msg ){
            case WM_ACTIVATE:
                // �E�B���h�E���A�N�e�B�u���m�F���Đݒ�
                mActive = ( wParam ? true : false );
                break;

            case WM_CLOSE:
                // ���C���E�B���h�E���j������钼�O�ɏI���ʒm
                EndRequest();
                break;

            case WM_DESTROY:
                // �E�B���h�E���j�����ꂽ�i�K��
                // �V�X�e���ɃA�v���P�[�V�����̏I����ʒm
                PostQuitMessage( 0 );
                break;

            case WM_KEYDOWN:
                switch( wParam ){
                case VK_ESCAPE: // ESC�ŏI��
                    EndRequest();
                    PostQuitMessage( 0 );
                    break;

                case VK_F11: // F11�őS��ʕ\��
                   EnableFullScreen( !mFullScreen );
                    break;

                default:
                    break;
                }
                break;  
            }

            // ��`�O�̃E�B���h�E���b�Z�[�W�̏ꍇ�AOS�Ɋۓ�������
            return DefWindowProc( hWnd, msg, wParam, lParam );
        }


        //----------------------------------------------------------
    private:// �w���p�֐�
        
        /// @brief �E�B���h�E�ݒ�����������܂��B
        void Init()
        {
            // �������ς݂̏ꍇ�ɗ�O
            if ( mReady )
            {
                // ���d����������܂���
                 MessageBox(NULL,_T("���d�����������s���悤�Ƃ��܂����B"),_T("���"),MB_OK|MB_ICONHAND);
            }

                // �E�B���h�E�N���X��o�^
                RegisterWndClass( mClassName );

                // �\������E�B���h�E�̐ݒ�
                InitWindow();


            // �������������Ƀt���O�𗧂Ă�
            mReady = true;
        }



        /// @brief �E�B���h�E�N���X��o�^���܂��B
        /// @param classname�@�E�B���h�E�^�C�g��
        void RegisterWndClass( const tstring classname ){

            WNDCLASSEX wc;

            wc.cbSize         = sizeof( WNDCLASSEX );         // �N���X�T�C�Y
            wc.style          = CS_HREDRAW | CS_VREDRAW;      // �X�^�C��(�E�B���h�E�T�C�Y�ύX���ɍĕ`��)
            wc.lpfnWndProc    = ::WndProc;                    // �g�p����E�B���h�E�v���V�[�W��
            wc.cbClsExtra     = NULL;                         // �g���̈�P
            wc.cbWndExtra     = NULL;                         // �g���̈�Q
            wc.hInstance      = GetModuleHandle( 0 );         // �g�p���郂�W���[���n���h��
            wc.hCursor        = LoadCursor( 0, IDC_ARROW );   // �J�[�\�� 
            wc.hbrBackground  = ( HBRUSH )GetStockObject( BLACK_BRUSH );    // �o�b�N�O���E���h�F
            wc.lpszMenuName   = NULL;                         // �g�p����ꍇ�̓��j���[�̎��ʖ���
            wc.lpszClassName  = classname.c_str();            // ���ʃE�B���h�E�N���X��
            wc.hIcon          = NULL;                         // �A�C�R���w��
            wc.hIconSm        = NULL;                         // SmallIcon�ANULL����Icon�������k�������̂��g��

            if ( !RegisterClassEx( &wc) ){
                // �o�^�ł��Ȃ������ꍇ�ɗ�O�𓊂���
                // �w�E�B���h�E�N���X�̓o�^�Ɏ��s���܂����B�x
                MessageBox(NULL,_T("�E�B���h�E�N���X�̓o�^�Ɏ��s���܂����B"),_T("�ǂݍ��ݎ��s"),MB_OK|MB_ICONHAND);
            }
        }



        /// @brief �E�B���h�E�T�C�Y���v�Z�����ʂ��i�[���܂��B
        /// @param style �Ώۂ̃E�B���h�E�X�^�C��
        /// @param width ����
        /// @param height�c��
        /// @note  mClientWidth��mClientHeight�����ƂɎZ�o���܂��B
        void SetWindowSize( DWORD a_style, int& a_width, int& a_height ){

            // �t���[�����l�������E�B���h�E�T�C�Y���v�Z��
            // �`��̈�Ɏg�p�������T�C�Y��ݒ肷��
            RECT rect;
            SetRect( &rect, 0, 0, mClientWidth, mClientHeight );

            AdjustWindowRect( &rect, a_style, false );
            rect.right -= rect.left;        // (�`��̈�+�E��)��(�`��X�n�_-�����ʒu)�܂ł̃}�C�i�X�������𑫂�
            rect.bottom -= rect.top;        // (�`��̈�+����etc)��(�`��Y�n�_-��^�C�g���ʒu)�܂ł̃}�C�i�X�������𑫂�
            rect.left = 0;
            rect.top = 0;


            // �T�C�Y���L�^
            a_width = rect.right;
            a_height = rect.bottom;
        }
        

        
        /// @brief  �E�B���h�E�̏���\���ʒu��ݒ肵�܂��B
        void InitWindowPos(){

            DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
            int w = 0;
            int h = 0;
            SetWindowSize( style, w, h );
            
            //�f�X�N�g�b�v�����ɕ\������悤��������
            mPositionX = ( GetSystemMetrics( SM_CXSCREEN ) - w ) / 2;
            mPositionY = ( GetSystemMetrics( SM_CYSCREEN ) - h ) / 2;
        }

        
        
        /// @brief �\������E�B���h�E��ݒ肵�܂��B
        void InitWindow(){

            // �E�B���h�E���[�h���̏���\���ʒu��ݒ�
            InitWindowPos();

            // �t���X�N���[���L������WS_POPUP
            mStyle = ( mFullScreen ? WS_POPUP : WND_STYLE );
            
            // �E�B���h�E�T�C�Y���Z�o���Ċi�[
            SetWindowSize( mStyle, mWidth, mHeight );

            // �\���ʒu��ݒ�
            int x = ( mFullScreen ? 0 : mPositionX );
            int y = ( mFullScreen ? 0 : mPositionY );

            // �E�B���h�E���쐬���ăn���h�����i�[
            HWND hWnd = NULL;

            hWnd = CreateWindow(
                mClassName.c_str(),
                mTitle.c_str(),
                mStyle,
                x,
                y,
                mWidth,
                mHeight,
                NULL,
                NULL,
                GetModuleHandle( NULL ),
                NULL
                );

            if ( !hWnd )
            {
                // ���s��( hWnd = NULL )�ɗ�O
                MessageBox(NULL,_T("Window�̍쐬�Ɏ��s���܂����B\n���s�𒆎~���܂��B"),_T("�쐬���~"),MB_OK);
                // �I����ʒm
                EndRequest();
                return;
            }

            // �n���h�����L�^
             mHandle = hWnd;
        }


    };

    /// @brief  ���̃N���X�C���X�^���X
    /// @attention ����gImpl���A�N�Z�X�����ۂ̍ŏI�I�ȏ���������N���X�ł���B
    unique_ptr< Impl > gImpl;
    
} // end of namespace

//----------------------------------------------------------
//----------------------------------------------------------


/// @brief  ���C���E�B���h�E�̃v���V�[�W��
/// @param  hWnd �E�B���h�E�n���h��
/// @param  msg ���b�Z�[�W�t���O
/// @param  wparam �p�����[�^�P
/// @param  lparam �p�����[�^�Q
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    // ���̓��̃E�B���h�E�v���V�[�W���Ƀ��_�C���N�g
    return gImpl->LocalWndProc( hWnd, msg, wParam, lParam );
}


//----------------------------------------------------------

namespace GameLib{

    namespace Window{

        //----------------------------------------------------------
        // ���ꃁ���o

        /// @brief �R���X�g���N�^
        WindowCreator::WindowCreator(){}

        /// @brief �f�X�g���N�^
        WindowCreator::~WindowCreator(){}

       
        //----------------------------------------------------------
        // �����o�֐�

        /// @brief �C���X�^���X���쐬���܂��B
        void WindowCreator::Create(){

            // �쐬�ς݂��ǂ������m�F����B
            if( gImpl.get() != NULL){
                ::MessageBeep(MB_ICONASTERISK);
                MessageBox(NULL,_T("WindowCreator�̎��̂𕡐��쐬���悤�Ƃ��܂����B"),_T("�C���X�^���X�쐬���~"),MB_OK);
                return;
            }
            
            // ���Ȃ���Ύ��̂��쐬
            gImpl.reset(new Impl() );

        }

        /// @brief �E�B���h�E��\�����܂��B
        void WindowCreator::Show(){
            gImpl->Show();
        }

        /// @brief �E�B���h�E���b�Z�[�W���������܂��B
        /// @attention ���t���[����������K�v����I
        void WindowCreator::Update(){
            gImpl->Update();
        }

        /// @brief �v���O�����ɏI���ʒm�����܂��B
        const bool WindowCreator::CheckEndRequested() const{
            return gImpl->mEndRequested;
        }

        /// @brief �t���X�N���[�����[�h�̎w��
        /// @brief �t���X�N���[���ɂ���ꍇ��true���w�肷��
        void WindowCreator::FlagFullScreen( bool flag ){
            gImpl->EnableFullScreen( flag );
        }

        //----------------------------------------------------------
        // �A�N�Z�T

        /// @brief �`��̈�̕���ݒ肷��B
        /// @param width �ݒ肷��`��̈�̕�
        void WindowCreator::SetWidth(const int width ){
            gImpl->mClientWidth = width;
            
            // ���łɍ쐬����Ă�����
            if( gImpl->mHandle ){
                // �ʒu�𒲐����Ȃ����B
                gImpl->EnableFullScreen(gImpl->mFullScreen);
            }
        }

        /// @brief �`��̈�̍�����ݒ肷��B
        /// @param height �ݒ肷��`��̈�̍���
        void WindowCreator::SetHeight( const int height ){
            gImpl->mClientHeight = height;

            // ���łɍ쐬����Ă�����
            if( gImpl->mHandle ){
                // �ʒu�𒲐����Ȃ����B
                gImpl->EnableFullScreen(gImpl->mFullScreen);
            }
        }

        /// @brief �E�B���h�E�^�C�g����ݒ肷��B
        /// @param title �ݒ肷�镶����
        void WindowCreator::SetTitle( const std::tstring title ){
            gImpl->mTitle = title;
        
            // �E�B���h�E�쐬�ς݂̏ꍇ�̓e�L�X�g��ύX
            if( gImpl->mHandle ){
                SetWindowText( gImpl->mHandle, title.c_str() );
            }
        }

        /// @brief �E�B���h�E�A�C�R����ݒ肷��B
        /// @param id �A�C�R���̃��\�[�XID
        void WindowCreator::SetIcon( const int id ){
            gImpl->mIconID = id;

            // �E�B���h�E�쐬�ς݂̏ꍇ�͑����ăA�C�R����ύX
            if( gImpl->mHandle ){
                HICON icon = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( id ) );
                SetClassLong( gImpl->mHandle, GCL_HICON, reinterpret_cast< LONG >( icon ) );
            }
        }

        /// @brief �E�B���h�E�n���h�����擾����B
        /// @return HWND �E�B���h�E�n���h��
        const HWND WindowCreator::GetHandle() const{
            return gImpl->mHandle;
        }


        /// @brief �N���C�A���g�̈�̕����擾���܂��B
        /// @return int �ݒ肵����
        const int WindowCreator::GetWidth() const{
            return gImpl->mClientWidth;
        }

        /// @brief �N���C�A���g�̈�̍������擾���܂��B
        /// @return int �ݒ肵������
        const int WindowCreator::GetHeight() const{
            return gImpl->mClientHeight;
        }




        /// @brief �E�B���h�E���A�N�e�B�u�����m�F����B
        /// @return bool �A�N�e�B�u����true�A��A�N�e�B�u����false
        const bool WindowCreator::CheckActive() const{
            return gImpl->mActive;
        }

        /// @brief �t���X�N���[�����[�h���擾���܂��B
        /// @return bool �t���X�N���[������true�A�E�B���h�E����false��Ԃ��܂��B
        const bool WindowCreator::CheckFullScreen() const{
            return gImpl->mFullScreen;
        }

    }
}






