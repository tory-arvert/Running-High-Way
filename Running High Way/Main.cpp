/// @file main.cpp
/// @brief ��ԍŏ��̃��C���ƂȂ郁�\�b�h
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              main.cpp
//--------------------------------------------------------------------
//    �������e : ��ԍŏ��̃��C���ƂȂ郁�\�b�h
//    �������e : 
//    �쐬�ڍ� : 2011/09/01
//    �⑫     : ����ɍ�蒼��
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#include <Windows.h>
#include <tsstream.h>

#include "GameLib/Window/WindowCreator.h"
#include "GameLib/Framework.h"

#include "GameLib/Graphics/GraphicsManager.h"

// �ȉ��e�X�g�p
#include <Comptr.hpp>
#include "GameLib/Graphics/Sprite.h"
#include <d3d9.h>



using namespace std;
using namespace GameLib::Window;

#include <MemoryLeakCheck.h>

/// @brief ���C�����\�b�h�A�S�Ă̎n�܂�
/// @param 
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR lpCmd, int nCmd){

    // �������[���[�N���Ď����Ă���
    Common::MemoryLeakCheckStart();

    // �E�B���h�E�}�l�[�W���쐬
    WindowCreator w;
    
    

    // �t���[�����[�N�p�A�N�Z�T����
    GameLib::Framework framework;

    // �t���[�����[�N���쐬�A������
    framework.Create();

    
    GameLib::Graphics::GraphicsManager gm;

    
    GameLib::Graphics::Sprite sp;
    sp.TestTexCreate("back001.png");
    //sp.TestTexCreate(NULL);
    sp.Position(0,0);
    //sp.UV(0.0f,0.0f,1.0f,1.0f);
    sp.UV(0,0,1,1);
    sp.Size(800,600);
    sp.Scale(1,1);
    //sp.UseTextureAlpha(true);
    sp.Color(255,0,0);
    sp.Alpha(128);
    sp.Priority(0.3);

    
    GameLib::Graphics::Sprite sp2;
    sp2.TestTexCreate("100.png");
    sp2.Position(750,400);
    sp2.Size(200,200);
    //sp2.UV(0.0,0.0,2.0f,2.0f);
    sp2.Scale(1,1);
    sp2.Rotate(45);
    sp2.Pivot(100,100);
    sp2.UseTextureAlpha(true);
    //sp2.Alpha(128);

	
    GameLib::Graphics::Sprite sp3;
    //sp3.TestTexCreate("100.png");
    sp3.Position(751,300);
    sp3.Size(200,200);
    sp3.Scale(2,2);
    sp3.Pivot(50,0);
    sp3.UV(0,0,1,1);
    sp3.UseTextureAlpha(true);
    sp3.Color(0,255,0);
    //sp3.Rotate(45);
    //sp3.Pivot(128,128);
    sp3.Alpha(128);
    sp3.Priority(0.5);


    unsigned int frame = 0;
    while( !w.isEndRequested() ){

        w.Update();
        ++frame;

        Sleep(5);
        sp2.Priority((float(frame)/2000.0));

        gm.BeginDraw();
        sp.Draw();
        sp3.Draw();
        sp2.Draw();
        //sp2.Position(100,100);
        //sp3.Pivot(frame/600,frame/600);
        sp.DrawALL();
        gm.EndDraw();

        /*
        if(frame == 180){
            GameLib::Graphics::GraphicsManager gm;
            gm.setFullScreen( true );
            gm.RecreateDevice();
        }

        
        if(frame == 300){
            GameLib::Graphics::GraphicsManager gm;
            w.EnableFullScreen( false );
            gm.setFullScreen( false );
            gm.RecreateDevice();
        }
        */

        tstringstream oss;
        oss << (frame/60) << ":" << frame << (w.isMinimized()? "�ŏ�����":"�ŏ�������Ȃ���");
        w.SetTitle( oss.str() );
        
    }

    gm.EndDraw();
    
    return (0);

};

