/// @file Vector2.h
/// @brief xyの要素を持つVector2クラスの定義
/// @brief Positionなどのxy用クラスとして使用します
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            Vector2.h
//--------------------------------------------------------------------
//    処理内容 : xyの要素を持つVector2クラスの定義
//    処理内容 : Positionなどのxy用クラスとして使用します
//    作成詳細 : 2012/12/12    tory
//    補足     : なし
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR2_H
#define INCLUDED_GAMELIB_VECTOR2_H

#include <memory>       // shared_ptr用

using namespace std;

namespace GameLib{

    namespace Graphics{

        /// @brief xyの要素を持つVectorクラス
        class Vector2{
        //----------------------------------------------------------
        // プロトタイプ宣言

        /// @brief Vevtor2実装クラス
        class Impl;

        //----------------------------------------------------------
        // 別名宣言

        /// @brief Vector2Implのshared_ptrの別名
        typedef shared_ptr < Impl > Vector2Impl_sp;
        
        //----------------------------------------------------------
        // メンバ変数
        private:
        Vector2Impl_sp mImpl;

        //----------------------------------------------------------
        // 特殊メンバ関数
        public:

        /// @brief コンストラクタ
        Vector2::Vector2();

        /// @brief コンストラクタ
        Vector2::Vector2(const float x, const float y);

        /// @brief コピーコンストラクタ
        Vector2(const Vector2& obj);

        /// @brief デストラクタ
        virtual ~Vector2();

        /// @brief コピー（=演算子オーバーロード）
        Vector2& operator=(const Vector2& obj);

        private:
        /// @brief コピー時に内部で行う処理
        void Copy(const Vector2& obj);



        //----------------------------------------------------------
        // メンバ関数
        public:
        //----------------------------------------
        // アクセサ
            
        /// @brief 要素Xを設定します。
        void setX(const float x);

        /// @brief 要素Yを設定します。
        void setY(const float y);

        //----------------------------------------

        /// @brief 要素Xを取得します。
        const float x() const;

        /// @brief 要素Yを取得します。
        const float y() const;

        }; // end of class Vector2

    }  // end of namespace Graphics
} // end of namespace GameLib

#endif