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
#include "Sqare.h"

#include <list>
#include <algorithm>
#include <functional>

#include <Transform2D.hpp>
#include <ImageBase.hpp>
#include <TemplateBaseClass.hpp>
#include <Color.hpp>


// StaticLib�v���W�F�N�g�̃v���p�e�B����lib���Ăяo���ꍇwarning���o�邽�߁A����̑�p�@
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")

using namespace std;

namespace GameLib{
    namespace Graphics{

        /// @brief  �C���X�^���X
        extern shared_ptr< ImplDirect3D > gImplDirect3D;


        /// @class SpriteListState
        /// @brief �X�v���C�g�`��p�̃X�e�[�^�X���X�g
        class SpriteListState{

            //----------------------------------------------------------
            // �ʖ��錾
            typedef Com_ptr< IDirect3DTexture9 > Texture_sp;

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
        private:
            
            D3DXMATRIX mProj;       ///< @brief 2D�p�ˉe�ϊ�Matrix
            D3DXMATRIX mWorld;      ///< @brief ���[���h�ϊ��s��
            Texture_sp mTexture;    ///< @brief �e�N�X�`��
            BaseUV<float> mUV;      ///< @brief UV
            Color4<float> mColor;   ///< @brief �F
            //----------------------------------------------------------
        public:
            /// @brief �`��ɕK�v�ȃX�e�[�^�X��ێ����܂��B
            void set(const D3DXMATRIX& a_World, const Texture_sp& a_Texture, const BaseUV<float>& a_UV, const Color4<float>& a_Color){
                mWorld = a_World;
                mTexture = a_Texture;
                mUV = a_UV;
                mColor = a_Color;
            }

            /// @brief 2D�p�ˉe�ϊ��s���Ԃ��܂��B
            const D3DXMATRIX* proj() const{
                return &mProj;
            }

            /// @brief ���[���h�ϊ��s���Ԃ��܂��B
            const D3DXMATRIX* world() const{
                return &mWorld;
            }

            /// @brief UV��e�N�X�`���̒l��Ԃ��܂��B
            Texture_sp texture() const{
                return mTexture;
            }

            /// @brief UV�̒l��Ԃ��܂��B
            BaseUV<float> UV() const{
                return mUV;
            }

            /// @brief �F�ƃ��l��Ԃ��܂��B
            Color4<float> Color() const{
                return mColor;
            }

            const float z() const{
                return mWorld._43;
            }

        };


        /// @class ImplSpriteShader
        /// @brief DirectX�W����LPD3DXSPRITE��p�����X�v���C�g�\��
        class ImplSpriteShader : public ISpriteImpl{

            
            //----------------------------------------------------------
            // �ʖ��錾
            typedef shared_ptr<SpriteListState> SpriteListState_sp;

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            /// @brief  �s�����X�v���C�g�̕`��X�e�[�^�X�̃X�}�[�g�|�C���^���X�g
            list <SpriteListState_sp> mDrawList;
            /// @brief  �������X�v���C�g�̕`��X�e�[�^�X�̃X�}�[�g�|�C���^���X�g
            list <SpriteListState_sp> mAlphaDrawList;


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
                if (mEffect == nullptr) {
                    ID3DXBuffer *error = 0;
                    if ( FAILED( D3DXCreateEffectFromFile( Device.getPtr(), "../shader/sprite.fx", 0, 0, 0, 0, mEffect.ToCreator(), &error) ) ) {
                        OutputDebugString( (const char*)error->GetBufferPointer());
                        return;
                    }
                }

                // ���_�錾�쐬
                if (mDecl == nullptr) {
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
                SpriteListState_sp spriteState;
                spriteState.reset( new SpriteListState());

                // �v�Z���K�v�ɂȂ���̂͊e�������K�v�Ȃ��̂𒊏o
                // �g�嗦�𒊏o
                auto a_Scale = a_Transform.scale();
                // ���W�𒊏o
                auto a_Position = a_Transform.position();

                D3DXMATRIX world, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );
                // �|���S���T�C�Y
                D3DXMatrixScaling( &world, a_Size.width(), a_Size.height(), 1.0f );	
                // ���[�J���X�P�[��
                D3DXMatrixScaling( &scale, a_Scale.x() * mResolution.x(), a_Scale.y() * mResolution.y(), 1.0f );
                // ��]
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // �s�{�b�g���I�t�Z�b�g
                world._41 = -a_Pivot.x();
                world._42 = -a_Pivot.y();

                // �g�����X�t�H�[�����v�Z����
                world = world * scale * rot;
                // ���W���ړ�����
                world._41 += ( a_Position.x() * mResolution.x() );
                world._42 += ( a_Position.y() * mResolution.y() );
                world._43 += ( a_Transform.position().z()  );

                auto a_Texture = a_Image.Texture();
                auto a_UV = a_Image.getUV();

                // �e�N�X�`�������݂��Ȃ��ꍇ
                if(a_Texture == nullptr){
                    // �F��`���Z�b�g
                    Sqare sqare;
                    a_Texture = sqare.texture();
                    a_UV.setUV(0,0,1,1);
                }else if( a_Image.isTextureAlpha() ){
                    // �`��ɕK�v�ȃf�[�^�Z�b�g���܂Ƃ߂�
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // ������List�ɒǉ�����
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // ���������w�肳��Ă���Ƃ�
                if( a_Color.a() < 255){
                    // �`��ɕK�v�ȃf�[�^�Z�b�g���܂Ƃ߂�
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // ������List�ɒǉ�����
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // �`��ɕK�v�ȃf�[�^�Z�b�g���܂Ƃ߂�
                spriteState->set(world, a_Texture, a_UV, a_Color);   
                // �s����List�ɒǉ�����
                mDrawList.push_back( spriteState );
            }

            /// @brief �X�N���[���T�C�Y�̏k�ڕ␳�Ɋ֌W�Ȃ��w�肳�ꂽ�T�C�Y�ŕ`�悵�܂��B
            /// @param a_Transform ���W�E�g��E��]�p
            /// @param a_Image �e�N�X�`���֘A
            /// @param a_Pivot �g��E��]���̊�_
            /// @param a_Size �g�嗦��1�̎��̉�ʂւ̓\��t���T�C�Y
            /// @param a_Color �`�掞�Ɏg�p����F�⃿�l
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){

                // 2D�`��ւ̎ˉe�ϊ��s��
                SpriteListState_sp spriteState;
                spriteState.reset( new SpriteListState());

                // �v�Z���K�v�ɂȂ���̂͊e�������K�v�Ȃ��̂𒊏o
                // �g�嗦�𒊏o
                auto a_Scale = a_Transform.scale();
                // ���W�𒊏o
                auto a_Position = a_Transform.position();

                D3DXMATRIX world, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );
                // �|���S���T�C�Y
                D3DXMatrixScaling( &world, a_Size.width(), a_Size.height(), 1.0f );	
                // ���[�J���X�P�[��
                D3DXMatrixScaling( &scale, a_Scale.x(), a_Scale.y(), 1.0f );
                // ��]
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // �s�{�b�g���I�t�Z�b�g
                world._41 = -a_Pivot.x();
                world._42 = -a_Pivot.y();
                world = world * scale * rot;
                world._41 += a_Position.x();
                world._42 += a_Position.y();
                world._43 += a_Transform.position().z();

                auto a_Texture = a_Image.Texture();
                auto a_UV = a_Image.getUV();

                // �e�N�X�`�������݂��Ȃ��ꍇ
                if(a_Texture == nullptr){
                    // �F��`���Z�b�g
                    Sqare sqare;
                    a_Texture = sqare.texture();
                    a_UV.setUV(0,0,1.0,1.0);
                }else if( a_Image.isTextureAlpha() ){
                    // �`��ɕK�v�ȃf�[�^�Z�b�g���܂Ƃ߂�
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // ������List�ɒǉ�����
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // ���������w�肳��Ă���Ƃ�
                if( a_Color.a() < 255){
                    // �`��ɕK�v�ȃf�[�^�Z�b�g���܂Ƃ߂�
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // ������List�ɒǉ�����
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // �`��ɕK�v�ȃf�[�^�Z�b�g���܂Ƃ߂�
                spriteState->set(world, a_Texture, a_UV, a_Color);   
                // �s����List�ɒǉ�����
                mDrawList.push_back( spriteState );
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

                // �`��O�ɊeList���\�[�g���܂��B
                SortList();

                // �V�F�[�_�J�n
                UINT numPass = 0;
                mEffect->SetTechnique( "Tech" );
                mEffect->Begin(&numPass, 0);
                mEffect->BeginPass(0);

                Device->SetRenderState(D3DRS_LIGHTING, false);              // ���C�g�v�Z��؂�

                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);       // �A���t�@�u�����f�B���O�̗L����
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);         // ����������s
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);           // Z�o�b�t�@�ɏ������݂��s��
                Device->SetRenderState( D3DRS_ZENABLE,false);               // Z�o�b�t�@����͍s��
                DrawSpriteList(mDrawList);
                
                Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);      // SRC�̐ݒ�
                Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // DEST�̐ݒ�
                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);            // �A���t�@�u�����f�B���O�̗L����
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);             // ����������s
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);               // Z�o�b�t�@�ɏ������݂��s��
                Device->SetRenderState( D3DRS_ZENABLE,false);                   // Z�o�b�t�@����͍s��Ȃ�
                DrawSpriteList(mAlphaDrawList);



                // �`�惊�X�g���N���A����B
                mAlphaDrawList.clear();

                
                mEffect->EndPass();
                mEffect->End();



            }


            /// @brief �w�肵�����X�g�ɐς�Sprite���܂Ƃ߂ĕ`�悵�܂��B
            void DrawSpriteList(list <SpriteListState_sp>& a_List){

                auto Device = gImplDirect3D->getDevice();

                list <SpriteListState_sp>::iterator it = a_List.begin();
                for(; it != a_List.end(); it++){
                    auto p = it->get();
                    auto a_UV = p->UV();
                    auto a_Color = p->Color();
                    D3DXCOLOR color( p->Color().r(), p->Color().g(), p->Color().b(), p->Color().a());
                    // �F���𐳋K��
                    color*= 0.00392156862;
                    mEffect->SetMatrix( "world", p->world() );
                    mEffect->SetMatrix( "proj", p->proj() );
                    mEffect->SetTexture( "tex", p->texture().getPtr() );
                    mEffect->SetFloat( "uv_left"    , a_UV.left() );
                    mEffect->SetFloat( "uv_top"     , a_UV.top() );
                    mEffect->SetFloat( "uv_width"   , a_UV.width() );
                    mEffect->SetFloat( "uv_height"  , a_UV.height() );
                    mEffect->SetValue( "color", (void*)(float *)&color, sizeof(D3DXCOLOR) );
                    mEffect->CommitChanges();
                    Device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
                }
                // �`�惊�X�g���N���A����B
                a_List.clear();

            }

            /// @brief ���ꂼ��̃��X�g��K�������ԂɃ\�[�g���܂��B
            void SortList(){
                mDrawList.sort(&SortDraw);
                mAlphaDrawList.sort(&SortAlphaDraw);
            }

            /// @brief �s����Sprite�̃\�[�g������ۂ̏���
            /// @param a_Left �����|�C���^�v�f
            /// @param a_Right �E���|�C���^�v�f
            /// @return bool ����ւ��邩�ۂ�
            static bool SortDraw(const SpriteListState_sp a_Left, const SpriteListState_sp a_Right){
                return ((a_Left)->z() < (a_Right)->z() );
            }


            /// @brief ������Sprite�̃\�[�g������ۂ̏���
            /// @param a_Left �����|�C���^�v�f
            /// @param a_Right �E���|�C���^�v�f
            /// @return bool ����ւ��邩�ۂ�
            static bool SortAlphaDraw(const SpriteListState_sp a_Left, const SpriteListState_sp a_Right){
                return ((a_Left)->z() > (a_Right)->z() );
            }


        };




    } // end of namespace Graphics
} // end of namespace GameLib
#endif