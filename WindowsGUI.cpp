#include <windows.h>
#include <iostream>

/****************************************************************************************
 * 
 * WINAPI: 这个是调用约定，实质上是它是宏 #define WINAPI __stdcall  说明是stdcall的调用约定
 * WinMain: 函数名，就像控制台中的main
 * HINSTANCE: 自定义类型，句柄型数据类型，相当于装入了内存的资源的ID
 * hInstance: 应用程序当前实例的句柄。 这个值其实就是程序加载到内存空间后的首地址。
 * 
 * PSTR szCmdLine：
 * 在WINNT.H中有如下定义
 * typedef char CHAR;
 * typedef CHAR *LPSTR, *PSTR;
 * 这就说明 PSTR 其实就是个char类型的指针而已。
 * 这个参数的作用就是接受命令行参数。比如在启动程序的时候用如下命令：
 * zixue7.exe admin password
 * 那么这个szCmdLine 中保存的就是 admin password这个字符串
 * 这个参数的值，可以直接使用，也可以通过 GetCommandLine() 函数获取到。
 * 
 * int iCmdShow: 这个是控制窗口的显示状态，比如最大化，最小化，隐藏
 * 
 *****************************************************************************************/

#pragma   warning(disable:28251)

 //窗口过程函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
    WNDCLASS wc;//windows 类

    static TCHAR *szAppName = TEXT("windows test");

    HWND hwnd = NULL;

    MSG msg;

    wc.style = CS_HREDRAW | CS_VREDRAW;//窗口样式
    wc.lpfnWndProc = WndProc;//过程函数
    wc.cbClsExtra = 0;//扩展字段
    wc.cbWndExtra = 0;//扩展字段
    wc.hInstance = hInstance;//当前实例句柄
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);//设置程序图标
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);//设置鼠标

    //用白色画刷填充背景
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    //菜单
    wc.lpszMenuName = NULL;

    //类名
    wc.lpszClassName = szAppName;

    //像操作系统注册窗口类
    if(!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("程序只能在windowsNT下运行"), szAppName, MB_ICONERROR);
        return 0;
    }

    //创建窗口
    hwnd = CreateWindow(szAppName, //要注册的窗口类名
                        TEXT("c语言编写的第一个窗口程序"), //窗口标题
                        WS_OVERLAPPEDWINDOW, //窗口样式
                        CW_USEDEFAULT,//窗口距离屏幕左上角横坐标 
                        CW_USEDEFAULT,//窗口距离屏幕左上角纵坐标 
                        400, //窗口宽度
                        300, //窗口高度
                        NULL,//父窗口句柄
                        NULL, //菜单句柄
                        hInstance, //当前实例句柄
                        NULL);//指向一个值的指针，改值传递给窗口WM_CREATE消息。一般为NULL
    //显示窗口
    ShowWindow(hwnd, iCmdShow);

    //更新窗口
    UpdateWindow(hwnd);

    //消息循环，一直停在这里，退出消息循环就代表程序结束了
    while(GetMessage(&msg, NULL, 0, 0))
    {
        //翻译消息
        TranslateMessage(&msg);

        //分发消息
        DispatchMessage(&msg);
    }

    //MessageBox(NULL, TEXT("Hello"), TEXT("Hello"), MB_OK);

    return msg.wParam;
}

/* 消息处理函数 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            //发送结束请求，里面的参数为退出码
            PostQuitMessage(0);
            break;
    }

    //调用默认的过程函数
    return DefWindowProc(hwnd, message, wParam, lParam);
}

