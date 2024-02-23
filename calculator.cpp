#include <windows.h>
#include <cstdio>

HWND TextField , number1 , number2 , plusb , minorb , mutipb , divb;
	char text1[100],text2[100];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            TextField = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER| ES_READONLY, 
                                        10, 10, 200, 25, hwnd, NULL, NULL, NULL);
            SetWindowText(TextField, "Please input two numbers");
            number1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER , 
                                    10, 40, 150, 25, hwnd, NULL, NULL, NULL);
            number2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER , 
                                    10, 70, 150, 25, hwnd, NULL, NULL, NULL);
            plusb = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE , 
                                    10, 100, 50, 50, hwnd, (HMENU) 1, NULL, NULL);
            minorb = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE , 
                                    60, 100, 50, 50, hwnd, (HMENU) 2, NULL, NULL);
            mutipb = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE , 
                                    110, 100, 50, 50, hwnd, (HMENU) 3, NULL, NULL);
            divb = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE , 
                                    160, 100, 50, 50, hwnd, (HMENU) 4, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
				int n1 , n2;
				double num1, num2 , sum;
				char result[100];
                case 1:
                    n1 = GetWindowText(number1,&text1[0],100);
					n2 = GetWindowText(number2,&text2[0],100);
					num1 = atof(text1);
					num2 = atof(text2);
					sum = num1 + num2;
					sprintf(result,"%.2f",sum);
					::MessageBox(hwnd,result,"Result",MB_OK);
					break;
				case 2:
                    GetWindowText(number1 , text1 , 100);
                    GetWindowText(number2 , text2 , 100);
                    num1 = atof(text1);
                    num2 = atof(text2);
                    sum = num1 - num2;

                    sprintf(result, "%.2f", sum);
                    ::MessageBox(NULL, result, "Result", MB_OK | MB_ICONINFORMATION);
                    break;
                
				case 3:

                    GetWindowText(number1 , text1 , 100);
                    GetWindowText(number2 , text2 , 100);
                    num1 = atof(text1);
                    num2 = atof(text2);
                    sum = num1 * num2;

                    sprintf(result, "%.2f", sum);
                    ::MessageBox(NULL, result, "Result", MB_OK | MB_ICONINFORMATION);
                    break;
                
				case 4:

                    GetWindowText(number1 , text1 , 100);
                    GetWindowText(number2 , text2 , 100);
                    num1 = atof(text1);
                    num2 = atof(text2);
                    sum = num1 / num2;
                    sprintf(result, "%.2f", sum);
                    ::MessageBox(NULL, result, "Result", MB_OK | MB_ICONINFORMATION);
                    break;
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255, 153, 255));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
