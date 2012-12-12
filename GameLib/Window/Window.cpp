/// @file window.cpp
/// @brief ウィンドウを作成する処理クラス - 実装
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              window.cpp
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

#include "window.h"


using namespace std;
using namespace GameLib::Window;


// プロトタイプ宣言
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


// 無名ネームスペース定義
namespace{

    //----------------------------------------------------------
    // 定数定義

    /// @brief ウィンドウタイトル
    const tstring WND_TITLE("GameApplication");
    /// @brief ウィンドウクラスネーム
    const tstring WND_CLASSNAME("GameApplication");
    /// @brief 規定のウィンドウスタイル
    const DWORD WND_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    /// @class Impl
    /// @brief 実体クラス
    class Impl
    {
        //----------------------------------------------------------
    public: // メンバ変数

        tstring mTitle;      ///< @brief ウィンドウタイトル
        tstring mClassName;  ///< @brief クラスネーム
        int mIconID;        ///< @brief アイコンID
        int mClientWidth;   ///< @brief 描画領域横幅
        int mClientHeight;  ///< @brief 描画領域縦幅
        int mWidth;         ///< @brief ウィンドウ横幅
        int mHeight;        ///< @brief ウィンドウ縦幅
        bool mActive;       ///< @brief ウィンドウのアクティブ
        bool mFullScreen;   ///< @brief フルスクリーンモード
        int mPositionX;     ///< @brief X位置
        int mPositionY;     ///< @brief Y位置
        bool mMinimized;    ///< @brief 最小化フラグ
        bool mEndRequested; ///< @brief ウィンドウ終了フラグ
        HWND mHandle;       ///< @brief ウィンドウハンドル
        bool mReady;        ///< @brief 準備完了フラグ
        DWORD mStyle;       ///< @brief ウィンドウスタイル

        //----------------------------------------------------------
    public: // 特殊メンバ

        /// @brief コンストラクタ
        Impl() :
            mTitle( WND_TITLE ),
            mClassName( WND_CLASSNAME ),
            mClientWidth( 1280 ),
            mClientHeight( 720 ),
            mWidth( 0 ),
            mHeight( 0 ),
            mIconID( 101 ),
            mActive( false ),
            mFullScreen( false ),
            mPositionX( 0 ),
            mPositionY( 0 ),
            mMinimized( false ),
            mEndRequested( false ),
            mHandle( NULL ),
            mReady( false ),
            mStyle( 0x0000 )
        {};



        /// @brief デストラクタ
        virtual ~Impl(){};


        //----------------------------------------------------------
    public: // メンバ関数
        
        /// @brief ウィンドウを表示します。
        /// @attention 初期化されていない場合、自動でinit関数がコールされます。
        void Show()
        {
            // 非初期化時にinitをコール
            if ( !mReady ){ 
                Init();
            }

            // プログラム開始時の指定をもとに表示
            STARTUPINFO info;
            GetStartupInfo( &info );
            ShowWindow( mHandle, info.wShowWindow );
            UpdateWindow( mHandle );
        }



        /// @brief ディスプレイモードを切り替えます。
        /// @param a_Flag trueでフルスクリーン、falseでウィンドウです。
        void EnableFullScreen( bool a_Flag ){

            // 今回設定する値
            DWORD style = WS_VISIBLE;
            int px = 0;
            int py = 0;
            int w = 0;
            int h = 0;

            // フラグがフルスクリーンONに切り替えの場合・・・
            if( a_Flag ){
                // 現在のウィンドウ位置を記録しておく
                RECT rect;
                GetWindowRect( mHandle, &rect );
                mPositionX = rect.left;
                mPositionY = rect.top;

                // フルスクリーンモード時の設定
                px = 0;
                py = 0;
                style |= WS_POPUP;
            }
            else
            {
                // ウィンドウモード自の位置を復帰
                px = mPositionX;
                py = mPositionY;
                // ウィンドウモード時の設定
                // const DWORD WND_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
                style |= WND_STYLE;
            }

            // ウィンドウスタイルとサイズを再設定
            mStyle = style;
            SetWindowSize( mStyle, mWidth, mHeight );

            // ウィンドウスタイルを修正
            SetWindowLong( mHandle, GWL_STYLE, mStyle );

            // 位置を移動
            SetWindowPos( mHandle, HWND_NOTOPMOST, px, py, mWidth, mHeight, SWP_SHOWWINDOW );

            // ウィンドウを更新
            UpdateWindow( mHandle );

            // フラグを再設定
            mFullScreen = a_Flag;
        }



        /// @brief ウィンドウの終了を通知します。
        void EndRequest(){
            mEndRequested = true;
        }



        /// @brief ウィンドウメッセージを処理します。
        /// @note 毎フレーム処理する必要があります
        void Update()
        {
            MSG msg;

            // ウィンドウメッセージがあった場合それを処理する
            if( PeekMessage( &msg, 0, 0, 0, PM_NOREMOVE ) ){
                if( GetMessage( &msg, 0, 0, 0 ) ){
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                } else {
                    // メッセージの取得に失敗したらプログラムを終了する
                    // ESCやその他のメッセージなどでウィンドウが消えた場合
                    mEndRequested = true;
                }
            }
        }



        /// @brief ローカルウィンドウプロシージャ
        /// @param hWnd ウィンドウハンドル
        /// @param msg メッセージフラグ
        /// @param wparam パラメータ１
        /// @param lparam パラメータ２
        /// @return LRESULT 処理結果
        /// @note ウィンドウメッセージを処理します。
        LRESULT LocalWndProc( HWND hWnd, UINT msg, DWORD wParam, DWORD lParam )
        {
            // 各メッセージに対応した処理を行う
            switch ( msg ){
            case WM_ACTIVATE:
                // ウィンドウがアクティブか確認して設定
                mActive = ( wParam ? true : false );
                break;

            case WM_CLOSE:
                // メインウィンドウが破棄される直前に終了通知
                EndRequest();
                break;

            case WM_DESTROY:
                // ウィンドウが破棄された段階で
                // システムにアプリケーションの終了を通知
                PostQuitMessage( 0 );
                break;

            case WM_KEYDOWN:
                switch( wParam ){
                case VK_ESCAPE: // ESCで終了
                    EndRequest();
                    PostQuitMessage( 0 );
                    break;

                case VK_F11: // F11で全画面表示
                   EnableFullScreen( !mFullScreen );
                    break;

                default:
                    break;
                }
                break;  
            }

            // 定義外のウィンドウメッセージの場合、OSに丸投げする
            return DefWindowProc( hWnd, msg, wParam, lParam );
        }


        //----------------------------------------------------------
    private:// ヘルパ関数
        
        /// @brief ウィンドウ設定を初期化します。
        void Init()
        {
            // 初期化済みの場合に例外
            if ( mReady )
            {
                // 多重初期化されました
                 MessageBox(NULL,_T("多重初期化を実行しようとしました。"),_T("情報"),MB_OK|MB_ICONHAND);
            }

                // ウィンドウクラスを登録
                RegisterWndClass( mClassName );

                // 表示するウィンドウの設定
                InitWindow();


            // 初期化完了時にフラグを立てる
            mReady = true;
        }



        /// @brief ウィンドウクラスを登録します。
        /// @param classname　ウィンドウタイトル
        void RegisterWndClass( const tstring classname ){

            WNDCLASSEX wc;

            wc.cbSize         = sizeof( WNDCLASSEX );         // クラスサイズ
            wc.style          = CS_HREDRAW | CS_VREDRAW;      // スタイル(ウィンドウサイズ変更時に再描画)
            wc.lpfnWndProc    = ::WndProc;                    // 使用するウィンドウプロシージャ
            wc.cbClsExtra     = NULL;                         // 拡張領域１
            wc.cbWndExtra     = NULL;                         // 拡張領域２
            wc.hInstance      = GetModuleHandle( 0 );         // 使用するモジュールハンドル
            wc.hCursor        = LoadCursor( 0, IDC_ARROW );   // カーソル 
            wc.hbrBackground  = ( HBRUSH )GetStockObject( BLACK_BRUSH );    // バックグラウンド色
            wc.lpszMenuName   = NULL;                         // 使用する場合はメニューの識別名称
            wc.lpszClassName  = classname.c_str();            // 識別ウィンドウクラス名
            wc.hIcon          = NULL;                         // アイコン指定
            wc.hIconSm        = NULL;                         // SmallIcon、NULLだとIconを強制縮小したのを使う

            if ( !RegisterClassEx( &wc) ){
                // 登録できなかった場合に例外を投げる
                // 『ウィンドウクラスの登録に失敗しました。』
                MessageBox(NULL,_T("ウィンドウクラスの登録に失敗しました。"),_T("読み込み失敗"),MB_OK|MB_ICONHAND);
            }
        }



        /// @brief ウィンドウサイズを計算し結果を格納します。
        /// @param style 対象のウィンドウスタイル
        /// @param width 横幅
        /// @param height縦幅
        /// @note  mClientWidthとmClientHeightをもとに算出します。
        void SetWindowSize( DWORD a_style, int& a_width, int& a_height ){

            // フレームを考慮したウィンドウサイズを計算し
            // 描画領域に使用したいサイズを設定する
            RECT rect;
            SetRect( &rect, 0, 0, mClientWidth, mClientHeight );

            AdjustWindowRect( &rect, a_style, false );
            rect.right -= rect.left;        // (描画領域+右縁)に(描画X始点-左縁位置)までのマイナス距離分を足す
            rect.bottom -= rect.top;        // (描画領域+下縁etc)に(描画Y始点-上タイトル位置)までのマイナス距離分を足す
            rect.left = 0;
            rect.top = 0;


            // サイズを記録
            a_width = rect.right;
            a_height = rect.bottom;
        }
        

        
        /// @brief  ウィンドウの初回表示位置を設定します。
        void InitWindowPos(){

            DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
            int w = 0;
            int h = 0;
            SetWindowSize( style, w, h );
            
            //デスクトップ中央に表示するよう調整する
            mPositionX = ( GetSystemMetrics( SM_CXSCREEN ) - w ) / 2;
            mPositionY = ( GetSystemMetrics( SM_CYSCREEN ) - h ) / 2;
        }

        
        
        /// @brief 表示するウィンドウを設定します。
        void InitWindow(){

            // ウィンドウモード時の初回表示位置を設定
            InitWindowPos();

            // フルスクリーン有効時にWS_POPUP
            mStyle = ( mFullScreen ? WS_POPUP : WND_STYLE );
            
            // ウィンドウサイズを算出して格納
            SetWindowSize( mStyle, mWidth, mHeight );

            // 表示位置を設定
            int x = ( mFullScreen ? 0 : mPositionX );
            int y = ( mFullScreen ? 0 : mPositionY );

            // ウィンドウを作成してハンドルを格納
            HWND hWnd = NULL;

            hWnd = CreateWindow(
                mClassName.c_str(),
                mTitle.c_str(),
                mStyle,
                x,
                y,
                mWidth,
                mHeight,
                NULL,
                NULL,
                GetModuleHandle( NULL ),
                NULL
                );

            if ( !hWnd )
            {
                // 失敗時( hWnd = NULL )に例外
                MessageBox(NULL,_T("Windowの作成に失敗しました。\n実行を中止します。"),_T("作成中止"),MB_OK);
                // 終了を通知
                EndRequest();
                return;
            }

            // ハンドルを記録
             mHandle = hWnd;
        }


    };

    /// @brief  実体クラスインスタンス
    /// @attention このgImplがアクセスした際の最終的な処理をするクラスである。
    unique_ptr< Impl > gImpl;
    
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
            if( gImpl.get() != NULL){
                ::MessageBeep(MB_ICONASTERISK);
                MessageBox(NULL,_T("WindowCreatorの実体を複数作成しようとしました。"),_T("インスタンス作成中止"),MB_OK);
                return;
            }
            
            // 問題なければ実体を作成
            gImpl.reset(new Impl() );

        }

        /// @brief ウィンドウを表示します。
        void WindowCreator::Show(){
            gImpl->Show();
        }

        /// @brief ウィンドウメッセージを処理します。
        /// @attention 毎フレーム処理する必要あり！
        void WindowCreator::Update(){
            gImpl->Update();
        }

        /// @brief プログラムに終了通知をします。
        const bool WindowCreator::CheckEndRequested() const{
            return gImpl->mEndRequested;
        }

        /// @brief フルスクリーンモードの指定
        /// @brief フルスクリーンにする場合はtrueを指定する
        void WindowCreator::FlagFullScreen( bool flag ){
            gImpl->EnableFullScreen( flag );
        }

        //----------------------------------------------------------
        // アクセサ

        /// @brief 描画領域の幅を設定する。
        /// @param width 設定する描画領域の幅
        void WindowCreator::SetWidth(const int width ){
            gImpl->mClientWidth = width;
            
            // すでに作成されていたら
            if( gImpl->mHandle ){
                // 位置を調整しなおす。
                gImpl->EnableFullScreen(gImpl->mFullScreen);
            }
        }

        /// @brief 描画領域の高さを設定する。
        /// @param height 設定する描画領域の高さ
        void WindowCreator::SetHeight( const int height ){
            gImpl->mClientHeight = height;

            // すでに作成されていたら
            if( gImpl->mHandle ){
                // 位置を調整しなおす。
                gImpl->EnableFullScreen(gImpl->mFullScreen);
            }
        }

        /// @brief ウィンドウタイトルを設定する。
        /// @param title 設定する文字列
        void WindowCreator::SetTitle( const std::tstring title ){
            gImpl->mTitle = title;
        
            // ウィンドウ作成済みの場合はテキストを変更
            if( gImpl->mHandle ){
                SetWindowText( gImpl->mHandle, title.c_str() );
            }
        }

        /// @brief ウィンドウアイコンを設定する。
        /// @param id アイコンのリソースID
        void WindowCreator::SetIcon( const int id ){
            gImpl->mIconID = id;

            // ウィンドウ作成済みの場合は続けてアイコンを変更
            if( gImpl->mHandle ){
                HICON icon = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( id ) );
                SetClassLong( gImpl->mHandle, GCL_HICON, reinterpret_cast< LONG >( icon ) );
            }
        }

        /// @brief ウィンドウハンドルを取得する。
        /// @return HWND ウィンドウハンドル
        const HWND WindowCreator::GetHandle() const{
            return gImpl->mHandle;
        }


        /// @brief クライアント領域の幅を取得します。
        /// @return int 設定した幅
        const int WindowCreator::GetWidth() const{
            return gImpl->mClientWidth;
        }

        /// @brief クライアント領域の高さを取得します。
        /// @return int 設定した高さ
        const int WindowCreator::GetHeight() const{
            return gImpl->mClientHeight;
        }




        /// @brief ウィンドウがアクティブかを確認する。
        /// @return bool アクティブ時にtrue、非アクティブ時にfalse
        const bool WindowCreator::CheckActive() const{
            return gImpl->mActive;
        }

        /// @brief フルスクリーンモードか取得します。
        /// @return bool フルスクリーン時はtrue、ウィンドウ時はfalseを返します。
        const bool WindowCreator::CheckFullScreen() const{
            return gImpl->mFullScreen;
        }

    }
}






