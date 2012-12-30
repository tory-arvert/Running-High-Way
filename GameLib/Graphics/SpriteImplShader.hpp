/// @file SpriteImplShader.hpp
/// @brief 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - Impl
/// @note 速度重視のshader描画Impl
/// @date 2012/12/28     tory

//====================================================================
//              SpriteImplShader.hpp
//--------------------------------------------------------------------
//    処理内容 : 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - Impl
//    処理内容 : 
//    作成詳細 : 2012/12/28
//    補足     : 速度重視のshader描画Impl
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2013/01/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_SPRITE_SHADER_IMPL_H
#define INCLUDE_GAMELIB_SPRITE_SHADER_IMPL_H

#include <memory>
#include <Comptr.hpp>
#include <tiostream.h>          // tstring型などのTCHAR拡張定義

#include <d3d9.h>
#include <d3dx9.h>
#include "GraphicsManagerImplDirect3D.hpp"

#include "Sprite.h"
#include <list>
#include <Transform2D.h>
#include <ImageBase.h>
#include <TemplateBaseClass.h>
#include <Color.h>


// StaticLibプロジェクトのプロパティからlibを呼び出す場合warningが出るため、それの代用法
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")


// 無名ネームスペース定義
namespace{
    

    
} // end of namespace


namespace GameLib{
    namespace Graphics{

        /// @brief  インスタンス
        extern shared_ptr< ImplDirect3D > gImplDirect3D;


        /// @class SpriteListState
        /// @brief スプライト描画用のステータスリスト
        class SpriteListState{

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            SpriteListState(){
            
                // 2D描画への射影変換行列
                D3DXMatrixIdentity( &mProj );
                mProj._41 = -1.0f;
                mProj._42 = 1.0f;
            
                int clientWidth,clientHeight =0;
                gImplDirect3D->getClientSize(&clientWidth, &clientHeight);
                mProj._11 = 2.0f / clientWidth;
                mProj._22 =-2.0f / clientHeight;

            }

            /// @brief デストラクタ
            ~SpriteListState(){}

            //----------------------------------------------------------
            // メンバ変数
        public:
            
            D3DXMATRIX mProj;       ///< @brief 2D用射影変換Matrix
            D3DXMATRIX mWorld;      ///< @brief ワールド変換行列
            ImageBase  m_Image;     ///< @brief UVやテクスチャ
            Color4<float> mColor;   ///< @brief 色
            //----------------------------------------------------------
        public:
            /// @brief 描画に必要なステータスを保持します。
            void set(const D3DXMATRIX& a_World, const ImageBase& a_Image, const Color4<float> a_Color){
                mWorld = a_World;
                m_Image = a_Image;
                mColor = a_Color;
            }

        };


        /// @class ImplSpriteShader
        /// @brief DirectX標準のLPD3DXSPRITEを用いたスプライト表示
        class ImplSpriteShader : public ISpriteImpl{

            //----------------------------------------------------------
            // メンバ変数
        private:
            /// @brief  スプライトの描画ステータスのリスト
            std::list <SpriteListState*> mDrawList;


            Com_ptr <IDirect3DVertexBuffer9 > mBuffer;
            Com_ptr <IDirect3DVertexDeclaration9> mDecl;
            Com_ptr <ID3DXEffect> mEffect;


            BaseXY<float>   mResolution;    ///< @brief 解像度の調整用縮尺値
    
            bool            mbListBegin;    ///< @brief リスト積み込み開始を有効にしたかどうか

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            ImplSpriteShader(){

                InitializeSprite();
                int c_x, c_y = 0;
                int c2d_x, c2d_y =0;
                gImplDirect3D->getClientSize(&c_x, &c_y);
                gImplDirect3D->get2DClientSize(&c2d_x, &c2d_y);

                // 表示クライアントサイズ÷2D用描画領域サイズ
                mResolution.setX( float(c_x) / float(c2d_x) );
                mResolution.setY( float(c_y) / float(c2d_y) );

            }

            /// @brief デストラクタ
            ~ImplSpriteShader(){}


            //----------------------------------------------------------
            // メンバ関数
        public:

            /// @brief スプライトを使用出来るように初期化します。
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

                // シェーダ作成
                if (mEffect == 0) {
                    ID3DXBuffer *error = 0;
                    if ( FAILED( D3DXCreateEffectFromFile( Device.getPtr(), "shader/sprite.fx", 0, 0, 0, 0, mEffect.ToCreator(), &error) ) ) {
                        OutputDebugString( (const char*)error->GetBufferPointer());
                        return;
                    }
                }

                // 頂点宣言作成
                if (mDecl == 0) {
                    D3DVERTEXELEMENT9 elems[] = {
                        // 頂点座標情報の宣言(Stream,Offset,Type,Method,Usage,UsageIndex)
                        {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
                        // テクスチャUV座標情報の宣言(Stream,Offset,Type,Method,Usage,UsageIndex)
                        {0, sizeof(float) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
                        // 終端宣言
                        D3DDECL_END()
                    };
                    Device->CreateVertexDeclaration( elems, mDecl.ToCreator() );
                }

            }


            /// @brief 描画を行います。2D用基準領域サイズ用へと自動補正されます。
            /// @attention 描画の仕方によって計算に使う変数が複雑になるため事前に計算しておくことが困難。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            /// @todo Matrixの計算式を新しいものに修正すること
            void Draw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color) {

                // 2D描画への射影変換行列
                SpriteListState spriteState;

                D3DXMATRIX world, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );
                // ポリゴンサイズ
                D3DXMatrixScaling( &world, a_Size.width(), a_Size.height(), 1.0f );	
                // ローカルスケール
                D3DXMatrixScaling( &scale, a_Transform.scale().x(), a_Transform.scale().y(), 1.0f );
                // 回転
                D3DXMatrixRotationZ( &rot, a_Transform.degree() );
                // ピボット分オフセット
                world._41 = -a_Pivot.x();
                world._42 = -a_Pivot.y();
                world = world * scale * rot;
                world._41 += a_Transform.position().x() + a_Pivot.x();	// ピボット分オフセット
                world._42 += a_Transform.position().y() + a_Pivot.y();

                // データをListに保持させる。
                spriteState.set(world, a_Image, a_Color);

            }

            /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){




            }


            /// @brief リストに積んだSpriteをまとめて描画します。
            void DrawAll(){
                if(mBuffer == nullptr || mEffect == nullptr || mDecl == nullptr ){
                    return; // 描画しない
                }

                // 頂点バッファ・頂点宣言設定
                auto Device = gImplDirect3D->getDevice();
                Device->SetStreamSource( 0, mBuffer.getPtr(), 0, sizeof(float) * 5);
                Device->SetVertexDeclaration( mDecl.getPtr() );


                // シェーダ開始
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