/// @file Vector2.cpp
/// @brief xy�̗v�f������Vector2�N���X�̃��b�p�[
/// @brief Position�Ȃǂ�xy�p�N���X�Ƃ��Ďg�p���܂�
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            Vector2.cpp
//--------------------------------------------------------------------
//    �������e : xy�̗v�f������Vector2�N���X�̃��b�p�[
//    �������e : Vector2Impl�ւ̒��p�������s���܂��B
//    �쐬�ڍ� : 2012/12/12    tory
//    �⑫     : ������Impl���؂�ւ��鏈�������Ε�SDK�����ւ̈ڍs���\�B
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#include "Vector2.h"
#include "Vector2Impl.hpp"


namespace GameLib{

    namespace Graphics{

        /// @brief �R���X�g���N�^
        Vector2::Vector2(){
            this->mImpl.reset(new Impl() );
        }

        /// @brief �R���X�g���N�^
        Vector2::Vector2(const float x, const float y){
            this->mImpl.reset(new Impl(x, y) );
        }

        /// @brief �R�s�[�R���X�g���N�^
        Vector2::Vector2(const Vector2& obj){
            this->mImpl.reset(new Impl(obj.x(), obj.y()) );
            this->Copy(obj);
        }

        /// @brief �f�X�g���N�^
        Vector2::~Vector2(){}


        /// @brief �R�s�[�i=���Z�q�I�[�o�[���[�h�j
        Vector2& Vector2::operator=(const Vector2& obj){
            this->Copy(obj);
            return *this;
        }
        
        /// @brief �R�s�[���ɓ����ōs������
        void Vector2::Copy(const Vector2& obj){
            this->setX(obj.x());
            this->setY(obj.y());
        }


        //----------------------------------------------------------

        /// @brief �v�fX��ݒ肵�܂��B
        void Vector2::setX(const float x){
            this->mImpl->setX(x);
        }

         /// @brief �v�fY��ݒ肵�܂��B
        void Vector2::setY(const float y){
            this->mImpl->setY(y);
        }

        
        //----------------------------------------------------------

        /// @brief �v�fX���擾���܂��B
        const float Vector2::x() const{
            return this->mImpl->x();
        }

        /// @brief �v�fY���擾���܂��B
        const float Vector2::y() const{
            return this->mImpl->y();
        }


    }   // end of namespace Graphics
}    // end of namespace GameLib
