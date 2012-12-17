/// @file WindowImpl.hpp
/// @brief �E�B���h�E���쐬���鏈���N���X - ����
/// @note 
/// @date 2012/12/17     tory

//====================================================================
//              WindowImpl.hpp
//--------------------------------------------------------------------
//    �������e : �E�B���h�E���쐬���鏈�� - ����
//    �������e : 
//    �쐬�ڍ� : 2012/12/17
//    �⑫     : 
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/09/01     tory
//         
//====================================================================


#ifndef INCLUDE_GAMELIB_WINDOW_CREATOR_IMPL_H
#define INCLUDE_GAMELIB_WINDOW_CREATOR_IMPL_H

#include <Windows.h>

#include <tiostream.h>
#include <TemplateBaseClass.h>


//----------------------------------------
// �v���g�^�C�v�錾

/// @brief  ���C���E�B���h�E�̃v���V�[�W��
/// @param  hWnd �E�B���h�E�n���h��
/// @param  msg ���b�Z�[�W�t���O
/// @param  wParam �p�����[�^1
/// @param  lParam �p�����[�^2
/// @note   WindowCreator.cpp�Ŏ���
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


namespace GameLib{

    using namespace std;

    namespace Window{

        //----------------------------------------------------------
        // �萔��`

        /// @brief �E�B���h�E�^�C�g��
        const tstring WND_TITLE("GameApplication");
        /// @brief �E�B���h�E�N���X�l�[��
        const tstring WND_CLASSNAME("GameApplication");
        /// @brief �K��̃E�B���h�E�X�^�C��
        const DWORD WND_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;



        /// @class WindowStatesFlag
        /// @brief �E�B���h�E�̏�ԃt���O�Ɋւ�����̂��W�߂��N���X
        class WindowStatesFlag{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            bool mActive;               ///< @brief �E�B���h�E�̃A�N�e�B�u
            bool mFullScreen;           ///< @brief �t���X�N���[�����[�h
            bool mMinimized;            ///< @brief �ŏ����t���O
            bool mEndRequested;         ///< @brief �E�B���h�E�I���t���O
            bool mReady;                ///< @brief ���������t���O

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            WindowStatesFlag::WindowStatesFlag():
                mActive( false ),
                mFullScreen( false ),
                mMinimized( false ),
                mReady( false ),
                mEndRequested( false )            
            {};
        
            /// @brief �f�X�g���N�^
            WindowStatesFlag::~WindowStatesFlag(){};

            //----------------------------------------------------------
            // �����o�֐�
        public:

            /// @brief �A�N�e�B�u��Ԃ��Z�b�g���܂�
            void setActive(const bool a_flag){
                mActive = a_flag;
            }

            /// @brief �t���X�N���[���t���O���Z�b�g���܂�
            void setFullScreen(const bool a_flag){
                mFullScreen = a_flag;
            }

            /// @brief �ŏ����t���O���Z�b�g���܂�
            void setMinimized(const bool a_flag){
                mMinimized = a_flag;
            }

            /// @brief �E�B���h�E�I���t���O���Z�b�g���܂�
            void setEndRequested(const bool a_flag){
                mEndRequested = a_flag;
            }

            /// @brief ���������t���O���Z�b�g���܂�
            void setReady( const bool a_flag){
                mReady = a_flag;
            }

            //----------------------------------------------------------
            // �v���p�e�B
        public:

            /// @brief �E�B���h�E�̃A�N�e�B�u��Ԃ̃t���O�l��Ԃ��܂��B
            const bool active() const{return mActive;}
            
            /// @brief ���݂̃t���X�N���[�����[�h�̃t���O�l��Ԃ��܂��B
            const bool fullScreen() const{return mFullScreen;}

            /// @brief ���݂̍ŏ����t���O�l��Ԃ��܂��B
            const bool minimized() const{return mMinimized;}

            /// @brief ���݂̃E�B���h�E�I���t���O�l��Ԃ��܂��B
            const bool endRequested() const{return mEndRequested;}

            /// @brief ���݂̏��������t���O�l��Ԃ��܂��B
            const bool ready() const{return mReady;}


        }; // end of class WindowStatesFlag

        //----------------------------------------------------------
        //----------------------------------------------------------

        /// @class WindowInfo
        /// @brief �E�B���h�E�\���ɂ����鎯�ʏ����܂Ƃ߂��N���X
        class WindowInfo{
            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            tstring mTitle;             ///< @brief �E�B���h�E�^�C�g��        
            tstring mClassName;         ///< @brief �N���X�l�[��
            int mIconID;                ///< @brief �A�C�R��ID
            HWND mHandle;               ///< @brief �E�B���h�E�n���h��
            DWORD mStyle;               ///< @brief �E�B���h�E�X�^�C��

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            WindowInfo():
                mTitle( WND_TITLE ),
                mClassName( WND_CLASSNAME ),
                mIconID( 0 ),
                mHandle( NULL ),
                mStyle( 0x0000 )
            {};

            /// @brief �f�X�g���N�^
            ~WindowInfo(){};

            //----------------------------------------------------------
            // �����o�ϐ�
        public:

            /// @brief �^�C�g������ݒ肵�܂��B
            void setTitle(const tstring a_title){
                mTitle = a_title;
            }

            /// @brief �N���X�l�[������ݒ肵�܂��B
            void setClassName(const tstring a_className){
                mClassName = a_className;
            }

            /// @brief �A�C�R��ID�ԍ���ݒ肵�܂��B
            void setIconID(const int a_value){
                mIconID = a_value;
            }

            /// @brief �E�B���h�E�n���h����ݒ肵�܂��B
            void setHandle(const HWND a_handle){
                mHandle = a_handle;
            }

            /// @brief �E�B���h�E�X�^�C����ݒ肵�܂��B
            void setStyle(const DWORD a_style){
                mStyle = a_style;
            }


            //----------------------------------------------------------
            // �v���p�e�B
        public:

            /// @brief �^�C�g�������擾���܂��B
            const tstring title() const{return mTitle;}

            /// @brief �N���X�l�[�����擾���܂��B
            const tstring className() const{return mClassName;}

            /// @brief �A�C�R��ID�̔ԍ����擾���܂��B
            const int iconID() const{return mIconID;}

            /// @brief �ݒ肵�Ă���E�B���h�E�n���h�����擾���܂��B
            const HWND handle() const{return mHandle;}

            /// @brief �ݒ肵�Ă���E�B���h�E�X�^�C�����擾���܂��B
            const DWORD style() const{return mStyle;}

        }; // end of class WindowInfo




        /// @class WindowCreator
        /// @brief WindowCreator�����N���X
        class WindowCreatorImpl{
            //----------------------------------------------------------
            // �v���g�^�C�v�錾

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            WindowInfo mWindowInfo;     ///< @brief �E�B���h�E���ʏ��N���X

            BaseWH<int> mClientSize;    ///< @brief �`��̈�T�C�Y
            BaseWH<int> mWindowSize;    ///< @brief �E�B���h�E�T�C�Y
            BaseXY<int> mPosition;      ///< @brief �E�B���h�E�ʒu

            WindowStatesFlag mStatesFlag;   /// @brief ��ԃt���O

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            WindowCreatorImpl():
                mWindowInfo(),
                mClientSize( 1280, 720 ),
                mWindowSize(),
                mPosition(),
                mStatesFlag()
            {};

            /// @brief �f�X�g���N�^
            ~WindowCreatorImpl(){};

            //----------------------------------------------------------
            // �����o�֐�
        public:

            /// @brief �E�B���h�E�����������܂��B
            void Initialize(){
                // �������ς݂̏ꍇ�ɗ�O
                if ( mStatesFlag.ready() )
                {
                    // ���d����������܂���
                     MessageBox(NULL,_T("���d�����������s���悤�Ƃ��܂����B"),_T("���"),MB_OK|MB_ICONHAND);
                }

                // �E�B���h�E�N���X��o�^
                RegisterWndClass( mWindowInfo.className() );

                // �\������E�B���h�E�̐ݒ�
                InitWindowInfo();


                // �������������Ƀt���O�𗧂Ă�
                mStatesFlag.setReady( true );
            }


            /// @brief �E�B���h�E��\�����܂��B
            /// @attention ����������Ă��Ȃ��ꍇ�A������Initialize�֐����R�[������܂��B
            void Show()
            {
                // �񏉊�������init���R�[��
                if ( !mStatesFlag.ready() ){ 
                    Initialize();
                }

                // vistual Studio 2012�̃o�O�̂���
                // GetStartupInfo�Ő����showCmd�l���擾�ł��Ȃ��̂�
                // �ʂ̕��@��showCmd�l���擾���Ă��܂��B
                WINDOWPLACEMENT info;
                info.length = sizeof(WINDOWPLACEMENT);
                GetWindowPlacement( mWindowInfo.handle(), &info );
                
                // �v���O�����J�n���̎w������Ƃɕ\��
                if(info.showCmd = SW_MAXIMIZE){
                    // �ݒ肳�ꂽStyle�ɂčő剻���L���Ȏ��͍ő剻����B
                    ShowWindow( mWindowInfo.handle(), SW_RESTORE );
                }else{
                    // ����ȊO(�V���[�g�J�b�g�Ȃǂōő剻�w��)�̎��͖�������B
                    ShowWindow( mWindowInfo.handle(), info.showCmd  );
                }

                // �E�B���h�E���ŏ����̏�Ԃ��ǂ����擾����B
                CheckMinimized();


                // �E�B���h�E���X�V����B
                UpdateWindow( mWindowInfo.handle() );
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

                // �t���X�N���[���t���O�̏�Ԃɍ��킹�E�B���h�E�ʒu���L�^�A�܂��͓Ǎ�����B
                a_Flag ? SaveWindowPosition(&px, &py, &style) : LoadWindowPosition(&px, &py, &style);

                // �E�B���h�E�X�^�C���ƃT�C�Y���Đݒ�
                mWindowInfo.setStyle(style);
                CalculationWindowSize( mWindowInfo.style(), &w, &h );
                mWindowSize.setWH( w, h );

                // �E�B���h�E�X�^�C�����C��
                SetWindowLong( mWindowInfo.handle(), GWL_STYLE, mWindowInfo.style() );

                // �ʒu���ړ�
                SetWindowPos( mWindowInfo.handle(), HWND_NOTOPMOST, px, py,  mWindowSize.width(), mWindowSize.height(), SWP_SHOWWINDOW );

                // �E�B���h�E���X�V
                UpdateWindow(mWindowInfo.handle() );

                // �t���O���Đݒ�
                mStatesFlag.setFullScreen( a_Flag );
            }

            /// @brief �E�B���h�E�̏I����ʒm���܂��B
            void EndRequest(){
                mStatesFlag.setEndRequested( true );
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
                        mStatesFlag.setEndRequested( true );
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
                    mStatesFlag.setActive( wParam ? true : false );
                    break;

                case WM_CLOSE:
                    // ���C���E�B���h�E���j������钼�O�ɏI���ʒm
                    EndRequest();
                    break;

                case WM_SIZE:
                    // �E�B���h�E�T�C�Y�ɕύX���������Ƃ�
                    CheckMinimized();
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
                        EnableFullScreen( !mStatesFlag.fullScreen() );
                        break;

                    default:
                        break;
                    }
                    break;  
                }

                // ��`�O�̃E�B���h�E���b�Z�[�W�̏ꍇ�AOS�Ɋۓ�������
                return DefWindowProc( hWnd, msg, wParam, lParam );
            }

            /// @brief �`��̈�T�C�Y��width��ݒ肵�܂��B
            void setClientWidth(const int a_width){
                mClientSize.setWidth( a_width );
            }

            /// @brief �`��̈�T�C�Y��height��ݒ肵�܂��B
            void setClientHeight(const int a_height){
                mClientSize.setHeight( a_height );
            }

            /// @brief �E�B���h�E�^�C�g����ݒ肵�܂��B
            void setTitle(const tstring a_title){
                mWindowInfo.setTitle( a_title );
            }

            /// @brief �E�B���h�E�A�C�R����ݒ肵�܂��B
            void setIcon( const int a_id ){
                mWindowInfo.setIconID( a_id );
            }


            //----------------------------------------------------------
            // �v���p�e�B
        public:

            /// @brief �`��̈�T�C�Y��width��ݒ肵�܂��B
            const int clientWidth(){
                return mClientSize.width();
            }

            /// @brief �`��̈�T�C�Y��height��ݒ肵�܂��B
            const int clientHeight(){
                return mClientSize.height();
            }

            /// @brief ���݂̃E�B���h�E�n���h���l���擾���܂��B
            const HWND handle(){
                return mWindowInfo.handle();
            }

            /// @brief ���݂̃E�B���h�E���A�N�e�B�u���ǂ����̃t���O�l���擾���܂��B
            const bool isActive(){
                return mStatesFlag.active();
            }

            /// @brief ���݂̃t���X�N���[���̃t���O�l���擾���܂��B
            const bool isFullScreen(){
                return mStatesFlag.fullScreen();
            }

            /// @brief �E�B���h�E�̍ŏ����t���O�l���擾���܂��B
            const bool isMinimized(){
                return mStatesFlag.minimized();
            }

            /// @brief ���݂̃E�B���h�E�I���t���O�l(�I���ʒm)���擾���܂��B
            const bool isEndRequest(){
                return mStatesFlag.endRequested();
            }

            //----------------------------------------------------------
            // �w���p�[�֐�

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
            /// @param height �c��
            /// @note  mClientWidth��mClientHeight�����ƂɎZ�o���܂��B
            void CalculationWindowSize(const DWORD a_style, int* a_width, int* a_height ){

                // �t���[�����l�������E�B���h�E�T�C�Y���v�Z��
                // �`��̈�Ɏg�p�������T�C�Y��ݒ肷��
                RECT rect;
                SetRect( &rect, 0, 0, mClientSize.width(), mClientSize.height() );

                AdjustWindowRect( &rect, a_style, false );
                rect.right -= rect.left;        // (�`��̈�+�E��)��(�`��X�n�_-�����ʒu)�܂ł̃}�C�i�X�������𑫂�
                rect.bottom -= rect.top;        // (�`��̈�+����etc)��(�`��Y�n�_-��^�C�g���ʒu)�܂ł̃}�C�i�X�������𑫂�
                rect.left = 0;
                rect.top = 0;


                // �T�C�Y���L�^
                (*a_width) = rect.right;
                (*a_height) = rect.bottom;
            }

            /// @brief  �E�B���h�E�̏���\���ʒu��ݒ肵�܂��B
            void InitWindowPosition(){

                DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
                int w = 0;
                int h = 0;
                CalculationWindowSize( style, &w, &h );
            
                //�f�X�N�g�b�v�����ɕ\������悤��������
                mPosition.setX( ( GetSystemMetrics( SM_CXSCREEN ) - w ) / 2);
                mPosition.setY( ( GetSystemMetrics( SM_CYSCREEN ) - h ) / 2);
            }


            
            /// @brief �\������E�B���h�E�̏����������ݒ肵�܂��B
            void InitWindowInfo(){

                // �E�B���h�E���[�h���̏���\���ʒu��ݒ�
                InitWindowPosition();

                // �t���X�N���[���L������WS_POPUP
                mWindowInfo.setStyle ( mStatesFlag.fullScreen() ? WS_POPUP : WND_STYLE );
            
                int w = 0;
                int h = 0;
                // �E�B���h�E�T�C�Y���Z�o���Ċi�[
                CalculationWindowSize( mWindowInfo.style(), &w, &h );
                mWindowSize.setWH( w, h );

                // �\���ʒu��ݒ�
                int x = ( mStatesFlag.fullScreen() ? 0 : mPosition.x() );
                int y = ( mStatesFlag.fullScreen() ? 0 : mPosition.y() );

                // �E�B���h�E���쐬���ăn���h�����i�[
                HWND hWnd = NULL;

                hWnd = CreateWindow(
                    mWindowInfo.className().c_str(),
                    mWindowInfo.title().c_str(),
                    mWindowInfo.style(),
                    x,
                    y,
                    mWindowSize.width(),
                    mWindowSize.height(),
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
                mWindowInfo.setHandle( hWnd );
            }




            /// @brief �t���X�N���[���ؑւɍۂ��Č��݂̃E�B���h�E�ʒu���L�^���܂��B
            void SaveWindowPosition(int* a_x, int* a_y, DWORD* a_style){
                // ���݂̃E�B���h�E�ʒu���L�^���Ă���
                RECT rect;
                GetWindowRect( mWindowInfo.handle(), &rect );
                mPosition.setXY(rect.left, rect.top);

                // �t���X�N���[�����[�h���̐ݒ�
                *a_x = 0;
                *a_y = 0;
                *a_style |= WS_POPUP;
            }

            /// @brief �t���X�N���[���ؑւɍۂ��đO��̃E�B���h�E�ʒu��ǂݍ��݂܂��B
            void LoadWindowPosition(int* a_x, int* a_y, DWORD* a_style){
                // �E�B���h�E���[�h���̈ʒu�𕜋A
                (*a_x) = mPosition.x();
                (*a_y) = mPosition.y();
                // �E�B���h�E���[�h���̐ݒ�(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
                (*a_style) |= WND_STYLE;

            }

            /// @brief ���݂̃E�B���h�E�̍ŏ����̏�Ԃ��t���O�l�ɐݒ肵�܂��B
            void CheckMinimized(){
                WINDOWPLACEMENT info;
                info.length = sizeof(WINDOWPLACEMENT);
                GetWindowPlacement( mWindowInfo.handle(), &info );

                switch ( info.showCmd ){                
                case SW_SHOWNORMAL:     // ���ʂ̏��
                    mStatesFlag.setMinimized( false );
                    break;

                case SW_SHOWMINIMIZED:  // �ŏ����̏��
                    mStatesFlag.setMinimized( true );
                    break;

                case SW_SHOWMAXIMIZED:  // �ő剻�̏��
                    mStatesFlag.setMinimized( false );
                    break;

                default:        // ���̑��̏���(�G���[���Ȃǂ͏I������)
                    EndRequest();
                }
            }




        }; // end of class WindowCreatorImpl



    } // end of namespace Window
} // end of namespace GameLib
#endif