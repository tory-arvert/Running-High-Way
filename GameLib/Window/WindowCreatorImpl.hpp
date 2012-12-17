/// @file WindowImpl.hpp
/// @brief ウィンドウを作成する処理クラス - 実装
/// @note 
/// @date 2012/12/17     tory

//====================================================================
//              WindowImpl.hpp
//--------------------------------------------------------------------
//    処理内容 : ウィンドウを作成する処理 - 実装
//    処理内容 : 
//    作成詳細 : 2012/12/17
//    補足     : 
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2011/09/01     tory
//         
//====================================================================


#ifndef INCLUDE_GAMELIB_WINDOW_CREATOR_IMPL_H
#define INCLUDE_GAMELIB_WINDOW_CREATOR_IMPL_H

#include <Windows.h>

#include <tiostream.h>
#include <TemplateBaseClass.h>


//----------------------------------------
// プロトタイプ宣言

/// @brief  メインウィンドウのプロシージャ
/// @param  hWnd ウィンドウハンドル
/// @param  msg メッセージフラグ
/// @param  wParam パラメータ1
/// @param  lParam パラメータ2
/// @note   WindowCreator.cppで実装
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


namespace GameLib{

    using namespace std;

    namespace Window{

        //----------------------------------------------------------
        // 定数定義

        /// @brief ウィンドウタイトル
        const tstring WND_TITLE("GameApplication");
        /// @brief ウィンドウクラスネーム
        const tstring WND_CLASSNAME("GameApplication");
        /// @brief 規定のウィンドウスタイル
        const DWORD WND_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;



        /// @class WindowStatesFlag
        /// @brief ウィンドウの状態フラグに関するものを集めたクラス
        class WindowStatesFlag{

            //----------------------------------------------------------
            // メンバ変数
        private:
            bool mActive;               ///< @brief ウィンドウのアクティブ
            bool mFullScreen;           ///< @brief フルスクリーンモード
            bool mMinimized;            ///< @brief 最小化フラグ
            bool mEndRequested;         ///< @brief ウィンドウ終了フラグ
            bool mReady;                ///< @brief 準備完了フラグ

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            WindowStatesFlag::WindowStatesFlag():
                mActive( false ),
                mFullScreen( false ),
                mMinimized( false ),
                mReady( false ),
                mEndRequested( false )            
            {};
        
            /// @brief デストラクタ
            WindowStatesFlag::~WindowStatesFlag(){};

            //----------------------------------------------------------
            // メンバ関数
        public:

            /// @brief アクティブ状態をセットします
            void setActive(const bool a_flag){
                mActive = a_flag;
            }

            /// @brief フルスクリーンフラグをセットします
            void setFullScreen(const bool a_flag){
                mFullScreen = a_flag;
            }

            /// @brief 最小化フラグをセットします
            void setMinimized(const bool a_flag){
                mMinimized = a_flag;
            }

            /// @brief ウィンドウ終了フラグをセットします
            void setEndRequested(const bool a_flag){
                mEndRequested = a_flag;
            }

            /// @brief 準備完了フラグをセットします
            void setReady( const bool a_flag){
                mReady = a_flag;
            }

            //----------------------------------------------------------
            // プロパティ
        public:

            /// @brief ウィンドウのアクティブ状態のフラグ値を返します。
            const bool active() const{return mActive;}
            
            /// @brief 現在のフルスクリーンモードのフラグ値を返します。
            const bool fullScreen() const{return mFullScreen;}

            /// @brief 現在の最小化フラグ値を返します。
            const bool minimized() const{return mMinimized;}

            /// @brief 現在のウィンドウ終了フラグ値を返します。
            const bool endRequested() const{return mEndRequested;}

            /// @brief 現在の準備完了フラグ値を返します。
            const bool ready() const{return mReady;}


        }; // end of class WindowStatesFlag

        //----------------------------------------------------------
        //----------------------------------------------------------

        /// @class WindowInfo
        /// @brief ウィンドウ表示における識別情報をまとめたクラス
        class WindowInfo{
            //----------------------------------------------------------
            // メンバ変数
        private:
            tstring mTitle;             ///< @brief ウィンドウタイトル        
            tstring mClassName;         ///< @brief クラスネーム
            int mIconID;                ///< @brief アイコンID
            HWND mHandle;               ///< @brief ウィンドウハンドル
            DWORD mStyle;               ///< @brief ウィンドウスタイル

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            WindowInfo():
                mTitle( WND_TITLE ),
                mClassName( WND_CLASSNAME ),
                mIconID( 0 ),
                mHandle( NULL ),
                mStyle( 0x0000 )
            {};

            /// @brief デストラクタ
            ~WindowInfo(){};

            //----------------------------------------------------------
            // メンバ変数
        public:

            /// @brief タイトル情報を設定します。
            void setTitle(const tstring a_title){
                mTitle = a_title;
            }

            /// @brief クラスネーム情報を設定します。
            void setClassName(const tstring a_className){
                mClassName = a_className;
            }

            /// @brief アイコンID番号を設定します。
            void setIconID(const int a_value){
                mIconID = a_value;
            }

            /// @brief ウィンドウハンドルを設定します。
            void setHandle(const HWND a_handle){
                mHandle = a_handle;
            }

            /// @brief ウィンドウスタイルを設定します。
            void setStyle(const DWORD a_style){
                mStyle = a_style;
            }


            //----------------------------------------------------------
            // プロパティ
        public:

            /// @brief タイトル名を取得します。
            const tstring title() const{return mTitle;}

            /// @brief クラスネームを取得します。
            const tstring className() const{return mClassName;}

            /// @brief アイコンIDの番号を取得します。
            const int iconID() const{return mIconID;}

            /// @brief 設定してあるウィンドウハンドルを取得します。
            const HWND handle() const{return mHandle;}

            /// @brief 設定してあるウィンドウスタイルを取得します。
            const DWORD style() const{return mStyle;}

        }; // end of class WindowInfo




        /// @class WindowCreator
        /// @brief WindowCreator実装クラス
        class WindowCreatorImpl{
            //----------------------------------------------------------
            // プロトタイプ宣言

            //----------------------------------------------------------
            // メンバ変数
        private:
            WindowInfo mWindowInfo;     ///< @brief ウィンドウ識別情報クラス

            BaseWH<int> mClientSize;    ///< @brief 描画領域サイズ
            BaseWH<int> mWindowSize;    ///< @brief ウィンドウサイズ
            BaseXY<int> mPosition;      ///< @brief ウィンドウ位置

            WindowStatesFlag mStatesFlag;   /// @brief 状態フラグ

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:

            /// @brief コンストラクタ
            WindowCreatorImpl():
                mWindowInfo(),
                mClientSize( 1280, 720 ),
                mWindowSize(),
                mPosition(),
                mStatesFlag()
            {};

            /// @brief デストラクタ
            ~WindowCreatorImpl(){};

            //----------------------------------------------------------
            // メンバ関数
        public:

            /// @brief ウィンドウを初期化します。
            void Initialize(){
                // 初期化済みの場合に例外
                if ( mStatesFlag.ready() )
                {
                    // 多重初期化されました
                     MessageBox(NULL,_T("多重初期化を実行しようとしました。"),_T("情報"),MB_OK|MB_ICONHAND);
                }

                // ウィンドウクラスを登録
                RegisterWndClass( mWindowInfo.className() );

                // 表示するウィンドウの設定
                InitWindowInfo();


                // 初期化完了時にフラグを立てる
                mStatesFlag.setReady( true );
            }


            /// @brief ウィンドウを表示します。
            /// @attention 初期化されていない場合、自動でInitialize関数がコールされます。
            void Show()
            {
                // 非初期化時にinitをコール
                if ( !mStatesFlag.ready() ){ 
                    Initialize();
                }

                // vistual Studio 2012のバグのため
                // GetStartupInfoで正常にshowCmd値が取得できないので
                // 別の方法でshowCmd値を取得しています。
                WINDOWPLACEMENT info;
                info.length = sizeof(WINDOWPLACEMENT);
                GetWindowPlacement( mWindowInfo.handle(), &info );
                
                // プログラム開始時の指定をもとに表示
                if(info.showCmd = SW_MAXIMIZE){
                    // 設定されたStyleにて最大化が有効な時は最大化する。
                    ShowWindow( mWindowInfo.handle(), SW_RESTORE );
                }else{
                    // それ以外(ショートカットなどで最大化指定)の時は無視する。
                    ShowWindow( mWindowInfo.handle(), info.showCmd  );
                }

                // ウィンドウが最小化の状態かどうか取得する。
                CheckMinimized();


                // ウィンドウを更新する。
                UpdateWindow( mWindowInfo.handle() );
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

                // フルスクリーンフラグの状態に合わせウィンドウ位置を記録、または読込する。
                a_Flag ? SaveWindowPosition(&px, &py, &style) : LoadWindowPosition(&px, &py, &style);

                // ウィンドウスタイルとサイズを再設定
                mWindowInfo.setStyle(style);
                CalculationWindowSize( mWindowInfo.style(), &w, &h );
                mWindowSize.setWH( w, h );

                // ウィンドウスタイルを修正
                SetWindowLong( mWindowInfo.handle(), GWL_STYLE, mWindowInfo.style() );

                // 位置を移動
                SetWindowPos( mWindowInfo.handle(), HWND_NOTOPMOST, px, py,  mWindowSize.width(), mWindowSize.height(), SWP_SHOWWINDOW );

                // ウィンドウを更新
                UpdateWindow(mWindowInfo.handle() );

                // フラグを再設定
                mStatesFlag.setFullScreen( a_Flag );
            }

            /// @brief ウィンドウの終了を通知します。
            void EndRequest(){
                mStatesFlag.setEndRequested( true );
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
                        mStatesFlag.setEndRequested( true );
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
                    mStatesFlag.setActive( wParam ? true : false );
                    break;

                case WM_CLOSE:
                    // メインウィンドウが破棄される直前に終了通知
                    EndRequest();
                    break;

                case WM_SIZE:
                    // ウィンドウサイズに変更があったとき
                    CheckMinimized();
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
                        EnableFullScreen( !mStatesFlag.fullScreen() );
                        break;

                    default:
                        break;
                    }
                    break;  
                }

                // 定義外のウィンドウメッセージの場合、OSに丸投げする
                return DefWindowProc( hWnd, msg, wParam, lParam );
            }

            /// @brief 描画領域サイズのwidthを設定します。
            void setClientWidth(const int a_width){
                mClientSize.setWidth( a_width );
            }

            /// @brief 描画領域サイズのheightを設定します。
            void setClientHeight(const int a_height){
                mClientSize.setHeight( a_height );
            }

            /// @brief ウィンドウタイトルを設定します。
            void setTitle(const tstring a_title){
                mWindowInfo.setTitle( a_title );
            }

            /// @brief ウィンドウアイコンを設定します。
            void setIcon( const int a_id ){
                mWindowInfo.setIconID( a_id );
            }


            //----------------------------------------------------------
            // プロパティ
        public:

            /// @brief 描画領域サイズのwidthを設定します。
            const int clientWidth(){
                return mClientSize.width();
            }

            /// @brief 描画領域サイズのheightを設定します。
            const int clientHeight(){
                return mClientSize.height();
            }

            /// @brief 現在のウィンドウハンドル値を取得します。
            const HWND handle(){
                return mWindowInfo.handle();
            }

            /// @brief 現在のウィンドウがアクティブかどうかのフラグ値を取得します。
            const bool isActive(){
                return mStatesFlag.active();
            }

            /// @brief 現在のフルスクリーンのフラグ値を取得します。
            const bool isFullScreen(){
                return mStatesFlag.fullScreen();
            }

            /// @brief ウィンドウの最小化フラグ値を取得します。
            const bool isMinimized(){
                return mStatesFlag.minimized();
            }

            /// @brief 現在のウィンドウ終了フラグ値(終了通知)を取得します。
            const bool isEndRequest(){
                return mStatesFlag.endRequested();
            }

            //----------------------------------------------------------
            // ヘルパー関数

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
            /// @param height 縦幅
            /// @note  mClientWidthとmClientHeightをもとに算出します。
            void CalculationWindowSize(const DWORD a_style, int* a_width, int* a_height ){

                // フレームを考慮したウィンドウサイズを計算し
                // 描画領域に使用したいサイズを設定する
                RECT rect;
                SetRect( &rect, 0, 0, mClientSize.width(), mClientSize.height() );

                AdjustWindowRect( &rect, a_style, false );
                rect.right -= rect.left;        // (描画領域+右縁)に(描画X始点-左縁位置)までのマイナス距離分を足す
                rect.bottom -= rect.top;        // (描画領域+下縁etc)に(描画Y始点-上タイトル位置)までのマイナス距離分を足す
                rect.left = 0;
                rect.top = 0;


                // サイズを記録
                (*a_width) = rect.right;
                (*a_height) = rect.bottom;
            }

            /// @brief  ウィンドウの初回表示位置を設定します。
            void InitWindowPosition(){

                DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
                int w = 0;
                int h = 0;
                CalculationWindowSize( style, &w, &h );
            
                //デスクトップ中央に表示するよう調整する
                mPosition.setX( ( GetSystemMetrics( SM_CXSCREEN ) - w ) / 2);
                mPosition.setY( ( GetSystemMetrics( SM_CYSCREEN ) - h ) / 2);
            }


            
            /// @brief 表示するウィンドウの情報を初期化設定します。
            void InitWindowInfo(){

                // ウィンドウモード時の初回表示位置を設定
                InitWindowPosition();

                // フルスクリーン有効時にWS_POPUP
                mWindowInfo.setStyle ( mStatesFlag.fullScreen() ? WS_POPUP : WND_STYLE );
            
                int w = 0;
                int h = 0;
                // ウィンドウサイズを算出して格納
                CalculationWindowSize( mWindowInfo.style(), &w, &h );
                mWindowSize.setWH( w, h );

                // 表示位置を設定
                int x = ( mStatesFlag.fullScreen() ? 0 : mPosition.x() );
                int y = ( mStatesFlag.fullScreen() ? 0 : mPosition.y() );

                // ウィンドウを作成してハンドルを格納
                HWND hWnd = NULL;

                hWnd = CreateWindow(
                    mWindowInfo.className().c_str(),
                    mWindowInfo.title().c_str(),
                    mWindowInfo.style(),
                    x,
                    y,
                    mWindowSize.width(),
                    mWindowSize.height(),
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
                mWindowInfo.setHandle( hWnd );
            }




            /// @brief フルスクリーン切替に際して現在のウィンドウ位置を記録します。
            void SaveWindowPosition(int* a_x, int* a_y, DWORD* a_style){
                // 現在のウィンドウ位置を記録しておく
                RECT rect;
                GetWindowRect( mWindowInfo.handle(), &rect );
                mPosition.setXY(rect.left, rect.top);

                // フルスクリーンモード時の設定
                *a_x = 0;
                *a_y = 0;
                *a_style |= WS_POPUP;
            }

            /// @brief フルスクリーン切替に際して前回のウィンドウ位置を読み込みます。
            void LoadWindowPosition(int* a_x, int* a_y, DWORD* a_style){
                // ウィンドウモード自の位置を復帰
                (*a_x) = mPosition.x();
                (*a_y) = mPosition.y();
                // ウィンドウモード時の設定(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
                (*a_style) |= WND_STYLE;

            }

            /// @brief 現在のウィンドウの最小化の状態をフラグ値に設定します。
            void CheckMinimized(){
                WINDOWPLACEMENT info;
                info.length = sizeof(WINDOWPLACEMENT);
                GetWindowPlacement( mWindowInfo.handle(), &info );

                switch ( info.showCmd ){                
                case SW_SHOWNORMAL:     // 普通の状態
                    mStatesFlag.setMinimized( false );
                    break;

                case SW_SHOWMINIMIZED:  // 最小化の状態
                    mStatesFlag.setMinimized( true );
                    break;

                case SW_SHOWMAXIMIZED:  // 最大化の状態
                    mStatesFlag.setMinimized( false );
                    break;

                default:        // その他の処理(エラー時などは終了する)
                    EndRequest();
                }
            }




        }; // end of class WindowCreatorImpl



    } // end of namespace Window
} // end of namespace GameLib
#endif