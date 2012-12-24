/// @file Vector2.h
/// @brief xy�̗v�f������Vector2�N���X�̒�`
/// @brief Position�Ȃǂ�xy�p�N���X�Ƃ��Ďg�p���܂�
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            Vector2.h
//--------------------------------------------------------------------
//    �������e : xy�̗v�f������Vector2�N���X�̒�`
//    �������e : Position�Ȃǂ�xy�p�N���X�Ƃ��Ďg�p���܂�
//    �쐬�ڍ� : 2012/12/12    tory
//    �⑫     : �Ȃ�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR2_H
#define INCLUDED_GAMELIB_VECTOR2_H

#include <memory>       // shared_ptr�p

using namespace std;

namespace GameLib{

    namespace Graphics{

        /// @brief xy�̗v�f������Vector�N���X
        class Vector2{
        //----------------------------------------------------------
        // �v���g�^�C�v�錾

        /// @brief Vevtor2�����N���X
        class Impl;

        //----------------------------------------------------------
        // �ʖ��錾

        /// @brief Vector2Impl��shared_ptr�̕ʖ�
        typedef shared_ptr < Impl > Vector2Impl_sp;
        
        //----------------------------------------------------------
        // �����o�ϐ�
        private:
        Vector2Impl_sp mImpl;

        //----------------------------------------------------------
        // ���ꃁ���o�֐�
        public:

        /// @brief �R���X�g���N�^
        Vector2::Vector2();

        /// @brief �R���X�g���N�^
        Vector2::Vector2(const float x, const float y);

        /// @brief �R�s�[�R���X�g���N�^
        Vector2(const Vector2& obj);

        /// @brief �f�X�g���N�^
        virtual ~Vector2();

        /// @brief �R�s�[�i=���Z�q�I�[�o�[���[�h�j
        Vector2& operator=(const Vector2& obj);

        private:
        /// @brief �R�s�[���ɓ����ōs������
        void Copy(const Vector2& obj);



        //----------------------------------------------------------
        // �����o�֐�
        public:
        //----------------------------------------
        // �A�N�Z�T
            
        /// @brief �v�fX��ݒ肵�܂��B
        void setX(const float x);

        /// @brief �v�fY��ݒ肵�܂��B
        void setY(const float y);

        //----------------------------------------

        /// @brief �v�fX���擾���܂��B
        const float x() const;

        /// @brief �v�fY���擾���܂��B
        const float y() const;

        }; // end of class Vector2

    }  // end of namespace Graphics
} // end of namespace GameLib

#endif