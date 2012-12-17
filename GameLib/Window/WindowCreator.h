/// @file Window.h
/// @brief �E�B���h�E���쐬���鏈���N���X - ��`
/// @note 
/// @date 2011/09/01     tory

//====================================================================
//              Window.h
//--------------------------------------------------------------------
//    �������e : �E�B���h�E���쐬���鏈�� - ��`
//    �������e : 
//    �쐬�ڍ� : 2011/09/01
//    �⑫     : GameLib���̋@�\
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================

#include <tiostream.h>  // tstring�^�Ȃǂ�TCHAR�g����`


#ifndef INCLUDE_GAMELIB_WINDOW_CREATOR_H
#define INCLUDE_GAMELIB_WINDOW_CREATOR_H


namespace GameLib{

    namespace Window{

        /// @class WindowCreator
        /// @brief �E�B���h�E�̍쐬�Ɋ֘A����N���X
        class WindowCreator{

            //----------------------------------------------------------
            // ���ꃁ���o
        public:

            /// @brief �R���X�g���N�^
            WindowCreator();

            /// @brief �f�X�g���N�^
            virtual ~WindowCreator();


            //----------------------------------------------------------            
            // �����o�֐�
        public: 

            /// @brief �C���X�^���X���쐬���܂��B
            void Create();

            /// @brief �E�B���h�E��\�����܂��B
            /// @attention ����������Ă��Ȃ��ꍇ�Ɏ�����init�֐����R�[������܂��B
            void Show() const;

            /// @brief �E�B���h�E���b�Z�[�W���������܂��B
            /// @attention ���t���[����������K�v������܂��B
            void Update() const;

            /// @brief �v���O�����ɏI���ʒm���m�F���܂��B
            const bool isEndRequested() const;

            /// @brief �v���O�����̏I�����s���܂��B
            void End() const;

            /// @brief �t���X�N���[�����[�h�̐ݒ�����܂��B
            /// �t���X�N���[���ɂ���ꍇ��true�w��ɂ��܂��B
            void FlagFullScreen( bool flag ) const;

            //----------------------------------------------------------           
            // �A�N�Z�T
        public:

            /// @brief �`��̈�̕���ݒ肵�܂��B
            /// @param width �ݒ肷�镝
            void SetWidth( const int width );

            /// @brief �`��̈�̍�����ݒ肵�܂��B
            /// @param height �ݒ肷�鍂��
            void SetHeight( const int height );

            /// @brief �E�B���h�E�^�C�g����ݒ肵�܂��B
            /// @param title �ݒ肷�镶����
            void SetTitle( const std::tstring title );

            /// @brief �E�B���h�E�A�C�R����ݒ肵�܂��B
            /// @param id �A�C�R���̃��\�[�XID
            void SetIcon( const int id );

            //----------------------------------------------------------
            // �v���p�e�B

            /// @brief �E�B���h�E�n���h�����擾���܂��B
            /// @return HWND �E�B���h�E�n���h��
            const HWND handle() const;

            /// @brief �E�B���h�E���A�N�e�B�u���m�F���܂��B
            /// @return bool �A�N�e�B�u����true�A��A�N�e�B�u���ɂ�false��Ԃ��܂��B
            const bool isActive() const;

            /// @brief �t���X�N���[�����[�h���擾���܂��B
            /// @return bool �t���X�N���[������true,�E�B���h�E����false��Ԃ��܂��B
            const bool isFullScreen() const;

            /// @brief  �E�B���h�E���ŏ�������Ă��邩���m�F���܂��B
            /// @return bool true �ŏ�������true�A��ŏ�������false��Ԃ��܂��B
            const bool isMinimized() const;

            /// @brief �N���C�A���g�̈�̕����擾���܂��B
            /// @return int �ݒ肵����
            const int width() const;

            /// @brief �N���C�A���g�̈�̍������擾���܂��B
            /// @return int �ݒ肵������
            const int height() const;

        }; // end of class L_WindowCreator

    } // end of namespace Window
} // end of namespace GameLib
#endif
