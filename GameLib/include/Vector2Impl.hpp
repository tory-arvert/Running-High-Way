/// @file Vector2Impl.h
/// @brief xyの要素を持つVector2クラスの実装
/// @brief Positionなどのxy用クラスとして使用します
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            Vector2Impl.h
//--------------------------------------------------------------------
//    処理内容 : xyの要素を持つVector2クラスの実装
//    処理内容 : Positionなどのxy用クラスとして使用します
//    作成詳細 : 2012/12/12    tory
//    補足     : なし
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR2_IMPL
#define INCLUDED_GAMELIB_VECTOR2_IMPL

#include <d3dx9.h>                  // D3DXVECTOR2用
#include "Vector2.h"

namespace GameLib{

    namespace Graphics{

        /// @class Vector2の実体クラス
        /// @brief xyの要素を持つVector3クラス
        class Vector2::Impl{
            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            Impl() : mVector2()
            {
            }

            /// @brief コンストラクタ
            Impl(const float x, const float y){
                setX( x );
                setY( y );
            }

            /// @brief デストラクタ
            virtual ~Impl()
            {
            }

            //----------------------------------------------------------
            // メンバ変数
        private:
            D3DXVECTOR2 mVector2;

            //----------------------------------------------------------
            // メンバ関数
        public:
            
            /// @brief 要素Xを設定します。
            void setX(const float x){
                mVector2.x = x;
            }

            /// @brief 要素Yを設定します。
            void setY(const float y){
                mVector2.y = y;
            }


            /// @brief 要素Xを取得します。
            const float x() const{
                return mVector2.x;
            }

            /// @brief 要素Yを取得します。
            const float y() const{
                return mVector2.y;
            }


            
        }; // end of class Impl

    }   // end of namespace Graphics
}    // end of namespace GameLib

#endif
