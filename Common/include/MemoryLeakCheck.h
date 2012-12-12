///    @file    MemoryLeakCheck.h
///    @brief    CRTライブラリを使用したメモリリークの検出
/*
@note            メモリチェックを有効化したいプログラムの
                                エントリーポイント(例:main関数)の先頭に以下のコードを記述する。
                                @code
                                _CrtSetDbgFlag(    _CRTDBG_ALLOC_MEM_DF    |    _CRTDBG_LEAK_CHECK_DF    );
                                @endcode
                                また、以下のメソッドの引数に検出したリークの数値を代入することで
                                リーク元となる生成場所で止まることができる。
                                _CrtSetBreakAlloc(    xxx    );    //    xxxが検出したリークの数値
*/
///    @attention    newを書き換えるため一部のライブラリ(例:DirectX関連)で
///    @attention    コンパイルエラーが発生することがある。
///    @attention    そのためincludeの順番は最後に持っていくように気をつけること。
///    @date    2012/12/11                    tory
//====================================================================
//                                                MemoryLeakCheck.h
//--------------------------------------------------------------------
//                処理内容    :    CRTライブラリを使用したメモリリークの検出
//                作成詳細    :    2012/12/11                tory
//                補足                    :    メモリチェックを有効化したいプログラムの
//                補足                    :    エントリーポイント(例:main関数)の先頭に以下のコードを記述する。
//                補足                    :    _CrtSetDbgFlag(    _CRTDBG_ALLOC_MEM_DF    |    _CRTDBG_LEAK_CHECK_DF    );
//    
//                追記内容    :    
//                作成詳細    :    2011/04/01                YourName
//                                    
//====================================================================

#ifndef    INCLUDED_COMMON_MEMORYLEAKCHECK_H
#define    INCLUDED_COMMON_MEMORYLEAKCHECK_H

namespace    Common{
                //デバッグ時にメモリリークの検出を有効化する
                #ifdef    _DEBUG

                #define    _CRTDBG_MAP_ALLOC
                #include    <crtdbg.h>
                #define    new    new(    _NORMAL_BLOCK,    __FILE__,    __LINE__    )

                #endif

                ///    @brief    メモリーリークの検出を始めます
                void    MemoryLeakCheckStart(){
                #ifdef    _DEBUG
                                _CrtSetDbgFlag(    _CRTDBG_ALLOC_MEM_DF    |    _CRTDBG_LEAK_CHECK_DF    );
                #endif
                }

                ///    @brief    リーク検出後に出力された数値を指定することで
                ///    @brief    デバッグ実行中にリーク元をnewした場所でブレークポイントを発生させます
                ///    @param    value    リーク検出時の数値を指定
                ///    @note    {value}    normal    block    at    ....
                void    BreakAllocNumber(const    int    value){
                #ifdef    _DEBUG
                                _CrtSetBreakAlloc(    value    );    
                #endif
                }

}
#endif