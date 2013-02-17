/// @file Sprite.h
/// @brief ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - ��`
/// @note �݊����d���̕`���Sharder�𗘗p���������ȕ`��ɑΉ����Ă���
/// @date 2011/10/18     tory

//====================================================================
//              Sprite.h
//--------------------------------------------------------------------
//    �������e : ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - ��`
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

#ifndef INCLUDE_GAMELIB_GRAPHICS_SPRITE_H
#define INCLUDE_GAMELIB_GRAPHICS_SPRITE_H

#include <Comptr.hpp>
#include <d3d9.h>               // Texture���̗p

#include <Transform2D.hpp>
#include <ImageBase.hpp>
#include <TemplateBaseClass.hpp>
#include <Color.hpp>


#include <tiostream.h>          ///< @todo TestTexCreate�p�A�J���I�����͓P������

namespace GameLib{
    namespace Graphics{

        /// @class Sprite
        /// @brief ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X
        class Sprite{
            
            //----------------------------------------------------------
            // �ʖ��錾

            /// @brief IDirect3DTexture9�̃X�}�[�g�|�C���^�^
            typedef Com_ptr< IDirect3DTexture9 > Texture_sp;

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            Transform2D     mTransform;     ///< @brief ���W�E�g��E��]�p
            ImageBase       mImage;         ///< @brief �e�N�X�`���֘A
            BaseXY<float>   mPivot;         ///< @brief �g��E��]���̊�_(0,0�ŃX�v���C�g�̍���ʒu�A1�P�ʓ�����1pixel)
            BaseWH<float>   mSize;          ///< @brief �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            Color4<float>   mColor;         ///< @brief �X�v���C�g�`�掞�Ɏg�p����F�⃿�l
            bool            mActivity;      ///< @brief �`�悷�邩�ǂ����̉�
            
            
            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            Sprite();

            /// @brief �f�X�g���N�^
            ~Sprite();

            //----------------------------------------------------------
            // �����o�֐�
        public:


            /// @brief Sprite�̎��̃C���X�^���X��DirectX�f�o�C�X�̏�Ԃɍ��킹�č쐬���܂��B
            /// @brief ����ɂ����Impl���݊����d�������x�d���������肵�܂��B
            /// @brief �����Ȃ��A�܂���true�ŗD��I��shader(���x�d��)�ɂȂ�悤�ɂ��܂��B
            /// @attention ���̃��\�b�h��extern�ɂĊ֘A�t����GraphicsManager�̃��\�b�h���g�p���܂��B
            /// @param a_ShaderPriority �D��I��shader�ŏ�������悤�ɐݒ肷�邩�ǂ���
            void Create(const bool a_ShaderPriority = true);

            //----------------------------------------
            // �A�N�Z�T

            /// @brief ������Ԃ̃X�e�[�^�X��ݒ肵�܂��B
            /// @brief Position(0,0),Rotate(0),Scale(1,1),Texture(null),UV(0.0f,0.0f,1.0f,1.0f)
            /// @brief Size(128,128),Pivot(0,0),Color(255,255,255),Alpha(255),Priority(1.0f),Activity(true)
            void Initialize();
            
            /// @brief �`�掞�̊�_�ƂȂ���W���w�肵�܂��B
            /// @param a_x �X�N���[�����X���W
            /// @param a_y �X�N���[�����Y���W
            void Position(const float a_x, const float a_y);

            /// @brief �X�v���C�g�̉�]�l���w�肵�܂��B
            /// @attention �P�ʁF�x ���̒l�Ŏ��v���ɉ�]
            /// @param a_Deg ��]������l(�x)
            void Rotate(const float a_Deg);

            /// @brief �X�v���C�g�̊g�嗦���w�肵�܂��B
            /// @attention �\�t���̎w��T�C�Y�ɑ΂��Ċg�嗦��K�p���܂��B
            /// @attention 2D�\�t���̃x�[�X�ƂȂ��ʃT�C�Y�Ƃ̎����g��⊮�Ƃ͊֘A����܂���B
            void Scale(const float a_x, const float a_y);

            /// @brief �g�p����e�N�X�`�����w�肵�܂��B
            /// @attention �e�N�X�`�����w�肵�Ȃ��ꍇ�͎w�肵���F�ŋ�`��h��Ԃ��܂��B
            /// @param a_Texture �g�p����e�N�X�`��
            void Texture(const Texture_sp a_Texture);

            /// @brief UV�͈̔͂�float�ɂĐݒ肵�܂��B
            /// @attention �g�p�e�N�X�`����ݒ�ςłȂ�����Size�w�肪�܂��s���Ă��Ȃ��ꍇ
            /// @attention Width��Height�̒l����Size�������⊮���܂��B
            /// @param a_Left �e�N�X�`���ォ��؂���ۂ�X�ʒu
            /// @param a_Top �e�N�X�`���ォ��؂���ۂ�Y�ʒu
            /// @param a_Width �؂��镝(1.0f�Ńe�N�X�`���̑S�̃T�C�Y)
            /// @param a_Height �؂��鍂��(1.0f�Ńe�N�X�`���̑S�̃T�C�Y)
            void UV(const float a_Left, const float a_Top, const float a_Width, const float a_Height);

            /// @brief UV�͈̔͂�int�ɂĐݒ肵�܂��B
            /// @attention Size�w�肪�܂��s���Ă��Ȃ��ꍇ�AWidth��Height�̒l����Size�������⊮���܂��B
            /// @param a_Left �e�N�X�`���ォ��؂���ۂ�X�ʒu(pixel�w��)
            /// @param a_Top �e�N�X�`���ォ��؂���ۂ�Y�ʒu(pixel�w��)
            /// @param a_Width �؂��镝(pixel�w��)
            /// @param a_Height �؂��鍂��(pixel�w��)
            void UV(const int a_Left, const int a_Top, const int a_Width, const int a_Height);

            /// @brief �X�v���C�g�̓\�t���̃T�C�Y��ݒ肵�܂��B
            /// @attention ���̃T�C�Y��Scale�ɂ��g�嗦��(1,1)�̏�Ԃ̎��̃T�C�Y�ƂȂ�܂��B
            /// @param a_Width �\�t���̕�(pixel�P��)
            /// @param a_Width �\�t���̍���(pixel�P��)
            void Size(const float a_Width, const float a_Height);

            /// @brief �s�{�b�g���w�肵�܂��B
            /// @param a_x X�ʒu
            /// @param a_y Y�ʒu
            void Pivot(const float a_x, const float a_y);

            /// @brief �`�掞�̐F��ݒ肵�܂��B
            /// @param a_Red �w�肷��F�̐Ԓl
            /// @param a_Green �w�肷��F�̗Βl
            /// @param a_Blue �w�肷��F�̐l
            void Color(const float a_Red, const float a_Green, const float a_Blue);

            /// @brief �`�掞�̓����x��ݒ肵�܂��B
            /// @param a_Alpha �����x
            void Alpha(const float a_Alpha);

            /// @brief �e�N�X�`���̃��l���g�p���邩�ݒ肵�܂��B
            /// @brief ���̃X�e�[�^�X�ɂ����List�̔z�񂪍œK������܂��B
            /// @param a_Value �e�N�X�`���̃��l��L���ɂ��邩�ǂ���
            void UseTextureAlpha(const bool a_Value);

            /// @brief �`�掞�̕\���D��x��ݒ肵�܂��B
            /// @param a_z �D��x
            void Priority(const float a_z);

            /// @brief �`�悷�邩�ǂ�����ݒ肵�܂��B
            /// @param a_value �`����s�̉�
            void Activity(const bool a_value);

            /// @brief Sprite�̕`������X�g�Ƃ��Đς�ł����܂��B
            /// @note ����͂܂Ƃ߂ĕ`�悳���邱�Ƃɂ�鍂�����̂��߂ł��B
            void BeginList() const;

            /// @brief �`����s���܂��B2D�p��̈�T�C�Y�p�ւƎ����␳����܂��B
            void Draw() const;

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
            void FixedDraw() const;

            /// @brief ���X�g�ɐς�Sprite���܂Ƃ߂ĕ`�悵�܂��B
            void DrawALL() const;

            /// @brief ���C�u�����쐬���̃e�X�g�p�֐�
            /// @brief �e�N�X�`�������쐬���܂��B
            /// @todo ���������炱�̃��\�b�h�͍폜���܂��I
            void TestTexCreate(const std::tstring a_str);

            //----------------------------------------
            // �w���p�[�֐�
        private:



        }; // end of class Sprite

    } // end of namespace Graphics
} // end of namespace GameLib
#endif