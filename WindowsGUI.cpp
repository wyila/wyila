#include <windows.h>
#include <iostream>

/****************************************************************************************
 * 
 * WINAPI: ����ǵ���Լ����ʵ���������Ǻ� #define WINAPI __stdcall  ˵����stdcall�ĵ���Լ��
 * WinMain: ���������������̨�е�main
 * HINSTANCE: �Զ������ͣ�������������ͣ��൱��װ�����ڴ����Դ��ID
 * hInstance: Ӧ�ó���ǰʵ���ľ���� ���ֵ��ʵ���ǳ�����ص��ڴ�ռ����׵�ַ��
 * 
 * PSTR szCmdLine��
 * ��WINNT.H�������¶���
 * typedef char CHAR;
 * typedef CHAR *LPSTR, *PSTR;
 * ���˵�� PSTR ��ʵ���Ǹ�char���͵�ָ����ѡ�
 * ������������þ��ǽ��������в��������������������ʱ�����������
 * zixue7.exe admin password
 * ��ô���szCmdLine �б���ľ��� admin password����ַ���
 * ���������ֵ������ֱ��ʹ�ã�Ҳ����ͨ�� GetCommandLine() ������ȡ����
 * 
 * int iCmdShow: ����ǿ��ƴ��ڵ���ʾ״̬��������󻯣���С��������
 * 
 *****************************************************************************************/

#pragma   warning(disable:28251)

 //���ڹ��̺���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
    WNDCLASS wc;//windows ��

    static TCHAR *szAppName = TEXT("windows test");

    HWND hwnd = NULL;

    MSG msg;

    wc.style = CS_HREDRAW | CS_VREDRAW;//������ʽ
    wc.lpfnWndProc = WndProc;//���̺���
    wc.cbClsExtra = 0;//��չ�ֶ�
    wc.cbWndExtra = 0;//��չ�ֶ�
    wc.hInstance = hInstance;//��ǰʵ�����
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);//���ó���ͼ��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);//�������

    //�ð�ɫ��ˢ��䱳��
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    //�˵�
    wc.lpszMenuName = NULL;

    //����
    wc.lpszClassName = szAppName;

    //�����ϵͳע�ᴰ����
    if(!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("����ֻ����windowsNT������"), szAppName, MB_ICONERROR);
        return 0;
    }

    //��������
    hwnd = CreateWindow(szAppName, //Ҫע��Ĵ�������
                        TEXT("c���Ա�д�ĵ�һ�����ڳ���"), //���ڱ���
                        WS_OVERLAPPEDWINDOW, //������ʽ
                        CW_USEDEFAULT,//���ھ�����Ļ���ϽǺ����� 
                        CW_USEDEFAULT,//���ھ�����Ļ���Ͻ������� 
                        400, //���ڿ��
                        300, //���ڸ߶�
                        NULL,//�����ھ��
                        NULL, //�˵����
                        hInstance, //��ǰʵ�����
                        NULL);//ָ��һ��ֵ��ָ�룬��ֵ���ݸ�����WM_CREATE��Ϣ��һ��ΪNULL
    //��ʾ����
    ShowWindow(hwnd, iCmdShow);

    //���´���
    UpdateWindow(hwnd);

    //��Ϣѭ����һֱͣ������˳���Ϣѭ���ʹ�����������
    while(GetMessage(&msg, NULL, 0, 0))
    {
        //������Ϣ
        TranslateMessage(&msg);

        //�ַ���Ϣ
        DispatchMessage(&msg);
    }

    //MessageBox(NULL, TEXT("Hello"), TEXT("Hello"), MB_OK);

    return msg.wParam;
}

/* ��Ϣ������ */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            //���ͽ�����������Ĳ���Ϊ�˳���
            PostQuitMessage(0);
            break;
    }

    //����Ĭ�ϵĹ��̺���
    return DefWindowProc(hwnd, message, wParam, lParam);
}

