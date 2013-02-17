/// @file GraphicsManager.cpp
/// @brief 描画に関することを管理するマネージャークラス - Implリダイレクト
/// @note Implとインターフェイスによる継承を利用して描画デバイスの変更も対応可能。
/// @date 2011/10/18     tory

//====================================================================
//              GraphicsManager.cpp
//--------------------------------------------------------------------
//    処理内容 : 描画に関することを管理するマネージャークラス - Implリダイレクト
//    処理内容 : 
//    作成詳細 : 2011/10/18
//    補足     : Implとインターフェイスによる継承を利用して描画デバイスの変更も対応可能。
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 大幅なリファクタリングを実行
//    作成詳細 : 2012/12/18    tory
//         
//====================================================================

#include <Windows.h>                        // MessageBeepやウィンドウプロシージャなどの基本に必須
#include <memory>                           // unique_ptrなどに必要
#include <tiostream.h>                      // tstring型などのTCHAR拡張定義


#include "GraphicsManager.h"
#include "IGraphicsManagerImpl.h"
#include "GraphicsManagerImplDirect3D.hpp"

#include "Sprite.h"                         // Sprite初期化用

using namespace std;
using namespace GameLib::Graphics;

// 無名ネームスペース定義
namespace{
      
    /// @brief  実体クラスインスタンス
    /// @attention このインターフェイス用gImplに実体化したImplを継承させて使用する。
    /// @attention 通常使用する形式ではインターフェイスで公開されているメソッドのみを使用させる。
    shared_ptr< IGraphicsManagerImpl > gImpl( nullptr );


} // end of namespace

//----------------------------------------------------------
//----------------------------------------------------------

namespace GameLib{
    namespace Graphics{

        /// @brief  実体クラスインスタンス
        /// @attention このImplがアクセスした際の最終的な処理をするクラスである。
        /// @attention これは公開していないImplのpublicメソッドをexternで使用できるようにするためである。
        /// @attention モジュールから使用するため無名ネームスペースには隠ぺいしない。
        shared_ptr< ImplDirect3D > gImplDirect3D( nullptr );    


        /// @class InitManagers
        /// @brief 描画関係の各インスタンスの初期化だけを行う専用クラス
        /// @attention 外部から処理を隠ぺいしているためにこのような形となっている。
        class InitManagers{

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:
            /// @brief コンストラクタ
            InitManagers(){
            
                // スプライトを初期化
                Sprite sp;
                if(1){
                /**/sp.Create(true);
                }else{
                //**/
                    sp.Create(false);
                }
            }

            /// @brief デストラクタ
            ~InitManagers(){}
           
        };


        //----------------------------------------------------------
        // 特殊メンバ

        /// @brief コンストラクタ
        GraphicsManager::GraphicsManager(){}

        /// @brief デストラクタ
        GraphicsManager::~GraphicsManager(){}


        //----------------------------------------------------------
        // メンバ関数

        /// @brief インスタンスを作成します。
        /// @param a_HWND ウィンドウハンドル
        /// @param a_Width 描画領域のXサイズ
        /// @param a_Height 描画領域のYサイズ
        /// @param a_Fullscreen フルスクリーンフラグ
        /// @param a_Vsync 垂直同期フラグ
        /// @param a_AntiAlias アンチエイリアスフラグ
        /// @param a_Width2D 2D描画時の基準領域Xサイズ(=800)
        /// @param a_Height2D 2D描画時の基準領域Yサイズ(=600)
        void GraphicsManager::Create(
                const HWND a_HWND,
                const int a_Width,
                const int a_Height,
                const bool a_Fullscreen,
                const bool a_Vsync,
                const bool a_AntiAlias,
                const int a_Width2D,
                const int a_Height2D
            ){

            // 作成済みかどうかを確認する。
            if(gImpl != nullptr){
                MessageBox(NULL,_T("GraphicsManagerの実体を複数作成しようとしました。"),_T("インスタンス作成中止"),MB_OK);
                return;
            }
            
            // 問題なければ実体を作成
            // ここで作成するImplによって使用する描画デバイスが変わってくる。
            /// @todo ここで分岐を作り、DirectXやOpenGLなどで作成を切り替えられるようにする。
            gImplDirect3D.reset(new ImplDirect3D(
                a_HWND, a_Width, a_Height, a_Fullscreen, a_Vsync, a_AntiAlias, a_Width2D, a_Height2D )
                );

            // インターフェイスクラスに継承させる。
            // 普段はgImplを使用し、Implの公開してないpublic関数を使用するときはImplDirect3Dを使用する。            
            gImpl = static_pointer_cast<IGraphicsManagerImpl>(gImplDirect3D);
                

            // 作成済みであればその他の初期化も行う
            // この処理はクラスを1度作成するだけでよい
            if(gImpl != nullptr){
                InitManagers init;            
            }
        }

        /// @brief インスタンスを破棄します。
        void GraphicsManager::Destroy(){
            
            if(gImpl == nullptr){
                return;
            }
            gImpl.reset();
            gImplDirect3D.reset();
        }


        /// @brief 描画を開始します。
        void GraphicsManager::BeginDraw(){
            gImpl->BeginDraw();
        }

        /// @brief 描画を終了します。
        void GraphicsManager::EndDraw(){
            gImpl->EndDraw();
        }

        /// @brief フルスクリーン値などの変化を反映させるために
        /// @brief 現在のデバイスを破棄後、新たに再構築します。
        void GraphicsManager::RecreateDevice(){
            gImpl->RecreateDevice();
        }

        /// @brief 現在描画可能な状態かを確認します。
        /// @retval true 描画可能
        /// @retval false 描画不可能
        const bool GraphicsManager::isRenderable() const{
            return gImpl->isRenderable();   
        };

        /// @brief デバイスの復帰を試みます。
        /// @retval true 正常終了
        /// @retval false 異常終了
        const bool GraphicsManager::Restore(){
            return gImpl->Restore();
        }

        //----------------------------------------
        // アクセサ

        /// @brief  これまでのフレームカウントを取得します。
        /// @return フレームカウント
        const int GraphicsManager::getFrameCount() const{
            return gImpl->getFrameCount();
        }

        /// @brief フルスクリーンモードのフラグを設定し直します。
        /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
        void GraphicsManager::setFullScreen(const bool value){
            gImpl->setFullScreen( value );
        }

        /// @brief 垂直同期のフラグ値を設定し直します。
        /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
        void GraphicsManager::setVSync(const bool value){
            gImpl->setVSync( value );
        }

        /// @brief アンチエイリアスのフラグ値を設定し直します。
        /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
        void GraphicsManager::setAntialias(const bool value){
            gImpl->setAntialias( value );
        }

        /// @brief クライアントサイズを設定し直します。
        /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
        void GraphicsManager::setClientSize(const int a_Width, const int a_Height){
            gImpl->setClientSize( a_Width, a_Height );
        }

        /// @brief その他のManagerを初期化します。
        // void GraphicsManager::InitializeManager(){

            /// @todo LineやSpriteの基底データの初期化など
            //Sprite sp;
            //sp.Create(true);
        // }




    } // end of namespace Graphics
} // end of namespace GameLib