///    @file    tsstream.h
///    @brief    �����R�[�h�؂�ւ��Ή���stringstream��`
///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
///    @note    
///    @date    2012/02/16                    tory
//====================================================================
//                                                tsstream.h
//--------------------------------------------------------------------
//                �������e    :    �����R�[�h�؂�ւ��Ή���stringstream��`
//                �������e    :    ��ɕ�����̉��H���Ɏg�p���܂��B
//                �쐬�ڍ�    :    2012/02/16                tory
//                �⑫                    :    �Ȃ�
//
//                �ǋL���e    :    
//                �쐬�ڍ�    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_TSSTREAM_H
#define    INCLUDED_COMMON_TSSTREAM_H

#include    <tchar.h>
#include    <sstream>

namespace    std{
                
                ///    @brief    ��������H�X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_stringstream<TCHAR>    tstringstream;

                ///    @brief    ������o�̓X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_ostringstream<TCHAR>    tostringstream;

                ///    @brief    ��������̓X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_istringstream<TCHAR>    tistringstream;

}
#endif