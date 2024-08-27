#include<Windows.h>
#include <tchar.h> // �ؽ�Ʈ ĳ����


#pragma region WinAPI
/*
�� API (Application Programing Interface)

- �ü���� ���� ���α׷� ������ ���� �����ϴ� �Լ��� ����. <- ������ �ý����� ����� ����ϱ� ����.

- ��ɾ��� �������� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ��� �� �ʿ䰡 ���� ���
API ��ɾ� ȣ���� ����ȴ�.

 EX)
 �ϵ���� ----------------- �ü�� (Windows) ---------------------- �������α׷�
 (API �Լ�)

 �� ����
 - �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������ / ���������� �����ϴ�.
    �� �������� != ������

 �� ����
 - ����ϴ� ���α׷����� ������ ���� �÷����� ���� ����ȭ�� �߻��� �� �ִ�. (WinAPI)
    �� C ���� ���ߵ� �÷����� �Ѱ����� �غ����� ���Ѵٴ� ���α׷����� ���.

 - �̴� ��κ��� Ÿ ���̺귯�� Ȯ������ �ذ��� ������ ���α׷����� (�����)������ ���� �䱸�ϱ� ������ �̴� ��� ���忡���� �����̴�.

 �ڡڡڡڡ�
 ��  API ����
 - ũ�� 3 ������ ���
    �� ������, ���� (�޼���), Window Procedure
 �ڡڡڡڡ�
*/

#pragma endregion

// ���� ����
/*
- �ν��Ͻ�
    �� ������ os�� ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��.
    �� ���� ���α׷��̸� �Ϲݴ����� ���� �ν��Ͻ� ���� ������.
    �� Ŭ������ �޸𸮿� ������ ������ ��ü
    �� ����ǰ� �ִ� ������ ���α׷���.
*/

HINSTANCE _hInstance;
// �ڵ� : ������ â
HWND _hWnd;
// ������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("Windows API");

// TCHAR* pszString = _T("Windows API");

/*
LPSTR     = char*
LPCSTR    = const char*
LPCTSTR   = const tchar*

*/

/*
�� TCHAR

- �� �ڷ����� ������Ʈ ���ڼ� ������ ���� �ڵ������� ��ȯ�� ���ִ� �߰� ��ũ�� �ڷ���
    �� Type Casting�� �����ϸ� char �Ǵ� wchar_t �� ��ȯ�Ѵ�.

- ��Ƽ�� ���� ȯ�濡�� ������  �����۾����� ���α׷��� �����ϱ� ���ؼ��� TCHAR������ ���ڿ��� ǥ���ϴ� ���� �����Ѵ�.

- ������ ���ø����̼��� ����ϴ� ���α׷����ʹ� ���� ���α׷����� ���ڿ� ����� ���� ���ؼ��� �߰� ������ ����
char* -> wchar_t*�� ��ȯ�� ���ִ� _T��ũ�ε� ��ȿ�ϴ�.


*/

//LPCSTR script1 = "ABC";
//LPCWSTR script2 = L"ABC"; // �����ڵ� L
//const TCHAR* script3 = _T("ABC"); // TCHAR ��� �����߰� �ӵ��� ������.
// �ظ��ϸ� �տ� �ڷ��� ������ ����.


// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:

// �ݹ��Լ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

/*
hInstance : ���α׷� �ν��Ͻ� �ڵ�
hPrevInstance : ������ ����� �ν��Ͻ� �ڵ�
lpszCmdparam : ��������� �Էµ� ���α׷� ����(��)
nCmdShow : ���α׷��� ���۵� ����(�ּ�ȭ / ���� ũ�� ���...)

*/

// ������ w world wide
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdparam,
    int       nCmdShow)
{
    _hInstance = hInstance;

    /*
    winMain�� ����
    �� 1. ������ â�� ������ ȭ�鿡 ����
        �� ȭ�鿡 â�� ���� ���ؼ��� 4���� ó���� ����
    �� 2. �޼��� ����

    */


    // 1-1. ������â ����ü ���� �� �ʱ�ȭ
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0;                                        // Ŭ���� ���� �޸� �Ҵ�.
    wndClass.cbWndExtra = 0;                                        // ������ ���� �޸� �Ҵ�/
    wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH)); // �ڵ� �귯�� ���� ĥ�ϱ�. ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                 // Ŀ�� ���
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                // â �»�� ������
    wndClass.hInstance = hInstance;                                 // �ν��Ͻ� ��Ī
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                        // �������� ��ų� �ѹ��� �⺻���� 0
    wndClass.lpszClassName = _lpszClass;                            // â �����ߴ� Ÿ��Ʋ
    wndClass.lpszMenuName = NULL;                                   // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                       // ���� �޴����� ������ ��Ÿ��



    // 1-2. ������ Ŭ���� ���
    RegisterClass(&wndClass);

    //  HInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // 1-3. ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindowW
    (
        _lpszClass,             // ������ Ŭ���� �ĺ���
        _lpszClass,             // ������ Ÿ��Ʋ �� �̸�
        WS_OVERLAPPEDWINDOW,    // ������ ��Ÿ��
        400,                    // ������ ȭ�� x ��ǥ
        100,                    // ������ ȭ�� y ��ǥ
        800,                    // ������ ȭ�� ���� ũ��
        800,                    // ������ ȭ�� ���� ũ��
        NULL,                   // �θ� ������  GetDesktopWindow() ����Ǵ� â�� ������ ����� ���� �θ� ������ ���Ҷ� ����Ѵ�. �ڽ������� ���� �ȴ�.
        (HMENU)NULL,            // �޴� �ڵ�
        hInstance,              // �ν��Ͻ� ����
        NULL                    // �������� �ڽ� �����츦 �����ϸ� ���� / NULL
    );


    // 1-4. ȭ�鿡 ������ â�� �����ֱ�
    ShowWindow(_hWnd, nCmdShow);
    // 
    // UpdateWindow(_hWnd); update �κ�


    // �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
    MSG message;
    //ZeroMemory(&message, sizeof(message));

    // �ڡڡڡڡ�
    // 2. �⺻ �޽��� ����

    // GetMessage() : �޼����� ������ �� ������ ���� ���
    //  �� �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ �����Ѵ�.
    //  �� �ٸ� �޼��� ť�� ������� ��� �޼����� ���ö����� ���.

    // - PeekMessage : �޼����� ������ ��ȯ�� �ȴ�.

    while (GetMessage(&message, 0, 0, 0))
    {

        TranslateMessage(&message);
        DispatchMessage(&message);

    }
    /*
    TranslateMessage(&message);
      �� Ű������ �Է� �޼��� ó���� ����Ѵ�. �Էµ� Ű�� ���� Ű���� Ȯ���ϰ� �빮�� Ȥ�� �ҹ���, �ѱ�, ���������� ���� WM_CHAR �޼����� �߻���Ų��.


    DispatchMessage(&message);
      �� ������ ���ν����� ���޵� �޼����� ���� ������� �����Ѵ�.

    */
    return message.wParam;
}

// Window Procedure
// ������ ���ν���
// hWnd: ��� �����쿡�� �߻��� �޼������� ����
// imessage: �޼��� ���й�ȣ
// wParam: unsigned int ���콺 ��ư�� ���� / Ű���� ���� Ű�� ���¸� �����Ѵ�.
// lParam: unsigned long ���콺 Ŭ�� ��ǥ�� ����.
LRESULT CALLBACK WndProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
    /*
    Window Procedure

    - �޼����� �ü���� ���� -> �ü���� ������ ȣ���� �ȴ�.
        �� WinMain�� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ� �Լ���� �Ҽ��ִ�.
        �� �����츦 �����Ҷ��� �ݵ�� ������ ���־�� �Ѵ�.

    - ������ ���ν��� ���ο����� �����쿡�� �߻��� ��� �޼����� ó���ϴ°��� �ƴ϶� Ư�� �޼������� ó���ϰ�
    ������ �޼����� DefWindowProc �Լ��� ó���ϵ��� ������ �����ϴ°��� �Ϲ���.

    */
    switch (imessage)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:

        // PostQuitMessage: ���Լ��� �޼��� ť�� QUIT�� ������ ������ ����
        // QUIT �޼����� �����ϴ� ���� GetMessage�� FALSE�� ��ȯ�ϹǷ� �޼��������� ����
        PostQuitMessage(0);

        return (DefWindowProc(hWnd, imessage, wParam, lParam));
    }
}

/*
���� 1.
���� ����.

- ��Ʈ�� ������ ����´�.
    �� CallBack Function, DC, GetDC, ReleaseDC, BeginPaint, EndPaint, WM_PAINT, PAINTSTRUCT


Ÿ�Ӿ��� ������ â �����

- �ð��� 10��.

- ���н� ���� -> ���� �ο� x 2

*/