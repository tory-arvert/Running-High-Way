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
#include "Sqare.h"

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
            Com_ptr <ID3DXSprite>   mSprite;        ///< @brief 不透明用スプライト描画クラス
            Com_ptr <ID3DXSprite>   mAlphaSprite;   ///< @brief 半透明用スプライト描画クラス
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

                // リスト積み込みができるようにfalseにしておく
                mbListBegin = false;

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
                if(FAILED(D3DXCreateSprite( Device.getPtr(), mSprite.ToCreator() ))){
                    MessageBox(NULL,_T("スプライトの作成に失敗しました"),_T("読み込み失敗"),MB_OK);
                }
                if(FAILED(D3DXCreateSprite( Device.getPtr(), mAlphaSprite.ToCreator() ))){
                    MessageBox(NULL,_T("半透明用スプライトの作成に失敗しました"),_T("読み込み失敗"),MB_OK);
                }

            }


            /// @brief 描画リストへのスプライト追加を開始します。
            void Begin() {
                if(!mbListBegin){
                    auto Device = gImplDirect3D->getDevice();

                    // MicroSoftの実装バグでD3DXSPRITE_SORT_DEPTH_BACKTOFRONTとD3DXSPRITE_SORT_DEPTH_FRONTTOBACKが
                    // 逆の動作になっている可能性が非常に高いです。勘違いではないので念のため。
                    mSprite->Begin(D3DXSPRITE_DONOTSAVESTATE|D3DXSPRITE_SORT_TEXTURE|D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);
                    mAlphaSprite->Begin(D3DXSPRITE_DONOTSAVESTATE|D3DXSPRITE_ALPHABLEND|D3DXSPRITE_SORT_TEXTURE|D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);

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

                // 描画リストへの追加の有効性の確認 & 開始
                Begin();

                // 計算が必要になるものは各引数より必要なものを抽出
                // UV値を抽出
                auto a_UV = a_Image.getUV();
                // 拡大率を抽出
                auto a_Scale = a_Transform.scale();
                // 座標を抽出
                auto a_Position = a_Transform.position();
                // テクスチャを抽出
                auto texture = a_Image.Texture();
                // テクスチャのサイズを取得
                auto a_TextureSize = a_Image.Size();

                // 計算に使用する変数の初期化
                D3DXMATRIX world,poly, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &poly );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );

                // テクスチャ実体があるとき
                if(texture != nullptr){
                    // ポリゴンサイズ
                    D3DXMatrixScaling(
                    &poly, 
                    a_Size.width() / ( a_UV.width() * a_TextureSize.width() ),
                    a_Size.height() /( a_UV.height() * a_TextureSize.height()),
                    1.0f
                    );
                }else{
                    // テクスチャ実体がないとき(boxfのとき)
                    D3DXMatrixScaling(
                    &poly, 
                    a_Size.width(),
                    a_Size.height(),
                    1.0f
                    );
                }

                // ローカルスケール
                D3DXMatrixScaling( &scale, a_Transform.scale().x() * mResolution.x(), a_Transform.scale().y() * mResolution.y(), 1.0f );                
                // 回転
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // ピボット分オフセット
                world._41 -= ( a_Pivot.x());
                world._42 -= ( a_Pivot.y());

                // トランスフォームを計算する
                world = poly * world * scale * rot;
                // 座標を移動する
                world._41 += ( a_Transform.position().x()  ) * mResolution.x();
                world._42 += ( a_Transform.position().y()  ) * mResolution.y();
                world._43 += ( a_Transform.position().z()  );


                // 切り出す画像サイズを計算
                RECT rect ={ 0, 0, 1, 1};
                if(texture != nullptr){
                    rect.left    = int( a_UV.left() * a_TextureSize.width() );
                    rect.top     = int( a_UV.top() * a_TextureSize.height() );
                    rect.right   = int( rect.left + ( a_UV.width() * a_TextureSize.width() ) );
                    rect.bottom  = int( rect.top  + ( a_UV.height() * a_TextureSize.height() ) );
                }

                // テクスチャの色設定
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));

                // テクスチャが存在しない場合
                if(texture == nullptr){
                    // 色矩形をセット                    
                    Sqare sqare;
                    texture = sqare.texture();
                }else if( a_Image.isTextureAlpha() ){
                    // 半透明Listに追加する
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                if( a_Color.a() < 255 ){
                    // 半透明Listに追加する
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                // 不透明Listに追加する
                mSprite->SetTransform(&world);
                mSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);

            }

            /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){

                // 描画リストへの追加の有効性の確認 & 開始
                Begin();

                // 計算が必要になるものは各引数より必要なものを抽出
                // UV値を抽出
                auto a_UV = a_Image.getUV();
                // 拡大率を抽出
                auto a_Scale = a_Transform.scale();
                // 座標を抽出
                auto a_Position = a_Transform.position();
                // テクスチャを抽出
                auto texture = a_Image.Texture();
                // テクスチャのサイズを取得
                auto a_TextureSize = a_Image.Size();

                // 計算に使用する変数の初期化
                D3DXMATRIX world,poly, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &poly );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );

                // テクスチャ実体があるとき
                if(texture != nullptr){
                    // ポリゴンサイズ
                    D3DXMatrixScaling(
                        &poly, 
                        a_Size.width() / ( a_UV.width() * a_TextureSize.width() ),
                        a_Size.height() /( a_UV.height() * a_TextureSize.height()),
                        1.0f
                        );
                }else{
                    // テクスチャ実体がないとき(boxfのとき)
                    D3DXMatrixScaling(
                        &poly, 
                        a_Size.width(),
                        a_Size.height(),
                        1.0f
                        );
                }

                // ローカルスケール
                D3DXMatrixScaling( &scale, a_Transform.scale().x(), a_Transform.scale().y(), 1.0f );                
                // 回転
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // ピボット分オフセット
                world._41 -= ( a_Pivot.x());
                world._42 -= ( a_Pivot.y());

                // トランスフォームを計算する
                world = poly * world * scale * rot;
                // 座標を移動する
                world._41 += a_Transform.position().x();
                world._42 += a_Transform.position().y();
                world._43 += a_Transform.position().z();

                // 切り出す画像サイズを計算
                RECT rect ={ 0, 0, 1, 1};
                if(texture != nullptr){
                    rect.left    = int( a_UV.left() * a_TextureSize.width() );
                    rect.top     = int( a_UV.top() * a_TextureSize.height() );
                    rect.right   = int( rect.left + ( a_UV.width() * a_TextureSize.width() ) );
                    rect.bottom  = int( rect.top  + ( a_UV.height() * a_TextureSize.height() ) );
                }

                // テクスチャの色設定
                D3DCOLOR color = D3DCOLOR_ARGB(int(a_Color.a()), int(a_Color.r()), int(a_Color.g()), int(a_Color.b()));

                // テクスチャが存在しない場合
                if(texture == nullptr){
                    // 色矩形をセット                    
                    Sqare sqare;
                    texture = sqare.texture();
                }else if( a_Image.isTextureAlpha() ){
                    // 半透明Listに追加する
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                if( a_Color.a() < 255 ){
                    // 半透明Listに追加する
                    mAlphaSprite->SetTransform(&world);
                    mAlphaSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);
                    return;
                }

                // 不透明Listに追加する
                mSprite->SetTransform(&world);
                mSprite->Draw(texture.getPtr(), &rect, NULL, NULL, color);

            }


            /// @brief リストに積んだSpriteをまとめて描画します。
            void DrawAll(){

                auto Device = gImplDirect3D->getDevice();
                // device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_MIRROR);
                // device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_MIRROR); 
                Device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
                Device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

                Device->SetRenderState(D3DRS_LIGHTING, false);              // ライト計算を切る

                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);       // アルファブレンディングの有効化
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);         // α判定を実行
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);           // Zバッファに書き込みを行う
                Device->SetRenderState( D3DRS_ZENABLE,false);               // Zバッファ判定は行う
                mSprite->End();
                
                Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);      // SRCの設定
                Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // DESTの設定
                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);            // アルファブレンディングの有効化
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);             // α判定を実行
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);               // Zバッファに書き込みを行う
                Device->SetRenderState( D3DRS_ZENABLE,false);                   // Zバッファ判定は行わない
                mAlphaSprite->End();
                
                mbListBegin = false;                                
            }




        };


    } // end of namespace Graphics
} // end of namespace GameLib
#endif