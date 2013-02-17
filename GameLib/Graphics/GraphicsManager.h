/// @file GraphicsManager.h
/// @brief 描画に関することを管理するマネージャークラス - 定義
/// @note Implとインターフェイスによる継承を利用して描画デバイスの変更も対応可能。
/// @date 2011/10/18     tory

//====================================================================
//              GraphicsManager.h
//--------------------------------------------------------------------
//    処理内容 : 描画に関することを管理するマネージャークラス - 定義
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

#ifndef INCLUDE_GAMELIB_GRAPHICS_MANAGER_H
#define INCLUDE_GAMELIB_GRAPHICS_MANAGER_H

namespace GameLib{
    namespace Graphics{

        /// @class GraphicsManager
        /// @brief 描画に関することを管理するマネージャークラス
        class GraphicsManager{

            //----------------------------------------------------------
            // メンバ変数
        private:

            //----------------------------------------------------------
            // 特殊メンバ
        public:

            /// @brief コンストラクタ
            GraphicsManager();

            /// @brief デストラクタ
            ~GraphicsManager();

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
            static void Create(
                const HWND a_HWND,
                const int a_Width,
                const int a_Height,
                const bool a_Fullscreen,
                const bool a_Vsync,
                const bool a_AntiAlias,
                const int a_Width2D = 800,
                const int a_Height2D = 600
                );

            /// @brief インスタンスを破棄します。
            static void Destroy();


            /// @brief 描画を開始します。
            void BeginDraw();

            /// @brief 描画を終了します。
            void EndDraw();

            /// @brief 現在描画可能な状態かを確認します。
            /// @retval true 描画可能
            /// @retval false 描画不可能
            const bool isRenderable() const;


            /// @brief フルスクリーン値などの変化を反映させるために
            /// @brief 現在のデバイスを破棄後、新たに再構築します。
            void RecreateDevice();

            /// @brief デバイスの復帰を試みます。
            /// @retval true 正常復帰完了
            /// @retval false 異常終了
            const bool Restore();

            //----------------------------------------
            // アクセサ


            /// @brief  これまでのフレームカウントを取得します。
            /// @return フレームカウント
            const int getFrameCount() const;

            /// @brief フルスクリーンモードのフラグを設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setFullScreen(const bool value);

            /// @brief 垂直同期のフラグ値を設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setVSync(const bool value);

            /// @brief アンチエイリアスのフラグ値を設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setAntialias(const bool value);

            /// @brief クライアントサイズを設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setClientSize(const int a_Width, const int a_Height);

            /// @brief その他のManagerを初期化します。
            // void InitializeManager();




        }; // end of class GraphicsManager

    } // end of namespace Graphics
} // end of namespace GameLib
#endif