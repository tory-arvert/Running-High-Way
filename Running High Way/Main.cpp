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

#include "GameLib/Window/Window.h"
#include "GameLib/Framework.h"

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
