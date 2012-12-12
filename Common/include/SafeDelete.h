///    @file
///    @brief        SAFEDELETEサポートヘッダ
///    @data            2012/06/24

#ifndef    INCLUDED_COMMON_SAFE_DELETE
#define    INCLUDED_COMMON_SAFE_DELETE

///    @brief        オブジェクトの存在を確認し開放した後NULLを設定するマクロ
///    @attention        配列の解放にはSAFE_DELETE_ARRAYを使用してください。
#define    SAFE_DELETE(p)                                        {    if(p){delete    (p);                        (p)=NULL;    }    }

///    @brief        配列オブジェクトの存在を確認し開放した後NULLを設定するマクロ
#define    SAFE_DELETE_ARRAY(p)                {    if(p){delete[]    (p);                (p)=NULL;    }    }

///    @brief        COMオブジェクトの存在を確認し開放した後NULLを設定するマクロ
#define    SAFE_RELEASE(p)                                    {    if(p){(p)->Release();        (p)=NULL;    }    }

#endif