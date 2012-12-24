/// @file GraphicsManager.cpp
/// @brief �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X - Impl���_�C���N�g
/// @note Impl�ƃC���^�[�t�F�C�X�ɂ��p���𗘗p���ĕ`��f�o�C�X�̕ύX���Ή��\�B
/// @date 2011/10/18     tory

//====================================================================
//              GraphicsManager.cpp
//--------------------------------------------------------------------
//    �������e : �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X - Impl���_�C���N�g
//    �������e : 
//    �쐬�ڍ� : 2011/10/18
//    �⑫     : Impl�ƃC���^�[�t�F�C�X�ɂ��p���𗘗p���ĕ`��f�o�C�X�̕ύX���Ή��\�B
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : �啝�ȃ��t�@�N�^�����O�����s
//    �쐬�ڍ� : 2012/12/18    tory
//         
//====================================================================

#include <Windows.h>                        // MessageBeep��E�B���h�E�v���V�[�W���Ȃǂ̊�{�ɕK�{
#include <memory>                           // unique_ptr�ȂǂɕK�v
#include <tiostream.h>                      // tstring�^�Ȃǂ�TCHAR�g����`


#include "GraphicsManager.h"
#include "IGraphicsManagerImpl.h"
#include "GraphicsManagerImplDirect3D.hpp"

using namespace std;
using namespace GameLib::Graphics;

// �����l�[���X�y�[�X��`
namespace{
      
    /// @brief  ���̃N���X�C���X�^���X
    /// @attention ����gImpl���A�N�Z�X�����ۂ̍ŏI�I�ȏ���������N���X�ł���B
    unique_ptr< IGraphicsManagerImpl > gImpl( nullptr );
    
} // end of namespace

//----------------------------------------------------------
//----------------------------------------------------------

namespace GameLib{
    namespace Graphics{

        //----------------------------------------------------------
        // ���ꃁ���o

        /// @brief �R���X�g���N�^
        GraphicsManager::GraphicsManager(){}

        /// @brief �f�X�g���N�^
        GraphicsManager::~GraphicsManager(){}


        //----------------------------------------------------------
        // �����o�֐�

        /// @brief �C���X�^���X���쐬���܂��B
        /// @param a_HWND �E�B���h�E�n���h��
        /// @param a_Width �`��̈��X�T�C�Y
        /// @param a_Height �`��̈��Y�T�C�Y
        /// @param a_Fullscreen �t���X�N���[���t���O
        /// @param a_Vsync ���������t���O
        /// @param a_AntiAlias �A���`�G�C���A�X�t���O
        /// @param a_Width2D 2D�`�掞�̊�̈�X�T�C�Y(=800)
        /// @param a_Height2D 2D�`�掞�̊�̈�Y�T�C�Y(=600)
        void GraphicsManager::Create(
                const HWND a_HWND,
                const int a_Width,
                const int a_Height,
                const bool a_Fullscreen,
                const bool a_Vsync,
                const bool a_AntiAlias,
                const int a_Width2D,
                const int a_Height2D
            ){

            // �쐬�ς݂��ǂ������m�F����B
            if(gImpl != nullptr){
                MessageBox(NULL,_T("GraphicsManager�̎��̂𕡐��쐬���悤�Ƃ��܂����B"),_T("�C���X�^���X�쐬���~"),MB_OK);
                return;
            }
            
            // ���Ȃ���Ύ��̂��쐬
            // �����ō쐬����Impl�ɂ���Ďg�p����`��f�o�C�X���ς���Ă���B
            /// @todo DirectX��OpenGL�Ȃǂō쐬��؂�ւ�����悤�ɂ���B
            gImpl.reset(new ImplDirect3D(
                a_HWND, a_Width, a_Height, a_Fullscreen, a_Vsync, a_AntiAlias, a_Width2D, a_Height2D )
                );

        }

        /// @brief �C���X�^���X��j�����܂��B
        void GraphicsManager::Destroy(){
            
            if(gImpl == nullptr){
                return;
            }
            gImpl.reset( nullptr );
        }


        /// @brief �`����J�n���܂��B
        void GraphicsManager::BeginDraw(){
            gImpl->BeginDraw();
        }

        /// @brief �`����I�����܂��B
        void GraphicsManager::EndDraw(){
            gImpl->EndDraw();
        }

        /// @brief �t���X�N���[���l�Ȃǂ̕ω��𔽉f�����邽�߂�
        /// @brief ���݂̃f�o�C�X��j����A�V���ɍč\�z���܂��B
        void GraphicsManager::RecreateDevice(){
            gImpl->RecreateDevice();
        }

        /// @brief ���ݕ`��\�ȏ�Ԃ����m�F���܂��B
        /// @retval true �`��\
        /// @retval false �`��s�\
        const bool GraphicsManager::isRenderable() const{
            return gImpl->isRenderable();   
        };

        /// @brief �f�o�C�X�̕��A�����݂܂��B
        /// @retval true ����I��
        /// @retval false �ُ�I��
        const bool GraphicsManager::Restore(){
            return gImpl->Restore();
        }

        //----------------------------------------
        // �A�N�Z�T

        /// @brief  ����܂ł̃t���[���J�E���g���擾���܂��B
        /// @return �t���[���J�E���g
        const int GraphicsManager::getFrameCount() const{
            return gImpl->getFrameCount();
        }

        /// @brief �t���X�N���[�����[�h�̃t���O��ݒ肵�����܂��B
        /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
        void GraphicsManager::setFullScreen(const bool value){
            gImpl->setFullScreen( value );
        }

        /// @brief ���������̃t���O�l��ݒ肵�����܂��B
        /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
        void GraphicsManager::setVSync(const bool value){
            gImpl->setVSync( value );
        }

        /// @brief �A���`�G�C���A�X�̃t���O�l��ݒ肵�����܂��B
        /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
        void GraphicsManager::setAntialias(const bool value){
            gImpl->setAntialias( value );
        }

        /// @brief �N���C�A���g�T�C�Y��ݒ肵�����܂��B
        /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
        void GraphicsManager::setClientSize(const int a_Width, const int a_Height){
            gImpl->setClientSize( a_Width, a_Height );
        }

        /// @brief ���̑���Manager�����������܂��B
        void GraphicsManager::InitializeManager(){

            /// @todo Line��Sprite�̊��f�[�^�̏������Ȃ�
            
        }




    } // end of namespace Graphics
} // end of namespace GameLib