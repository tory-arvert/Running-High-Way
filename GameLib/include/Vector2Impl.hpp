/// @file Vector2Impl.h
/// @brief xy�̗v�f������Vector2�N���X�̎���
/// @brief Position�Ȃǂ�xy�p�N���X�Ƃ��Ďg�p���܂�
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            Vector2Impl.h
//--------------------------------------------------------------------
//    �������e : xy�̗v�f������Vector2�N���X�̎���
//    �������e : Position�Ȃǂ�xy�p�N���X�Ƃ��Ďg�p���܂�
//    �쐬�ڍ� : 2012/12/12    tory
//    �⑫     : �Ȃ�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR2_IMPL
#define INCLUDED_GAMELIB_VECTOR2_IMPL

#include <d3dx9.h>                  // D3DXVECTOR2�p
#include "Vector2.h"

namespace GameLib{

    namespace Graphics{

        /// @class Vector2�̎��̃N���X
        /// @brief xy�̗v�f������Vector3�N���X
        class Vector2::Impl{
            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            Impl() : mVector2()
            {
            }

            /// @brief �R���X�g���N�^
            Impl(const float x, const float y){
                setX( x );
                setY( y );
            }

            /// @brief �f�X�g���N�^
            virtual ~Impl()
            {
            }

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            D3DXVECTOR2 mVector2;

            //----------------------------------------------------------
            // �����o�֐�
        public:
            
            /// @brief �v�fX��ݒ肵�܂��B
            void setX(const float x){
                mVector2.x = x;
            }

            /// @brief �v�fY��ݒ肵�܂��B
            void setY(const float y){
                mVector2.y = y;
            }


            /// @brief �v�fX���擾���܂��B
            const float x() const{
                return mVector2.x;
            }

            /// @brief �v�fY���擾���܂��B
            const float y() const{
                return mVector2.y;
            }


            
        }; // end of class Impl

    }   // end of namespace Graphics
}    // end of namespace GameLib

#endif
