/// @file SpriteImpl.hpp
/// @brief 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - Impl
/// @note 互換性重視の描画Impl
/// @date 2012/12/28     tory

//====================================================================
//              SpriteImpl.hpp
//--------------------------------------------------------------------
//    処理内容 : 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - Impl
//    処理内容 : 
//    作成詳細 : 2012/12/28
//    補足     : 互換性重視の描画Impl
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2013/01/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_SPRITE_IMPL_H
#define INCLUDE_GAMELIB_SPRITE_IMPL_H

#include <memory>
#include <tiostream.h>          // tstring型などのTCHAR拡張定義

#include <d3d9.h>
#include <d3dx9.h>
#include "GraphicsManagerImplDirect3D.hpp"


#include <Transform2D.hpp>
#include <ImageBase.hpp>
#include <TemplateBaseClass.hpp>
#include <Color.hpp>

// StaticLibプロジェクトのプロパティからlibを呼び出す場合warningが出るため、それの代用法
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")

namespace GameLib{
    namespace Graphics{

        /// @brief  インスタンス
        extern shared_ptr< ImplDirect3D > gImplDirect3D;


        /// @class ImplSprite
        /// @brief DirectX標準のLPD3DXSPRITEを用いたスプライト表示
        class ImplSprite : public ISpriteImpl{

            //----------------------------------------------------------
            // メンバ変数
        private:
            LPD3DXSPRITE    mSprite;        ///< @brief スプライト描画クラス
            BaseXY<float>   mResolution;    ///< @brief 解像度の調整用縮尺値
    
            bool            mbListBegin;    ///< @brief リスト積み込み開始を有効にしたかどうか

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            ImplSprite(){

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
            ~ImplSprite(){}


            //----------------------------------------------------------
            // メンバ関数
        public:

            /// @brief スプライトを使用出来るように初期化します。
            void InitializeSprite(){
                auto Device = gImplDirect3D->getDevice();
                if(FAILED(D3DXCreateSprite( Device.getPtr(), &mSprite ))){
                    MessageBox(NULL,_T("スプライトの作成に失敗しました"),_T("読み込み失敗"),MB_OK);
                }
            }

            /// @brief スプライトを描画リストに積み上げることを有効にします。
            void Begin() {
                if(!mbListBegin){
                    mSprite->Begin(D3DXSPRITE_ALPHABLEND);
                    mbListBegin = true;
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

                // リスト積み込みの有効値を確認 & 設定
                if(!mbListBegin){
                    Begin();
                }

                // 計算が必要になるものは各引数より必要なものを抽出
                // UV値を抽出
                auto a_UV = a_Image.getUV();
                // 拡大率を抽出
                auto a_Scale = a_Transform.scale();
                // 座標を抽出
                auto a_Position = a_Transform.position();
                // テクスチャを抽出
                auto texture = a_Image.Texture();


                // テクスチャの拡大率
                D3DXVECTOR2 scale(a_Scale.x(), a_Scale.y());
                // 解像度による貼り付け時の縮尺変化に伴う修正
                scale.x *= mResolution.x() * a_Size.width();
                scale.y *= mResolution.y() * a_Size.height();
                scale.x /= a_UV.width();
                scale.y /= a_UV.height();

                // 切り取り画像の中心
                D3DXVECTOR2 pivot(a_Pivot.x(), a_Pivot.y() );
                // 描画位置
                D3DXVECTOR2 Pos(( a_Position.x() * scale.x ) - pivot.x, ( a_Position.y() * scale.y )- pivot.y);            
                // 回転行列を作成
                D3DXMATRIX pOut;
                D3DXMatrixTransformation2D(&pOut, &pivot, 0, &scale, &pivot, D3DXToRadian(a_Transform.degree()), &Pos);


                // テクスチャのサイズを取得
                BaseWH<int> a_TextureSize = a_Image.Size();

                int rectLeft    = int( a_UV.left() * a_TextureSize.width() );
                int rectTop     = int( a_UV.top() * a_TextureSize.height() );
                int rectRight   = int( rectLeft + ( a_UV.width() * a_TextureSize.width() ) );
                int rectBottom  = int( rectTop  + ( a_UV.height() * a_TextureSize.height() ) );

                // 画像の元位置
                RECT rect={ rectLeft, rectTop, rectRight, rectBottom };
                // テクスチャの色設定
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));
            

                // 描画スタックに積み込む
                mSprite->SetTransform(&pOut);
                mSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
            
            }

            /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){

                // リスト積み込みの有効値を確認 & 設定
                if(!mbListBegin){
                    Begin();
                }

                                // 計算が必要になるものは各引数より必要なものを抽出
                // UV値を抽出
                auto a_UV = a_Image.getUV();
                // 拡大率を抽出
                auto a_Scale = a_Transform.scale();
                // 座標を抽出
                auto a_Position = a_Transform.position();
                // テクスチャを抽出
                auto a_Texture = a_Image.Texture();


                // テクスチャの拡大率
                D3DXVECTOR2 scale(a_Scale.x(), a_Scale.y());
                // 解像度による貼り付け時の縮尺変化に伴う修正
                scale.x *= a_Size.width();
                scale.y *= a_Size.height();
                scale.x /= a_UV.width();
                scale.y /= a_UV.height();

                // 切り取り画像の中心
                D3DXVECTOR2 pivot(a_Pivot.x(), a_Pivot.y() );
                // 描画位置
                D3DXVECTOR2 Pos( a_Position.x() - pivot.x,  a_Position.y() - pivot.y);            
                // 回転行列を作成
                D3DXMATRIX pOut;
                D3DXMatrixTransformation2D(&pOut, &pivot, 0, &scale, &pivot, D3DXToRadian(a_Transform.degree()), &Pos);

                // テクスチャのサイズを取得
                BaseWH<int> a_TextureSize = a_Image.Size();

                int rectLeft    = int( a_UV.left() * a_TextureSize.width() );
                int rectTop     = int( a_UV.top() * a_TextureSize.height() );
                int rectRight   = int( rectLeft + ( a_UV.width() * a_TextureSize.width() ) );
                int rectBottom  = int( rectTop  + ( a_UV.height() * a_TextureSize.height() ) );

                // 画像の元位置
                RECT rect={ rectLeft, rectTop, rectRight, rectBottom };
                // テクスチャの色設定
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));
            

                // 描画スタックに積み込む
                mSprite->SetTransform(&pOut);
                mSprite->Draw(a_Texture.getPtr(), &rect, NULL, NULL, color);

            }


            /// @brief リストに積んだSpriteをまとめて描画します。
            void DrawAll(){
                mSprite->End();
                mbListBegin = false;                                
            }




        };


    } // end of namespace Graphics
} // end of namespace GameLib
#endif