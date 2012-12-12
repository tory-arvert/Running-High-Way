/// @file Framework.cpp
/// @brief 一番初めの全体の初期化等をする処理 - 実装
/// @note 
/// @date 2011/10/15     tory

//====================================================================
//              Framework.cpp
//--------------------------------------------------------------------
//    処理内容 : 一番初めの全体の初期化等をする処理 - 実装
//    処理内容 : 
//    作成詳細 : 2011/10/15
//    補足     : GameLib内のManagerの初期化を行うが、そのプログラムの
//    補足     : 固有読み込みなどを記述するときもあります。
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================

#include <Windows.h>    // MessageBeepやウィンドウプロシージャなどの基本に必須
#include <memory>       // unique_ptrなどに必要
#include <tchar.h>      // _T("")に必要

#include "Framework.h"
#include "Window/Window.h"
//#include "Graphics/GraphicsManager.h"
//#include "FileIO/FileIOManager.h"


using namespace std;
using namespace GameLib::Window;


// 無名ネームスペース定義
namespace{


    /// @class Impl
    /// @brief 実体クラス
    class Impl
    {

        //----------------------------------------------------------
    public:     // 特殊メンバ

        /// @brief コンストラクタ
        Impl(){};

        /// @brief デストラクタ
        virtual ~Impl(){};       

    };

    /// @note 実体クラスインスタンス
    /// @attention このgImplがアクセスした際の最終的な処理をするクラスである。    
    unique_ptr< Impl > gImpl;

}
//----------------------------------------------------------
//----------------------------------------------------------


namespace GameLib{

    
    //----------------------------------------------------------
    // 特殊メンバ

    ///＠brief コンストラクタ
    Framework::Framework(){}

    ///＠brief デストラクタ
    Framework::~Framework(){}


    //----------------------------------------------------------
    // メンバ関数

    ///＠brief インスタンスを作成します。
    void Framework::Create(){

        // 作成済みかどうか確認する。
        if(gImpl != nullptr){
            MessageBox(NULL,_T("FrameWorkの実体を複数作成しようとしました。"),_T("インスタンス作成中止"),MB_OK);
            return;
        }
         
        // 問題なければ実体を作成
         gImpl.reset(new Impl() );
         


        // その他に必要なManagerを初期化(create)する。
        
        // ウィンドウマネージャ作成
        WindowCreator w;
        // 初期化
        w.Create();
        w.SetWidth( 1024 );
        w.SetHeight( 768 );
        w.SetTitle( _T("Library Test") );              
        w.Show();


    }





}  // end of namespace GameLib