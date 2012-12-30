/// @file Comptr.h
/// @brief DirectXのCOMインターフェイス用の共有ポインタ
/// @brief 参照カウンタやコピー等の問題を解決します。
/// @note 
/// @date 2012/12/10     tory
//====================================================================
//            Comptr.h
//--------------------------------------------------------------------
//    処理内容 : DirectXのCOMインターフェイス用の共有ポインタ
//    処理内容 : 参照カウンタやコピー等の問題を解決します。
//    作成詳細 : 2012/12/10    tory
//    補足     : なし
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================

#ifndef INCLUDED_COMMON_COMPTR_H
#define INCLUDED_COMMON_COMPTR_H

#include <Windows.h>

/// @brief DirectXのCOMインターフェイス用の共有ポインタ
template< class T >
class Com_ptr{

    //----------------------------------------------------------
    // メンバ変数
private:

    /// @brief インターフェイスへのダブルポインタ
    T**        mppInterface;
    /// @brief COMポインタの参照カウンタ
    ULONG*    mCounter;


    //----------------------------------------------------------
    // 特殊メンバ
public:

    /// @brief コンストラクタ
    /// @param ptr インターフェイスへのポインタ
    /// @param add 参照カウンタを増やすフラグ ( デフォルト:FALSE(0) )
    /// @attention 暗黙的型変換代入を無効化しています。
    /// @attention 通常、コンストラクタに渡されるインターフェイスは
    /// @attention 参照カウンタが増加しているのでAddRefは行いません
    explicit Com_ptr( T* ptr = NULL, BOOL add = FALSE ){

        // インターフェイスが有効であり
        // なおかつフラグが立っているときにのみ参照カウンタを増やします
        if( ptr && add ){
            ptr->AddRef();
        }

        // スマートポインタを初期化します
        mppInterface = new T*;
        mCounter = new ULONG( 1 );

        // インターフェイスを格納します
        if( ptr ){
            *mppInterface = ptr;
        }else{
            *mppInterface = NULL;
        }
    }

    /// @brief 暗黙型キャストコピーコンストラクタ
    template< class T2 >
    Com_ptr( Com_ptr< T2 >& src ){

        // 参照カウンタを共有してインクリメント
        mCounter = src.mCounter;
        ++( *mCounter );

        // インターフェイスを共有
        mppInterface = static_cast< T** >( src.getWPtr() );
        ( *mppInterface ) = ( src.getPtr() );

        // インターフェイスの参照カウンタを増やす
        if( *mppInterface ){
            AddRef( *mppInterface );
        }

    }

    /// @brief 同型コピーコンストラクタ
    Com_ptr( const Com_ptr< T >& src ){

        // 参照カウンタを共有してインクリメント
        mCounter = src.mCounter;
        ++( *mCounter );

        // インターフェイスを共有
        mppInterface = static_cast< T** >( src.getWPtr() );

        // インターフェイスの参照カウンタを増やす
        if( *mppInterface ){
            AddRef( *mppInterface );
        }

    }

    /// @brief コピーコンストラクタ(NULL代入用)
    Com_ptr(const int null){
        mppInterface = new T*;
        *mppInterface = NULL;
        mCounter = new ULONG( 1 );
    }

    /// @brief デストラクタ
    virtual ~Com_ptr(){
        // 有効なインターフェイスが保持されていたら開放する
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // COM参照カウンタを元に処理
        ReleaseComRef();
    }

    //----------------------------------------------------------
    // オペレータ
public:

    /// @brief =同型代入演算子(明示的コピー)
    /// @param src コピー元のCom_ptr
    Com_ptr< T >& operator =( const Com_ptr< T >& src ){

        // 参照先が同一である場合には処理をしない
        if( mCounter == src.getCountPtr() ){
            return *this;
        }

        // 保持するインターフェイスの参照カウンタを1つ減らす
        if( *mppInterface){
            Release( *mppInterface );
        }

        // 自らはコピー元になってしまうため参照カウンタを減らす
        ReleaseComRef();

        // コピー元からコピー
        mppInterface = src.mppInterface;
        mCounter = src.mCounter;

        // 参照カウンタを増やす
        if( *mppInterface ){
            AddRef( *mppInterface );
        }
        ++( *mCounter );

        return *this;
    }

    /// @brief =暗黙型変換代入演算子(明示的コピー)
    /// @param src コピー元のCom_ptr
    template< class T2 >
    Com_ptr< T >& operator =( const Com_ptr< T2 >& src ){

        // 参照先が同一である場合には処理をしない
        if( mCounter == src.getCountPtr() ){
            return *this;
        }

        // 保持するインターフェイスの参照カウンタを1つ減らす
        if( *mppInterface){
            Release( *mppInterface );
        }

        // 自らはコピー元になってしまうため参照カウンタを減らす
        ReleaseComRef();

        // コピー元からコピー
        mppInterface = static_cast< T** >( src.getWPtr() );
        *mppInterface = src.getPtr();  // 型チェック用に代入
        mCounter = src.getCountPtr();

        // 参照カウンタを増やす
        if( *mppInterface ){
            AddRef( *mppInterface );
        }
        ++( *mCounter );

        return *this; 
    }

    /// @brief =NULL代入用演算子(明示的コピー)
    /// @param null NULL値(引数は無視されます)
    Com_ptr< T >& operator =( const int null ){

        // 保持するインターフェイスの参照カウンタを1つ減らす
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // 自らは空になってしまうため参照カウンタを減らす
        ReleaseComRef();

        // ポインタを初期化
        mppInterface = new T*;
        *mppInterface = NULL;
        mCounter = new ULONG( 1 );

        return *this;
    }

    /// @brief インターフェイス代入演算子(新規インターフェイス登録)
    /// @param ptr 登録するインターフェイスへのポインタ
    /// @note 明示的にインターフェイスを登録したい場合に用います
    template< class T2 >
    void operator =( T2* ptr ){

        // 保持するインターフェイスの参照カウンタを1つ減らす
        if( *mppInterface){
            Release( *mppInterface );
        }

        // 自らは新規登録するものになってしまうため参照カウンタを減らす
        ReleaseComRef();

        // 新規登録するものになるので
        // ポインタを初期化
        mppInterface = new T*;
        mCounter = new ULONG( 1 );

        // インターフェイスの代入
        if( ptr ){
            *mppInterface = ptr;
        }else{
            *mppInterface = NULL;
        }

    }

    //----------------------------------------

    /// @brief != 比較演算子
    bool operator !=( T* ptr ) const{
        return ( ptr != *mppInterface ? true : false );
    }

    /// @brief != 比較演算子
    /// @param src 比較元のCom_ptr
    bool operator !=( Com_ptr< T >& src ) const{
        return ( *mppInterface != *( src.mppInterface ) ? true : false );
    }

    /// @brief != 比較演算子
    /// @attention NULL比較用のため引数は無視されます
    bool operator !=(const int null ) const{
        return ( *mppInterface != NULL ? true : false );
    }

    //----------------------------------------

    /// @brief == 比較演算子
    bool operator ==( T* ptr ) const{
        return ( ptr != *mppInterface ? true : false; );
    }

    /// @brief == 比較演算子
    /// @param src 比較元のCom_ptr
    bool operator ==( Com_ptr< T >& src ) const{
        return ( *mppInterface != *( src.mppInterface ) ? true : false );
    }
    
    //----------------------------------------

    /// @brief ! 単項演算子
    bool operator !() const{
        return ( *mppInterface == NULL ? true : false );
    }

    /// @brief -> アロー演算子
    T* operator ->(){
        return *mppInterface;
    }

    //----------------------------------------------------------
    // アクセサ
public:
    /// @brief 保持するインターフェイスへのポインタを取得します
    /// @return 保持するインターフェイスへのポインタ
    /// @param ユーザー側でReleaseしてはいけません
    T* getPtr() const{
        return ( *mppInterface );
    }

    /// @brief 参照数を取得します
    /// @return 保持するインターフェイスの参照数
    const unsigned int useCount() const{
        return mCounter;
    }

    //----------------------------------------------------------
    // メンバ関数
public:

    /// @brief インターフェイス生成メソッドへ渡すダブルポインタを取得します
    /// @return 保持するインターフェイスへのダブルポインタ
    /// @attention ユーザー側でReleaseしてはいけません
    T** ToCreator(){
        // 保持するインターフェイスの参照カウンタを減らす
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // 自らは新しく作成されるため参照カウンタを減らす
        ReleaseComRef();

        // ポインタを初期化
        mppInterface = new T*;
        *mppInterface = NULL;   // 一応代入しておきます
        mCounter = new ULONG( 1 );

        return mppInterface;
    }

    /// @brief アップキャストコピー
    /// @param src コピー元のCom_ptr
    template< class T2 >
    void UpcastCopy( Com_ptr< T2 >& src ){

         // 保持するインターフェイスの参照カウンタを1つ減らす
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // 自らはコピー元になってしまうため参照カウンタを減らす
        ReleaseComRef();

        // コピー元からコピー
        mppInterface = static_cast< T** >( src.getWPtr() );
        *mppInterface = src.getPtr();  // 型チェック用に代入
        mCounter = src.getCountPtr();

        // 参照カウンタを増やす
        if( *mppInterface ){
            AddRef( *mppInterface );
        }
        ++( *mCounter );

    }

    /// @brief 同型のCOM共有ポインタとインターフェイスを交換します
    /// @param src 同型のCOM共有ポインタ
    /// @return 成功の可否
    /// @retval true 成功
    /// @retval false 失敗
    bool Swap( Com_ptr< T >& src ){
        
        // お互いの参照カウンタを確認する
        ULONG srcComCount = *( src.getCountPtr() );
        ULONG thisComCount = *mCounter;

        // お互いの参照カウンタの差を算出する
        bool srcDecriment = false; // 引数の参照カウンタを減少させる場合にtrueになる
        
        ULONG defComCount = thisComCount - srcComCount;
        if( srcComCount > thisComCount ){
            // 引数の参照のほうが多いのでフラグをtrueにする
            defComCount = srcComCount - thisComCount;
            srcDecriment = true;
        }

        // 参照カウンタの増加側と減少側を確定する
        T* pReleaseObj;
        T* pAddObj;
        if( srcDecriment ){
            pReleaseObj = src.getPtr();    // 引数のを減少する
            pAddObj = *mppInterface;
        }else{
            pReleaseObj = *mppInterface;
            pAddObj = src.getPtr();        // 引数のを増加する
        }

        // お互いの参照カウントを交換する
        if( pReleaseObj && pAddObj ){
            for( ULONG i = 0; i < defComCount; ++i ){
                pReleaseObj->Release();
                pAddObj->AddRef();
            }
        }
        else if( pReleaseObj && ( pAddObj == NULL ) ){
            for ( ULONG i = 0; i < defComCount; ++i ){
                pReleaseObj->Release();
            }
        }
        else if( ( pReleaseObj == NULL ) && pAddObj ){
            for ( ULONG i = 0; i < defComCount; ++i ){
                pAddObj->AddRef();
            }
        }

        // インターフェイスポインタを交換する
        T* temp = *src.mppInterface;
        *src.mppInterface = *mppInterface;
        *mppInterface = temp;

        return true;
    }

    //----------------------------------------------------------
    // ヘルパ関数
protected:

    /// @brief インターフェイスへのダブルポインタを取得します
    /// @return インターフェイスへのダブルポインタ
    T** getWPtr() const{
        return mppInterface;
    }

    /// @brief 参照カウンタへのポインタを取得します
    /// @return 参照カウンタへのポインタ
    const ULONG* getCountPtr() const{
        return mCounter;
    }

    /// @brief インターフェイス内部の参照カウンタを増やします
    /// @param 内部の参照カウンタを増やしたいインターフェイス
    /// @attention 引数があるため一般的なインターフェイス用のAddRef()とは区別されます
    void AddRef( T* pInterface ){
        pInterface->AddRef();
    }

    /// @brief インターフェイスの参照カウンタを減らします
    /// @param 内部の参照カウンタを減らしたいインターフェイス
    /// @attention 引数があるため一般的なインターフェイス用のRelease()とは区別されます
    void Release( T* pInterface ){
        pInterface->Release();
    }

    /// @brief 参照カウンタを減らし、0の時点でインターフェイスを開放します
    void ReleaseComRef(){
        --( *mCounter );
        if( *mCounter <= 0 ){
            delete mppInterface;
            delete mCounter;
        }
    }

};  // end of class Com_Ptr

#endif