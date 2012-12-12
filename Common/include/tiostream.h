///    @file    tiostream.h
///    @brief    文字コード切り替え対応のiostream定義
///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
///    @note    
///    @date    2012/02/16                    tory
//====================================================================
//                                                tiostream.h
//--------------------------------------------------------------------
//                処理内容    :    文字コード切り替え対応のiostream定義
//                処理内容    :    主に文字列の入出力に使います。
//                作成詳細    :    2012/02/16                tory
//                補足                    :    なし
//
//                追記内容    :    
//                作成詳細    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_TIOSTREAM_H
#define    INCLUDED_COMMON_TIOSTREAM_H

#include    <tchar.h>
#include    <string>
#include    <iostream>

namespace    std{
                
                ///    @brief    tstring型を定義
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_string<TCHAR>    tstring;
                                
                ///    @brief    標準入力ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_istream<TCHAR>    tistream;

                ///    @brief    標準出力ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_ostream<TCHAR>    tostream;

                //    標準出力の切り替えマクロ
                #ifdef    UNICODE
                #define    tcin    wcin    ///<    @brief        標準入力(UNICODE)
                #define    tcout    wcout    ///<    @brief        標準出力(UNICODE)
                #define    tcerr    wcerr    ///<    @brief        標準エラー(UNICODE)
                #define    tclog    wclog    ///<    @brief        標準ログ(UNICODE)
                #else
                #define    tcin    cin    ///<    @brief    標準入力(マルチバイト文字)
                #define    tcout    cout    ///<    @brief    標準出力(マルチバイト文字)
                #define    tcerr    cerr    ///<    @brief    標準エラー(マルチバイト文字)
                #define    tclog    clog    ///<    @brief    標準ログ(マルチバイト文字)
                #endif

}
#endif