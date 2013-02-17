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
#include "Sqare.h"

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
            Com_ptr <ID3DXSprite>   mSprite;        ///< @brief �s�����p�X�v���C�g�`��N���X
            Com_ptr <ID3DXSprite>   mAlphaSprite;   ///< @brief �������p�X�v���C�g�`��N���X
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

                // ���X�g�ςݍ��݂��ł���悤��false�ɂ��Ă���
                mbListBegin = false;

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
                if(FAILED(D3DXCreateSprite( Device.getPtr(), mSprite.ToCreator() ))){
                    MessageBox(NULL,_T("�X�v���C�g�̍쐬�Ɏ��s���܂���"),_T("�ǂݍ��ݎ��s"),MB_OK);
                }
                if(FAILED(D3DXCreateSprite( Device.getPtr(), mAlphaSprite.ToCreator() ))){
                    MessageBox(NULL,_T("�������p�X�v���C�g�̍쐬�Ɏ��s���܂���"),_T("�ǂݍ��ݎ��s"),MB_OK);
                }

            }


            /// @brief �`�惊�X�g�ւ̃X�v���C�g�ǉ����J�n���܂��B
            void Begin() {
                if(!mbListBegin){
                    auto Device = gImplDirect3D->getDevice();

                    // MicroSoft�̎����o�O��D3DXSPRITE_SORT_DEPTH_BACKTOFRONT��D3DXSPRITE_SORT_DEPTH_FRONTTOBACK��
                    // �t�̓���ɂȂ��Ă���\�������ɍ����ł��B���Ⴂ�ł͂Ȃ��̂ŔO�̂��߁B
                    mSprite->Begin(D3DXSPRITE_DONOTSAVESTATE|D3DXSPRITE_SORT_TEXTURE|D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);
                    mAlphaSprite->Begin(D3DXSPRITE_DONOTSAVESTATE|D3DXSPRITE_ALPHABLEND|D3DXSPRITE_SORT_TEXTURE|D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);

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

                // �`�惊�X�g�ւ̒ǉ��̗L�����̊m�F & �J�n
                Begin();

                // �v�Z���K�v�ɂȂ���̂͊e�������K�v�Ȃ��̂𒊏o
                // UV�l�𒊏o
                auto a_UV = a_Image.getUV();
                // �g�嗦�𒊏o
                auto a_Scale = a_Transform.scale();
                // ���W�𒊏o
                auto a_Position = a_Transform.position();
                // �e�N�X�`���𒊏o
                auto texture = a_Image.Texture();
                // �e�N�X�`���̃T�C�Y���擾
                auto a_TextureSize = a_Image.Size();

                // �v�Z�Ɏg�p����ϐ��̏�����
                D3DXMATRIX world,poly, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &poly );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );

                // �e�N�X�`�����̂�����Ƃ�
                if(texture != nullptr){
                    // �|���S���T�C�Y
                    D3DXMatrixScaling(
                    &poly, 
                    a_Size.width() / ( a_UV.width() * a_TextureSize.width() ),
                    a_Size.height() /( a_UV.height() * a_TextureSize.height()),
                    1.0f
                    );
                }else{
                    // �e�N�X�`�����̂��Ȃ��Ƃ�(boxf�̂Ƃ�)
                    D3DXMatrixScaling(
                    &poly, 
                    a_Size.width(),
                    a_Size.height(),
                    1.0f
                    );
                }

                // ���[�J���X�P�[��
                D3DXMatrixScaling( &scale, a_Transform.scale().x() * mResolution.x(), a_Transform.scale().y() * mResolution.y(), 1.0f );                
                // ��]
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // �s�{�b�g���I�t�Z�b�g
                world._41 -= ( a_Pivot.x());
                world._42 -= ( a_Pivot.y());

                // �g�����X�t�H�[�����v�Z����
                world = poly * world * scale * rot;
                // ���W���ړ�����
                world._41 += ( a_Transform.position().x()  ) * mResolution.x();
                world._42 += ( a_Transform.position().y()  ) * mResolution.y();
                world._43 += ( a_Transform.position().z()  );


                // �؂�o���摜�T�C�Y���v�Z
                RECT rect ={ 0, 0, 1, 1};
                if(texture != nullptr){
                    rect.left    = int( a_UV.left() * a_TextureSize.width() );
                    rect.top     = int( a_UV.top() * a_TextureSize.height() );
                    rect.right   = int( rect.left + ( a_UV.width() * a_TextureSize.width() ) );
                    rect.bottom  = int( rect.top  + ( a_UV.height() * a_TextureSize.height() ) );
                }

                // �e�N�X�`���̐F�ݒ�
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));

                // �e�N�X�`�������݂��Ȃ��ꍇ
                if(texture == nullptr){
                    // �F��`���Z�b�g                    
                    Sqare sqare;
                    texture = sqare.texture();
                }else if( a_Image.isTextureAlpha() ){
                    // ������List�ɒǉ�����
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                if( a_Color.a() < 255 ){
                    // ������List�ɒǉ�����
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                // �s����List�ɒǉ�����
                mSprite->SetTransform(&world);
                mSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);

            }

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){

                // �`�惊�X�g�ւ̒ǉ��̗L�����̊m�F & �J�n
                Begin();

                // �v�Z���K�v�ɂȂ���̂͊e�������K�v�Ȃ��̂𒊏o
                // UV�l�𒊏o
                auto a_UV = a_Image.getUV();
                // �g�嗦�𒊏o
                auto a_Scale = a_Transform.scale();
                // ���W�𒊏o
                auto a_Position = a_Transform.position();
                // �e�N�X�`���𒊏o
                auto texture = a_Image.Texture();
                // �e�N�X�`���̃T�C�Y���擾
                auto a_TextureSize = a_Image.Size();

                // �v�Z�Ɏg�p����ϐ��̏�����
                D3DXMATRIX world,poly, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &poly );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );

                // �e�N�X�`�����̂�����Ƃ�
                if(texture != nullptr){
                    // �|���S���T�C�Y
                    D3DXMatrixScaling(
                        &poly, 
                        a_Size.width() / ( a_UV.width() * a_TextureSize.width() ),
                        a_Size.height() /( a_UV.height() * a_TextureSize.height()),
                        1.0f
                        );
                }else{
                    // �e�N�X�`�����̂��Ȃ��Ƃ�(boxf�̂Ƃ�)
                    D3DXMatrixScaling(
                        &poly, 
                        a_Size.width(),
                        a_Size.height(),
                        1.0f
                        );
                }

                // ���[�J���X�P�[��
                D3DXMatrixScaling( &scale, a_Transform.scale().x(), a_Transform.scale().y(), 1.0f );                
                // ��]
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // �s�{�b�g���I�t�Z�b�g
                world._41 -= ( a_Pivot.x());
                world._42 -= ( a_Pivot.y());

                // �g�����X�t�H�[�����v�Z����
                world = poly * world * scale * rot;
                // ���W���ړ�����
                world._41 += a_Transform.position().x();
                world._42 += a_Transform.position().y();
                world._43 += a_Transform.position().z();

                // �؂�o���摜�T�C�Y���v�Z
                RECT rect ={ 0, 0, 1, 1};
                if(texture != nullptr){
                    rect.left    = int( a_UV.left() * a_TextureSize.width() );
                    rect.top     = int( a_UV.top() * a_TextureSize.height() );
                    rect.right   = int( rect.left + ( a_UV.width() * a_TextureSize.width() ) );
                    rect.bottom  = int( rect.top  + ( a_UV.height() * a_TextureSize.height() ) );
                }

                // �e�N�X�`���̐F�ݒ�
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));

                // �e�N�X�`�������݂��Ȃ��ꍇ
                if(texture == nullptr){
                    // �F��`���Z�b�g                    
                    Sqare sqare;
                    texture = sqare.texture();
                }else if( a_Image.isTextureAlpha() ){
                    // ������List�ɒǉ�����
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                if( a_Color.a() < 255 ){
                    // ������List�ɒǉ�����
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                // �s����List�ɒǉ�����
                mSprite->SetTransform(&world);
                mSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);

            }


            /// @brief ���X�g�ɐς�Sprite���܂Ƃ߂ĕ`�悵�܂��B
            void DrawAll(){

                auto Device = gImplDirect3D->getDevice();
                // device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_MIRROR);
                // device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_MIRROR); 
                Device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
                Device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

                Device->SetRenderState(D3DRS_LIGHTING, false);              // ���C�g�v�Z��؂�

                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);       // �A���t�@�u�����f�B���O�̗L����
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);         // ����������s
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);           // Z�o�b�t�@�ɏ������݂��s��
                Device->SetRenderState( D3DRS_ZENABLE,false);               // Z�o�b�t�@����͍s��
                mSprite->End();
                
                Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);      // SRC�̐ݒ�
                Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // DEST�̐ݒ�
                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);            // �A���t�@�u�����f�B���O�̗L����
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);             // ����������s
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);               // Z�o�b�t�@�ɏ������݂��s��
                Device->SetRenderState( D3DRS_ZENABLE,false);                   // Z�o�b�t�@����͍s��Ȃ�
                mAlphaSprite->End();
                
                mbListBegin = false;                                
            }




        };


    } // end of namespace Graphics
} // end of namespace GameLib
#endif