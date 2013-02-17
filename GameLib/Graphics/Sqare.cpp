/// @file Sqare.cpp
/// @brief 指定色で矩形を描画するのに必要なテクスチャを管理するクラス - 実装
/// @note Sprite機能を使って描画を行います。
/// @date 2013/01/13     tory

//====================================================================
//              Sqare.cpp
//--------------------------------------------------------------------
//    処理内容 : 指定色で矩形を描画するのに必要なテクスチャを管理するクラス - 実装
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

#include "Sqare.h"
#include <memory>
#include "GraphicsManagerImplDirect3D.hpp"

// 無名ネームスペース定義
namespace{
      
    /// @brief  実体インスタンス
    /// @attention このgSqareTextureが実際のSqare用のテクスチャバッファである。
    Com_ptr < IDirect3DTexture9 > gSqareTexture;  ///< @brief Sqare用の白地テクスチャ
    
} // end of namespace

//----------------------------------------------------------
//----------------------------------------------------------



namespace GameLib{
    namespace Graphics{

        /// @brief  実体クラスインスタンスの外部参照
        extern shared_ptr< ImplDirect3D > gImplDirect3D;

        //----------------------------------------------------------
        // 特殊メンバ関数

        /// @brief コンストラクタ
        Sqare::Sqare(){
            // テクスチャを作成します
            Create( gSqareTexture );            
        }
        /// @brief デストラクタ
        Sqare::~Sqare(){}

        //----------------------------------------------------------
        // メンバ関数


        /// @brief デバイスロスト等に対応するため参照カウンタはそのままにSqare用のテクスチャを開放します。
        void Sqare::Backup(){            
            // 1度作成されたことがあるときはその先を開放する。
            if( gSqareTexture.getPtr() ) {
                Com_ptr<IDirect3DTexture9> cpTmp;
                gSqareTexture.Swap( cpTmp );
            }
        }

        /// @brief デバイスロストで開放していたSqare用テクスチャを再作成します。
        void Sqare::Recover(){
            // テクスチャを復活させる。
            Com_ptr<IDirect3DTexture9> cpTmp;
            Create( cpTmp );
            // 新しく作成したテクスチャと交換する。
            gSqareTexture.Swap( cpTmp );

        }
        //----------------------------------------
        // アクセサ
            
        /// @brief テクスチャの実体を取得します。
        Com_ptr < IDirect3DTexture9 > Sqare::texture() const{
            return gSqareTexture;
        }


        //----------------------------------------
        // ヘルパー関数

        /// @brief Sqare用のテクスチャを作成します。
        /// @a_Texture 指定したスマートポインタ先にSqare用テクスチャを作成します。
        /// @note 実体がすでにある場合は何も処理をしません。
        void Sqare::Create(Com_ptr < IDirect3DTexture9 >& a_Texture){

            // 作成されていないのならば
            if( a_Texture == nullptr ) {

                auto Device = gImplDirect3D->getDevice();

                // Sqare用の空テクスチャ領域を作成します。
                Device->CreateTexture( 1, 1, 0, D3DUSAGE_RENDERTARGET ,D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, a_Texture.ToCreator(), NULL);
                
                Com_ptr<IDirect3DSurface9> SqareSurface, backSurface;

                // 現在のバックバッファのサーフェイスを保持しておく。
                Device->GetRenderTarget(0, backSurface.ToCreator());

                // Sqare用テクスチャのサーフェイス取得
                a_Texture->GetSurfaceLevel(0, SqareSurface.ToCreator());
                // Sqare用のテクスチャにレンダリングターゲットを切り替える。
                Device->SetRenderTarget(0, SqareSurface.getPtr());

				// 白色を作成する。
                Device->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
                //Device->EndScene();
				//Device->BeginScene();

                // レンダリングターゲットを元のバックバッファに戻しておく。
                Device->SetRenderTarget(0, backSurface.getPtr());
            }
        }


    } // end of namespace Graphics
} // end of namespace GameLib
