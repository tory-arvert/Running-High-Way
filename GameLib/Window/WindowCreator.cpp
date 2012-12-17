/// @file Window.cpp
/// @brief �E�B���h�E���쐬���鏈���N���X - ����
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              Window.cpp
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

#include "WindowCreator.h"
#include "WindowCreatorImpl.hpp"


using namespace std;
using namespace GameLib::Window;



// �����l�[���X�y�[�X��`
namespace{
      
    /// @brief  ���̃N���X�C���X�^���X
    /// @attention ����gImpl���A�N�Z�X�����ۂ̍ŏI�I�ȏ���������N���X�ł���B
    unique_ptr< WindowCreatorImpl > gImpl( nullptr );
    
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
            if(gImpl != nullptr){
                MessageBox(NULL,_T("WindowCreator�̎��̂𕡐��쐬���悤�Ƃ��܂����B"),_T("�C���X�^���X�쐬���~"),MB_OK);
                return;
            }
            
            // ���Ȃ���Ύ��̂��쐬
            gImpl.reset(new WindowCreatorImpl() );

        }

        /// @brief �E�B���h�E��\�����܂��B
        void WindowCreator::Show() const{
            gImpl->Show();
        }

        /// @brief �E�B���h�E���b�Z�[�W���������܂��B
        /// @attention ���t���[����������K�v����I
        void WindowCreator::Update() const{
            gImpl->Update();
        }

        /// @brief �v���O�����ɏI���ʒm���m�F���܂��B
        const bool WindowCreator::isEndRequested() const{
            return gImpl->isEndRequest();
        }

        /// @brief �v���O�����̏I�����s���܂��B
        void WindowCreator::End() const{
            gImpl->EndRequest();
        }


        /// @brief �t���X�N���[�����[�h�̎w��
        /// @brief �t���X�N���[���ɂ���ꍇ��true���w�肷��
        void WindowCreator::FlagFullScreen( bool flag ) const{
            gImpl->EnableFullScreen( flag );
        }

        //----------------------------------------------------------
        // �A�N�Z�T

        /// @brief �`��̈�̕���ݒ肷��B
        /// @param width �ݒ肷��`��̈�̕�
        void WindowCreator::SetWidth(const int a_width ){
            gImpl->setClientWidth( a_width );
            
            // ���łɍ쐬����Ă�����
            if( gImpl->handle() ){
                // �ʒu�𒲐����Ȃ����B
                gImpl->EnableFullScreen(gImpl->isFullScreen() );
            }
        }

        /// @brief �`��̈�̍�����ݒ肷��B
        /// @param height �ݒ肷��`��̈�̍���
        void WindowCreator::SetHeight( const int a_height ){
            gImpl->setClientHeight( a_height );

            // ���łɍ쐬����Ă�����
            if( gImpl->handle() ){
                // �ʒu�𒲐����Ȃ����B
                gImpl->EnableFullScreen(gImpl->isFullScreen());
            }
        }

        /// @brief �E�B���h�E�^�C�g����ݒ肷��B
        /// @param title �ݒ肷�镶����
        void WindowCreator::SetTitle( const std::tstring title ){
            gImpl->setTitle( title );
        
            // �E�B���h�E�쐬�ς݂̏ꍇ�̓e�L�X�g��ύX
            if( gImpl->handle() ){
                SetWindowText( gImpl->handle(), title.c_str() );
            }
        }

        /// @brief �E�B���h�E�A�C�R����ݒ肷��B
        /// @param id �A�C�R���̃��\�[�XID
        void WindowCreator::SetIcon( const int id ){
            gImpl->setIcon( id );

            // �E�B���h�E�쐬�ς݂̏ꍇ�͑����ăA�C�R����ύX
            if( gImpl->handle() ){
                HICON icon = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( id ) );
                SetClassLong( gImpl->handle(), GCL_HICON, reinterpret_cast< LONG >( icon ) );
            }
        }

        //----------------------------------------------------------
        // �v���p�e�B

        /// @brief �E�B���h�E�n���h�����擾����B
        /// @return HWND �E�B���h�E�n���h��
        const HWND WindowCreator::handle() const{
            return gImpl->handle();
        }

        /// @brief �E�B���h�E���A�N�e�B�u�����m�F����B
        /// @return bool �A�N�e�B�u����true�A��A�N�e�B�u����false
        const bool WindowCreator::isActive() const{
            return gImpl->isActive();
        }

        /// @brief �t���X�N���[�����[�h���擾���܂��B
        /// @return bool �t���X�N���[������true�A�E�B���h�E����false��Ԃ��܂��B
        const bool WindowCreator::isFullScreen() const{
            return gImpl->isFullScreen();
        }

        /// @brief  �E�B���h�E���ŏ�������Ă��邩���m�F���܂��B
        /// @return bool true �ŏ�������true�A��ŏ�������false��Ԃ��܂��B
        const bool WindowCreator::isMinimized() const
        {
            return gImpl->isMinimized();
        }

        
        /// @brief �N���C�A���g�̈�̕����擾���܂��B
        /// @return int �ݒ肵����
        const int WindowCreator::width() const{
            return gImpl->clientWidth();
        }

        /// @brief �N���C�A���g�̈�̍������擾���܂��B
        /// @return int �ݒ肵������
        const int WindowCreator::height() const{
            return gImpl->clientHeight();
        }





    }
}






