/// @file Common.h
/// @brief SAFE_DELETEや文字ストリームなど
/// @brief 共通してよく使うヘッダーなどのまとめ
/// @attention  ほぼ全てのcppにインクルードしているため
/// @attention  編集時はコンパイルに時間がかかります。
/// @date 2011/06/22     tory

//====================================================================
//            Common.h
//--------------------------------------------------------------------
//    処理内容 : SAFE_DELETEや文字ストリームなど
//    処理内容 : 共通してよく使うヘッダーなどのまとめ
//    作成詳細 : 2011/06/22    tory
//    補足     : ほぼ全てのcppにインクルードしているため
//             : 編集時はコンパイルに時間がかかります。
//
//    追記内容 : リファクタリング
//    作成詳細 : 2012/12/11    YourName
//         
//====================================================================

#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

// 文字コードの違いを吸収するストリーム機能
#include "tfstream.h"
#include "tiostream.h"
#include "tsstream.h"

// オブジェクトの安全な解放
#include "SafeDelete.h"


// tで指定した変数がMin(最小)とMax(最大)以内に収まるように修正する
// なお、tの値はそのまま、返り値に修正値が入る
template <class T>
inline T Limit( const T& t, const T& Min, const T& Max){
    T tempT;
    tempT = (Min)<(t)?(t):(Min);
    tempT = (tempT)<(Max)?(tempT):(Max);
    return( tempT );
}

#endif