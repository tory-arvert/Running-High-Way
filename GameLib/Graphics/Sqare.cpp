/// @file Sqare.cpp
/// @brief �w��F�ŋ�`��`�悷��̂ɕK�v�ȃe�N�X�`�����Ǘ�����N���X - ����
/// @note Sprite�@�\���g���ĕ`����s���܂��B
/// @date 2013/01/13     tory

//====================================================================
//              Sqare.cpp
//--------------------------------------------------------------------
//    �������e : �w��F�ŋ�`��`�悷��̂ɕK�v�ȃe�N�X�`�����Ǘ�����N���X - ����
//    �������e : 
//    �쐬�ڍ� : 2013/01/13
//    �⑫     : Sprite�@�\���g���ĕ`����s���܂��B
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2013/00/00    tory
//         
//====================================================================

#include "Sqare.h"
#include <memory>
#include "GraphicsManagerImplDirect3D.hpp"

// �����l�[���X�y�[�X��`
namespace{
      
    /// @brief  ���̃C���X�^���X
    /// @attention ����gSqareTexture�����ۂ�Sqare�p�̃e�N�X�`���o�b�t�@�ł���B
    Com_ptr < IDirect3DTexture9 > gSqareTexture;  ///< @brief Sqare�p�̔��n�e�N�X�`��
    
} // end of namespace

//----------------------------------------------------------
//----------------------------------------------------------



namespace GameLib{
    namespace Graphics{

        /// @brief  ���̃N���X�C���X�^���X�̊O���Q��
        extern shared_ptr< ImplDirect3D > gImplDirect3D;

        //----------------------------------------------------------
        // ���ꃁ���o�֐�

        /// @brief �R���X�g���N�^
        Sqare::Sqare(){
            // �e�N�X�`�����쐬���܂�
            Create( gSqareTexture );            
        }
        /// @brief �f�X�g���N�^
        Sqare::~Sqare(){}

        //----------------------------------------------------------
        // �����o�֐�


        /// @brief �f�o�C�X���X�g���ɑΉ����邽�ߎQ�ƃJ�E���^�͂��̂܂܂�Sqare�p�̃e�N�X�`�����J�����܂��B
        void Sqare::Backup(){            
            // 1�x�쐬���ꂽ���Ƃ�����Ƃ��͂��̐���J������B
            if( gSqareTexture.getPtr() ) {
                Com_ptr<IDirect3DTexture9> cpTmp;
                gSqareTexture.Swap( cpTmp );
            }
        }

        /// @brief �f�o�C�X���X�g�ŊJ�����Ă���Sqare�p�e�N�X�`�����č쐬���܂��B
        void Sqare::Recover(){
            // �e�N�X�`���𕜊�������B
            Com_ptr<IDirect3DTexture9> cpTmp;
            Create( cpTmp );
            // �V�����쐬�����e�N�X�`���ƌ�������B
            gSqareTexture.Swap( cpTmp );

        }
        //----------------------------------------
        // �A�N�Z�T
            
        /// @brief �e�N�X�`���̎��̂��擾���܂��B
        Com_ptr < IDirect3DTexture9 > Sqare::texture() const{
            return gSqareTexture;
        }


        //----------------------------------------
        // �w���p�[�֐�

        /// @brief Sqare�p�̃e�N�X�`�����쐬���܂��B
        /// @a_Texture �w�肵���X�}�[�g�|�C���^���Sqare�p�e�N�X�`�����쐬���܂��B
        /// @note ���̂����łɂ���ꍇ�͉������������܂���B
        void Sqare::Create(Com_ptr < IDirect3DTexture9 >& a_Texture){

            // �쐬����Ă��Ȃ��̂Ȃ��
            if( a_Texture == nullptr ) {

                auto Device = gImplDirect3D->getDevice();

                // Sqare�p�̋�e�N�X�`���̈���쐬���܂��B
                Device->CreateTexture( 1, 1, 0, D3DUSAGE_RENDERTARGET ,D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, a_Texture.ToCreator(), NULL);
                
                Com_ptr<IDirect3DSurface9> SqareSurface, backSurface;

                // ���݂̃o�b�N�o�b�t�@�̃T�[�t�F�C�X��ێ����Ă����B
                Device->GetRenderTarget(0, backSurface.ToCreator());

                // Sqare�p�e�N�X�`���̃T�[�t�F�C�X�擾
                a_Texture->GetSurfaceLevel(0, SqareSurface.ToCreator());
                // Sqare�p�̃e�N�X�`���Ƀ����_�����O�^�[�Q�b�g��؂�ւ���B
                Device->SetRenderTarget(0, SqareSurface.getPtr());

				// ���F���쐬����B
                Device->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
                //Device->EndScene();
				//Device->BeginScene();

                // �����_�����O�^�[�Q�b�g�����̃o�b�N�o�b�t�@�ɖ߂��Ă����B
                Device->SetRenderTarget(0, backSurface.getPtr());
            }
        }


    } // end of namespace Graphics
} // end of namespace GameLib
