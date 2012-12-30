/// @file SpriteImplShader.hpp
/// @brief ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - Impl
/// @note ���x�d����shader�`��Impl
/// @date 2012/12/28     tory

//====================================================================
//              SpriteImplShader.hpp
//--------------------------------------------------------------------
//    �������e : ��ʏ��2D�e�N�X�`��(�܂��͐F�t����`)��`�悷��N���X - Impl
//    �������e : 
//    �쐬�ڍ� : 2012/12/28
//    �⑫     : ���x�d����shader�`��Impl
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2013/01/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_SPRITE_SHADER_IMPL_H
#define INCLUDE_GAMELIB_SPRITE_SHADER_IMPL_H

#include <memory>
#include <Comptr.hpp>
#include <tiostream.h>          // tstring�^�Ȃǂ�TCHAR�g����`

#include <d3d9.h>
#include <d3dx9.h>
#include "GraphicsManagerImplDirect3D.hpp"

#include "Sprite.h"
#include <list>
#include <Transform2D.h>
#include <ImageBase.h>
#include <TemplateBaseClass.h>
#include <Color.h>


// StaticLib�v���W�F�N�g�̃v���p�e�B����lib���Ăяo���ꍇwarning���o�邽�߁A����̑�p�@
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")


// �����l�[���X�y�[�X��`
namespace{
    

    
} // end of namespace


namespace GameLib{
    namespace Graphics{

        /// @brief  �C���X�^���X
        extern shared_ptr< ImplDirect3D > gImplDirect3D;


        /// @class SpriteListState
        /// @brief �X�v���C�g�`��p�̃X�e�[�^�X���X�g
        class SpriteListState{

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            SpriteListState(){
            
                // 2D�`��ւ̎ˉe�ϊ��s��
                D3DXMatrixIdentity( &mProj );
                mProj._41 = -1.0f;
                mProj._42 = 1.0f;
            
                int clientWidth,clientHeight =0;
                gImplDirect3D->getClientSize(&clientWidth, &clientHeight);
                mProj._11 = 2.0f / clientWidth;
                mProj._22 =-2.0f / clientHeight;

            }

            /// @brief �f�X�g���N�^
            ~SpriteListState(){}

            //----------------------------------------------------------
            // �����o�ϐ�
        public:
            
            D3DXMATRIX mProj;       ///< @brief 2D�p�ˉe�ϊ�Matrix
            D3DXMATRIX mWorld;      ///< @brief ���[���h�ϊ��s��
            ImageBase  m_Image;     ///< @brief UV��e�N�X�`��
            Color4<float> mColor;   ///< @brief �F
            //----------------------------------------------------------
        public:
            /// @brief �`��ɕK�v�ȃX�e�[�^�X��ێ����܂��B
            void set(const D3DXMATRIX& a_World, const ImageBase& a_Image, const Color4<float> a_Color){
                mWorld = a_World;
                m_Image = a_Image;
                mColor = a_Color;
            }

        };


        /// @class ImplSpriteShader
        /// @brief DirectX�W����LPD3DXSPRITE��p�����X�v���C�g�\��
        class ImplSpriteShader : public ISpriteImpl{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            /// @brief  �X�v���C�g�̕`��X�e�[�^�X�̃��X�g
            std::list <SpriteListState*> mDrawList;


            Com_ptr <IDirect3DVertexBuffer9 > mBuffer;
            Com_ptr <IDirect3DVertexDeclaration9> mDecl;
            Com_ptr <ID3DXEffect> mEffect;


            BaseXY<float>   mResolution;    ///< @brief �𑜓x�̒����p�k�ڒl
    
            bool            mbListBegin;    ///< @brief ���X�g�ςݍ��݊J�n��L���ɂ������ǂ���

            //----------------------------------------------------------
            // ���ꃁ���o�֐�
        public:

            /// @brief �R���X�g���N�^
            ImplSpriteShader(){

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
            ~ImplSpriteShader(){}


            //----------------------------------------------------------
            // �����o�֐�
        public:

            /// @brief �X�v���C�g���g�p�o����悤�ɏ��������܂��B
            void InitializeSprite(){
                auto Device = gImplDirect3D->getDevice();

                if(mBuffer == nullptr){
                    float commonVtx[] = {
                        0.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // 0
                        1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // 1
                        0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // 2
                        1.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // 3
                    };

                    Device->CreateVertexBuffer( sizeof(commonVtx), 0, 0, D3DPOOL_MANAGED, mBuffer.ToCreator(), 0 );
                    float *p = 0;
                    
                    if (mBuffer != nullptr){

                        mBuffer->Lock( 0, 0, (void**)&p, 0 );
                        memcpy( p, commonVtx, sizeof(commonVtx) );
                        mBuffer->Unlock();
                    }
                }

                // �V�F�[�_�쐬
                if (mEffect == 0) {
                    ID3DXBuffer *error = 0;
                    if ( FAILED( D3DXCreateEffectFromFile( Device.getPtr(), "shader/sprite.fx", 0, 0, 0, 0, mEffect.ToCreator(), &error) ) ) {
                        OutputDebugString( (const char*)error->GetBufferPointer());
                        return;
                    }
                }

                // ���_�錾�쐬
                if (mDecl == 0) {
                    D3DVERTEXELEMENT9 elems[] = {
                        // ���_���W���̐錾(Stream,Offset,Type,Method,Usage,UsageIndex)
                        {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
                        // �e�N�X�`��UV���W���̐錾(Stream,Offset,Type,Method,Usage,UsageIndex)
                        {0, sizeof(float) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
                        // �I�[�錾
                        D3DDECL_END()
                    };
                    Device->CreateVertexDeclaration( elems, mDecl.ToCreator() );
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

                // 2D�`��ւ̎ˉe�ϊ��s��
                SpriteListState spriteState;

                D3DXMATRIX world, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );
                // �|���S���T�C�Y
                D3DXMatrixScaling( &world, a_Size.width(), a_Size.height(), 1.0f );	
                // ���[�J���X�P�[��
                D3DXMatrixScaling( &scale, a_Transform.scale().x(), a_Transform.scale().y(), 1.0f );
                // ��]
                D3DXMatrixRotationZ( &rot, a_Transform.degree() );
                // �s�{�b�g���I�t�Z�b�g
                world._41 = -a_Pivot.x();
                world._42 = -a_Pivot.y();
                world = world * scale * rot;
                world._41 += a_Transform.position().x() + a_Pivot.x();	// �s�{�b�g���I�t�Z�b�g
                world._42 += a_Transform.position().y() + a_Pivot.y();

                // �f�[�^��List�ɕێ�������B
                spriteState.set(world, a_Image, a_Color);

            }

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){




            }


            /// @brief ���X�g�ɐς�Sprite���܂Ƃ߂ĕ`�悵�܂��B
            void DrawAll(){
                if(mBuffer == nullptr || mEffect == nullptr || mDecl == nullptr ){
                    return; // �`�悵�Ȃ�
                }

                // ���_�o�b�t�@�E���_�錾�ݒ�
                auto Device = gImplDirect3D->getDevice();
                Device->SetStreamSource( 0, mBuffer.getPtr(), 0, sizeof(float) * 5);
                Device->SetVertexDeclaration( mDecl.getPtr() );


                // �V�F�[�_�J�n
                UINT numPass = 0;
                mEffect->SetTechnique( "Tech" );
                mEffect->Begin(&numPass, 0);
                mEffect->BeginPass(0);




                mEffect->EndPass();
                mEffect->End();

            }




        };




    } // end of namespace Graphics
} // end of namespace GameLib
#endif