/// @file GraphicsManagerImplDirect3D.hpp
/// @brief 描画に関することを管理するマネージャークラス用Impl - 実体
/// @note DirectX用の描画デバイスの処理を行う。
/// @date 2012/12/18     tory

//====================================================================
//              GraphicsManagerImplDirect3D.hpp
//--------------------------------------------------------------------
//    処理内容 : 描画デバイスの処理を管理するクラスのImpl - 実体
//    処理内容 : 
//    作成詳細 : 2012/12/18
//    補足     : DirectX用の描画デバイスの処理を行う。
//
//    追記内容 : 
//    作成詳細 : 2012/04/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_H
#define INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_H

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>              // D3DFVF_XYZRHW等の使用に必要

#include "IGraphicsManagerImpl.h"
#include <tiostream.h>          // tstring型などのTCHAR拡張定義
#include "TemplateBaseClass.hpp"
#include "Comptr.hpp"

#include "ISpriteImpl.h"

// StaticLibプロジェクトのプロパティからlibを呼び出す場合warningが出るため、それの代用法
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


namespace GameLib{
    namespace Graphics{

        using namespace std;

        /// @brief stateFlag
        /// @brief Direct3D環境の状態フラグに関するものを集めたクラス
        class D3DStatesFlag{

            //----------------------------------------------------------
            // メンバ変数
        private:
            bool mFullScreen;           ///< @brief フルスクリーンモードフラグ
            bool mVSync;                ///< @brief 垂直同期フラグ
            bool mAntiAlias;            ///< @brief アンチエイリアスフラグ
            bool mRenderable;           ///< @brief 描画可能状態
            bool mVertexShaderReady;    ///< @brief 頂点シェーダの有無
            bool mPixelShaderReady;     ///< @brief ピクセルシェーダの有無

            DWORD mVertexVersion;       ///< @brief 頂点シェーダのver
            DWORD mPixelVersion;        ///< @brief ピクセルシェーダのver

            //----------------------------------------------------------
            // 特殊メンバ関数
        public:
            
            /// @brief コンストラクタ
            D3DStatesFlag(){
                mFullScreen         = false;
                mVSync              = false;
                mAntiAlias          = false;
                mRenderable         = false;
                mVertexShaderReady  = false;
                mPixelShaderReady   = false;     
                mVertexVersion      = 0;
                mPixelVersion       = 0;
            }
            
            /// @brief デストラクタ
            ~D3DStatesFlag(){}
            


            //----------------------------------------------------------
            // メンバ関数
        public:

            //----------------------------------------
            // アクセサ
        public:

            /// @brief フルスクリーンフラグ値を設定します。
            void setFullScreen(const bool value){
                mFullScreen = value;
            }

            /// @brief 垂直同期フラグ値を設定します。
            void setVSync(const bool value){
                mVSync = value;
            }

            /// @brief アンテエイリアスフラグ値を設定します。
            void setAntiAlias(const bool value){
                mAntiAlias = value;
            }

            /// @brief 今現在描画可能な状態を設定します。
            void setRenderable(const bool value){
                mRenderable = value;
            }

            /// @brief 頂点シェーダの有無を設定します。
            void setVertexShaderReady(const bool value){
                mVertexShaderReady = value;
            }

            /// @brief ピクセルシェーダの有無を設定します。
            void setPixelShaderReady(const bool value){
                mPixelShaderReady = value;
            }

            /// @brief 頂点シェーダのバージョンを記録します。
            void setVertexVersion(const DWORD value){
                mVertexVersion = value;
            }

            /// @brief ピクセルシェーダのバージョンを記録します。
            void setPixelVersion(const DWORD value){
                mPixelVersion = value;
            }

           //----------------------------------------

            /// @brief フルスクリーンフラグ値を返します。
            const bool isFullScreen() const { return mFullScreen; }

            /// @brief 垂直同期フラグ値を返します。
            const bool isVSync() const { return mVSync; }

            /// @brief アンテエイリアスフラグ値を返します。
            const bool isAntiAlias() const { return mAntiAlias; }

            /// @brief 今現在描画可能な状態か返します。
            const bool isRenderable() const { return mRenderable;}

            /// @brief 頂点シェーダの有無を返します。
            const bool isVertexShaderReady() const { return mVertexShaderReady; }

            /// @brief ピクセルシェーダの有無を返します。
            const bool isPixelShaderReady() const { return mPixelShaderReady; }

            /// @brief 頂点シェーダのバージョンを返します。
            /// @param a_Major メジャーバージョン
            /// @param a_Minor マイナーバージョン
            void getVertexVersion(int* a_Major, int* a_Minor) const {            
                *a_Major = ((mVertexVersion)>>8 & 0xFF);
                *a_Minor = ((mVertexVersion)>>0 & 0xFF);
            }

            /// @brief ピクセルシェーダのバージョンを返します。
            /// @param a_Major メジャーバージョン
            /// @param a_Minor マイナーバージョン
            void getPixelVersion(int* a_Major, int* a_Minor) const {
                *a_Major = ((mPixelVersion)>>8 & 0xFF);
                *a_Minor = ((mPixelVersion)>>0 & 0xFF);
            }

        };


        /// @class ImplDirect3D
        /// @brief DirectX描画デバイスの描画を管理するクラス
        class ImplDirect3D : public IGraphicsManagerImpl{

            //----------------------------------------------------------
            // 別名宣言

            /// @brief IDirect3D9のスマートポインタ型
            typedef Com_ptr< IDirect3D9 >  IDirect3D9_sp;
            /// @brief IDirect3DDevice9のスマートポインタ型
            typedef Com_ptr< IDirect3DDevice9 > IDirect3DDevice9_sp;
            /// @brief スプライトインターフェイスのスマートポインタ型
            typedef shared_ptr< ISpriteImpl > ISpriteImpl_sp;
            //----------------------------------------------------------
            // メンバ変数
        private:
            tstring mTitle;     ///< @brief ウィンドウタイトル
            HWND    mHandle;    ///< @brief ウィンドウハンドル
            
            IDirect3D9_sp mDirect3D;        ///< @brief Direct3D9
            IDirect3DDevice9_sp mDevice;    ///< @brief レンダリングデバイス
        
            BaseWH<int> mClient;            ///< @brief ベースクライアント領域
            BaseWH<int> m2DClient;          ///< @brief 2D描画時の基準領域サイズ

            unsigned int mFrameCount;       ///< @brief これまでのフレーム数

            D3DStatesFlag mStatesFlag;      ///< @brief Direct3D環境の状態フラグに関するものを集めたクラス
            D3DPRESENT_PARAMETERS mPresentParams;   ///< @brief PresentParameters構造体
        public:
            /// @brief スプライトのインターフェイス用インプル
            /// @attention このSpriteImplはexternで使用する仕組みとなっている。
            ISpriteImpl_sp mSpriteImpl;     ///< @brief スプライトのインターフェイスインプル

            //----------------------------------------------------------
            // 特殊メンバ
        public:
                
            /// @brief コンストラクタ
            ImplDirect3D(
                const HWND a_Handle,            // ウィンドウハンドル
                const int a_Width,              // クライアントXサイズ
                const int a_Height,             // クライアントYサイズ
                const bool a_Fullscreen,        // フルスクリーンフラグ
                const bool a_VSync,             // 垂直同期フラグ
                const bool a_AntiAlias,         // アンチエイリアスフラグ
                const int a_Width2D,            // 2D描画時の基準領域Xサイズ
                const int a_Height2D            // 2D描画時の基準領域Yサイズ
                ):
            mDirect3D( NULL ),
            mDevice( NULL ),
            mFrameCount( 0 )
            {
                // 共通メンバ初期化
                Init( a_Handle, a_Width, a_Height, a_Fullscreen, a_VSync, a_AntiAlias );

                // 2D描画時の基準領域サイズを設定する。これはSpriteやFontの描画時に縮尺を自動補正してくれる。
                // このサイズは初回作成時のみ設定可能とする。
                m2DClient.setWH( a_Width2D, a_Height2D );

                // COMの初期化
                InitD3D9();
                // シェーダの有無を確認
                isReadyShader();
                // プレゼントパラメータの初期化
                InitPresentParams();
                // デバイスの作成
                auto a_Success = CreateDevice();
                    
                // デバイスの作成に成功したら
                if( a_Success ){ 
                
                    // 描画可能状態を設定
                    mStatesFlag.setRenderable( true );
                    // テクスチャ0stageのSamplerStateを設定しておく。
                    setSamplerState(0);
            
                }
            }

            /// @brief デストラクタ
            virtual ~ImplDirect3D(){}

            //----------------------------------------------------------
            // メンバ関数


            /// @brief  描画開始
            void BeginDraw()
            {
                // フレームカウント
                ++mFrameCount;

                //画面をクリア( 青色でクリア )
                mDevice->Clear( 
                    0,
                    0,
                    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                    D3DCOLOR_XRGB( 0, 0, 128 ),
                    1.0f,
                    0
                    );
                //描画開始を宣言
                mDevice->BeginScene();
            }


            /// @brief  描画終了
            void EndDraw()
            {
                HRESULT hr = S_OK;

                //描画終了を宣言
                mDevice->EndScene();
                //バックバッファを転送する
                hr = mDevice->Present( 0, 0, 0, 0 );

                // デバイスロスト発生時に復帰処理を行う
                if ( hr == D3DERR_DEVICELOST )
                {
                    // 描画不可能を報告
                    mStatesFlag.setRenderable( false );
                }
            }

            /// @brief フルスクリーン値などの変化を反映させるために
            /// @brief 現在のデバイスを破棄後、新たに再構築します。
            void RecreateDevice(){

                // リソース破棄中にアクセスしないように描画不可に設定
                mStatesFlag.setRenderable( false );

                // リソースの開放
                CleanupResource();

                // デバイスの開放(ComptrなのでNULL代入にて開放)
                mDevice = NULL;

                // 新しいフラグ値の状態になるようプレゼントパラメータを初期化
                InitPresentParams();

                // デバイスの再作成
                CreateDevice();
                
                // リソースの再作成
                RecreateResource();

                // リソースにアクセスできるようになったため描画可能に設定
                mStatesFlag.setRenderable( true );

            }


            /// @brief  Direct3Dデバイスの復帰を試みます。
            /// @retval true 正常復帰完了
            /// @retval false 異常終了
            const bool Restore()
            {
                HRESULT hr = S_OK;

                // デバイスが復帰可能かを確認
                hr = mDevice->TestCooperativeLevel();
                switch( hr )
                {
                // 復帰可能状態
                case D3DERR_DEVICENOTRESET:
                    hr = mDevice->Reset( &mPresentParams );
                    if ( FAILED( hr ) )
                    {
                        // デバイス復帰は判定に時間がかかるときがあるため、何回か繰り返す必要がある場合がある。
                        // そのため毎回メッセージを表示するとまずい可能性が高い。
                        // MessageBox(NULL,_T("デバイスロストからの復帰に失敗しました。"),_T("復帰作業中止"),MB_OK);
                        return false;
                    }
                }

                return true;
            }


            //----------------------------------------
            // アクセサ
            /// @brief  Direct3DDevice9を取得します。
            /// @return Direct3DDevice9へのスマートポインタ
            /// @note デバイス取得は外部に公開せず、externで必要なクラスの内部でのみ使用できるようにする。
            IDirect3DDevice9_sp getDevice() const {
                return mDevice;
            }

            /// @brief 頂点シェーダが使用可能かどうかを返します。
            /// @return bool 頂点シェーダの使用の可否
            const bool getVertexShaderReady() const { return mStatesFlag.isVertexShaderReady(); }

            /// @brief ピクセルシェーダが使用可能かどうかを返します。
            /// @return bool ピクセルシェーダの使用の可否
            const bool getPixelShaderReady() const { return mStatesFlag.isPixelShaderReady(); }

            /// @brief 2D用の基準領域サイズを取得します。
            /// @param a_w 基準の幅を返します。
            /// @param a_h 基準の高さを返します。
            void get2DClientSize( int *a_w, int *a_h){
                *a_w = m2DClient.width();
                *a_h = m2DClient.height();
            }

            /// @brief クライアント領域サイズを取得します。
            /// @param a_w 基準の幅を返します。
            /// @param a_h 基準の高さを返します。
            void getClientSize( int *a_w, int *a_h){
                *a_w = mClient.width();
                *a_h = mClient.height();
            }



            /// @brief  これまでのフレームカウントを取得します。
            /// @return フレームカウント
            const int getFrameCount() const{
                return mFrameCount;
            }

            /// @brief  デバイスが描画可能状態かを確認します。
            /// @retval true 描画可能
            /// @retval false 描画不可能
            const bool isRenderable() const {
                return mStatesFlag.isRenderable();
            }

            /// @brief フルスクリーンモードのフラグを設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setFullScreen(const bool value){
                mStatesFlag.setFullScreen( value );
            }

            /// @brief 垂直同期のフラグ値を設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setVSync(const bool value){
                mStatesFlag.setVSync( value );
            }

            /// @brief アンチエイリアスのフラグ値を設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setAntialias(const bool value){
                mStatesFlag.setAntiAlias( value );
            }

            /// @brief クライアントサイズを設定し直します。
            /// @attention 実際に変更するにはRecreateDeviceを呼ぶ必要があります。
            void setClientSize(const int a_Width, const int a_Height){
                mClient.setWH( a_Width, a_Height );
                RecreateDevice();
            }

            //----------------------------------------
            // ヘルパー関数
        protected:


            /// @brief  共通メンバを初期化します。
            /// @param  a_Handle        描画対象のウィンドウハンドル
            /// @param  a_Width         ウィンドウの高さ
            /// @param  a_Height        ウィンドウの幅
            /// @param  a_Fullscreen    フルスクリーン
            /// @param  a_VSync         垂直同期
            /// @param  a_AntiAlias     アンチエイリアス
            void Init(
                const HWND a_Handle,
                const int a_Width,
                const int a_Height,
                const bool a_Fullscreen,
                const bool a_VSync,
                const bool a_AntiAlias
                ){
                mHandle = a_Handle;
                mClient.setWH( a_Width, a_Height );
                mStatesFlag.setFullScreen( a_Fullscreen );
                mStatesFlag.setVSync( a_VSync );
                mStatesFlag.setAntiAlias( a_AntiAlias );

            } // end of void Init


            /// @brief DirectXを使用できるように初期化します。
            /// @note コンストラクタ専用ヘルパー関数
            const bool InitD3D9(){
                mDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
                // 正常に取得できたかのチェック
                return (mDirect3D != nullptr) ? true : false;
            }


            /// @brief  シェーダ機能の有無を確認
            /// @note コンストラクタ専用ヘルパー関数
            const bool isReadyShader()
            {
                HRESULT hr = S_OK;

                // ハードウェア情報を取得
                D3DCAPS9 caps;
                ZeroMemory(&caps, sizeof(caps));
                hr = mDirect3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

                // VertexShader1.1を確認
                mStatesFlag.setVertexShaderReady( caps.VertexShaderVersion >= D3DVS_VERSION( 1, 1 ) );
                mStatesFlag.setVertexVersion(caps.VertexShaderVersion);

                // PixelShader2.2を確認
                mStatesFlag.setPixelShaderReady( caps.PixelShaderVersion >= D3DPS_VERSION( 2, 0 ) );
                mStatesFlag.setPixelVersion( caps.PixelShaderVersion );

                return (hr == S_OK ? true : false);
            }

            /// @brief PresentParametersのの初期化をします。
            /// @attention 初期化前にHWNDなどの指定を忘れないこと。
            void InitPresentParams(){
                ZeroMemory(&mPresentParams, sizeof(mPresentParams));
                // フルスクリーンとウィンドウモードの設定
                mPresentParams.Windowed                     = !mStatesFlag.isFullScreen();
                // バックバッファのスワップエフェクト = Direct3Dにスワップエフェクトをまかせる
                mPresentParams.SwapEffect                   = D3DSWAPEFFECT_DISCARD;
                // バックバッファのフォーマット
                SelectBackBufferFormat();
                // Direct3Dに深度バッファの管理をまかせる
                mPresentParams.EnableAutoDepthStencil       = true;
                // 深度バッファのフォーマット（通常はこの値で問題ない）
                mPresentParams.AutoDepthStencilFormat       = D3DFMT_D16;
                // カバーウィンドウ＝アプリケーションのウィンドウハンドル
                mPresentParams.hDeviceWindow                = mHandle;
                // フルスクリーン時の画面のサイズ（バックバッファの幅,バックバッファの高さ）
                mPresentParams.BackBufferWidth              = mClient.width();
                mPresentParams.BackBufferHeight             = mClient.height();

                // バックバッファの数 = 1
                mPresentParams.BackBufferCount              = 1;
                // マルチサンプリング関連を設定する。
                SelectMultiSample();
                // フラグは使わない
                mPresentParams.Flags                        = 0;
                // 今のリフレッシュレートをそのまま使う
                SelectRefreshRateInHz();
                // 垂直同期を設定する。
                SelectVSync();
            }


            /// @brief マルチサンプリングをアンチエイリアスフラグ値に合わせて自動で設定します。
            /// @attention アンチエイリアスフラグ値がtrueの場合、設定可能範囲内での最大値を選択します。
            /// @note InitPresentParams専用ヘルパー関数専用ヘルパー関数
            void SelectMultiSample(){

                // アンチエイリアスが無効に設定されていた場合
                if(!mStatesFlag.isAntiAlias()){
                    // アンチエイリアスを使わない場合はNoneに設定する。
                    mPresentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
                    mPresentParams.MultiSampleQuality = 0;
                    return;
                }

                // アンチエイリアスが有効に設定されていた場合
                HRESULT hr = E_FAIL;
                DWORD qualityBackBuffer = 0;
                DWORD qualityZBuffer = 0;
                DWORD antialiasChoiceCount = (DWORD)D3DMULTISAMPLE_16_SAMPLES;

                while( antialiasChoiceCount ){
                    //レンダリングターゲットでアンチエイリアシングがサポートされているかをチェック
                    hr = mDirect3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
                                                                D3DDEVTYPE_HAL,
                                                                mPresentParams.BackBufferFormat,
                                                                mPresentParams.Windowed,
                                                                (D3DMULTISAMPLE_TYPE)antialiasChoiceCount,
                                                                &qualityBackBuffer );
                    if( SUCCEEDED(hr) ){
                        //深度ステンシル サーフェイスでアンチエイリアスがサポートされているかをチェック
                        hr = mDirect3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
                                                                    D3DDEVTYPE_HAL,
                                                                    mPresentParams.AutoDepthStencilFormat,
                                                                    mPresentParams.Windowed,
                                                                    (D3DMULTISAMPLE_TYPE)antialiasChoiceCount,
                                                                    &qualityZBuffer );
                        if( SUCCEEDED(hr) ){
                            // アンチエイリアスが使用できるのでD3DPRESENT_PARAMETERSにタイプをセットする。
                            mPresentParams.MultiSampleType = (D3DMULTISAMPLE_TYPE)antialiasChoiceCount;
            
                            // QualityBackBufferとQualityZBufferで小さい方の値を有効にする。
                            // どんなパターンで値が返るのかわからないため、このような処理にしている。
                            ( qualityBackBuffer < qualityZBuffer ) ?
                                mPresentParams.MultiSampleQuality = qualityBackBuffer - 1 :
                                mPresentParams.MultiSampleQuality = qualityZBuffer - 1;
                            break;
                        }
                    }
      
                //現在のタイプでアンチエイリアスが使用できないので、１段階低いタイプで再チェックする。
                --antialiasChoiceCount;
                }

            }




            /// @brief バックバッファのフォーマットを自動で選択します。
            /// @note InitPresentParams専用ヘルパー関数
            void SelectBackBufferFormat(){

                // ウィンドウモードのとき
                if(mPresentParams.Windowed){
                   mPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
                } 

                // フルスクリーンモードのとき
                // 現在のプライマリディスプレイアダプタのモードを取得する
                // ディスプレイモードの情報を収める
                D3DDISPLAYMODE displayMode;
                ZeroMemory(&displayMode, sizeof(displayMode));

                if(FAILED( mDirect3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &displayMode )))
                {
                    MessageBox(NULL, _T("ディスプレイモードの取得に失敗しました"), _T("DirectX"),MB_OK | MB_ICONSTOP);
                    mPresentParams.BackBufferFormat = D3DFMT_UNKNOWN; 
                    return;
                }

                mPresentParams.BackBufferFormat = displayMode.Format;
            }

            /// @brief リフレッシュレートを自動で選択設定します。
            /// @note InitPresentParams専用ヘルパー関数
            void SelectRefreshRateInHz(){

                // ウィンドウモード時は0を使用
                if( mPresentParams.Windowed ){
                    mPresentParams.FullScreen_RefreshRateInHz = 0;
                    return;
                }

                // フルスクリーンモード時
                // 今のリフレッシュレートをそのまま使う
                mPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

            }

            /// @brief フラグ値の設定によって垂直同期を自動で設定します。
            /// @attention 垂直同期はフルスクリーン時でないと有効になりません。
            /// @note InitPresentParams専用ヘルパー関数
            void SelectVSync(){

                if(mStatesFlag.isVSync() & mStatesFlag.isFullScreen()){ 
                    mPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
                    return;
                }
                mPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
                return;
            }



            /// @brief Direct3Dデバイスを作成します。
            const bool CreateDevice(){

                HRESULT hr = S_OK;

                // ハードウェアデバイスの作成( VertexShader1.1が有効時 )
                if ( mStatesFlag.isVertexShaderReady() ){

                    hr = mDirect3D->CreateDevice(
                                        D3DADAPTER_DEFAULT,
                                        // ハードウェア描画処理
                                        D3DDEVTYPE_HAL,
                                        mHandle,
                                        // HARDWARE頂点処理 | 速度は若干落ちるが少数を倍精度にする。
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                        &mPresentParams,
                                        mDevice.ToCreator()
                                    );
                } else {
                    hr = D3DERR_INVALIDDEVICE;
                }

                // (頂点)ソフトウェアデバイスの作成( VertexShader1.1非対応 or 作成失敗時 )
                if ( FAILED( hr ) )
                {
                    hr = mDirect3D->CreateDevice(
                                        D3DADAPTER_DEFAULT,
                                        // ハードウェア描画処理
                                        D3DDEVTYPE_HAL,
                                        mHandle,
                                        // SOFTWARE頂点処理 | 速度は若干落ちるが少数を倍精度にする。
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                        &mPresentParams,
                                        mDevice.ToCreator()
                                    );
                }

                // ソフトウェアデバイスの作成( さらに作成失敗時、処理速度は目も当てられない… )
                if ( FAILED( hr ) )
                {
                    hr = mDirect3D->CreateDevice(
                                        D3DADAPTER_DEFAULT,
                                        // ソフトフェアエミュレーション描画処理
                                        D3DDEVTYPE_REF,
                                        mHandle,
                                        // SOFTWARE頂点処理 | 速度は若干落ちるが少数を倍精度にする。
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                        &mPresentParams,
                                        mDevice.ToCreator()
                                    );
                }



                // どのデバイス作成にも失敗した場合
                // 例外コンテナをthrowする
                if ( FAILED( hr ) )
                {
                    MessageBox(NULL,_T("DirectXデバイスの作成に失敗しました。\nグラフィックボードが対応していません。"), _T("Direct3D"),MB_OK);
                    return false;
                }

                return true;
            }

            /// @brief テクスチャのsamplerStateを設定します。
            void setSamplerState(const int a_No){
                // 拡大時のフィルター
                mDevice->SetSamplerState(a_No, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
                // 縮小時のフィルター
                mDevice->SetSamplerState(a_No, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
                // ミップマップ レベル間のフィルター
                mDevice->SetSamplerState(a_No, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
            }

            /// @brief  メモリリソースの全解放を行います。
            void CleanupResource()
            {
                // ここにリソースを解放するメソッドを記述
            
                // 解放しなければならない物
                // - レンダリングターゲット
                // - 深度ステンシルサーフェイス
                // - 追加スワップチェーン
                // - ステートブロック
                // - D3DPOOL_DEFAULTリソース
            }

            /// @brief  メモリリソースの再作成を行います。
            void RecreateResource()
            {
                // ここにリソースを再作成するメソッドを記述
            
                // 解放しなければならない物
                // - レンダリングターゲット
                // - 深度ステンシルサーフェイス
                // - 追加スワップチェーン
                // - ステートブロック
                // - D3DPOOL_DEFAULTリソース
            }



        }; // end of class GraphicsManager

    } // end of namespace Graphics
} // end of namespace GameLib


#endif