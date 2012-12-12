/// @file Vector3Impl.h
/// @brief xyzの要素を持つVector3クラスの実装
/// @brief PositionやScaleなどのxyz用クラスとして使用します
/// @note 
/// @date 2012/12/05     tory
//====================================================================
//            Vector3Impl.h
//--------------------------------------------------------------------
//    処理内容 : xyzの要素を持つVector3クラスの実装
//    処理内容 : PositionやScaleなどのxyz用クラスとして使用します
//    作成詳細 : 2012/12/05    tory
//    補足     : なし
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_VECTOR3_IMPL
#define INCLUDED_GAMELIB_VECTOR3_IMPL

#include <d3dx9.h>                  // D3DXVECTOR3用
#include "Vector3.h"

namespace GameLib{

    namespace Graphics{

        /// @class Vector3の実体クラス
        /// @brief xyzの要素を持つVector3クラス
        class Vector3::Impl{
            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            Impl(){
                this->setX(0.0f);
                this->setY(0.0f);
                this->setZ(0.0f);
            }

            /// @brief コンストラクタ
            Impl(const float x, const float y, const float z){
                this->setX(x);
                this->setY(y);
                this->setZ(z);
            }

            /// @brief デストラクタ
            virtual ~Impl(){}

            //----------------------------------------------------------
            // メンバ変数
        private:
            D3DXVECTOR3 mVector3;

            //----------------------------------------------------------
            // メンバ関数
        public:
            
            /// @brief 要素Xを設定します。
            void setX(const float x){
                this->mVector3.x = x;
            }

            /// @brief 要素Yを設定します。
            void setY(const float y){
                this->mVector3.y = y;
            }

            /// @brief 要素Zを設定します。
            void setZ(const float z){
                this->mVector3.z = z;
            }

            /// @brief 要素Xを取得します。
            const float x() const{
                return this->mVector3.x;
            }

            /// @brief 要素Yを取得します。
            const float y() const{
                return this->mVector3.y;
            }

            /// @brief 要素Zを取得します。
            const float z() const{
                return this->mVector3.z;
            }

            
        }; // end of class Impl

    }   // end of namespace Graphics
}    // end of namespace GameLib

#endif
