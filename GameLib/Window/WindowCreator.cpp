/// @file Window.cpp
/// @brief ウィンドウを作成する処理クラス - 実装
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              Window.cpp
//--------------------------------------------------------------------
//    処理内容 : ウィンドウを作成する処理 - 実装
//    処理内容 : 
//    作成詳細 : 2011/09/01
//    補足     : 
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2011/09/01     tory
//         
//====================================================================


#include <Windows.h>                        // MessageBeepやウィンドウプロシージャなどの基本に必須
#include <memory>                           // unique_ptrなどに必要
#include <tiostream.h>                      // tstring型などのTCHAR拡張定義

#include "WindowCreator.h"
#include "WindowCreatorImpl.hpp"


using namespace std;
using namespace GameLib::Window;



// 無名ネームスペース定義
namespace{
      
    /// @brief  実体クラスインスタンス
    /// @attention このgImplがアクセスした際の最終的な処理をするクラスである。
    unique_ptr< WindowCreatorImpl > gImpl( nullptr );
    
} // end of namespace

//----------------------------------------------------------
//----------------------------------------------------------


/// @brief  メインウィンドウのプロシージャ
/// @param  hWnd ウィンドウハンドル
/// @param  msg メッセージフラグ
/// @param  wparam パラメータ１
/// @param  lparam パラメータ２
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    // 実体内のウィンドウプロシージャにリダイレクト
    return gImpl->LocalWndProc( hWnd, msg, wParam, lParam );
}


//----------------------------------------------------------

namespace GameLib{

    namespace Window{

        //----------------------------------------------------------
        // 特殊メンバ

        /// @brief コンストラクタ
        WindowCreator::WindowCreator(){}

        /// @brief デストラクタ
        WindowCreator::~WindowCreator(){}

       
        //----------------------------------------------------------
        // メンバ関数

        /// @brief インスタンスを作成します。
        void WindowCreator::Create(){

            // 作成済みかどうかを確認する。
            if(gImpl != nullptr){
                MessageBox(NULL,_T("WindowCreatorの実体を複数作成しようとしました。"),_T("インスタンス作成中止"),MB_OK);
                return;
            }
            
            // 問題なければ実体を作成
            gImpl.reset(new WindowCreatorImpl() );

        }

        /// @brief ウィンドウを表示します。
        void WindowCreator::Show() const{
            gImpl->Show();
        }

        /// @brief ウィンドウメッセージを処理します。
        /// @attention 毎フレーム処理する必要あり！
        void WindowCreator::Update() const{
            gImpl->Update();
        }

        /// @brief プログラムに終了通知を確認します。
        const bool WindowCreator::isEndRequested() const{
            return gImpl->isEndRequest();
        }

        /// @brief プログラムの終了を行います。
        void WindowCreator::End() const{
            gImpl->EndRequest();
        }


        /// @brief フルスクリーンモードの指定
        /// @brief フルスクリーンにする場合はtrueを指定する
        void WindowCreator::FlagFullScreen( bool flag ) const{
            gImpl->EnableFullScreen( flag );
        }

        //----------------------------------------------------------
        // アクセサ

        /// @brief 描画領域の幅を設定する。
        /// @param width 設定する描画領域の幅
        void WindowCreator::SetWidth(const int a_width ){
            gImpl->setClientWidth( a_width );
            
            // すでに作成されていたら
            if( gImpl->handle() ){
                // 位置を調整しなおす。
                gImpl->EnableFullScreen(gImpl->isFullScreen() );
            }
        }

        /// @brief 描画領域の高さを設定する。
        /// @param height 設定する描画領域の高さ
        void WindowCreator::SetHeight( const int a_height ){
            gImpl->setClientHeight( a_height );

            // すでに作成されていたら
            if( gImpl->handle() ){
                // 位置を調整しなおす。
                gImpl->EnableFullScreen(gImpl->isFullScreen());
            }
        }

        /// @brief ウィンドウタイトルを設定する。
        /// @param title 設定する文字列
        void WindowCreator::SetTitle( const std::tstring title ){
            gImpl->setTitle( title );
        
            // ウィンドウ作成済みの場合はテキストを変更
            if( gImpl->handle() ){
                SetWindowText( gImpl->handle(), title.c_str() );
            }
        }

        /// @brief ウィンドウアイコンを設定する。
        /// @param id アイコンのリソースID
        void WindowCreator::SetIcon( const int id ){
            gImpl->setIcon( id );

            // ウィンドウ作成済みの場合は続けてアイコンを変更
            if( gImpl->handle() ){
                HICON icon = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( id ) );
                SetClassLong( gImpl->handle(), GCL_HICON, reinterpret_cast< LONG >( icon ) );
            }
        }

        //----------------------------------------------------------
        // プロパティ

        /// @brief ウィンドウハンドルを取得する。
        /// @return HWND ウィンドウハンドル
        const HWND WindowCreator::handle() const{
            return gImpl->handle();
        }

        /// @brief ウィンドウがアクティブかを確認する。
        /// @return bool アクティブ時にtrue、非アクティブ時にfalse
        const bool WindowCreator::isActive() const{
            return gImpl->isActive();
        }

        /// @brief フルスクリーンモードか取得します。
        /// @return bool フルスクリーン時はtrue、ウィンドウ時はfalseを返します。
        const bool WindowCreator::isFullScreen() const{
            return gImpl->isFullScreen();
        }

        /// @brief  ウィンドウが最小化されているかを確認します。
        /// @return bool true 最小化時はtrue、非最小化時はfalseを返します。
        const bool WindowCreator::isMinimized() const
        {
            return gImpl->isMinimized();
        }

        
        /// @brief クライアント領域の幅を取得します。
        /// @return int 設定した幅
        const int WindowCreator::width() const{
            return gImpl->clientWidth();
        }

        /// @brief クライアント領域の高さを取得します。
        /// @return int 設定した高さ
        const int WindowCreator::height() const{
            return gImpl->clientHeight();
        }





    }
}






