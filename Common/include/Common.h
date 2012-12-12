/// @file Common.h
/// @brief SAFE_DELETE�╶���X�g���[���Ȃ�
/// @brief ���ʂ��Ă悭�g���w�b�_�[�Ȃǂ̂܂Ƃ�
/// @attention  �قڑS�Ă�cpp�ɃC���N���[�h���Ă��邽��
/// @attention  �ҏW���̓R���p�C���Ɏ��Ԃ�������܂��B
/// @date 2011/06/22     tory

//====================================================================
//            Common.h
//--------------------------------------------------------------------
//    �������e : SAFE_DELETE�╶���X�g���[���Ȃ�
//    �������e : ���ʂ��Ă悭�g���w�b�_�[�Ȃǂ̂܂Ƃ�
//    �쐬�ڍ� : 2011/06/22    tory
//    �⑫     : �قڑS�Ă�cpp�ɃC���N���[�h���Ă��邽��
//             : �ҏW���̓R���p�C���Ɏ��Ԃ�������܂��B
//
//    �ǋL���e : ���t�@�N�^�����O
//    �쐬�ڍ� : 2012/12/11    YourName
//         
//====================================================================

#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

// �����R�[�h�̈Ⴂ���z������X�g���[���@�\
#include "tfstream.h"
#include "tiostream.h"
#include "tsstream.h"

// �I�u�W�F�N�g�̈��S�ȉ��
#include "SafeDelete.h"


// t�Ŏw�肵���ϐ���Min(�ŏ�)��Max(�ő�)�ȓ��Ɏ��܂�悤�ɏC������
// �Ȃ��At�̒l�͂��̂܂܁A�Ԃ�l�ɏC���l������
template <class T>
inline T Limit( const T& t, const T& Min, const T& Max){
    T tempT;
    tempT = (Min)<(t)?(t):(Min);
    tempT = (tempT)<(Max)?(tempT):(Max);
    return( tempT );
}

#endif