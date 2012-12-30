/// @file IGraphicsManagerImpl.h
/// @brief �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X��Impl�p�C���^�[�t�F�C�X
/// @note �e�`��f�o�C�X��Impl���쐬����Ƃ��͂��̃C���^�[�t�F�C�X�N���X���p������B
/// @date 2012/12/18     tory

//====================================================================
//              IGraphicsManagerImpl.h
//--------------------------------------------------------------------
//    �������e : �`��Ɋւ��邱�Ƃ��Ǘ�����}�l�[�W���[�N���X�pImpl�̃C���^�[�t�F�C�X
//    �������e : 
//    �쐬�ڍ� : 2012/12/18
//    �⑫     : �e�`��f�o�C�X��Impl���쐬����Ƃ���
//    �⑫     : ���̃C���^�[�t�F�C�X�N���X���p�����邱�ƁB
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2012/04/01    YourName
//         
//====================================================================

#ifndef INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_INTERFACE_H
#define INCLUDE_GAMELIB_GRAPHICS_MANAGER_IMPL_INTERFACE_H


namespace GameLib{
    namespace Graphics{

        /// @class IGraphicsManagerImpl
        /// @brief �e�`��f�o�C�X�̌p�����ƂȂ�C���^�[�t�F�C�X�N���X
        class IGraphicsManagerImpl{

            //----------------------------------------------------------
            // �����o�ϐ�
        private:
            // Interface�̓����o�ϐ��Ȃǂ̎��̂������Ȃ��B

            //----------------------------------------------------------
            // ���ꃁ���o
        public:

            /// @brief �R���X�g���N�^
            IGraphicsManagerImpl(){}

            /// @brief �f�X�g���N�^
            virtual ~IGraphicsManagerImpl(){}

            //----------------------------------------------------------
            // �����o�֐�
            // �e�`��f�o�C�X�ŋ��ʂ��鏈�����L�q���邱�ƁB

            // Interface�Ȃ̂őS�Ẵ��\�b�h��virtual��=0�����Ă������ƁB
            //virtual void Test(const int x) = 0;

            /// @brief �`����J�n���܂��B
            virtual void BeginDraw() = 0;

            /// @brief �`����I�����܂��B
            virtual void EndDraw() = 0;

            /// @brief �t���X�N���[���l�Ȃǂ̕ω��𔽉f�����邽�߂�
            /// @brief ���݂̃f�o�C�X��j����A�V���ɍč\�z���܂��B
            virtual void RecreateDevice() = 0;

            /// @brief ���ݕ`��\�ȏ�Ԃ����m�F���܂��B
            /// @retval true �`��\
            /// @retval false �`��s�\
            virtual const bool isRenderable() const = 0;

            /// @brief �f�o�C�X�̕��A�����݂܂��B
            /// @retval true ����I��
            /// @retval false �ُ�I��
            virtual const bool Restore() = 0;

            //----------------------------------------
            // �A�N�Z�T�p

            // @brief  ����܂ł̃t���[���J�E���g���擾���܂��B
            /// @return �t���[���J�E���g
            virtual const int getFrameCount() const = 0;


            /// @brief �t���X�N���[�����[�h�̃t���O��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            virtual void setFullScreen(const bool value) = 0;

            /// @brief ���������̃t���O�l��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            virtual void setVSync(const bool value) = 0;

            /// @brief �A���`�G�C���A�X�̃t���O�l��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            virtual void setAntialias(const bool value) = 0;

            /// @brief �N���C�A���g�T�C�Y��ݒ肵�����܂��B
            /// @attention ���ۂɕύX����ɂ�RecreateDevice���ĂԕK�v������܂��B
            virtual void setClientSize(const int a_Width, const int a_Height) = 0;


        }; // end of class GraphicsManager

    } // end of namespace Graphics
} // end of namespace GameLib


#endif