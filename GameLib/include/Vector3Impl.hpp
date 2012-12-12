/// @file Vector3Impl.h
/// @brief xyz�̗v�f������Vector3�N���X�̎���
/// @brief Position��Scale�Ȃǂ�xyz�p�N���X�Ƃ��Ďg�p���܂�
/// @note 
/// @date 2012/12/05     tory
//====================================================================
//            Vector3Impl.h
//--------------------------------------------------------------------
//    �������e : xyz�̗v�f������Vector3�N���X�̎���
//    �������e : Position��Scale�Ȃǂ�xyz�p�N���X�Ƃ��Ďg�p���܂�
//    �쐬�ڍ� : 2012/12/05    tory
//    �⑫     : �Ȃ�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR3_IMPL
#define INCLUDED_GAMELIB_VECTOR3_IMPL

#include <d3dx9.h>                  // D3DXVECTOR3�p
#include "Vector3.h"

namespace GameLib{

    namespace Graphics{

        /// @class Vector3�̎��̃N���X
        /// @brief xyz�̗v�f������Vector3�N���X
        class Vector3::Impl{
            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            Impl(){
                this->setX(0.0f);
                this->setY(0.0f);
                this->setZ(0.0f);
            }

            /// @brief �R���X�g���N�^
            Impl(const float x, const float y, const float z){
                this->setX(x);
                this->setY(y);
                this->setZ(z);
            }

            /// @brief �f�X�g���N�^
            virtual ~Impl(){}

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            D3DXVECTOR3 mVector3;

            //----------------------------------------------------------
            // �����o�֐�
        public:
            
            /// @brief �v�fX��ݒ肵�܂��B
            void setX(const float x){
                this->mVector3.x = x;
            }

            /// @brief �v�fY��ݒ肵�܂��B
            void setY(const float y){
                this->mVector3.y = y;
            }

            /// @brief �v�fZ��ݒ肵�܂��B
            void setZ(const float z){
                this->mVector3.z = z;
            }

            /// @brief �v�fX���擾���܂��B
            const float x() const{
                return this->mVector3.x;
            }

            /// @brief �v�fY���擾���܂��B
            const float y() const{
                return this->mVector3.y;
            }

            /// @brief �v�fZ���擾���܂��B
            const float z() const{
                return this->mVector3.z;
            }

            
        }; // end of class Impl

    }   // end of namespace Graphics
}    // end of namespace GameLib

#endif
