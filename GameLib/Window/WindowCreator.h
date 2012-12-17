/// @file Window.h
/// @brief ウィンドウを作成する処理クラス - 定義
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              Window.h
//--------------------------------------------------------------------
//    処理内容 : ウィンドウを作成する処理 - 定義
//    処理内容 : 
//    作成詳細 : 2011/09/01
//    補足     : GameLib内の機能
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================

#include <tiostream.h>  // tstring型などのTCHAR拡張定義


#ifndef INCLUDE_GAMELIB_WINDOW_CREATOR_H
#define INCLUDE_GAMELIB_WINDOW_CREATOR_H


namespace GameLib{

    namespace Window{

        /// @class WindowCreator
        /// @brief ウィンドウの作成に関連するクラス
        class WindowCreator{

            //----------------------------------------------------------
            // 特殊メンバ
        public:

            /// @brief コンストラクタ
            WindowCreator();

            /// @brief デストラクタ
            virtual ~WindowCreator();


            //----------------------------------------------------------            
            // メンバ関数
        public: 

            /// @brief インスタンスを作成します。
            void Create();

            /// @brief ウィンドウを表示します。
            /// @attention 初期化されていない場合に自動でinit関数がコールされます。
            void Show() const;

            /// @brief ウィンドウメッセージを処理します。
            /// @attention 毎フレーム処理する必要があります。
            void Update() const;

            /// @brief プログラムに終了通知を確認します。
            const bool isEndRequested() const;

            /// @brief プログラムの終了を行います。
            void End() const;

            /// @brief フルスクリーンモードの設定をします。
            /// フルスクリーンにする場合はtrue指定にします。
            void FlagFullScreen( bool flag ) const;

            //----------------------------------------------------------           
            // アクセサ
        public:

            /// @brief 描画領域の幅を設定します。
            /// @param width 設定する幅
            void SetWidth( const int width );

            /// @brief 描画領域の高さを設定します。
            /// @param height 設定する高さ
            void SetHeight( const int height );

            /// @brief ウィンドウタイトルを設定します。
            /// @param title 設定する文字列
            void SetTitle( const std::tstring title );

            /// @brief ウィンドウアイコンを設定します。
            /// @param id アイコンのリソースID
            void SetIcon( const int id );

            //----------------------------------------------------------
            // プロパティ

            /// @brief ウィンドウハンドルを取得します。
            /// @return HWND ウィンドウハンドル
            const HWND handle() const;

            /// @brief ウィンドウがアクティブか確認します。
            /// @return bool アクティブ時はtrue、非アクティブ時にはfalseを返します。
            const bool isActive() const;

            /// @brief フルスクリーンモードか取得します。
            /// @return bool フルスクリーン時はtrue,ウィンドウ時はfalseを返します。
            const bool isFullScreen() const;

            /// @brief  ウィンドウが最小化されているかを確認します。
            /// @return bool true 最小化時はtrue、非最小化時はfalseを返します。
            const bool isMinimized() const;

            /// @brief クライアント領域の幅を取得します。
            /// @return int 設定した幅
            const int width() const;

            /// @brief クライアント領域の高さを取得します。
            /// @return int 設定した高さ
            const int height() const;

        }; // end of class L_WindowCreator

    } // end of namespace Window
} // end of namespace GameLib
#endif
