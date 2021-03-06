/// @file Sprite.cpp
/// @brief 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - 実装 + Implリダイレクト
/// @note 互換性重視の描画とSharderを利用した高速な描画に対応している
/// @date 2011/10/18     tory

//====================================================================
//              Sprite.cpp
//--------------------------------------------------------------------
//    処理内容 : 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - 実装 + Implリダイレクト
//    処理内容 : 
//    作成詳細 : 2011/10/18
//    補足     : 互換性重視の描画とSharderを利用した高速な描画に対応している
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 大幅なリファクタリングを実行
//    作成詳細 : 2012/12/26    tory
//         
//====================================================================

#include <memory>                           // unique_ptrなどに必要
//#include <tiostream.h>                      // tstring型などのTCHAR拡張定義

#include "Sprite.h"
#include "ISpriteImpl.h"
#include "GraphicsManagerImplDirect3D.hpp"

#include "SpriteImpl.hpp"
#include "SpriteImplShader.hpp"

// test用
#include <d3d9.h>

using namespace std;
using namespace GameLib::Graphics;


//----------------------------------------------------------
//----------------------------------------------------------

namespace GameLib{
    namespace Graphics{

        /// @brief  実体クラスインスタンスの外部参照
        extern shared_ptr< ImplDirect3D > gImplDirect3D;
       

        //----------------------------------------------------------
        // 特殊メンバ関数

        /// @brief コンストラクタ
        Sprite::Sprite(){
            Initialize();
        }

        /// @brief デストラクタ
        Sprite::~Sprite(){}

        //----------------------------------------------------------
        // メンバ関数

        /// @brief Spriteの実体インスタンスをDirectXデバイスの状態に合わせて作成します。
        /// @brief これによってImplが互換性重視か速度重視かが決定します。
        /// @brief 引数なし、またはtrueで優先的にshader(速度重視)になるようにします。
        /// @attention このメソッドはexternにて関連付けたGraphicsManagerのメソッドを使用します。
        /// @param a_ShaderPriority 優先的にshaderで処理するように設定するかどうか
        void Sprite::Create(const bool a_ShaderPriority){

            // 作成済みかどうかを確認する。
            if(gImplDirect3D->mSpriteImpl != nullptr){
                MessageBox(NULL,_T("Spriteの描画用実体を複数作成しようとしました。"),_T("インスタンス作成中止"),MB_OK);
                return;
            }


            // 問題なければ実体を作成
            // ここで作成するImplによって使用するSprite描画Implが変わってくる。
            if(a_ShaderPriority && gImplDirect3D->getVertexShaderReady()){
                shared_ptr< ImplSpriteShader > Impl(nullptr);
                Impl.reset(new ImplSpriteShader());
                gImplDirect3D->mSpriteImpl.reset();
                gImplDirect3D->mSpriteImpl = static_pointer_cast<ISpriteImpl>(Impl);
            }else{
                shared_ptr< ImplSprite > Impl(nullptr);
                Impl.reset(new ImplSprite());
                gImplDirect3D->mSpriteImpl.reset();
                gImplDirect3D->mSpriteImpl = static_pointer_cast<ISpriteImpl>(Impl);
            }

        }

        //----------------------------------------
        // アクセサ

        /// @brief 初期状態のステータスを設定します。
        /// @brief Position(0,0),Rotate(0),Scale(1,1),Texture(null),UV(0.0f,0.0f,1.0f,1.0f)
        /// @brief Size(128,128),Pivot(0,0),Color(255,255,255),Alpha(255),Priority(1.0f),Activity(true)
        void Sprite::Initialize(){

            Position(0,0);
            Rotate(0);
            Scale(1.0f, 1.0f);
            //Texture(NULL);
            UV(0.0f, 0.0f, 1.0f, 1.0f);
            //Size(0,0);
            Pivot(0,0);
            Color(255, 255, 255);
            Alpha(255);
            Priority(1.0f);
            Activity(true);
        }

            
        /// @brief 描画時の基点となる座標を指定します。
        /// @param a_x スクリーン上のX座標
        /// @param a_y スクリーン上のY座標
        void Sprite::Position(const float a_x, const float a_y){
            mTransform.setPositionX( a_x );
            mTransform.setPositionY( a_y );
        }

        /// @brief スプライトの回転値を指定します。
        /// @attention 単位：度 正の値で時計回りに回転
        /// @param a_Deg 回転させる値(度)
        void Sprite::Rotate(const float a_Deg){
            mTransform.setDegree( a_Deg );
        }

        /// @brief スプライトの拡大率を指定します。
        /// @attention 貼付時の指定サイズに対して拡大率を適用します。
        /// @attention 2D貼付時のベースとなる画面サイズとの自動拡大補完とは関連ありません。
        void Sprite::Scale(const float a_x, const float a_y){
            mTransform.setScale( a_x, a_y );
        }

        /// @brief 使用するテクスチャを指定します。
        /// @attention テクスチャを指定しない場合は指定した色で矩形を塗りつぶします。
        /// @param a_Texture 使用するテクスチャ
        void Sprite::Texture(const Texture_sp a_Texture){
                mImage.setTexture( a_Texture );
        }

        /// @brief UVの範囲をfloatにて設定します。
        /// @attention 使用テクスチャを設定済でなおかつSize指定がまだ行われていない場合
        /// @attention WidthとHeightの値からSizeを自動補完します。
        /// @param a_Left テクスチャ上から切り取る際のX位置
        /// @param a_Top テクスチャ上から切り取る際のY位置
        /// @param a_Width 切り取る幅(1.0fでテクスチャの全体サイズ)
        /// @param a_Height 切り取る高さ(1.0fでテクスチャの全体サイズ)
        void Sprite::UV(const float a_Left, const float a_Top, const float a_Width, const float a_Height){
            mImage.setUV( BaseUV<float>(a_Left, a_Top, a_Width, a_Height) );

            // UV領域の値をfloatで設定したためfalse指定
            mImage.setUVint( false );
            
            // テクスチャ実体がある場合
            if(mImage.Texture() != nullptr){
            
                // テクスチャの全体サイズを取得
                auto textureSize = mImage.Size();
                    
                // スプライトの幅がまだ未設定であるならUVの範囲をサイズとして指定
                if(mSize.width() == 0){
                    mSize.setWidth( textureSize.width()* a_Width );
                }
                // スプライトの高さがまだ未設定であるならUVの範囲をサイズとして指定
                if(mSize.height() == 0){
                    mSize.setHeight( textureSize.height() * a_Height );
                }

            }
        }

        /// @brief UVの範囲をintにて設定します。
        /// @attention Size指定がまだ行われていない場合、WidthとHeightの値からSizeを自動補完します。
        /// @param a_Left テクスチャ上から切り取る際のX位置(pixel指定)
        /// @param a_Top テクスチャ上から切り取る際のY位置(pixel指定)
        /// @param a_Width 切り取る幅(pixel指定)
        /// @param a_Height 切り取る高さ(pixel指定)
        void Sprite::UV(const int a_Left, const int a_Top, const int a_Width, const int a_Height){

            // UV領域の値をintで設定したことを記録
            // これは描画時にUVはfloatに変換する必要があるが
            // UV設定時にまだテクスチャが決まっていない場合、テクスチャサイズが分からない(=変換できない)ため
            // 後でfloat値に変換する際に識別で必要となる。
            mImage.setUVint( true );
            mImage.setUV( BaseUV<float>(float(a_Left), float(a_Top), float(a_Width), float(a_Height)) );
                    
            // スプライトの幅がまだ未設定であるならUVの範囲をサイズとして指定
            if(mSize.width() == 0){
                mSize.setWidth( float(a_Width) );
            }
            // スプライトの高さがまだ未設定であるならUVの範囲をサイズとして指定
            if(mSize.height() == 0){
                mSize.setHeight( float(a_Height) );
            }

        }

        /// @brief スプライトの貼付時のサイズを設定します。
        /// @attention このサイズはScaleによる拡大率が(1,1)の状態の時のサイズとなります。
        /// @param a_Width 貼付時の幅(pixel単位)
        /// @param a_Width 貼付時の高さ(pixel単位)
        void Sprite::Size(const float a_Width, const float a_Height){
            mSize.setWH( a_Width, a_Height );
        }

        /// @brief ピボットを指定します。
        /// @param a_x X位置
        /// @param a_y Y位置
        void Sprite::Pivot(const float a_x, const float a_y){
            mPivot.setXY( a_x, a_y );
        }

        /// @brief 描画時の色を設定します。
        /// @param a_Red 指定する色の赤値
        /// @param a_Green 指定する色の緑値
        /// @param a_Blue 指定する色の青値
        void Sprite::Color(const float a_Red, const float a_Green, const float a_Blue){
            mColor.setR( a_Red );
            mColor.setG( a_Green );
            mColor.setB( a_Blue );
        }

        /// @brief 描画時の透明度を設定します。
        /// @param a_Alpha 透明度
        void Sprite::Alpha(const float a_Alpha){
            mColor.setA( a_Alpha );
        }

        /// @brief テクスチャのα値を使用するか設定します。
        /// @brief このステータスによってListの配列が最適化されます。
        /// @param a_Value テクスチャのα値を有効にするかどうか
        void Sprite::UseTextureAlpha(const bool a_Value){
            mImage.UseTextureAlpha( a_Value );
        }

        /// @brief 描画時の表示優先度を設定します。
        /// @param a_z 優先度
        void Sprite::Priority(const float a_z){
            mTransform.setPositionZ( a_z );
        }

        /// @brief 描画するかどうかを設定します。
        /// @param a_value 描画実行の可否
        void Sprite::Activity(const bool a_value){
            mActivity = a_value;
        }



        /// @brief 描画を行います。2D用基準領域サイズ用へと自動補正されます。
        void Sprite::Draw() const{
            if(mActivity){
                gImplDirect3D->mSpriteImpl->Draw(mTransform, mImage, mPivot, mSize, mColor);
            }
        }

        /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
        void Sprite::FixedDraw() const{
            if(mActivity){
                gImplDirect3D->mSpriteImpl->FixedDraw(mTransform, mImage, mPivot, mSize, mColor);
            }
        }

        /// @brief リストに積んだSpriteをまとめて描画します。
        void Sprite::DrawALL() const{
            gImplDirect3D->mSpriteImpl->DrawAll();
        }

        /// @brief ライブラリ作成時のテスト用関数
        /// @brief テクスチャを仮作成します。
        /// @todo 完成したらこのメソッドは削除します！
        void Sprite::TestTexCreate(const std::tstring a_str){
            Com_ptr< IDirect3DTexture9 > tex;
            auto Device = gImplDirect3D->getDevice();
            D3DXCreateTextureFromFile( Device.getPtr(), a_str.c_str(), tex.ToCreator());
            this->Texture(tex);
        }

        //----------------------------------------
        // ヘルパー関数




    }
}
