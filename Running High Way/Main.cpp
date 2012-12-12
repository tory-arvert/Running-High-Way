/// @file main.cpp
/// @brief 一番最初のメインとなるメソッド
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              main.cpp
//--------------------------------------------------------------------
//    処理内容 : 一番最初のメインとなるメソッド
//    処理内容 : 
//    作成詳細 : 2011/09/01
//    補足     : さらに作り直し
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#include <Windows.h>
#include <tsstream.h>

#include "GameLib/Window/Window.h"
#include "GameLib/Framework.h"

using namespace std;
using namespace GameLib::Window;

#include <MemoryLeakCheck.h>


/// @brief メインメソッド、全ての始まり
/// @param 
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR lpCmd, int nCmd){

    // メモリーリークを監視しておく
    Common::MemoryLeakCheckStart();

    // ウィンドウマネージャ作成
    WindowCreator w;
    
    

    // フレームワーク用アクセサ生成
    GameLib::Framework framework;

    // フレームワークを作成、初期化
    framework.Create();


    unsigned int frame = 0;
    while( !w.CheckEndRequested() ){

        w.Update();
        ++frame;

        Sleep(5);

        tstringstream oss;
        oss << int(frame/60) << ":" << frame;
        w.SetTitle( oss.str() );
        
    }

    
    return (0);

};

