/// @file Sqare.h
/// @brief �w��F�ŋ�`��`�悷��̂ɕK�v�ȃe�N�X�`�����Ǘ�����N���X - ��`
/// @note Sprite�@�\���g���ĕ`����s���܂��B
/// @date 2013/01/13     tory

//====================================================================
//              Sqare.h
//--------------------------------------------------------------------
//    �������e : �w��F�ŋ�`��`�悷��̂ɕK�v�ȃe�N�X�`�����Ǘ�����N���X - ��`
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

#ifndef INCLUDE_GAMELIB_GRAPHICS_SQARE_H
#define INCLUDE_GAMELIB_GRAPHICS_SQARE_H

#include <Comptr.hpp>
#include <d3d9.h>               // Texture�p

namespace GameLib{
    namespace Graphics{

        /// @class Sqare
        /// @brief �w��F�ŋ�`��`�悷��̂ɕK�v�ȃe�N�X�`�����Ǘ�����N���X
        class Sqare{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            // �B�؂��̂���cpp�̖����X�y�[�X�ɋL��

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:
            /// @brief �R���X�g���N�^
            Sqare();
            /// @brief �f�X�g���N�^
            ~Sqare();

            //----------------------------------------------------------
            // �����o�֐�
        public:            
            /// @brief �f�o�C�X���X�g���ɑΉ����邽�ߎQ�ƃJ�E���^�͂��̂܂܂�Sqare�p�̃e�N�X�`�����J�����܂��B
            void Backup();

            /// @brief �f�o�C�X���X�g�ŊJ�����Ă���Sqare�p�e�N�X�`�����č쐬���܂��B
            void Recover();

            //----------------------------------------
            // �A�N�Z�T
            
            /// @brief �e�N�X�`���̎��̂��擾���܂��B
            Com_ptr < IDirect3DTexture9 > texture() const;

            //----------------------------------------
            // �w���p�[�֐�
        private:
            /// @brief Sqare�p�̃e�N�X�`�����쐬���܂��B
            /// @a_Texture �w�肵���X�}�[�g�|�C���^���Sqare�p�e�N�X�`�����쐬���܂��B
            /// @note ���̂����łɂ���ꍇ�͉������������܂���B
            void Create(Com_ptr < IDirect3DTexture9 >& a_Texture);


        }; // end of class Sqare

    } // end of namespace Graphics
} // end of namespace GameLib
#endif