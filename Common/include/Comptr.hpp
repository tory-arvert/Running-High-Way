/// @file Comptr.h
/// @brief DirectX��COM�C���^�[�t�F�C�X�p�̋��L�|�C���^
/// @brief �Q�ƃJ�E���^��R�s�[���̖����������܂��B
/// @note 
/// @date 2012/12/10     tory
//====================================================================
//            Comptr.h
//--------------------------------------------------------------------
//    �������e : DirectX��COM�C���^�[�t�F�C�X�p�̋��L�|�C���^
//    �������e : �Q�ƃJ�E���^��R�s�[���̖����������܂��B
//    �쐬�ڍ� : 2012/12/10    tory
//    �⑫     : �Ȃ�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================

#ifndef INCLUDED_COMMON_COMPTR_H
#define INCLUDED_COMMON_COMPTR_H

#include <Windows.h>

/// @brief DirectX��COM�C���^�[�t�F�C�X�p�̋��L�|�C���^
template< class T >
class Com_ptr{

    //----------------------------------------------------------
    // �����o�ϐ�
private:

    /// @brief �C���^�[�t�F�C�X�ւ̃_�u���|�C���^
    T**        mppInterface;
    /// @brief COM�|�C���^�̎Q�ƃJ�E���^
    ULONG*    mCounter;


    //----------------------------------------------------------
    // ���ꃁ���o
public:

    /// @brief �R���X�g���N�^
    /// @param ptr �C���^�[�t�F�C�X�ւ̃|�C���^
    /// @param add �Q�ƃJ�E���^�𑝂₷�t���O ( �f�t�H���g:FALSE(0) )
    /// @attention �ÖٓI�^�ϊ�����𖳌������Ă��܂��B
    /// @attention �ʏ�A�R���X�g���N�^�ɓn�����C���^�[�t�F�C�X��
    /// @attention �Q�ƃJ�E���^���������Ă���̂�AddRef�͍s���܂���
    explicit Com_ptr( T* ptr = NULL, BOOL add = FALSE ){

        // �C���^�[�t�F�C�X���L���ł���
        // �Ȃ����t���O�������Ă���Ƃ��ɂ̂ݎQ�ƃJ�E���^�𑝂₵�܂�
        if( ptr && add ){
            ptr->AddRef();
        }

        // �X�}�[�g�|�C���^�����������܂�
        mppInterface = new T*;
        mCounter = new ULONG( 1 );

        // �C���^�[�t�F�C�X���i�[���܂�
        if( ptr ){
            *mppInterface = ptr;
        }else{
            *mppInterface = NULL;
        }
    }

    /// @brief �Öٌ^�L���X�g�R�s�[�R���X�g���N�^
    template< class T2 >
    Com_ptr( Com_ptr< T2 >& src ){

        // �Q�ƃJ�E���^�����L���ăC���N�������g
        mCounter = src.mCounter;
        ++( *mCounter );

        // �C���^�[�t�F�C�X�����L
        mppInterface = static_cast< T** >( src.getWPtr() );
        ( *mppInterface ) = ( src.getPtr() );

        // �C���^�[�t�F�C�X�̎Q�ƃJ�E���^�𑝂₷
        if( *mppInterface ){
            AddRef( *mppInterface );
        }

    }

    /// @brief ���^�R�s�[�R���X�g���N�^
    Com_ptr( const Com_ptr< T >& src ){

        // �Q�ƃJ�E���^�����L���ăC���N�������g
        mCounter = src.mCounter;
        ++( *mCounter );

        // �C���^�[�t�F�C�X�����L
        mppInterface = static_cast< T** >( src.getWPtr() );

        // �C���^�[�t�F�C�X�̎Q�ƃJ�E���^�𑝂₷
        if( *mppInterface ){
            AddRef( *mppInterface );
        }

    }

    /// @brief �R�s�[�R���X�g���N�^(NULL����p)
    Com_ptr(const int null){
        mppInterface = new T*;
        *mppInterface = NULL;
        mCounter = new ULONG( 1 );
    }

    /// @brief �f�X�g���N�^
    virtual ~Com_ptr(){
        // �L���ȃC���^�[�t�F�C�X���ێ�����Ă�����J������
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // COM�Q�ƃJ�E���^�����ɏ���
        ReleaseComRef();
    }

    //----------------------------------------------------------
    // �I�y���[�^
public:

    /// @brief =���^������Z�q(�����I�R�s�[)
    /// @param src �R�s�[����Com_ptr
    Com_ptr< T >& operator =( const Com_ptr< T >& src ){

        // �Q�Ɛ悪����ł���ꍇ�ɂ͏��������Ȃ�
        if( mCounter == src.getCountPtr() ){
            return *this;
        }

        // �ێ�����C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
        if( *mppInterface){
            Release( *mppInterface );
        }

        // ����̓R�s�[���ɂȂ��Ă��܂����ߎQ�ƃJ�E���^�����炷
        ReleaseComRef();

        // �R�s�[������R�s�[
        mppInterface = src.mppInterface;
        mCounter = src.mCounter;

        // �Q�ƃJ�E���^�𑝂₷
        if( *mppInterface ){
            AddRef( *mppInterface );
        }
        ++( *mCounter );

        return *this;
    }

    /// @brief =�Öٌ^�ϊ�������Z�q(�����I�R�s�[)
    /// @param src �R�s�[����Com_ptr
    template< class T2 >
    Com_ptr< T >& operator =( const Com_ptr< T2 >& src ){

        // �Q�Ɛ悪����ł���ꍇ�ɂ͏��������Ȃ�
        if( mCounter == src.getCountPtr() ){
            return *this;
        }

        // �ێ�����C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
        if( *mppInterface){
            Release( *mppInterface );
        }

        // ����̓R�s�[���ɂȂ��Ă��܂����ߎQ�ƃJ�E���^�����炷
        ReleaseComRef();

        // �R�s�[������R�s�[
        mppInterface = static_cast< T** >( src.getWPtr() );
        *mppInterface = src.getPtr();  // �^�`�F�b�N�p�ɑ��
        mCounter = src.getCountPtr();

        // �Q�ƃJ�E���^�𑝂₷
        if( *mppInterface ){
            AddRef( *mppInterface );
        }
        ++( *mCounter );

        return *this; 
    }

    /// @brief =NULL����p���Z�q(�����I�R�s�[)
    /// @param null NULL�l(�����͖�������܂�)
    Com_ptr< T >& operator =( const int null ){

        // �ێ�����C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // ����͋�ɂȂ��Ă��܂����ߎQ�ƃJ�E���^�����炷
        ReleaseComRef();

        // �|�C���^��������
        mppInterface = new T*;
        *mppInterface = NULL;
        mCounter = new ULONG( 1 );

        return *this;
    }

    /// @brief �C���^�[�t�F�C�X������Z�q(�V�K�C���^�[�t�F�C�X�o�^)
    /// @param ptr �o�^����C���^�[�t�F�C�X�ւ̃|�C���^
    /// @note �����I�ɃC���^�[�t�F�C�X��o�^�������ꍇ�ɗp���܂�
    template< class T2 >
    void operator =( T2* ptr ){

        // �ێ�����C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
        if( *mppInterface){
            Release( *mppInterface );
        }

        // ����͐V�K�o�^������̂ɂȂ��Ă��܂����ߎQ�ƃJ�E���^�����炷
        ReleaseComRef();

        // �V�K�o�^������̂ɂȂ�̂�
        // �|�C���^��������
        mppInterface = new T*;
        mCounter = new ULONG( 1 );

        // �C���^�[�t�F�C�X�̑��
        if( ptr ){
            *mppInterface = ptr;
        }else{
            *mppInterface = NULL;
        }

    }

    //----------------------------------------

    /// @brief != ��r���Z�q
    bool operator !=( T* ptr ) const{
        return ( ptr != *mppInterface ? true : false );
    }

    /// @brief != ��r���Z�q
    /// @param src ��r����Com_ptr
    bool operator !=( Com_ptr< T >& src ) const{
        return ( *mppInterface != *( src.mppInterface ) ? true : false );
    }

    /// @brief != ��r���Z�q
    /// @attention NULL��r�p�̂��߈����͖�������܂�
    bool operator !=(const int null ) const{
        return ( *mppInterface != NULL ? true : false );
    }

    //----------------------------------------

    /// @brief == ��r���Z�q
    bool operator ==( T* ptr ) const{
        return ( ptr != *mppInterface ? true : false; );
    }

    /// @brief == ��r���Z�q
    /// @param src ��r����Com_ptr
    bool operator ==( Com_ptr< T >& src ) const{
        return ( *mppInterface != *( src.mppInterface ) ? true : false );
    }
    
    //----------------------------------------

    /// @brief ! �P�����Z�q
    bool operator !() const{
        return ( *mppInterface == NULL ? true : false );
    }

    /// @brief -> �A���[���Z�q
    T* operator ->(){
        return *mppInterface;
    }

    //----------------------------------------------------------
    // �A�N�Z�T
public:
    /// @brief �ێ�����C���^�[�t�F�C�X�ւ̃|�C���^���擾���܂�
    /// @return �ێ�����C���^�[�t�F�C�X�ւ̃|�C���^
    /// @param ���[�U�[����Release���Ă͂����܂���
    T* getPtr() const{
        return ( *mppInterface );
    }

    /// @brief �Q�Ɛ����擾���܂�
    /// @return �ێ�����C���^�[�t�F�C�X�̎Q�Ɛ�
    const unsigned int useCount() const{
        return mCounter;
    }

    //----------------------------------------------------------
    // �����o�֐�
public:

    /// @brief �C���^�[�t�F�C�X�������\�b�h�֓n���_�u���|�C���^���擾���܂�
    /// @return �ێ�����C���^�[�t�F�C�X�ւ̃_�u���|�C���^
    /// @attention ���[�U�[����Release���Ă͂����܂���
    T** ToCreator(){
        // �ێ�����C���^�[�t�F�C�X�̎Q�ƃJ�E���^�����炷
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // ����͐V�����쐬����邽�ߎQ�ƃJ�E���^�����炷
        ReleaseComRef();

        // �|�C���^��������
        mppInterface = new T*;
        *mppInterface = NULL;   // �ꉞ������Ă����܂�
        mCounter = new ULONG( 1 );

        return mppInterface;
    }

    /// @brief �A�b�v�L���X�g�R�s�[
    /// @param src �R�s�[����Com_ptr
    template< class T2 >
    void UpcastCopy( Com_ptr< T2 >& src ){

         // �ێ�����C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
        if( *mppInterface ){
            Release( *mppInterface );
        }

        // ����̓R�s�[���ɂȂ��Ă��܂����ߎQ�ƃJ�E���^�����炷
        ReleaseComRef();

        // �R�s�[������R�s�[
        mppInterface = static_cast< T** >( src.getWPtr() );
        *mppInterface = src.getPtr();  // �^�`�F�b�N�p�ɑ��
        mCounter = src.getCountPtr();

        // �Q�ƃJ�E���^�𑝂₷
        if( *mppInterface ){
            AddRef( *mppInterface );
        }
        ++( *mCounter );

    }

    /// @brief ���^��COM���L�|�C���^�ƃC���^�[�t�F�C�X���������܂�
    /// @param src ���^��COM���L�|�C���^
    /// @return �����̉�
    /// @retval true ����
    /// @retval false ���s
    bool Swap( Com_ptr< T >& src ){
        
        // ���݂��̎Q�ƃJ�E���^���m�F����
        ULONG srcComCount = *( src.getCountPtr() );
        ULONG thisComCount = *mCounter;

        // ���݂��̎Q�ƃJ�E���^�̍����Z�o����
        bool srcDecriment = false; // �����̎Q�ƃJ�E���^������������ꍇ��true�ɂȂ�
        
        ULONG defComCount = thisComCount - srcComCount;
        if( srcComCount > thisComCount ){
            // �����̎Q�Ƃ̂ق��������̂Ńt���O��true�ɂ���
            defComCount = srcComCount - thisComCount;
            srcDecriment = true;
        }

        // �Q�ƃJ�E���^�̑������ƌ��������m�肷��
        T* pReleaseObj;
        T* pAddObj;
        if( srcDecriment ){
            pReleaseObj = src.getPtr();    // �����̂���������
            pAddObj = *mppInterface;
        }else{
            pReleaseObj = *mppInterface;
            pAddObj = src.getPtr();        // �����̂𑝉�����
        }

        // ���݂��̎Q�ƃJ�E���g����������
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

        // �C���^�[�t�F�C�X�|�C���^����������
        T* temp = *src.mppInterface;
        *src.mppInterface = *mppInterface;
        *mppInterface = temp;

        return true;
    }

    //----------------------------------------------------------
    // �w���p�֐�
protected:

    /// @brief �C���^�[�t�F�C�X�ւ̃_�u���|�C���^���擾���܂�
    /// @return �C���^�[�t�F�C�X�ւ̃_�u���|�C���^
    T** getWPtr() const{
        return mppInterface;
    }

    /// @brief �Q�ƃJ�E���^�ւ̃|�C���^���擾���܂�
    /// @return �Q�ƃJ�E���^�ւ̃|�C���^
    const ULONG* getCountPtr() const{
        return mCounter;
    }

    /// @brief �C���^�[�t�F�C�X�����̎Q�ƃJ�E���^�𑝂₵�܂�
    /// @param �����̎Q�ƃJ�E���^�𑝂₵�����C���^�[�t�F�C�X
    /// @attention ���������邽�߈�ʓI�ȃC���^�[�t�F�C�X�p��AddRef()�Ƃ͋�ʂ���܂�
    void AddRef( T* pInterface ){
        pInterface->AddRef();
    }

    /// @brief �C���^�[�t�F�C�X�̎Q�ƃJ�E���^�����炵�܂�
    /// @param �����̎Q�ƃJ�E���^�����炵�����C���^�[�t�F�C�X
    /// @attention ���������邽�߈�ʓI�ȃC���^�[�t�F�C�X�p��Release()�Ƃ͋�ʂ���܂�
    void Release( T* pInterface ){
        pInterface->Release();
    }

    /// @brief �Q�ƃJ�E���^�����炵�A0�̎��_�ŃC���^�[�t�F�C�X���J�����܂�
    void ReleaseComRef(){
        --( *mCounter );
        if( *mCounter <= 0 ){
            delete mppInterface;
            delete mCounter;
        }
    }

};  // end of class Com_Ptr

#endif