/// @file  Framework.h
/// @brief ��ԏ��߂̑S�̂̏������������鏈�� - ��`
/// @note 
/// @date 2011/10/15     tory

//====================================================================
//              Framework.h
//--------------------------------------------------------------------
//    �������e : ��ԏ��߂̑S�̂̏������������鏈�� - ��`
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


#ifndef INCLUDE_GAMELIB_FRAMEWORK_H
#define INCLUDE_GAMELIB_FRAMEWORK_H


namespace GameLib
{

        /// @class Framework
        /// @brief �e�}�l�[�W���𓝊�����t���[�����[�N
        class Framework
        {
            //----------------------------------------------------------
            // ���ꃁ���o
        public:
            
            /// @brief �R���X�g���N�^
            Framework();

            /// @brief �f�X�g���N�^
            virtual ~Framework();

            //----------------------------------------------------------
            // �����o�֐�
        public: 

            /// @brief �C���X�^���X���쐬���܂��B
            void Create();

        }; // end of class Framework
} // end of namespace GameLib
#endif
