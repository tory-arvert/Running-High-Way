///    @file    tsstream.h
///    @brief    文字コード切り替え対応のstringstream定義
///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
///    @note    
///    @date    2012/02/16                    tory
//====================================================================
//                                                tsstream.h
//--------------------------------------------------------------------
//                処理内容    :    文字コード切り替え対応のstringstream定義
//                処理内容    :    主に文字列の加工等に使用します。
//                作成詳細    :    2012/02/16                tory
//                補足                    :    なし
//
//                追記内容    :    
//                作成詳細    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_TSSTREAM_H
#define    INCLUDED_COMMON_TSSTREAM_H

#include    <tchar.h>
#include    <sstream>

namespace    std{
                
                ///    @brief    文字列加工ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_stringstream<TCHAR>    tstringstream;

                ///    @brief    文字列出力ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_ostringstream<TCHAR>    tostringstream;

                ///    @brief    文字列入力ストリーム
                ///    @attention    ライブラリ作成時など、外部に公開する箇所ではこの型を使用しないで下さい。
                typedef    std::basic_istringstream<TCHAR>    tistringstream;

}
#endif