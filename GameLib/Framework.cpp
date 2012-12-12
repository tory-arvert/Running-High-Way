/// @file Framework.cpp
/// @brief ��ԏ��߂̑S�̂̏������������鏈�� - ����
/// @note 
/// @date 2011/10/15     tory

//====================================================================
//              Framework.cpp
//--------------------------------------------------------------------
//    �������e : ��ԏ��߂̑S�̂̏������������鏈�� - ����
//    �������e : 
//    �쐬�ڍ� : 2011/10/15
//    �⑫     : GameLib����Manager�̏��������s�����A���̃v���O������
//    �⑫     : �ŗL�ǂݍ��݂Ȃǂ��L�q����Ƃ�������܂��B
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================

#include <Windows.h>    // MessageBeep��E�B���h�E�v���V�[�W���Ȃǂ̊�{�ɕK�{
#include <memory>       // unique_ptr�ȂǂɕK�v
#include <tchar.h>      // _T("")�ɕK�v

#include "Framework.h"
#include "Window/Window.h"
//#include "Graphics/GraphicsManager.h"
//#include "FileIO/FileIOManager.h"


using namespace std;
using namespace GameLib::Window;


// �����l�[���X�y�[�X��`
namespace{


    /// @class Impl
    /// @brief ���̃N���X
    class Impl
    {

        //----------------------------------------------------------
    public:     // ���ꃁ���o

        /// @brief �R���X�g���N�^
        Impl(){};

        /// @brief �f�X�g���N�^
        virtual ~Impl(){};       

    };

    /// @note ���̃N���X�C���X�^���X
    /// @attention ����gImpl���A�N�Z�X�����ۂ̍ŏI�I�ȏ���������N���X�ł���B    
    unique_ptr< Impl > gImpl;

}
//----------------------------------------------------------
//----------------------------------------------------------


namespace GameLib{

    
    //----------------------------------------------------------
    // ���ꃁ���o

    ///��brief �R���X�g���N�^
    Framework::Framework(){}

    ///��brief �f�X�g���N�^
    Framework::~Framework(){}


    //----------------------------------------------------------
    // �����o�֐�

    ///��brief �C���X�^���X���쐬���܂��B
    void Framework::Create(){

        // �쐬�ς݂��ǂ����m�F����B
        if(gImpl != nullptr){
            MessageBox(NULL,_T("FrameWork�̎��̂𕡐��쐬���悤�Ƃ��܂����B"),_T("�C���X�^���X�쐬���~"),MB_OK);
            return;
        }
         
        // ���Ȃ���Ύ��̂��쐬
         gImpl.reset(new Impl() );
         


        // ���̑��ɕK�v��Manager��������(create)����B
        
        // �E�B���h�E�}�l�[�W���쐬
        WindowCreator w;
        // ������
        w.Create();
        w.SetWidth( 1024 );
        w.SetHeight( 768 );
        w.SetTitle( _T("Library Test") );              
        w.Show();


    }





}  // end of namespace GameLib