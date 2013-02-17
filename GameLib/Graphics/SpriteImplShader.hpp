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
#include "Sqare.h"

#include <list>
#include <algorithm>
#include <functional>

#include <Transform2D.hpp>
#include <ImageBase.hpp>
#include <TemplateBaseClass.hpp>
#include <Color.hpp>


// StaticLibプロジェクトのプロパティからlibを呼び出す場合warningが出るため、それの代用法
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")

using namespace std;

namespace GameLib{
    namespace Graphics{

        /// @brief  インスタンス
        extern shared_ptr< ImplDirect3D > gImplDirect3D;


        /// @class SpriteListState
        /// @brief スプライト描画用のステータスリスト
        class SpriteListState{

            //----------------------------------------------------------
            // 別名宣言
            typedef Com_ptr< IDirect3DTexture9 > Texture_sp;

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
        private:
            
            D3DXMATRIX mProj;       ///< @brief 2D用射影変換Matrix
            D3DXMATRIX mWorld;      ///< @brief ワールド変換行列
            Texture_sp mTexture;    ///< @brief テクスチャ
            BaseUV<float> mUV;      ///< @brief UV
            Color4<float> mColor;   ///< @brief 色
            //----------------------------------------------------------
        public:
            /// @brief 描画に必要なステータスを保持します。
            void set(const D3DXMATRIX& a_World, const Texture_sp& a_Texture, const BaseUV<float>& a_UV, const Color4<float>& a_Color){
                mWorld = a_World;
                mTexture = a_Texture;
                mUV = a_UV;
                mColor = a_Color;
            }

            /// @brief 2D用射影変換行列を返します。
            const D3DXMATRIX* proj() const{
                return &mProj;
            }

            /// @brief ワールド変換行列を返します。
            const D3DXMATRIX* world() const{
                return &mWorld;
            }

            /// @brief UVやテクスチャの値を返します。
            Texture_sp texture() const{
                return mTexture;
            }

            /// @brief UVの値を返します。
            BaseUV<float> UV() const{
                return mUV;
            }

            /// @brief 色とα値を返します。
            Color4<float> Color() const{
                return mColor;
            }

            const float z() const{
                return mWorld._43;
            }

        };


        /// @class ImplSpriteShader
        /// @brief DirectX標準のLPD3DXSPRITEを用いたスプライト表示
        class ImplSpriteShader : public ISpriteImpl{

            
            //----------------------------------------------------------
            // 別名宣言
            typedef shared_ptr<SpriteListState> SpriteListState_sp;

            //----------------------------------------------------------
            // メンバ変数
        private:
            /// @brief  不透明スプライトの描画ステータスのスマートポインタリスト
            list <SpriteListState_sp> mDrawList;
            /// @brief  半透明スプライトの描画ステータスのスマートポインタリスト
            list <SpriteListState_sp> mAlphaDrawList;


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
                if (mEffect == nullptr) {
                    ID3DXBuffer *error = 0;
                    if ( FAILED( D3DXCreateEffectFromFile( Device.getPtr(), "../shader/sprite.fx", 0, 0, 0, 0, mEffect.ToCreator(), &error) ) ) {
                        OutputDebugString( (const char*)error->GetBufferPointer());
                        return;
                    }
                }

                // 頂点宣言作成
                if (mDecl == nullptr) {
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
                SpriteListState_sp spriteState;
                spriteState.reset( new SpriteListState());

                // 計算が必要になるものは各引数より必要なものを抽出
                // 拡大率を抽出
                auto a_Scale = a_Transform.scale();
                // 座標を抽出
                auto a_Position = a_Transform.position();

                D3DXMATRIX world, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );
                // ポリゴンサイズ
                D3DXMatrixScaling( &world, a_Size.width(), a_Size.height(), 1.0f );	
                // ローカルスケール
                D3DXMatrixScaling( &scale, a_Scale.x() * mResolution.x(), a_Scale.y() * mResolution.y(), 1.0f );
                // 回転
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // ピボット分オフセット
                world._41 = -a_Pivot.x();
                world._42 = -a_Pivot.y();

                // トランスフォームを計算する
                world = world * scale * rot;
                // 座標を移動する
                world._41 += ( a_Position.x() * mResolution.x() );
                world._42 += ( a_Position.y() * mResolution.y() );
                world._43 += ( a_Transform.position().z()  );

                auto a_Texture = a_Image.Texture();
                auto a_UV = a_Image.getUV();

                // テクスチャが存在しない場合
                if(a_Texture == nullptr){
                    // 色矩形をセット
                    Sqare sqare;
                    a_Texture = sqare.texture();
                    a_UV.setUV(0,0,1,1);
                }else if( a_Image.isTextureAlpha() ){
                    // 描画に必要なデータセットをまとめる
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // 半透明Listに追加する
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // 半透明が指定されているとき
                if( a_Color.a() < 255){
                    // 描画に必要なデータセットをまとめる
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // 半透明Listに追加する
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // 描画に必要なデータセットをまとめる
                spriteState->set(world, a_Texture, a_UV, a_Color);   
                // 不透明Listに追加する
                mDrawList.push_back( spriteState );
            }

            /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color){

                // 2D描画への射影変換行列
                SpriteListState_sp spriteState;
                spriteState.reset( new SpriteListState());

                // 計算が必要になるものは各引数より必要なものを抽出
                // 拡大率を抽出
                auto a_Scale = a_Transform.scale();
                // 座標を抽出
                auto a_Position = a_Transform.position();

                D3DXMATRIX world, scale, rot;
                D3DXMatrixIdentity( &world );
                D3DXMatrixIdentity( &scale );
                D3DXMatrixIdentity( &rot );
                // ポリゴンサイズ
                D3DXMatrixScaling( &world, a_Size.width(), a_Size.height(), 1.0f );	
                // ローカルスケール
                D3DXMatrixScaling( &scale, a_Scale.x(), a_Scale.y(), 1.0f );
                // 回転
                D3DXMatrixRotationZ( &rot, D3DXToRadian(a_Transform.degree()) );
                // ピボット分オフセット
                world._41 = -a_Pivot.x();
                world._42 = -a_Pivot.y();
                world = world * scale * rot;
                world._41 += a_Position.x();
                world._42 += a_Position.y();
                world._43 += a_Transform.position().z();

                auto a_Texture = a_Image.Texture();
                auto a_UV = a_Image.getUV();

                // テクスチャが存在しない場合
                if(a_Texture == nullptr){
                    // 色矩形をセット
                    Sqare sqare;
                    a_Texture = sqare.texture();
                    a_UV.setUV(0,0,1.0,1.0);
                }else if( a_Image.isTextureAlpha() ){
                    // 描画に必要なデータセットをまとめる
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // 半透明Listに追加する
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // 半透明が指定されているとき
                if( a_Color.a() < 255){
                    // 描画に必要なデータセットをまとめる
                    spriteState->set(world, a_Texture, a_UV, a_Color); 
                    // 半透明Listに追加する
                    mAlphaDrawList.push_back( spriteState );
                    return;
                }

                // 描画に必要なデータセットをまとめる
                spriteState->set(world, a_Texture, a_UV, a_Color);   
                // 不透明Listに追加する
                mDrawList.push_back( spriteState );
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

                // 描画前に各Listをソートします。
                SortList();

                // シェーダ開始
                UINT numPass = 0;
                mEffect->SetTechnique( "Tech" );
                mEffect->Begin(&numPass, 0);
                mEffect->BeginPass(0);

                Device->SetRenderState(D3DRS_LIGHTING, false);              // ライト計算を切る

                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);       // アルファブレンディングの有効化
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);         // α判定を実行
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);           // Zバッファに書き込みを行う
                Device->SetRenderState( D3DRS_ZENABLE,false);               // Zバッファ判定は行う
                DrawSpriteList(mDrawList);
                
                Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);      // SRCの設定
                Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // DESTの設定
                Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);            // アルファブレンディングの有効化
                Device->SetRenderState(D3DRS_ALPHATESTENABLE,true);             // α判定を実行
                Device->SetRenderState( D3DRS_ZWRITEENABLE,true);               // Zバッファに書き込みを行う
                Device->SetRenderState( D3DRS_ZENABLE,false);                   // Zバッファ判定は行わない
                DrawSpriteList(mAlphaDrawList);



                // 描画リストをクリアする。
                mAlphaDrawList.clear();

                
                mEffect->EndPass();
                mEffect->End();



            }


            /// @brief 指定したリストに積んだSpriteをまとめて描画します。
            void DrawSpriteList(list <SpriteListState_sp>& a_List){

                auto Device = gImplDirect3D->getDevice();

                list <SpriteListState_sp>::iterator it = a_List.begin();
                for(; it != a_List.end(); it++){
                    auto p = it->get();
                    auto a_UV = p->UV();
                    auto a_Color = p->Color();
                    D3DXCOLOR color( p->Color().r(), p->Color().g(), p->Color().b(), p->Color().a());
                    // 色情報を正規化
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
                // 描画リストをクリアする。
                a_List.clear();

            }

            /// @brief それぞれのリストを適した順番にソートします。
            void SortList(){
                mDrawList.sort(&SortDraw);
                mAlphaDrawList.sort(&SortAlphaDraw);
            }

            /// @brief 不透明Spriteのソートをする際の処理
            /// @param a_Left 左側ポインタ要素
            /// @param a_Right 右側ポインタ要素
            /// @return bool 入れ替えるか否か
            static bool SortDraw(const SpriteListState_sp a_Left, const SpriteListState_sp a_Right){
                return ((a_Left)->z() < (a_Right)->z() );
            }


            /// @brief 半透明Spriteのソートをする際の処理
            /// @param a_Left 左側ポインタ要素
            /// @param a_Right 右側ポインタ要素
            /// @return bool 入れ替えるか否か
            static bool SortAlphaDraw(const SpriteListState_sp a_Left, const SpriteListState_sp a_Right){
                return ((a_Left)->z() > (a_Right)->z() );
            }


        };




    } // end of namespace Graphics
} // end of namespace GameLib
#endif