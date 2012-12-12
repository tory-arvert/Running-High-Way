///    @file    MemoryLeakCheck.h
///    @brief    CRT���C�u�������g�p�������������[�N�̌��o
/*
@note            �������`�F�b�N��L�����������v���O������
                                �G���g���[�|�C���g(��:main�֐�)�̐擪�Ɉȉ��̃R�[�h���L�q����B
                                @code
                                _CrtSetDbgFlag(    _CRTDBG_ALLOC_MEM_DF    |    _CRTDBG_LEAK_CHECK_DF    );
                                @endcode
                                �܂��A�ȉ��̃��\�b�h�̈����Ɍ��o�������[�N�̐��l�������邱�Ƃ�
                                ���[�N���ƂȂ鐶���ꏊ�Ŏ~�܂邱�Ƃ��ł���B
                                _CrtSetBreakAlloc(    xxx    );    //    xxx�����o�������[�N�̐��l
*/
///    @attention    new�����������邽�߈ꕔ�̃��C�u����(��:DirectX�֘A)��
///    @attention    �R���p�C���G���[���������邱�Ƃ�����B
///    @attention    ���̂���include�̏��Ԃ͍Ō�Ɏ����Ă����悤�ɋC�����邱�ƁB
///    @date    2012/12/11                    tory
//====================================================================
//                                                MemoryLeakCheck.h
//--------------------------------------------------------------------
//                �������e    :    CRT���C�u�������g�p�������������[�N�̌��o
//                �쐬�ڍ�    :    2012/12/11                tory
//                �⑫                    :    �������`�F�b�N��L�����������v���O������
//                �⑫                    :    �G���g���[�|�C���g(��:main�֐�)�̐擪�Ɉȉ��̃R�[�h���L�q����B
//                �⑫                    :    _CrtSetDbgFlag(    _CRTDBG_ALLOC_MEM_DF    |    _CRTDBG_LEAK_CHECK_DF    );
//    
//                �ǋL���e    :    
//                �쐬�ڍ�    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_MEMORYLEAKCHECK_H
#define    INCLUDED_COMMON_MEMORYLEAKCHECK_H

namespace    Common{
                //�f�o�b�O���Ƀ��������[�N�̌��o��L��������
                #ifdef    _DEBUG

                #define    _CRTDBG_MAP_ALLOC
                #include    <crtdbg.h>
                #define    new    new(    _NORMAL_BLOCK,    __FILE__,    __LINE__    )

                #endif

                ///    @brief    �������[���[�N�̌��o���n�߂܂�
                void    MemoryLeakCheckStart(){
                #ifdef    _DEBUG
                                _CrtSetDbgFlag(    _CRTDBG_ALLOC_MEM_DF    |    _CRTDBG_LEAK_CHECK_DF    );
                #endif
                }

                ///    @brief    ���[�N���o��ɏo�͂��ꂽ���l���w�肷�邱�Ƃ�
                ///    @brief    �f�o�b�O���s���Ƀ��[�N����new�����ꏊ�Ńu���[�N�|�C���g�𔭐������܂�
                ///    @param    value    ���[�N���o���̐��l���w��
                ///    @note    {value}    normal    block    at    ....
                void    BreakAllocNumber(const    int    value){
                #ifdef    _DEBUG
                                _CrtSetBreakAlloc(    value    );    
                #endif
                }

}
#endif