#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "myParam.h"
/**
 * @brief   OpenGLのウィンドウ関連の処理
 *
 * @note	主にメイン処理のクラスで継承して使う
 */
class Window
{

protected:
	// ウィンドウのハンドル
	GLFWwindow	*const	window;

	// ウィンドウの高さと幅
	int windowWidth, windowHeight;

	// キーボードの状態
	int keyStatus;

public:
	// コンストラクタ
	Window(int width = 640,	int	height = 480, const char *title = "Window")
				: window(glfwCreateWindow(width, height, title, NULL, NULL))
				, windowWidth(width)
				, windowHeight(height)
				, keyStatus(GLFW_RELEASE)
	{
		if (window == NULL)
		{
			// ウィンドウが作成できなかった
			std::cerr << "Can't create GLFW window." << std::endl;
			exit(1);
		}
		// 現在のウィンドウを処理対象にする
		glfwMakeContextCurrent(window);

		// 作成したウィンドウに対する設定
		glfwSwapInterval(1);
	}
	
	// デストラクタ
	virtual	~Window()
	{
		glfwDestroyWindow(window);
	}
	
	// ウィンドウを閉じるべきかを判定
	virtual int	shouldClose()
	{
		return	glfwWindowShouldClose(window) | glfwGetKey(window, GLFW_KEY_ESCAPE);
	}
	

	// カラーバッファを入れ替えてイベントを取り出す
	virtual void swapBuffers()
	{
#if SINGLE_BUFFERING
		glFinish();
#else
		// カラーバッファを入れ替える
		glfwSwapBuffers(window);
#endif
		// イベントを取り出す
		if (keyStatus == GLFW_RELEASE)
			glfwWaitEvents();
		else
			glfwPollEvents();
	}

	// ウィンドウのハンドルの取得
	GLFWwindow *const getWindowID() { return window; }


	// 画面クリア 図形描画の前に呼び出す
	virtual void clear()
	{
		glViewport(0, 0, windowWidth, windowHeight);

		// カラーバッファとデプスバッファを消去する
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// 幅の取得
	int getWidth() { return windowWidth; }
	// 高さの取得
	int getHeight() { return windowHeight; }
};


#endif