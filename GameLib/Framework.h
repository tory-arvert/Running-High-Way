/// @file  Framework.h
/// @brief 一番初めの全体の初期化等をする処理 - 定義
/// @note 
/// @date 2011/10/15     tory

//====================================================================
//              Framework.h
//--------------------------------------------------------------------
//    処理内容 : 一番初めの全体の初期化等をする処理 - 定義
//    処理内容 : 
//    作成詳細 : 2011/10/15
//    補足     : GameLib内のManagerの初期化を行うが、そのプログラムの
//    補足     : 固有読み込みなどを記述するときもあります。
//    追記内容 : 
//    作成詳細 : 
//
//    追記内容 : 
//    作成詳細 : 2011/04/01    YourName
//         
//====================================================================


#ifndef INCLUDE_GAMELIB_FRAMEWORK_H
#define INCLUDE_GAMELIB_FRAMEWORK_H


namespace GameLib
{

        /// @class Framework
        /// @brief 各マネージャを統括するフレームワーク
        class Framework
        {
            //----------------------------------------------------------
            // 特殊メンバ
        public:
            
            /// @brief コンストラクタ
            Framework();

            /// @brief デストラクタ
            virtual ~Framework();

            //----------------------------------------------------------
            // メンバ関数
        public: 

            /// @brief インスタンスを作成します。
            void Create();

        }; // end of class Framework
} // end of namespace GameLib
#endif
