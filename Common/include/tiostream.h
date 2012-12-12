///    @file    tiostream.h
///    @brief    �����R�[�h�؂�ւ��Ή���iostream��`
///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
///    @note    
///    @date    2012/02/16                    tory
//====================================================================
//                                                tiostream.h
//--------------------------------------------------------------------
//                �������e    :    �����R�[�h�؂�ւ��Ή���iostream��`
//                �������e    :    ��ɕ�����̓��o�͂Ɏg���܂��B
//                �쐬�ڍ�    :    2012/02/16                tory
//                �⑫                    :    �Ȃ�
//
//                �ǋL���e    :    
//                �쐬�ڍ�    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_TIOSTREAM_H
#define    INCLUDED_COMMON_TIOSTREAM_H

#include    <tchar.h>
#include    <string>
#include    <iostream>

namespace    std{
                
                ///    @brief    tstring�^���`
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_string<TCHAR>    tstring;
                                
                ///    @brief    �W�����̓X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_istream<TCHAR>    tistream;

                ///    @brief    �W���o�̓X�g���[��
                ///    @attention    ���C�u�����쐬���ȂǁA�O���Ɍ��J����ӏ��ł͂��̌^���g�p���Ȃ��ŉ������B
                typedef    std::basic_ostream<TCHAR>    tostream;

                //    �W���o�͂̐؂�ւ��}�N��
                #ifdef    UNICODE
                #define    tcin    wcin    ///<    @brief        �W������(UNICODE)
                #define    tcout    wcout    ///<    @brief        �W���o��(UNICODE)
                #define    tcerr    wcerr    ///<    @brief        �W���G���[(UNICODE)
                #define    tclog    wclog    ///<    @brief        �W�����O(UNICODE)
                #else
                #define    tcin    cin    ///<    @brief    �W������(�}���`�o�C�g����)
                #define    tcout    cout    ///<    @brief    �W���o��(�}���`�o�C�g����)
                #define    tcerr    cerr    ///<    @brief    �W���G���[(�}���`�o�C�g����)
                #define    tclog    clog    ///<    @brief    �W�����O(�}���`�o�C�g����)
                #endif

}
#endif