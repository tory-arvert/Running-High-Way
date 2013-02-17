/// @file Sqare.h
/// @brief 指定色で矩形を描画するのに必要なテクスチャを管理するクラス - 定義
/// @note Sprite機能を使って描画を行います。
/// @date 2013/01/13     tory

//====================================================================
//              Sqare.h
//--------------------------------------------------------------------
//    処理内容 : 指定色で矩形を描画するのに必要なテクスチャを管理するクラス - 定義
//    処理内容 : 
//    作成詳細 : 2013/01/13
//    補足     : Sprite機能を使って描画を行います。
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2013/00/00    tory
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_GRAPHICS_SQARE_H
#define INCLUDE_GAMELIB_GRAPHICS_SQARE_H

#include <Comptr.hpp>
#include <d3d9.h>               // Texture用

namespace GameLib{
    namespace Graphics{

        /// @class Sqare
        /// @brief 指定色で矩形を描画するのに必要なテクスチャを管理するクラス
        class Sqare{

            //----------------------------------------------------------
            // メンバ変数
        private:
            // 隠ぺいのためcppの無名スペースに記載

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:
            /// @brief コンストラクタ
            Sqare();
            /// @brief デストラクタ
            ~Sqare();

            //----------------------------------------------------------
            // メンバ関数
        public:            
            /// @brief デバイスロスト等に対応するため参照カウンタはそのままにSqare用のテクスチャを開放します。
            void Backup();

            /// @brief デバイスロストで開放していたSqare用テクスチャを再作成します。
            void Recover();

            //----------------------------------------
            // アクセサ
            
            /// @brief テクスチャの実体を取得します。
            Com_ptr < IDirect3DTexture9 > texture() const;

            //----------------------------------------
            // ヘルパー関数
        private:
            /// @brief Sqare用のテクスチャを作成します。
            /// @a_Texture 指定したスマートポインタ先にSqare用テクスチャを作成します。
            /// @note 実体がすでにある場合は何も処理をしません。
            void Create(Com_ptr < IDirect3DTexture9 >& a_Texture);


        }; // end of class Sqare

    } // end of namespace Graphics
} // end of namespace GameLib
#endif