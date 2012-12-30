/// @file ImageBase.h
/// @brief �e�N�X�`���֘A�̂܂Ƃ߃N���X
/// @note 
/// @date 2012/12/29     tory
//====================================================================
//            ImageBase.h
//--------------------------------------------------------------------
//    �������e : �e�N�X�`���֘A�̂܂Ƃ߃N���X
//    �������e : 
//    �쐬�ڍ� : 2012/12/29    tory
//    �⑫     : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================

#ifndef INCLUDED_GAMELIB_GRAPHICS_IMAGEBASE_H
#define INCLUDED_GAMELIB_GRAPHICS_IMAGEBASE_H

#include "TemplateBaseClass.h"
#include <Comptr.hpp>
#include <d3d9.h>               // Texture���̗p


namespace GameLib{
    namespace Graphics{

        /// @class ImageBase
        /// @brief �e�N�X�`���֘A�̂܂Ƃ߃N���X
        class ImageBase{

            /// @class TextureParameter
            /// @param �e�N�X�`���̏����܂Ƃ߂��N���X
            class TextureParameter{

                //----------------------------------------------------------
                // �����o�ϐ� 
            private:
                /// @brief �e�N�X�`���̑S�̃T�C�Y
                BaseWH<int>     mSize;
                /// @brief UV�̎w��͈�
                BaseUV<float>   mUV;
                /// @brief UV�l�̐ݒ肪int��float���̎��ʗp�t���O
                bool            mUVint;

                //----------------------------------------------------------
                // ���ꃁ���o�֐�
            public:
                /// @brief �R���X�g���N�^
                TextureParameter():
                    mSize(), mUV(){} // �������q�Ń����o�ϐ���������

                /// @brief �f�X�g���N�^
                ~TextureParameter(){}

                //----------------------------------------------------------
                // �����o�֐�
            public:

                //----------------------------------------
                // �A�N�Z�T

                /// @brief �e�N�X�`���̃T�C�Y���擾���܂��B
                const BaseWH<int> size() const{
                    return mSize;
                }

                /// @brief �e�N�X�`���̃T�C�Y��ݒ肵�܂��B
                /// @param a_Width �e�N�X�`���̕�
                /// @param a_Height �e�N�X�`���̍���
                void setSize(const int a_Width, const int a_Height){
                    mSize.setWH(a_Width, a_Height);
                }


                /// @brief �e�N�X�`����UV�l���擾���܂��B
                const BaseUV<float> UV() const{
                    return mUV;
                }


                /// @brief �e�N�X�`����UV�l��ݒ肵�܂��B
                /// @param a_UV �ݒ肷��UV�l
                void setUV(const BaseUV<float> a_UV){
                    mUV = a_UV;
                }

                /// @brief UV�l�̐ݒ肪int�ōs��ꂽ���ǂ����̏�Ԃ�Ԃ��܂��B
                /// @return bool UV�̐ݒ�P��
                const bool isUVint() const{
                    return mUVint;
                }

                /// @brief UV�l�̐ݒ�̒P�ʂ�int�ōs��ꂽ���ǂ�����ݒ肵�܂��B
                /// @param a_Value int�l��UV�̐ݒ肪�s��ꂽ���ǂ��� 
                void setUVint(const bool a_Value){
                    mUVint = a_Value;
                }



            };


            //----------------------------------------------------------
            // �ʖ��錾

            /// @brief IDirect3DTexture9�̃X�}�[�g�|�C���^�^
            typedef Com_ptr< IDirect3DTexture9 > Texture_sp;

            
            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            Texture_sp          mTexture;
            TextureParameter    mParameter;

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:
            /// @brief �R���X�g���N�^
            ImageBase(){}

            /// @brief �f�X�g���N�^
            ~ImageBase(){}

            //----------------------------------------------------------
            // �����o�֐�
        public:

            /// @brief �e�N�X�`�����̂�ݒ肵�܂��B
            /// @param a_Texture �e�N�X�`���̃X�}�[�g�|�C���^
            void setTexture(const Texture_sp a_Texture){
                mTexture = a_Texture;
                
                // �e�N�X�`��(���m�ɂ̓T�[�t�F�C�X)�̃T�C�Y��ݒ肵�܂��B
                D3DSURFACE_DESC desc;
                mTexture->GetLevelDesc( 0, &desc );
                mParameter.setSize( desc.Width, desc.Height );
            }

            /// @brief �e�N�X�`�����̂��擾���܂��B
            /// @return �e�N�X�`���̃X�}�[�g�|�C���^
            const Texture_sp Texture() const{
                return mTexture;
            }

            /// @brief �e�N�X�`���̃T�C�Y���擾���܂��B
            /// @return int��WH�N���X
            const BaseWH<int> Size() const{
                return mParameter.size();
            }

            /// @brief �e�N�X�`���Ŏg�p����UV�̈��ݒ肵�܂��B
            /// @param 
            void setUV(const BaseUV<float> a_UV){
                mParameter.setUV(a_UV);
            }

            /// @brief �e�N�X�`���Őݒ肷��UV�̈���擾���܂��B
            /// @return 
            const BaseUV<float> getUV() const{
                return mParameter.UV();
            }

            /// @brief �e�N�X�`���Őݒ肷��UV�̈�̍���n�_���W���擾���܂��B
            /// @param a_Left ���ӂ�X���W���i�[����܂��B
            /// @param a_Top�@��ӂ�Y���W���i�[����܂��B
            void getUV_LT(float *a_Left, float *a_Top) const{
                auto value = mParameter.UV();
                *a_Left  = value.left();
                *a_Top = value.top();
            }

            /// @brief �e�N�X�`���Őݒ肷��UV�̈�͈̔͂��擾���܂��B
            /// @param a_width   UV�̕����i�[����܂��B
            /// @param a_height�@UV�̍������i�[����܂��B
            void getUV_WH(float *a_Width, float *a_Height) const{
                auto value = mParameter.UV();
                *a_Width  = value.width();
                *a_Height = value.height();
            }

            /// @brief UV�l�̐ݒ肪int�ōs��ꂽ���ǂ����̏�Ԃ�Ԃ��܂��B
            /// @return bool UV�̐ݒ�P��
            const bool isUVint() const{
                return mParameter.isUVint();
            }

            /// @brief UV�l�̐ݒ�̒P�ʂ�int�ōs��ꂽ���ǂ�����ݒ肵�܂��B
            /// @param a_Value int�l��UV�̐ݒ肪�s��ꂽ���ǂ��� 
            void setUVint(const bool a_Value){
                mParameter.setUVint( a_Value );
            }


        };


    } // end of namespace Graphics
} // end of namespace GameLib
#endif