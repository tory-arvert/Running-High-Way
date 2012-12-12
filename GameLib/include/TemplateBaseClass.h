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

//#include <memory>       // shared_ptr�p

using namespace std;

namespace GameLib{

    namespace Graphics{

        template <class T>
        /// @brief Width,Height�̃����o�ϐ������N���X
        class WH<T>{
        protected:
            T mWidth, mHeight;
            WH(): mWidth(), mHeight(){};  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
            WH(const T width, const T height): mWidth(width), mHeight(height){};
            ~WH(){};

            T setWidth(const T Width){ mWidth = width;}
            T setHeight(const T height){ mHeight = height;}
            T setWH(const WH<T> wh){
                mWidth = wh.width();
                mHeight = wh.height();
            }

            const T width()const{ return mWidth;}
            const T height()const{ return mHeight;}
        ;

        template <class T>
        /// @brief Left,Top�̃����o�ϐ������N���X
        class LT<T>{
        protected:
            T mLeft, mTop;
            LT(): mLeft(), mTop(){};  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
            LT(const T left, const T top): mLeft(left), mTop(top){};
            ~LT(){};

            T setLeft(const T left){ mLeft = left;}
            T setTop(const T top){ mTop = top;}

            const T left()const{ return mLeft;}
            const T top()const{ return mTop;}
        };

        template <class T>
        /// @brief left, top, right. bottom�̃����o�ϐ������N���X
        class UV<T>{
        protected:
            T mLeft, mTop, mWidth, mHeight;
            UV(): mLeft(), mTop(), mWidth(), mHeight(){};  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
            UV(const T left, const T top, const T width, const T height)
                : mLeft(left)
                , mTop(top)
                , mWidth(width)
                , mHeight(height)
            {};
            UV(const UV<T> uv)
                : mLeft( uv.left() )
                , mTop( uv.top() )
                , mWidth( uv.width() )
                , mHeight( uv.height() )
            {};
            ~UV(){};

            T setLeft(const T left){ mLeft = left;}
            T setTop(const T top){ mTop = top;}
            T setWidth(const T Width){ mWidth = width;}
            T setHeight(const T height){ mHeight = height;}
            T setUV(const UV<T> uv){
                mLeft = uv.left();
                mTop = uv.top();
                mWidth = uv.width();
                mHeight = uv.height();
            }

            const T left()const{ return mLeft;}
            const T top()const{ return mTop;}
            const T width()const{ return mWidth;}
            const T height()const{ return mHeight;}
        };

        
        template <class T>
        /// @brief left, top, right. bottom�̃����o�ϐ������N���X
        class Rect<T>{
        protected:
            T mLeft, mTop, mRight, mBottom;
            LT(): mLeft(), mTop(), mRight(), mBottom(){};  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
            LT(const T left, const T top, const T right, const T bottom)
                : mLeft(left)
                , mTop(top)
                , mRight(right)
                , mBottom(bottom)
            {};
            LT(const Rect<T> rect)
                : mLeft( rect.left() )
                , mTop( rect.top() )
                , mRight( rect.right() )
                , mBottom( rect.bottom() )
            {};
            ~LT(){};

            T setLeft(const T left){ mLeft = left;}
            T setTop(const T top){ mTop = top;}
            T setRight(const T right){ mRight = right;}
            T setBottom(const T bottom){ mBottom = bottom;}
            T setRect(const Rect<T> rect){
                mLeft = rect.left();
                mTop = rect.top();
                mRight = rect.right();
                mBottom = rect.bottom();
            }

            const T left()const{ return mLeft;}
            const T top()const{ return mTop;}
            const T right()const{ return mRight;}
            const T bottom()const{ return mBottom;}
        };

        template <class T>
        /// @brief xy�̃����o�ϐ������N���X
        class XY<T>{
        protected:
            T mx, my;
            XY(): mx(),my(){};  // �������q���g�����Ƃł��̌^�̃f�t�H���g�R���X�g���N�^�g�p
            XY(const T x, const T y): mx(x), my(y){};
            ~XY(){};

            T setX(const T x){ mx = x;}
            T setY(const T y){ my = y;}
            T setXY(const XY<T> xy){
                mx = xy.x();
                my = xy.y();
            }

            const T x()const{ return mx;}
            const T y()const{ return my;}

        };

    }  // end of namespace Graphics
} // end of namespace GameLib

#endif