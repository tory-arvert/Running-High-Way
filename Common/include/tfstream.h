///    @file    tfstream.h
///    @brief    文字コード切り替え対応のfstream定義
///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
///    @note    
///    @date    2012/02/16                    tory
//====================================================================
//                                                tfstream.h
//--------------------------------------------------------------------
//                処理内容    :    文字コード切り替え対応のfstream定義
//                処理内容    :    主にファイルの入出力に使います。
//                作成詳細    :    2012/02/16                tory
//                補足                    :    なし
//
//                追記内容    :    
//                作成詳細    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_TFSTREAM_H
#define    INCLUDED_COMMON_TFSTREAM_H

#include    <tchar.h>
#include    <fstream>

namespace    std{

                ///    @brief    ファイルストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_fstream<TCHAR>    tfstream;

                ///    @brief    ファイル入力ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_ifstream<TCHAR>    tifstream;

                ///    @brief    ファイル出力ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_ofstream<TCHAR>    tofstream;

}
#endif