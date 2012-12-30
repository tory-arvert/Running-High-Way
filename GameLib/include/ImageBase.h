/// @file ImageBase.h
/// @brief テクスチャ関連のまとめクラス
/// @note 
/// @date 2012/12/29     tory
//====================================================================
//            ImageBase.h
//--------------------------------------------------------------------
//    処理内容 : テクスチャ関連のまとめクラス
//    処理内容 : 
//    作成詳細 : 2012/12/29    tory
//    補足     : 
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================

#ifndef INCLUDED_GAMELIB_GRAPHICS_IMAGEBASE_H
#define INCLUDED_GAMELIB_GRAPHICS_IMAGEBASE_H

#include "TemplateBaseClass.h"
#include <Comptr.hpp>
#include <d3d9.h>               // Texture実体用


namespace GameLib{
    namespace Graphics{

        /// @class ImageBase
        /// @brief テクスチャ関連のまとめクラス
        class ImageBase{

            /// @class TextureParameter
            /// @param テクスチャの情報をまとめたクラス
            class TextureParameter{

                //----------------------------------------------------------
                // メンバ変数 
            private:
                /// @brief テクスチャの全体サイズ
                BaseWH<int>     mSize;
                /// @brief UVの指定範囲
                BaseUV<float>   mUV;
                /// @brief UV値の設定がintかfloatかの識別用フラグ
                bool            mUVint;

                //----------------------------------------------------------
                // 特殊メンバ関数
            public:
                /// @brief コンストラクタ
                TextureParameter():
                    mSize(), mUV(){} // 初期化子でメンバ変数を初期化

                /// @brief デストラクタ
                ~TextureParameter(){}

                //----------------------------------------------------------
                // メンバ関数
            public:

                //----------------------------------------
                // アクセサ

                /// @brief テクスチャのサイズを取得します。
                const BaseWH<int> size() const{
                    return mSize;
                }

                /// @brief テクスチャのサイズを設定します。
                /// @param a_Width テクスチャの幅
                /// @param a_Height テクスチャの高さ
                void setSize(const int a_Width, const int a_Height){
                    mSize.setWH(a_Width, a_Height);
                }


                /// @brief テクスチャのUV値を取得します。
                const BaseUV<float> UV() const{
                    return mUV;
                }


                /// @brief テクスチャのUV値を設定します。
                /// @param a_UV 設定するUV値
                void setUV(const BaseUV<float> a_UV){
                    mUV = a_UV;
                }

                /// @brief UV値の設定がintで行われたかどうかの状態を返します。
                /// @return bool UVの設定単位
                const bool isUVint() const{
                    return mUVint;
                }

                /// @brief UV値の設定の単位がintで行われたかどうかを設定します。
                /// @param a_Value int値でUVの設定が行われたかどうか 
                void setUVint(const bool a_Value){
                    mUVint = a_Value;
                }



            };


            //----------------------------------------------------------
            // 別名宣言

            /// @brief IDirect3DTexture9のスマートポインタ型
            typedef Com_ptr< IDirect3DTexture9 > Texture_sp;

            
            //----------------------------------------------------------
            // メンバ変数
        private:
            Texture_sp          mTexture;
            TextureParameter    mParameter;

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:
            /// @brief コンストラクタ
            ImageBase(){}

            /// @brief デストラクタ
            ~ImageBase(){}

            //----------------------------------------------------------
            // メンバ関数
        public:

            /// @brief テクスチャ実体を設定します。
            /// @param a_Texture テクスチャのスマートポインタ
            void setTexture(const Texture_sp a_Texture){
                mTexture = a_Texture;
                
                // テクスチャ(正確にはサーフェイス)のサイズを設定します。
                D3DSURFACE_DESC desc;
                mTexture->GetLevelDesc( 0, &desc );
                mParameter.setSize( desc.Width, desc.Height );
            }

            /// @brief テクスチャ実体を取得します。
            /// @return テクスチャのスマートポインタ
            const Texture_sp Texture() const{
                return mTexture;
            }

            /// @brief テクスチャのサイズを取得します。
            /// @return intのWHクラス
            const BaseWH<int> Size() const{
                return mParameter.size();
            }

            /// @brief テクスチャで使用するUV領域を設定します。
            /// @param 
            void setUV(const BaseUV<float> a_UV){
                mParameter.setUV(a_UV);
            }

            /// @brief テクスチャで設定するUV領域を取得します。
            /// @return 
            const BaseUV<float> getUV() const{
                return mParameter.UV();
            }

            /// @brief テクスチャで設定するUV領域の左上始点座標を取得します。
            /// @param a_Left 左辺のX座標が格納されます。
            /// @param a_Top　上辺のY座標が格納されます。
            void getUV_LT(float *a_Left, float *a_Top) const{
                auto value = mParameter.UV();
                *a_Left  = value.left();
                *a_Top = value.top();
            }

            /// @brief テクスチャで設定するUV領域の範囲を取得します。
            /// @param a_width   UVの幅が格納されます。
            /// @param a_height　UVの高さが格納されます。
            void getUV_WH(float *a_Width, float *a_Height) const{
                auto value = mParameter.UV();
                *a_Width  = value.width();
                *a_Height = value.height();
            }

            /// @brief UV値の設定がintで行われたかどうかの状態を返します。
            /// @return bool UVの設定単位
            const bool isUVint() const{
                return mParameter.isUVint();
            }

            /// @brief UV値の設定の単位がintで行われたかどうかを設定します。
            /// @param a_Value int値でUVの設定が行われたかどうか 
            void setUVint(const bool a_Value){
                mParameter.setUVint( a_Value );
            }


        };


    } // end of namespace Graphics
} // end of namespace GameLib
#endif