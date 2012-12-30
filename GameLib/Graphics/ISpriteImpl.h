/// @file ISpriteImpl.h
/// @brief ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X��Impl�p�C���^�[�t�F�C�X
/// @note �݊����d���̕`���Sharder�𗘗p���������ȕ`��ɑΉ����Ă���
/// @date 2012/12/28     tory

//====================================================================
//              ISpriteImpl.h
//--------------------------------------------------------------------
//    �������e : ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X��Impl�p�C���^�[�t�F�C�X
//    �������e : 
//    �쐬�ڍ� : 2012/12/28
//    �⑫     : �݊����d���̕`���Sharder�𗘗p���������ȕ`��ɑΉ����Ă���
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2013/01/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_SPRITE_IMPL_INTERFACE_H
#define INCLUDE_GAMELIB_SPRITE_IMPL_INTERFACE_H

#include <Transform2D.h>
#include <ImageBase.h>
#include <TemplateBaseClass.h>
#include <Color.h>

namespace GameLib{
    namespace Graphics{

        /// @class ISpriteImpl
        /// @brief 2D�`��N���XImpl�̌p�����ƂȂ�C���^�[�t�F�C�X�N���X
        class ISpriteImpl{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            // Interface�̓����o�ϐ��Ȃǂ̎��̂������Ȃ��B

            //----------------------------------------------------------
            // ���ꃁ���o
        public:

            /// @brief �R���X�g���N�^
            ISpriteImpl(){}

            /// @brief �f�X�g���N�^
            virtual ~ISpriteImpl(){}

            //----------------------------------------------------------
            // �����o�֐�
            // �e�`��f�o�C�X�ŋ��ʂ��鏈�����L�q���邱�ƁB

            // Interface�Ȃ̂őS�Ẵ��\�b�h��virtual��=0�����Ă������ƁB
            //virtual void Test(const int x) = 0;

            /// @brief �`����s���܂��B2D�p��̈�T�C�Y�p�ւƎ����␳����܂��B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            virtual void Draw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color) = 0;

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            virtual void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color) = 0;

            /// @brief ���X�g�ɐς�Sprite���܂Ƃ߂ĕ`�悵�܂��B
            virtual void DrawAll() = 0;

            //----------------------------------------
            // �A�N�Z�T�p




        }; // end of class ISpriteImpl



    } // end of namespace Graphics
} // end of namespace GameLib
#endif