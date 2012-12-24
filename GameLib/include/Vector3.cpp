/// @file Vector3.cpp
/// @brief xyz�̗v�f������Vector3�N���X�̃��b�p�[
/// @brief Position��Scale�Ȃǂ�xyz�p�N���X�Ƃ��Ďg�p���܂�
/// @note 
/// @date 2012/12/05     tory
//====================================================================
//            Vector3.h
//--------------------------------------------------------------------
//    �������e : xyz�̗v�f������Vector3�N���X�̃��b�p�[
//    �������e : Vector3Impl�ւ̒��p�������s���܂��B
//    �쐬�ڍ� : 2012/12/05    tory
//    �⑫     : ������Impl���؂�ւ��鏈�������Ε�SDK�����ւ̈ڍs���\�B
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#include "Vector3.h"
#include "Vector3Impl.hpp"


namespace GameLib{

    namespace Graphics{

        /// @brief �R���X�g���N�^
        Vector3::Vector3(){
            this->mImpl.reset(new Impl() );
        }

        /// @brief �R���X�g���N�^
        Vector3::Vector3(const float x, const float y, const float z){
            this->mImpl.reset(new Impl(x, y, z) );
        }

        /// @brief �R�s�[�R���X�g���N�^
        Vector3::Vector3(const Vector3& obj){
            this->mImpl.reset(new Impl(obj.x(), obj.y(), obj.z()) );
            this->Copy(obj);
        }

        /// @brief �f�X�g���N�^
        Vector3::~Vector3(){}


        /// @brief �R�s�[�i=���Z�q�I�[�o�[���[�h�j
        Vector3& Vector3::operator=(const Vector3& obj){
            this->Copy(obj);
            return *this;
        }
        
        /// @brief �R�s�[���ɓ����ōs������
        void Vector3::Copy(const Vector3& obj){
            this->setX(obj.x());
            this->setY(obj.y());
            this->setZ(obj.z());
        }


        //----------------------------------------------------------

        /// @brief �v�fX��ݒ肵�܂��B
        void Vector3::setX(const float x){
            this->mImpl->setX(x);
        }

         /// @brief �v�fY��ݒ肵�܂��B
        void Vector3::setY(const float y){
            this->mImpl->setY(y);
        }

         /// @brief �v�fZ��ݒ肵�܂��B
        void Vector3::setZ(const float z){
            this->mImpl->setZ(z);
        }
        
        //----------------------------------------------------------

        /// @brief �v�fX���擾���܂��B
        const float Vector3::x() const{
            return this->mImpl->x();
        }

        /// @brief �v�fY���擾���܂��B
        const float Vector3::y() const{
            return this->mImpl->y();
        }

        /// @brief �v�fZ���擾���܂��B
        const float Vector3::z() const{
            return this->mImpl->z();
        }


    }   // end of namespace Graphics
}    // end of namespace GameLib
