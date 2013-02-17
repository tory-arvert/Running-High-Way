/// @file Transform2D.hpp
/// @brief 座標・拡大値・回転をまとめた2D用トランスフォームクラス
/// @note 
/// @date 2012/12/29     tory
//====================================================================
//            Transform2D.hpp
//--------------------------------------------------------------------
//    処理内容 : 座標・拡大値・回転をまとめた2D用トランスフォームクラス
//    処理内容 : 
//    作成詳細 : 2012/12/29    tory
//    補足     : 
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================

#ifndef INCLUDED_GAMELIB_GRAPHICS_TRANSFORM2D_H
#define INCLUDED_GAMELIB_GRAPHICS_TRANSFORM2D_H

#include "TemplateBaseClass.hpp"

namespace GameLib{
    namespace Graphics{

        /// @class Transform2D
        /// @brief 座標・拡大値・回転をまとめた2D用トランスフォームクラス
        class Transform2D{
            //----------------------------------------------------------
            // メンバ変数
        private:
            BaseXYZ<float>  mPosition;
            BaseXY<float>   mScale;
            float           mDegree;

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:
            /// @brief コンストラクタ
            Transform2D():mScale(1.0f,1.0f),mDegree(0.0f){}
            /// @brief デストラクタ
            ~Transform2D(){}

            //----------------------------------------------------------
            // メンバ関数
        public:
            // アクセサ

            /// @brief X座標を設定します。
            /// @param a_x X座標
            void setPositionX( const float a_x ){
                mPosition.setX(a_x);
            }

            /// @brief Y座標を設定します。
            /// @param a_y Y座標
            void setPositionY( const float a_y ){
                mPosition.setY(a_y);
            }

            /// @brief Z座標を設定します。
            /// @param a_z Z座標
            void setPositionZ( const float a_z ){
                mPosition.setZ(a_z);
            }


            /// @brief 拡大率を設定します。
            void setScale(const float a_x, const float a_y){
                mScale.setX(a_x);
                mScale.setY(a_y);
            }

            /// @brief 回転角度を設定します。
            /// @brief 設定範囲は0.0~360.0度に自動補正されます。
            /// @note 設定単位はdegree(度)のfloatです。
            /// @param a_Deg 設定する度
            const void setDegree(const float a_Deg){

                mDegree = a_Deg;
                // 360度より大きい時は範囲内の同値に修正。
                while( mDegree > 360.0000f){
                    mDegree -=360.0000f;
                }
                // 0度より小さい時は範囲内の同値に修正。
                while( mDegree < 0.0000f){
                    mDegree +=360.0000f;
                }
            }


            //----------------------------------------

            /// @brief 設定した座標値を取得します。
            /// @return BaseXY<float> 座標値XY
            const BaseXYZ<float> position() const{
                return BaseXYZ<float> (mPosition.x(), mPosition.y(), mPosition.z() );
            }

            /// @brief 拡大率を取得します。
            const BaseXY<float> scale() const{
                return BaseXY<float> ( mScale.x(), mScale.y() );
            }

            /// @brief 回転角度を取得します。
            /// @note 取得単位はdegree(度)のfloatです。
            const float degree() const{
                return mDegree;
            }

        };

    }
}

#endif