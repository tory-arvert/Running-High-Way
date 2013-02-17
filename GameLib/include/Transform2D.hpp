/// @file Transform2D.hpp
/// @brief ���W�E�g��l�E��]���܂Ƃ߂�2D�p�g�����X�t�H�[���N���X
/// @note 
/// @date 2012/12/29     tory
//====================================================================
//            Transform2D.hpp
//--------------------------------------------------------------------
//    �������e : ���W�E�g��l�E��]���܂Ƃ߂�2D�p�g�����X�t�H�[���N���X
//    �������e : 
//    �쐬�ڍ� : 2012/12/29    tory
//    �⑫     : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================

#ifndef INCLUDED_GAMELIB_GRAPHICS_TRANSFORM2D_H
#define INCLUDED_GAMELIB_GRAPHICS_TRANSFORM2D_H

#include "TemplateBaseClass.hpp"

namespace GameLib{
    namespace Graphics{

        /// @class Transform2D
        /// @brief ���W�E�g��l�E��]���܂Ƃ߂�2D�p�g�����X�t�H�[���N���X
        class Transform2D{
            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            BaseXYZ<float>  mPosition;
            BaseXY<float>   mScale;
            float           mDegree;

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:
            /// @brief �R���X�g���N�^
            Transform2D():mScale(1.0f,1.0f),mDegree(0.0f){}
            /// @brief �f�X�g���N�^
            ~Transform2D(){}

            //----------------------------------------------------------
            // �����o�֐�
        public:
            // �A�N�Z�T

            /// @brief X���W��ݒ肵�܂��B
            /// @param a_x X���W
            void setPositionX( const float a_x ){
                mPosition.setX(a_x);
            }

            /// @brief Y���W��ݒ肵�܂��B
            /// @param a_y Y���W
            void setPositionY( const float a_y ){
                mPosition.setY(a_y);
            }

            /// @brief Z���W��ݒ肵�܂��B
            /// @param a_z Z���W
            void setPositionZ( const float a_z ){
                mPosition.setZ(a_z);
            }


            /// @brief �g�嗦��ݒ肵�܂��B
            void setScale(const float a_x, const float a_y){
                mScale.setX(a_x);
                mScale.setY(a_y);
            }

            /// @brief ��]�p�x��ݒ肵�܂��B
            /// @brief �ݒ�͈͂�0.0~360.0�x�Ɏ����␳����܂��B
            /// @note �ݒ�P�ʂ�degree(�x)��float�ł��B
            /// @param a_Deg �ݒ肷��x
            const void setDegree(const float a_Deg){

                mDegree = a_Deg;
                // 360�x���傫�����͔͈͓��̓��l�ɏC���B
                while( mDegree > 360.0000f){
                    mDegree -=360.0000f;
                }
                // 0�x��菬�������͔͈͓��̓��l�ɏC���B
                while( mDegree < 0.0000f){
                    mDegree +=360.0000f;
                }
            }


            //----------------------------------------

            /// @brief �ݒ肵�����W�l���擾���܂��B
            /// @return BaseXY<float> ���W�lXY
            const BaseXYZ<float> position() const{
                return BaseXYZ<float> (mPosition.x(), mPosition.y(), mPosition.z() );
            }

            /// @brief �g�嗦���擾���܂��B
            const BaseXY<float> scale() const{
                return BaseXY<float> ( mScale.x(), mScale.y() );
            }

            /// @brief ��]�p�x���擾���܂��B
            /// @note �擾�P�ʂ�degree(�x)��float�ł��B
            const float degree() const{
                return mDegree;
            }

        };

    }
}

#endif