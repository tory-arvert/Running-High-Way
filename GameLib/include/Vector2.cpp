/// @file Vector2.cpp
/// @brief xyの要素を持つVector2クラスのラッパー
/// @brief Positionなどのxy用クラスとして使用します
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            Vector2.cpp
//--------------------------------------------------------------------
//    処理内容 : xyの要素を持つVector2クラスのラッパー
//    処理内容 : Vector2Implへの中継処理を行います。
//    作成詳細 : 2012/12/12    tory
//    補足     : ここでImpl先を切り替える処理を作れば別SDK処理への移行も可能。
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#include "Vector2.h"
#include "Vector2Impl.hpp"


namespace GameLib{

    namespace Graphics{

        /// @brief コンストラクタ
        Vector2::Vector2(){
            this->mImpl.reset(new Impl() );
        }

        /// @brief コンストラクタ
        Vector2::Vector2(const float x, const float y){
            this->mImpl.reset(new Impl(x, y) );
        }

        /// @brief コピーコンストラクタ
        Vector2::Vector2(const Vector2& obj){
            this->mImpl.reset(new Impl(obj.x(), obj.y()) );
            this->Copy(obj);
        }

        /// @brief デストラクタ
        Vector2::~Vector2(){}


        /// @brief コピー（=演算子オーバーロード）
        Vector2& Vector2::operator=(const Vector2& obj){
            this->Copy(obj);
            return *this;
        }
        
        /// @brief コピー時に内部で行う処理
        void Vector2::Copy(const Vector2& obj){
            this->setX(obj.x());
            this->setY(obj.y());
        }


        //----------------------------------------------------------

        /// @brief 要素Xを設定します。
        void Vector2::setX(const float x){
            this->mImpl->setX(x);
        }

         /// @brief 要素Yを設定します。
        void Vector2::setY(const float y){
            this->mImpl->setY(y);
        }

        
        //----------------------------------------------------------

        /// @brief 要素Xを取得します。
        const float Vector2::x() const{
            return this->mImpl->x();
        }

        /// @brief 要素Yを取得します。
        const float Vector2::y() const{
            return this->mImpl->y();
        }


    }   // end of namespace Graphics
}    // end of namespace GameLib
