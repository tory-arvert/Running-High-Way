/// @file TemplateBaseClass.h
/// @brief �g�p�p�x�̍����e���v���[�g�p�N���X�̒�`
/// @brief WH(Width,Height) XY(x,y)�Ȃǂ̃e���v���[�g�p�̔ėp�N���X
/// @note 
/// @date 2012/12/12     tory
//====================================================================
//            TemplateBaseClass.h
//--------------------------------------------------------------------
//    �������e : �g�p�p�x�̍����e���v���[�g�p�N���X�̒�`
//    �������e : WH(Width,Height) XY(x,y)�Ȃǂ̃e���v���[�g�p�̔ėp�N���X
//    �쐬�ڍ� : 2012/12/12    tory
//    �⑫     : �Ȃ�
//
//    �ǋL���e : 
//    �쐬�ڍ� : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDED_GAMELIB_BASE_CLASS_H
#define INCLUDED_GAMELIB_BASE_CLASS_H

    /// @brief Width, Height �̃����o�ϐ������N���X
    template <class T>
    class BaseWH{
    protected:
        T mWidth, mHeight;
    public:
        BaseWH(): mWidth(), mHeight(){}  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        BaseWH(const T a_width, const T a_height): mWidth(a_width), mHeight(a_height){}
        virtual ~BaseWH(){}

        void setWidth(const T a_width){ mWidth = a_width;}
        void setHeight(const T a_height){ mHeight = a_height;}
        void setWH(const BaseWH<T>& wh){
            mWidth = wh.width();
            mHeight = wh.height();
        }
        void setWH(const T a_width, const T a_height){
            mWidth = a_width;
            mHeight = a_height;
        }

        const T width()const{ return mWidth;}
        const T height()const{ return mHeight;}
    };

    /// @brief Left, Top �̃����o�ϐ������N���X
    template <class T>
    class BaseLT{
    protected:
        T mLeft, mTop;
    public:
        BaseLT(): mLeft(), mTop(){}  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        BaseLT(const T a_left, const T a_top): mLeft(a_left), mTop(a_top){}
        virtual ~BaseLT(){}

        void setLeft(const T a_left){ mLeft = a_left;}
        void setTop(const T a_top){ mTop = a_top;}
        void setLT(const BaseLT<T>& lt){
            mLeft = lt.left();
            mTop = lt.top();
        }
        void setLT(const T a_left, const T a_top){
            mLeft = a_left;
            mTop = a_top;
        }


        const T left()const{ return mLeft;}
        const T top()const{ return mTop;}
    };

    /// @brief Left, Top, Width, Height �̃����o�ϐ������N���X
    template <class T>
    class BaseUV{
    protected:
        T mLeft, mTop, mWidth, mHeight;
    public:
        BaseUV(): mLeft(), mTop(), mWidth(), mHeight(){}   // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        BaseUV(const T a_left, const T a_top, const T a_width, const T a_height)
            : mLeft(a_left)
            , mTop(a_top)
            , mWidth(a_width)
            , mHeight(a_height)
        {}
        BaseUV(const BaseUV<T>& uv)
            : mLeft( uv.left() )
            , mTop( uv.top() )
            , mWidth( uv.width() )
            , mHeight( uv.height() )
        {}
        virtual ~BaseUV(){}

        void setLeft(const T a_left){ mLeft = a_left;}
        void setTop(const T a_top){ mTop = a_top;}
        void setWidth(const T a_width){ mWidth = a_width;}
        void setHeight(const T a_height){ mHeight = a_height;}
        void setUV(const BaseUV<T>& uv){
            mLeft = uv.left();
            mTop = uv.top();
            mWidth = uv.width();
            mHeight = uv.height();
        }
        void setUV(const T a_left, const T a_top, const T a_width, const T a_height){
            mLeft = a_left;
            mTop = a_top;
            mWidth = a_width;
            mHeight = a_height;
        }

        const T left()const{ return mLeft;}
        const T top()const{ return mTop;}
        const T width()const{ return mWidth;}
        const T height()const{ return mHeight;}
    };

        
    /// @brief Left, Top, Right. Bottom�̃����o�ϐ������N���X
    template <class T>
    class BaseRect{
    protected:
        T mLeft, mTop, mRight, mBottom;
    public:
        BaseRect(): mLeft(), mTop(), mRight(), mBottom(){}   // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        BaseRect(const T a_left, const T a_top, const T a_right, const T a_bottom)
            : mLeft(a_left)
            , mTop(a_top)
            , mRight(a_right)
            , mBottom(a_bottom)
        {}
        BaseRect(const BaseRect<T>& rect)
            : mLeft( rect.left() )
            , mTop( rect.top() )
            , mRight( rect.right() )
            , mBottom( rect.bottom() )
        {}
        virtual ~BaseRect(){}

        void setLeft(const T a_left){ mLeft = a_left;}
        void setTop(const T a_top){ mTop = a_top;}
        void setRight(const T a_right){ mRight = a_right;}
        void setBottom(const T a_bottom){ mBottom = a_bottom;}
        void setRect(const BaseRect<T>& rect){
            mLeft = rect.left();
            mTop = rect.top();
            mRight = rect.right();
            mBottom = rect.bottom();
        }
        void setRect(const T a_left, const T a_top, const T a_right, const T a_bottom){
            mLeft = a_left;
            mTop = a_top;
            mRight = a_right;
            mBottom = a_bottom;
        }

        const T left()const{ return mLeft;}
        const T top()const{ return mTop;}
        const T right()const{ return mRight;}
        const T bottom()const{ return mBottom;}
    };

    /// @brief xy�̃����o�ϐ������N���X
    template <class T>
    class BaseXY{
    protected:
        T mx, my;
    public:
        BaseXY(): mx(),my(){}   // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
        BaseXY(const T a_x, const T a_y): mx(a_x), my(a_y){}
        virtual ~BaseXY(){}

        void setX(const T a_x){ mx = a_x;}
        void setY(const T a_y){ my = a_y;}
        void setXY(const BaseXY<T>& xy){
            mx = xy.x();
            my = xy.y();
        }
        void setXY(const T a_x, const T a_y){
            mx = a_x;
            my = a_y;
        }

        const T x()const{ return mx;}
        const T y()const{ return my;}

    };

#endif