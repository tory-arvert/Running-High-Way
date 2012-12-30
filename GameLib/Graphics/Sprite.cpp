/// @file Sprite.cpp
/// @brief ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - ���� + Impl���_�C���N�g
/// @note �݊����d���̕`���Sharder�𗘗p���������ȕ`��ɑΉ����Ă���
/// @date 2011/10/18     tory

//====================================================================
//              Sprite.cpp
//--------------------------------------------------------------------
//    �������e : ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - ���� + Impl���_�C���N�g
//    �������e : 
//    �쐬�ڍ� : 2011/10/18
//    �⑫     : �݊����d���̕`���Sharder�𗘗p���������ȕ`��ɑΉ����Ă���
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : �啝�ȃ��t�@�N�^�����O�����s
//    �쐬�ڍ� : 2012/12/26    tory
//         
//====================================================================

#include <memory>                           // unique_ptr�ȂǂɕK�v
//#include <tiostream.h>                      // tstring�^�Ȃǂ�TCHAR�g����`

#include "Sprite.h"
#include "ISpriteImpl.h"
#include "GraphicsManagerImplDirect3D.hpp"

#include "SpriteImpl.hpp"
#include "SpriteImplShader.hpp"

using namespace std;
using namespace GameLib::Graphics;

// �����l�[���X�y�[�X��`
namespace{
      
    /// @brief  ���̃N���X�C���X�^���X
    /// @attention ����gImpl���A�N�Z�X�����ۂ̍ŏI�I�ȏ���������N���X�ł���B
    shared_ptr< ISpriteImpl > gImpl( nullptr );
   

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
        Sprite::Sprite(){}

        /// @brief �f�X�g���N�^
        Sprite::~Sprite(){}

        //----------------------------------------------------------
        // �����o�֐�

        /// @brief �C���X�^���X���쐬���܂��B
        /// @note extern�̃f�o�C�X������K����Impl���쐬���܂��B
        void Sprite::Create() {

            // �쐬�ς݂��ǂ������m�F����B
            if(gImpl != nullptr){
                MessageBox(NULL,_T("Sprite�̕`��p���̂𕡐��쐬���悤�Ƃ��܂����B"),_T("�C���X�^���X�쐬���~"),MB_OK);
                return;
            }

            // ���Ȃ���Ύ��̂��쐬
            // �����ō쐬����Impl�ɂ���Ďg�p����Sprite�`��Impl���ς���Ă���B
            if(gImplDirect3D->getVertexShaderReady()){
                shared_ptr< ImplSpriteShader > Impl(nullptr);
                Impl.reset(new ImplSpriteShader());
                gImpl.reset();
                gImpl = static_pointer_cast<ISpriteImpl>(Impl);
            }else{
                shared_ptr< ImplSprite > Impl(nullptr);
                Impl.reset(new ImplSprite());
                gImpl.reset();
                gImpl = static_pointer_cast<ISpriteImpl>(Impl);
            }


        }

        //----------------------------------------
        // �A�N�Z�T

            
        /// @brief �`�掞�̊�_�ƂȂ���W���w�肵�܂��B
        /// @param a_x �X�N���[�����X���W
        /// @param a_y �X�N���[�����Y���W
        void Sprite::Position(const float a_x, const float a_y){
            mTransform.setPositionX( a_x );
            mTransform.setPositionY( a_y );
        }

        /// @brief �X�v���C�g�̉�]�l���w�肵�܂��B
        /// @attention �P�ʁF�x ���̒l�Ŏ��v���ɉ�]
        /// @param a_Deg ��]������l(�x)
        void Sprite::Rotate(const float a_Deg){
            mTransform.setDegree( a_Deg );
        }

        /// @brief �X�v���C�g�̊g�嗦���w�肵�܂��B
        /// @attention �\�t���̎w��T�C�Y�ɑ΂��Ċg�嗦��K�p���܂��B
        /// @attention 2D�\�t���̃x�[�X�ƂȂ��ʃT�C�Y�Ƃ̎����g��⊮�Ƃ͊֘A����܂���B
        void Sprite::Scale(const float a_x, const float a_y){
            mTransform.setScale( a_x, a_y );
        }

        /// @brief �g�p����e�N�X�`�����w�肵�܂��B
        /// @attention �e�N�X�`�����w�肵�Ȃ��ꍇ�͎w�肵���F�ŋ�`��h��Ԃ��܂��B
        /// @param a_Texture �g�p����e�N�X�`��
        void Sprite::Texture(const Texture_sp a_Texture){
            mImage.setTexture( a_Texture );
        }

        /// @brief UV�͈̔͂�float�ɂĐݒ肵�܂��B
        /// @attention �g�p�e�N�X�`����ݒ�ςłȂ�����Size�w�肪�܂��s���Ă��Ȃ��ꍇ
        /// @attention Width��Height�̒l����Size�������⊮���܂��B
        /// @param a_Left �e�N�X�`���ォ��؂���ۂ�X�ʒu
        /// @param a_Top �e�N�X�`���ォ��؂���ۂ�Y�ʒu
        /// @param a_Width �؂��镝(1.0f�Ńe�N�X�`���̑S�̃T�C�Y)
        /// @param a_Height �؂��鍂��(1.0f�Ńe�N�X�`���̑S�̃T�C�Y)
        void Sprite::UV(const float a_Left, const float a_Top, const float a_Width, const float a_Height){
            mImage.setUV( BaseUV<float>(a_Left, a_Top, a_Width, a_Height) );

            // UV�̈�̒l��float�Őݒ肵������false�w��
            mImage.setUVint( false );
            //auto texture = ;
            // �e�N�X�`�����̂�����ꍇ
            if(mImage.Texture() != nullptr){
            //if(texture != nullptr){
                // �e�N�X�`���̑S�̃T�C�Y���擾
                auto textureSize = mImage.Size();
                    
                // �X�v���C�g�̕����܂����ݒ�ł���Ȃ�UV�͈̔͂��T�C�Y�Ƃ��Ďw��
                if(textureSize.width() == 0){
                    mSize.setWidth( textureSize.width()* a_Width );
                }
                // �X�v���C�g�̍������܂����ݒ�ł���Ȃ�UV�͈̔͂��T�C�Y�Ƃ��Ďw��
                if(textureSize.height() == 0){
                    mSize.setHeight( textureSize.height() * a_Height );
                }

            }
        }

        /// @brief UV�͈̔͂�int�ɂĐݒ肵�܂��B
        /// @attention Size�w�肪�܂��s���Ă��Ȃ��ꍇ�AWidth��Height�̒l����Size�������⊮���܂��B
        /// @param a_Left �e�N�X�`���ォ��؂���ۂ�X�ʒu(pixel�w��)
        /// @param a_Top �e�N�X�`���ォ��؂���ۂ�Y�ʒu(pixel�w��)
        /// @param a_Width �؂��镝(pixel�w��)
        /// @param a_Height �؂��鍂��(pixel�w��)
        void Sprite::UV(const int a_Left, const int a_Top, const int a_Width, const int a_Height){

            // UV�̈�̒l��int�Őݒ肵�����Ƃ��L�^
            // ����͕`�掞��UV��float�ɕϊ�����K�v�����邪
            // UV�ݒ莞�ɂ܂��e�N�X�`�������܂��Ă��Ȃ��ꍇ�A�e�N�X�`���T�C�Y��������Ȃ�(=�ϊ��ł��Ȃ�)����
            // ���float�l�ɕϊ�����ۂɎ��ʂŕK�v�ƂȂ�B
            mImage.setUVint( true );
            mImage.setUV( BaseUV<float>(float(a_Left), float(a_Top), float(a_Width), float(a_Height)) );
                    
            // �X�v���C�g�̕����܂����ݒ�ł���Ȃ�UV�͈̔͂��T�C�Y�Ƃ��Ďw��
            if(mSize.width() == 0){
                mSize.setWidth( float(a_Width) );
            }
            // �X�v���C�g�̍������܂����ݒ�ł���Ȃ�UV�͈̔͂��T�C�Y�Ƃ��Ďw��
            if(mSize.height() == 0){
                mSize.setHeight( float(a_Height) );
            }

        }

        /// @brief �X�v���C�g�̓\�t���̃T�C�Y��ݒ肵�܂��B
        /// @attention ���̃T�C�Y��Scale�ɂ��g�嗦��(1,1)�̏�Ԃ̎��̃T�C�Y�ƂȂ�܂��B
        /// @param a_Width �\�t���̕�(pixel�P��)
        /// @param a_Width �\�t���̍���(pixel�P��)
        void Sprite::Size(const float a_Width, const float a_Height){
            mSize.setWH( a_Width, a_Height );
        }

        /// @brief �s�{�b�g���w�肵�܂��B
        /// @param a_x X�ʒu
        /// @param a_y Y�ʒu
        void Sprite::Pivot(const float a_x, const float a_y){
            mPivot.setXY( a_x, a_y );
        }

        /// @brief �`�掞�̐F��ݒ肵�܂��B
        /// @param a_Red �w�肷��F�̐Ԓl
        /// @param a_Green �w�肷��F�̗Βl
        /// @param a_Blue �w�肷��F�̐l
        void Sprite::Color(const float a_Red, const float a_Green, const float a_Blue){
            mColor.setR( a_Red );
            mColor.setG( a_Green );
            mColor.setB( a_Blue );
        }

        /// @brief �`�掞�̓����x��ݒ肵�܂��B
        /// @param a_Alpha �����x
        void Sprite::Alpha(const float a_Alpha){
            mColor.setA( a_Alpha );
        }

        /// @brief �`�掞�̕\���D��x��ݒ肵�܂��B
        /// @param a_z �D��x
        void Sprite::Priority(const float a_z){
            mTransform.setPositionZ( a_z );
        }

        /// @brief �`�悷�邩�ǂ�����ݒ肵�܂��B
        /// @param a_value �`����s�̉�
        void Sprite::Activity(const bool a_value){
            mActivity = a_value;
        }



        /// @brief �`����s���܂��B2D�p��̈�T�C�Y�p�ւƎ����␳����܂��B
        void Sprite::Draw() const{
            if(mActivity){
                gImpl->Draw(mTransform, mImage, mPivot, mSize, mColor);
            }
        }

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
        void Sprite::FixedDraw() const{
            if(mActivity){
                gImpl->FixedDraw(mTransform, mImage, mPivot, mSize, mColor);
            }
        }

        //----------------------------------------
        // �w���p�[�֐�




    }
}
