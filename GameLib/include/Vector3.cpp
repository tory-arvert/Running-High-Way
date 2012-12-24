/// @file Vector3.cpp
/// @brief xyzの要素を持つVector3クラスのラッパー
/// @brief PositionやScaleなどのxyz用クラスとして使用します
/// @note 
/// @date 2012/12/05     tory
//====================================================================
//            Vector3.h
//--------------------------------------------------------------------
//    処理内容 : xyzの要素を持つVector3クラスのラッパー
//    処理内容 : Vector3Implへの中継処理を行います。
//    作成詳細 : 2012/12/05    tory
//    補足     : ここでImpl先を切り替える処理を作れば別SDK処理への移行も可能。
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#include "Vector3.h"
#include "Vector3Impl.hpp"


namespace GameLib{

    namespace Graphics{

        /// @brief コンストラクタ
        Vector3::Vector3(){
            this->mImpl.reset(new Impl() );
        }

        /// @brief コンストラクタ
        Vector3::Vector3(const float x, const float y, const float z){
            this->mImpl.reset(new Impl(x, y, z) );
        }

        /// @brief コピーコンストラクタ
        Vector3::Vector3(const Vector3& obj){
            this->mImpl.reset(new Impl(obj.x(), obj.y(), obj.z()) );
            this->Copy(obj);
        }

        /// @brief デストラクタ
        Vector3::~Vector3(){}


        /// @brief コピー（=演算子オーバーロード）
        Vector3& Vector3::operator=(const Vector3& obj){
            this->Copy(obj);
            return *this;
        }
        
        /// @brief コピー時に内部で行う処理
        void Vector3::Copy(const Vector3& obj){
            this->setX(obj.x());
            this->setY(obj.y());
            this->setZ(obj.z());
        }


        //----------------------------------------------------------

        /// @brief 要素Xを設定します。
        void Vector3::setX(const float x){
            this->mImpl->setX(x);
        }

         /// @brief 要素Yを設定します。
        void Vector3::setY(const float y){
            this->mImpl->setY(y);
        }

         /// @brief 要素Zを設定します。
        void Vector3::setZ(const float z){
            this->mImpl->setZ(z);
        }
        
        //----------------------------------------------------------

        /// @brief 要素Xを取得します。
        const float Vector3::x() const{
            return this->mImpl->x();
        }

        /// @brief 要素Yを取得します。
        const float Vector3::y() const{
            return this->mImpl->y();
        }

        /// @brief 要素Zを取得します。
        const float Vector3::z() const{
            return this->mImpl->z();
        }


    }   // end of namespace Graphics
}    // end of namespace GameLib
