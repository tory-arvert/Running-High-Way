/// @file Color.h
/// @brief 使用頻度の多いColorクラスの定義
/// @brief (A)RGBクラスとして継承して使用します
/// @note Color4とColor3は一部互換機能があります
/// @date 2012/11/19     tory
//====================================================================
//            Color.h
//--------------------------------------------------------------------
//    処理内容 : 使用頻度の多いColorクラスの定義
//    処理内容 : (A)RGBクラスとして継承して使用します
//    作成詳細 : 2012/11/19    tory
//    補足     : Color4とColor3は一部互換機能があります
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_COLOR_H
#define INCLUDED_GAMELIB_COLOR_H


    /// @brief Alpha, Red, Green, Blue用のメンバ変数を持つクラス
    template <class T>
    class Color4{
    protected:
        T mAlpha, mRed, mGreen, mBlue;
    public:
        Color4(): mAlpha(255), mRed(), mGreen(), mBlue(){}   // 初期化子を使うことでその型のデフォルトコンストラクタ使用
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


    /// @brief Red, Green, Blue用のメンバ変数を持つクラス
    template <class T>
    class Color3{
    protected:
        T mRed, mGreen, mBlue;
    public:
        Color3(): mRed(), mGreen(), mBlue(){}  // 初期化子を使うことでその型のデフォルトコンストラクタ使用
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


