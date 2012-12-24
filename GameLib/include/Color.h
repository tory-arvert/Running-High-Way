/// @file Color.h
/// @brief �g�p�p�x�̑���Color�N���X�̒�`
/// @brief (A)RGB�N���X�Ƃ��Čp�����Ďg�p���܂�
/// @note Color4��Color3�͈ꕔ�݊��@�\������܂�
/// @date 2012/11/19     tory
//====================================================================
//            Color.h
//--------------------------------------------------------------------
//    �������e : �g�p�p�x�̑���Color�N���X�̒�`
//    �������e : (A)RGB�N���X�Ƃ��Čp�����Ďg�p���܂�
//    �쐬�ڍ� : 2012/11/19    tory
//    �⑫     : Color4��Color3�͈ꕔ�݊��@�\������܂�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_COLOR_H
#define INCLUDED_GAMELIB_COLOR_H


    /// @brief Alpha, Red, Green, Blue�p�̃����o�ϐ������N���X
    template <class T>
    class Color4{
    protected:
        T mAlpha, mRed, mGreen, mBlue;
    public:
        Color4(): mAlpha(255), mRed(), mGreen(), mBlue(){}   // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        Color4(const T a_alpha, const T a_red, const T a_green, const T a_blue)
            : mAlpha(a_alpha)
            , mRed(a_red)
            , mGreen(a_green)
            , mBlue(a_blue)
        {}
        Color4(const Color4<T>& color)
            : mAlpha( color.a() )
            , mRed( color.r() )
            , mGreen( color.g() )
            , mBlue( color.b() )
        {}
        Color4(const Color3<T>& color)
            : mAlpha( 255 )
            , mRed( color.r() )
            , mGreen( color.g() )
            , mBlue( color.b() )
        {}

        virtual ~Color4(){}

        void setA(const T a_alpha){ mAlpha = a_alpha;}
        void setR(const T a_red){ mRed = a_red;}
        void setG(const T a_green){ mGreen = a_green;}
        void setB(const T a_blue){ mBlue = a_blue;}
        void setARGB(const Color4<T>& color){
            mAlpha  = color.a();
            mRed    = color.r();
            mGreen  = color.g();
            mBlue   = color.b();
        }
        void setARGB(const T a_alpha, const T a_red, const T a_green, const T a_blue){
            mAlpha  = a_alpha;
            mRed    = a_red;
            mGreen  = a_green;
            mBlue   = a_blue;
        }
        void setRGB(const Color4<T>& color){
            mRed    = color.r();
            mGreen  = color.g();
            mBlue   = color.b();
        }
        void setRGB(const T a_red, const T a_green, const T a_blue){
            mRed    = a_red;
            mGreen  = a_green;
            mBlue   = a_blue;
        }
        void setRGB(const Color3<T>& color){
            mRed    = color.r();
            mGreen  = color.g();
            mBlue   = color.b();
        }

        const T a()const{ return mAlpha;}
        const T r()const{ return mRed;}
        const T g()const{ return mGreen;}
        const T b()const{ return mBlue;}
    };


    /// @brief Red, Green, Blue�p�̃����o�ϐ������N���X
    template <class T>
    class Color3{
    protected:
        T mRed, mGreen, mBlue;
    public:
        Color3(): mRed(), mGreen(), mBlue(){}  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        Color3(const T a_red, const T a_green, const T a_blue)
            : mRed(a_red)
            , mGreen(a_green)
            , mBlue(a_blue)
        {}
        Color3(const Color3<T>& color)
            : mRed( color.r() )
            , mGreen( color.g() )
            , mBlue( color.b() )
        {}
        Color3(const Color4<T>& color)
            : mRed( color.r() )
            , mGreen( color.g() )
            , mBlue( color.b() )
        {}

        virtual ~Color3(){}

        void setR(const T a_red){ mRed = a_red;}
        void setG(const T a_green){ mGreen = a_green;}
        void setB(const T a_blue){ mBlue = a_blue;}
        void setRGB(const Color3<T>& color){
            mRed    = color.r();
            mGreen  = color.g();
            mBlue   = color.b();
        }
        void setRGB(const T a_red, const T a_green, const T a_blue){
            mRed    = a_red;
            mGreen  = a_green;
            mBlue   = a_blue;
        }
        void setRGB(const Color4<T>& color){
            mRed    = color.r();
            mGreen  = color.g();
            mBlue   = color.b();
        }

        const T r()const{ return mRed;}
        const T g()const{ return mGreen;}
        const T b()const{ return mBlue;}
    };

#endif


