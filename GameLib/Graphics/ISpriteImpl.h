/// @file ISpriteImpl.h
/// @brief 画面上に2Dテクスチャ(または色付き矩形)を描画するクラスのImpl用インターフェイス
/// @note 互換性重視の描画とSharderを利用した高速な描画に対応している
/// @date 2012/12/28     tory

//====================================================================
//              ISpriteImpl.h
//--------------------------------------------------------------------
//    処理内容 : 画面上に2Dテクスチャ(または色付き矩形)を描画するクラスのImpl用インターフェイス
//    処理内容 : 
//    作成詳細 : 2012/12/28
//    補足     : 互換性重視の描画とSharderを利用した高速な描画に対応している
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2013/01/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_SPRITE_IMPL_INTERFACE_H
#define INCLUDE_GAMELIB_SPRITE_IMPL_INTERFACE_H

#include <Transform2D.h>
#include <ImageBase.h>
#include <TemplateBaseClass.h>
#include <Color.h>

namespace GameLib{
    namespace Graphics{

        /// @class ISpriteImpl
        /// @brief 2D描画クラスImplの継承元となるインターフェイスクラス
        class ISpriteImpl{

            //----------------------------------------------------------
            // メンバ変数
        private:
            // Interfaceはメンバ変数などの実体を持たない。

            //----------------------------------------------------------
            // 特殊メンバ
        public:

            /// @brief コンストラクタ
            ISpriteImpl(){}

            /// @brief デストラクタ
            virtual ~ISpriteImpl(){}

            //----------------------------------------------------------
            // メンバ関数
            // 各描画デバイスで共通する処理を記述すること。

            // Interfaceなので全てのメソッドにvirtualと=0をつけておくこと。
            //virtual void Test(const int x) = 0;

            /// @brief 描画を行います。2D用基準領域サイズ用へと自動補正されます。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            virtual void Draw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color) = 0;

            /// @brief スクリーンサイズの縮尺補正に関係なく指定されたサイズで描画します。
            /// @param a_Transform 座標・拡大・回転角
            /// @param a_Image テクスチャ関連
            /// @param a_Pivot 拡大・回転時の基点
            /// @param a_Size 拡大率が1の時の画面への貼り付けサイズ
            /// @param a_Color 描画時に使用する色やα値
            virtual void FixedDraw(const Transform2D &a_Transform, const ImageBase &a_Image, const BaseXY<float> &a_Pivot, const BaseWH<float> &a_Size, const Color4<float> &a_Color) = 0;

            /// @brief リストに積んだSpriteをまとめて描画します。
            virtual void DrawAll() = 0;

            //----------------------------------------
            // アクセサ用




        }; // end of class ISpriteImpl



    } // end of namespace Graphics
} // end of namespace GameLib
#endif