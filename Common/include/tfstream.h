///    @file    tfstream.h
///    @brief    �����R�[�h�؂�ւ��Ή���fstream��`
///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
///    @note    
///    @date    2012/02/16                    tory
//====================================================================
//                                                tfstream.h
//--------------------------------------------------------------------
//                �������e    :    �����R�[�h�؂�ւ��Ή���fstream��`
//                �������e    :    ��Ƀt�@�C���̓��o�͂Ɏg���܂��B
//                �쐬�ڍ�    :    2012/02/16                tory
//                �⑫                    :    �Ȃ�
//
//                �ǋL���e    :    
//                �쐬�ڍ�    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_TFSTREAM_H
#define    INCLUDED_COMMON_TFSTREAM_H

#include    <tchar.h>
#include    <fstream>

namespace    std{

                ///    @brief    �t�@�C���X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_fstream<TCHAR>    tfstream;

                ///    @brief    �t�@�C�����̓X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_ifstream<TCHAR>    tifstream;

                ///    @brief    �t�@�C���o�̓X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_ofstream<TCHAR>    tofstream;

}
#endif