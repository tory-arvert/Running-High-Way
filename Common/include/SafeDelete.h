///    @file
///    @brief        SAFEDELETE�T�|�[�g�w�b�_
///    @data            2012/06/24

#ifndef    INCLUDED_COMMON_SAFE_DELETE
#define    INCLUDED_COMMON_SAFE_DELETE

///    @brief        �I�u�W�F�N�g�̑��݂��m�F���J��������NULL��ݒ肷��}�N��
///    @attention        �z��̉���ɂ�SAFE_DELETE_ARRAY���g�p���Ă��������B
#define    SAFE_DELETE(p)                                        {    if(p){delete    (p);                        (p)=NULL;    }    }

///    @brief        �z��I�u�W�F�N�g�̑��݂��m�F���J��������NULL��ݒ肷��}�N��
#define    SAFE_DELETE_ARRAY(p)                {    if(p){delete[]    (p);                (p)=NULL;    }    }

///    @brief        COM�I�u�W�F�N�g�̑��݂��m�F���J��������NULL��ݒ肷��}�N��
#define    SAFE_RELEASE(p)                                    {    if(p){(p)->Release();        (p)=NULL;    }    }

#endif