/// @file SpriteImpl.hpp
/// @brief ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - Impl
/// @note �݊����d���̕`��Impl
/// @date 2012/12/28     tory

//====================================================================
//              SpriteImpl.hpp
//--------------------------------------------------------------------
//    �������e : ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - Impl
//    �������e : 
//    �쐬�ڍ� : 2012/12/28
//    �⑫     : �݊����d���̕`��Impl
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2013/01/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_SPRITE_IMPL_H
#define INCLUDE_GAMELIB_SPRITE_IMPL_H

#include <memory>
#include <tiostream.h>          // tstring�^�Ȃǂ�TCHAR�g����`

#include <d3d9.h>
#include <d3dx9.h>
#include "GraphicsManagerImplDirect3D.hpp"


#include <Transform2D.hpp>
#include <ImageBase.hpp>
#include <TemplateBaseClass.hpp>
#include <Color.hpp>

// StaticLib�v���W�F�N�g�̃v���p�e�B����lib���Ăяo���ꍇwarning���o�邽�߁A����̑�p�@
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")

namespace GameLib{
    namespace Graphics{

        /// @brief  �C���X�^���X
        extern shared_ptr< ImplDirect3D > gImplDirect3D;


        /// @class ImplSprite
        /// @brief DirectX�W����LPD3DXSPRITE��p�����X�v���C�g�\��
        class ImplSprite : public ISpriteImpl{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            LPD3DXSPRITE    mSprite;        ///< @brief �X�v���C�g�`��N���X
            BaseXY<float>   mResolution;    ///< @brief �𑜓x�̒����p�k�ڒl
    
            bool            mbListBegin;    ///< @brief ���X�g�ςݍ��݊J�n��L���ɂ������ǂ���

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            ImplSprite(){

                InitializeSprite();
                int c_x, c_y = 0;
                int c2d_x, c2d_y =0;
                gImplDirect3D->getClientSize(&c_x, &c_y);
                gImplDirect3D->get2DClientSize(&c2d_x, &c2d_y);

                // �\���N���C�A���g�T�C�Y��2D�p�`��̈�T�C�Y
                mResolution.setX( float(c_x) / float(c2d_x) );
                mResolution.setY( float(c_y) / float(c2d_y) );

            }

            /// @brief �f�X�g���N�^
            ~ImplSprite(){}


            //----------------------------------------------------------
            // �����o�֐�
        public:

            /// @brief �X�v���C�g���g�p�o����悤�ɏ��������܂��B
            void InitializeSprite(){
                auto Device = gImplDirect3D->getDevice();
                if(FAILED(D3DXCreateSprite( Device.getPtr(), &mSprite ))){
                    MessageBox(NULL,_T("�X�v���C�g�̍쐬�Ɏ��s���܂���"),_T("�ǂݍ��ݎ��s"),MB_OK);
                }
            }

            /// @brief �X�v���C�g��`�惊�X�g�ɐςݏグ�邱�Ƃ�L���ɂ��܂��B
            void Begin() {
                if(!mbListBegin){
                    mSprite->Begin(D3DXSPRITE_ALPHABLEND);
                    mbListBegin = true;
                }
            }

            /// @brief �`����s���܂��B2D�p��̈�T�C�Y�p�ւƎ����␳����܂��B
            /// @attention �`��̎d���ɂ���Čv�Z�Ɏg���ϐ������G�ɂȂ邽�ߎ��O�Ɍv�Z���Ă������Ƃ�����B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            /// @todo Matrix�̌v�Z����V�������̂ɏC�����邱��
            void Draw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color) {

                // ���X�g�ςݍ��݂̗L���l���m�F & �ݒ�
                if(!mbListBegin){
                    Begin();
                }

                // �v�Z���K�v�ɂȂ���̂͊e�������K�v�Ȃ��̂𒊏o
                // UV�l�𒊏o
                auto a_UV = a_Image.getUV();
                // �g�嗦�𒊏o
                auto a_Scale = a_Transform.scale();
                // ���W�𒊏o
                auto a_Position = a_Transform.position();
                // �e�N�X�`���𒊏o
                auto texture = a_Image.Texture();


                // �e�N�X�`���̊g�嗦
                D3DXVECTOR2 scale(a_Scale.x(), a_Scale.y());
                // �𑜓x�ɂ��\��t�����̏k�ڕω��ɔ����C��
                scale.x *= mResolution.x() * a_Size.width();
                scale.y *= mResolution.y() * a_Size.height();
                scale.x /= a_UV.width();
                scale.y /= a_UV.height();

                // �؂���摜�̒��S
                D3DXVECTOR2 pivot(a_Pivot.x(), a_Pivot.y() );
                // �`��ʒu
                D3DXVECTOR2 Pos(( a_Position.x() * scale.x ) - pivot.x, ( a_Position.y() * scale.y )- pivot.y);            
                // ��]�s����쐬
                D3DXMATRIX pOut;
                D3DXMatrixTransformation2D(&pOut, &pivot, 0, &scale, &pivot, D3DXToRadian(a_Transform.degree()), &Pos);


                // �e�N�X�`���̃T�C�Y���擾
                BaseWH<int> a_TextureSize = a_Image.Size();

                int rectLeft    = int( a_UV.left() * a_TextureSize.width() );
                int rectTop     = int( a_UV.top() * a_TextureSize.height() );
                int rectRight   = int( rectLeft + ( a_UV.width() * a_TextureSize.width() ) );
                int rectBottom  = int( rectTop  + ( a_UV.height() * a_TextureSize.height() ) );

                // �摜�̌��ʒu
                RECT rect={ rectLeft, rectTop, rectRight, rectBottom };
                // �e�N�X�`���̐F�ݒ�
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));
            

                // �`��X�^�b�N�ɐςݍ���
                mSprite->SetTransform(&pOut);
                mSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
            
            }

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){

                // ���X�g�ςݍ��݂̗L���l���m�F & �ݒ�
                if(!mbListBegin){
                    Begin();
                }

                                // �v�Z���K�v�ɂȂ���̂͊e�������K�v�Ȃ��̂𒊏o
                // UV�l�𒊏o
                auto a_UV = a_Image.getUV();
                // �g�嗦�𒊏o
                auto a_Scale = a_Transform.scale();
                // ���W�𒊏o
                auto a_Position = a_Transform.position();
                // �e�N�X�`���𒊏o
                auto a_Texture = a_Image.Texture();


                // �e�N�X�`���̊g�嗦
                D3DXVECTOR2 scale(a_Scale.x(), a_Scale.y());
                // �𑜓x�ɂ��\��t�����̏k�ڕω��ɔ����C��
                scale.x *= a_Size.width();
                scale.y *= a_Size.height();
                scale.x /= a_UV.width();
                scale.y /= a_UV.height();

                // �؂���摜�̒��S
                D3DXVECTOR2 pivot(a_Pivot.x(), a_Pivot.y() );
                // �`��ʒu
                D3DXVECTOR2 Pos( a_Position.x() - pivot.x,  a_Position.y() - pivot.y);            
                // ��]�s����쐬
                D3DXMATRIX pOut;
                D3DXMatrixTransformation2D(&pOut, &pivot, 0, &scale, &pivot, D3DXToRadian(a_Transform.degree()), &Pos);

                // �e�N�X�`���̃T�C�Y���擾
                BaseWH<int> a_TextureSize = a_Image.Size();

                int rectLeft    = int( a_UV.left() * a_TextureSize.width() );
                int rectTop     = int( a_UV.top() * a_TextureSize.height() );
                int rectRight   = int( rectLeft + ( a_UV.width() * a_TextureSize.width() ) );
                int rectBottom  = int( rectTop  + ( a_UV.height() * a_TextureSize.height() ) );

                // �摜�̌��ʒu
                RECT rect={ rectLeft, rectTop, rectRight, rectBottom };
                // �e�N�X�`���̐F�ݒ�
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));
            

                // �`��X�^�b�N�ɐςݍ���
                mSprite->SetTransform(&pOut);
                mSprite->Draw(a_Texture.getPtr(), &rect, NULL, NULL, color);

            }


            /// @brief ���X�g�ɐς�Sprite���܂Ƃ߂ĕ`�悵�܂��B
            void DrawAll(){
                mSprite->End();
                mbListBegin = false;                                
            }




        };


    } // end of namespace Graphics
} // end of namespace GameLib
#endif