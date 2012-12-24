/// @file Vector3.h
/// @brief xyz�̗v�f������Vector3�N���X�̒�`
/// @brief Position��Scale�Ȃǂ�xyz�p�N���X�Ƃ��Ďg�p���܂�
/// @note 
/// @date 2012/12/05     tory
//====================================================================
//            Vector.h
//--------------------------------------------------------------------
//    �������e : xyz�̗v�f������Vector3�N���X�̒�`
//    �������e : Position��Scale�Ȃǂ�xyz�p�N���X�Ƃ��Ďg�p���܂�
//    �쐬�ڍ� : 2012/12/05    tory
//    �⑫     : �Ȃ�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR3_H
#define INCLUDED_GAMELIB_VECTOR3_H

#include <memory>       // shared_ptr�p

using namespace std;

namespace GameLib{

    namespace Graphics{

        /// @brief xyz�̗v�f������Vector�N���X
        class Vector3{
            //----------------------------------------------------------
            // �v���g�^�C�v�錾

            /// @brief Vevtor3�����N���X
            class Impl;

            //----------------------------------------------------------
            // �ʖ��錾

            /// @brief Vector3Impl��shared_ptr�̕ʖ�
            typedef shared_ptr < Impl > Vector3Impl_sp;

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            Vector3();

            /// @brief �R���X�g���N�^
            Vector3(const float x, const float y, const float z);

            /// @brief �R�s�[�R���X�g���N�^
            Vector3(const Vector3& obj);

            /// @brief �f�X�g���N�^
            virtual ~Vector3();

            /// @brief �R�s�[�i=���Z�q�I�[�o�[���[�h�j
            Vector3& operator=(const Vector3& obj);

        private:
            /// @brief �R�s�[���ɓ����ōs������
            void Copy(const Vector3& obj);

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            Vector3Impl_sp mImpl;

            //----------------------------------------------------------
            // �����o�֐�
        public:
            //----------------------------------------
            // �A�N�Z�T
            
            /// @brief �v�fX��ݒ肵�܂��B
            void setX(const float x);

            /// @brief �v�fY��ݒ肵�܂��B
            void setY(const float y);

            /// @brief �v�fZ��ݒ肵�܂��B
            void setZ(const float z);

            //----------------------------------------

            /// @brief �v�fX���擾���܂��B
            const float x() const;

            /// @brief �v�fY���擾���܂��B
            const float y() const;

            /// @brief �v�fZ���擾���܂��B
            const float z() const;
          
        }; // end of class Vector3


    }   // end of namespace Graphics
}    // end of namespace GameLib

#endif
