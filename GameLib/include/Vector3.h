/// @file Vector3.h
/// @brief xyzの要素を持つVector3クラスの定義
/// @brief PositionやScaleなどのxyz用クラスとして使用します
/// @note 
/// @date 2012/12/05     tory
//====================================================================
//            Vector.h
//--------------------------------------------------------------------
//    処理内容 : xyzの要素を持つVector3クラスの定義
//    処理内容 : PositionやScaleなどのxyz用クラスとして使用します
//    作成詳細 : 2012/12/05    tory
//    補足     : なし
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR3_H
#define INCLUDED_GAMELIB_VECTOR3_H

#include <memory>       // shared_ptr用

using namespace std;

namespace GameLib{

    namespace Graphics{

        /// @brief xyzの要素を持つVectorクラス
        class Vector3{
            //----------------------------------------------------------
            // プロトタイプ宣言

            /// @brief Vevtor3実装クラス
            class Impl;

            //----------------------------------------------------------
            // 別名宣言

            /// @brief Vector3Implのshared_ptrの別名
            typedef shared_ptr < Impl > Vector3Impl_sp;

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            Vector3();

            /// @brief コンストラクタ
            Vector3(const float x, const float y, const float z);

            /// @brief コピーコンストラクタ
            Vector3(const Vector3& obj);

            /// @brief デストラクタ
            virtual ~Vector3();

            /// @brief コピー（=演算子オーバーロード）
            Vector3& operator=(const Vector3& obj);

        private:
            /// @brief コピー時に内部で行う処理
            void Copy(const Vector3& obj);

            //----------------------------------------------------------
            // メンバ変数
        private:
            Vector3Impl_sp mImpl;

            //----------------------------------------------------------
            // メンバ関数
        public:
            //----------------------------------------
            // アクセサ
            
            /// @brief 要素Xを設定します。
            void setX(const float x);

            /// @brief 要素Yを設定します。
            void setY(const float y);

            /// @brief 要素Zを設定します。
            void setZ(const float z);

            //----------------------------------------

            /// @brief 要素Xを取得します。
            const float x() const;

            /// @brief 要素Yを取得します。
            const float y() const;

            /// @brief 要素Zを取得します。
            const float z() const;
          
        }; // end of class Vector3


    }   // end of namespace Graphics
}    // end of namespace GameLib

#endif
