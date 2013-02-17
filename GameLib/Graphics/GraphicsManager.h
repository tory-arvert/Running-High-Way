/// @file GraphicsManager.h
/// @brief �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X - ��`
/// @note Impl�ƃC���^�[�t�F�C�X�ɂ��p���𗘗p���ĕ`��f�o�C�X�̕ύX���Ή��\�B
/// @date 2011/10/18     tory

//====================================================================
//              GraphicsManager.h
//--------------------------------------------------------------------
//    �������e : �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X - ��`
//    �������e : 
//    �쐬�ڍ� : 2011/10/18
//    �⑫     : Impl�ƃC���^�[�t�F�C�X�ɂ��p���𗘗p���ĕ`��f�o�C�X�̕ύX���Ή��\�B
//    �ǋL���e : 
//    �쐬�ڍ� : 
//
//    �ǋL���e : �啝�ȃ��t�@�N�^�����O�����s
//    �쐬�ڍ� : 2012/12/18    tory
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_GRAPHICS_MANAGER_H
#define INCLUDE_GAMELIB_GRAPHICS_MANAGER_H

namespace GameLib{
    namespace Graphics{

        /// @class GraphicsManager
        /// @brief �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X
        class GraphicsManager{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:

            //----------------------------------------------------------
            // ���ꃁ���o
        public:

            /// @brief �R���X�g���N�^
            GraphicsManager();

            /// @brief �f�X�g���N�^
            ~GraphicsManager();

            //----------------------------------------------------------
            // �����o�֐�

            /// @brief �C���X�^���X���쐬���܂��B
            /// @param a_HWND �E�B���h�E�n���h��
            /// @param a_Width �`��̈��X�T�C�Y
            /// @param a_Height �`��̈��Y�T�C�Y
            /// @param a_Fullscreen �t���X�N���[���t���O
            /// @param a_Vsync ���������t���O
            /// @param a_AntiAlias �A���`�G�C���A�X�t���O
            /// @param a_Width2D 2D�`�掞�̊�̈�X�T�C�Y(=800)
            /// @param a_Height2D 2D�`�掞�̊�̈�Y�T�C�Y(=600)
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

            /// @brief �C���X�^���X��j�����܂��B
            static void Destroy();


            /// @brief �`����J�n���܂��B
            void BeginDraw();

            /// @brief �`����I�����܂��B
            void EndDraw();

            /// @brief ���ݕ`��\�ȏ�Ԃ����m�F���܂��B
            /// @retval true �`��\
            /// @retval false �`��s�\
            const bool isRenderable() const;


            /// @brief �t���X�N���[���l�Ȃǂ̕ω��𔽉f�����邽�߂�
            /// @brief ���݂̃f�o�C�X��j����A�V���ɍč\�z���܂��B
            void RecreateDevice();

            /// @brief �f�o�C�X�̕��A�����݂܂��B
            /// @retval true ���한�A����
            /// @retval false �ُ�I��
            const bool Restore();

            //----------------------------------------
            // �A�N�Z�T


            /// @brief  ����܂ł̃t���[���J�E���g���擾���܂��B
            /// @return �t���[���J�E���g
            const int getFrameCount() const;

            /// @brief �t���X�N���[�����[�h�̃t���O��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setFullScreen(const bool value);

            /// @brief ���������̃t���O�l��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setVSync(const bool value);

            /// @brief �A���`�G�C���A�X�̃t���O�l��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setAntialias(const bool value);

            /// @brief �N���C�A���g�T�C�Y��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            void setClientSize(const int a_Width, const int a_Height);

            /// @brief ���̑���Manager�����������܂��B
            // void InitializeManager();




        }; // end of class GraphicsManager

    } // end of namespace Graphics
} // end of namespace GameLib
#endif