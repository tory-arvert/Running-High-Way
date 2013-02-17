/// @file Sprite.h
/// @brief 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - 定義
/// @note 互換性重視の描画とSharderを利用した高速な描画に対応している
/// @date 2011/10/18     tory

//====================================================================
//              Sprite.h
//--------------------------------------------------------------------
//    処理内容 : 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス - 定義
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

#ifndef INCLUDE_GAMELIB_GRAPHICS_SPRITE_H
#define INCLUDE_GAMELIB_GRAPHICS_SPRITE_H

#include <Comptr.hpp>
#include <d3d9.h>               // Texture実体用

#include <Transform2D.hpp>
#include <ImageBase.hpp>
#include <TemplateBaseClass.hpp>
#include <Color.hpp>


#include <tiostream.h>          ///< @todo TestTexCreate用、開発終了時は撤去する

namespace GameLib{
    namespace Graphics{

        /// @class Sprite
        /// @brief 画面上に2Dテクスチャ(または色付き矩形)を描画するクラス
        class Sprite{
            
            //----------------------------------------------------------
            // 別名宣言

            /// @brief IDirect3DTexture9のスマートポインタ型
            typedef Com_ptr< IDirect3DTexture9 > Texture_sp;

            //----------------------------------------------------------
            // メンバ変数
        private:
            Transform2D     mTransform;     ///< @brief 座標・拡大・回転角
            ImageBase       mImage;         ///< @brief テクスチャ関連
            BaseXY<float>   mPivot;         ///< @brief 拡大・回転時の基点(0,0でスプライトの左上位置、1単位当たり1pixel)
            BaseWH<float>   mSize;          ///< @brief 拡大率が1の時の画面への貼り付けサイズ
            Color4<float>   mColor;         ///< @brief スプライト描画時に使用する色やα値
            bool            mActivity;      ///< @brief 描画するかどうかの可否
            
            
            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            Sprite();

            /// @brief デストラクタ
            ~Sprite();

            //----------------------------------------------------------
            // メンバ関数
        public:


            /// @brief Spriteの実体インスタンスをDirectXデバイスの状態に合わせて作成します。
            /// @brief これによってImplが互換性重視か速度重視かが決定します。
            /// @brief 引数なし、またはtrueで優先的にshader(速度重視)になるようにします。
            /// @attention このメソッドはexternにて関連付けたGraphicsManagerのメソッドを使用します。
            /// @param a_ShaderPriority 優先的にshaderで処理するように設定するかどうか
            void Create(const bool a_ShaderPriority = true);

            //----------------------------------------
            // アクセサ

            /// @brief 初期状態のステータスを設定します。
            /// @brief Position(0,0),Rotate(0),Scale(1,1),Texture(null),UV(0.0f,0.0f,1.0f,1.0f)
            /// @brief Size(128,128),Pivot(0,0),Color(255,255,255),Alpha(255),Priority(1.0f),Activity(true)
            void Initialize();
            
            /// @brief 描画時の基点となる座標を指定します。
            /// @param a_x スクリーン上のX座標
            /// @param a_y スクリーン上のY座標
            void Position(const float a_x, const float a_y);

            /// @brief スプライトの回転値を指定します。
            /// @attention 単位：度 正の値で時計回りに回転
            /// @param a_Deg 回転させる値(度)
            void Rotate(const float a_Deg);

            /// @brief スプライトの拡大率を指定します。
            /// @attention 貼付時の指定サイズに対して拡大率を適用します。
            /// @attention 2D貼付時のベースとなる画面サイズとの自動拡大補完とは関連ありません。
            void Scale(const float a_x, const float a_y);

            /// @brief 使用するテクスチャを指定します。
            /// @attention テクスチャを指定しない場合は指定した色で矩形を塗りつぶします。
            /// @param a_Texture 使用するテクスチャ
            void Texture(const Texture_sp a_Texture);

            /// @brief UVの範囲をfloatにて設定します。
            /// @attention 使用テクスチャを設定済でなおかつSize指定がまだ行われていない場合
            /// @attention WidthとHeightの値からSizeを自動補完します。
            /// @param a_Left テクスチャ上から切り取る際のX位置
            /// @param a_Top テクスチャ上から切り取る際のY位置
            /// @param a_Width 切り取る幅(1.0fでテクスチャの全体サイズ)
            /// @param a_Height 切り取る高さ(1.0fでテクスチャの全体サイズ)
            void UV(const float a_Left, const float a_Top, const float a_Width, const float a_Height);

            /// @brief UVの範囲をintにて設定します。
            /// @attention Size指定がまだ行われていない場合、WidthとHeightの値からSizeを自動補完します。
            /// @param a_Left テクスチャ上から切り取る際のX位置(pixel指定)
            /// @param a_Top テクスチャ上から切り取る際のY位置(pixel指定)
            /// @param a_Width 切り取る幅(pixel指定)
            /// @param a_Height 切り取る高さ(pixel指定)
            void UV(const int a_Left, const int a_Top, const int a_Width, const int a_Height);

            /// @brief スプライトの貼付時のサイズを設定します。
            /// @attention このサイズはScaleによる拡大率が(1,1)の状態の時のサイズとなります。
            /// @param a_Width 貼付時の幅(pixel単位)
            /// @param a_Width 貼付時の高さ(pixel単位)
            void Size(const float a_Width, const float a_Height);

            /// @brief ピボットを指定します。
            /// @param a_x X位置
            /// @param a_y Y位置
            void Pivot(const float a_x, const float a_y);

            /// @brief 描画時の色を設定します。
            /// @param a_Red 指定する色の赤値
            /// @param a_Green 指定する色の緑値
            /// @param a_Blue 指定する色の青値
            void Color(const float a_Red, const float a_Green, const float a_Blue);

            /// @brief 描画時の透明度を設定します。
            /// @param a_Alpha 透明度
            void Alpha(const float a_Alpha);

            /// @brief テクスチャのα値を使用するか設定します。
            /// @brief このステータスによってListの配列が最適化されます。
            /// @param a_Value テクスチャのα値を有効にするかどうか
            void UseTextureAlpha(const bool a_Value);

            /// @brief 描画時の表示優先度を設定します。
            /// @param a_z 優先度
            void Priority(const float a_z);

            /// @brief 描画するかどうかを設定します。
            /// @param a_value 描画実行の可否
            void Activity(const bool a_value);

            /// @brief Spriteの描画をリストとして積んでいきます。
            /// @note これはまとめて描画させることによる高速化のためです。
            void BeginList() const;

            /// @brief 描画を行います。2D用基準領域サイズ用へと自動補正されます。
            void Draw() const;

            /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
            void FixedDraw() const;

            /// @brief リストに積んだSpriteをまとめて描画します。
            void DrawALL() const;

            /// @brief ライブラリ作成時のテスト用関数
            /// @brief テクスチャを仮作成します。
            /// @todo 完成したらこのメソッドは削除します！
            void TestTexCreate(const std::tstring a_str);

            //----------------------------------------
            // ヘルパー関数
        private:



        }; // end of class Sprite

    } // end of namespace Graphics
} // end of namespace GameLib
#endif