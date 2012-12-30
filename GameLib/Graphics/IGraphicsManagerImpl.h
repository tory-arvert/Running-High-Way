/// @file IGraphicsManagerImpl.h
/// @brief 描画に関することを管理するマネージャークラスのImpl用インターフェイス
/// @note 各描画デバイスのImplを作成するときはこのインターフェイスクラスを継承する。
/// @date 2012/12/18     tory

//====================================================================
//              IGraphicsManagerImpl.h
//--------------------------------------------------------------------
//    処理内容 : 描画に関することを管理するマネージャークラス用Implのインターフェイス
//    処理内容 : 
//    作成詳細 : 2012/12/18
//    補足     : 各描画デバイスのImplを作成するときは
//    補足     : このインターフェイスクラスを継承すること。
//
//    追記内容 : 
//    作成詳細 : 2012/04/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_INTERFACE_H
#define INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_INTERFACE_H


namespace GameLib{
    namespace Graphics{

        /// @class IGraphicsManagerImpl
        /// @brief 各描画デバイスの継承元となるインターフェイスクラス
        class IGraphicsManagerImpl{

            //----------------------------------------------------------
            // メンバ変数
        private:
            // Interfaceはメンバ変数などの実体を持たない。

            //----------------------------------------------------------
            // 特殊メンバ
        public:

            /// @brief コンストラクタ
            IGraphicsManagerImpl(){}

            /// @brief デストラクタ
            virtual ~IGraphicsManagerImpl(){}

            //----------------------------------------------------------
            // メンバ関数
            // 各描画デバイスで共通する処理を記述すること。

            // Interfaceなので全てのメソッドにvirtualと=0をつけておくこと。
            //virtual void Test(const int x) = 0;

            /// @brief 描画を開始します。
            virtual void BeginDraw() = 0;

            /// @brief 描画を終了します。
            virtual void EndDraw() = 0;

            /// @brief フルスクリーン値などの変化を反映させるために
            /// @brief 現在のデバイスを破棄後、新たに再構築します。
            virtual void RecreateDevice() = 0;

            /// @brief 現在描画可能な状態かを確認します。
            /// @retval true 描画可能
            /// @retval false 描画不可能
            virtual const bool isRenderable() const = 0;

            /// @brief デバイスの復帰を試みます。
            /// @retval true 正常終了
            /// @retval false 異常終了
            virtual const bool Restore() = 0;

            //----------------------------------------
            // アクセサ用

            // @brief  これまでのフレームカウントを取得します。
            /// @return フレームカウント
            virtual const int getFrameCount() const = 0;


            /// @brief フルスクリーンモードのフラグを設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            virtual void setFullScreen(const bool value) = 0;

            /// @brief 垂直同期のフラグ値を設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            virtual void setVSync(const bool value) = 0;

            /// @brief アンチエイリアスのフラグ値を設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            virtual void setAntialias(const bool value) = 0;

            /// @brief クライアントサイズを設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            virtual void setClientSize(const int a_Width, const int a_Height) = 0;


        }; // end of class GraphicsManager

    } // end of namespace Graphics
} // end of namespace GameLib


#endif