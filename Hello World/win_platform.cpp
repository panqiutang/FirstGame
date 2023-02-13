/* Windows dependent logic */

#include "utils.cpp"

#include <windows.h>

struct Render_State {
    /* Allocate memory to store pixels for rendering */
    void* memory;
    int width, height;
    BITMAPINFO bitmap_info;
};

bool running = true; // if the game is running
Render_State render_state;

#include "platform_common.cpp"
#include "renderer.cpp"

//#include "game.cpp"

/* Callback function for events such as messages */
LRESULT CALLBACK window_callback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (uMsg) {
        // exit game
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        }
            break;
        // window resize
        case WM_SIZE: {
            RECT rect;
            GetClientRect(hWnd, &rect);
            render_state.width = rect.right - rect.left;
            render_state.height = rect.bottom - rect.top;

            int buffer_size = render_state.width * render_state.height * sizeof(unsigned int);

            // reallocate pixel memory on resize
            if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
            render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
            render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
            render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
            render_state.bitmap_info.bmiHeader.biPlanes = 1;
            render_state.bitmap_info.bmiHeader.biBitCount = 32;
            render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
        }
            break;
        default:
            result = DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return result;
}

/* Entry point for windows applications */
int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow)
{
    // Create Window class
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = L"Game Window Class";
    window_class.lpfnWndProc = window_callback;

    // Register window
    RegisterClass(&window_class);

    // create window
    HWND window = CreateWindow(window_class.lpszClassName, L"My First Game!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280 , 720, 0, 0, hInst, 0);
    HDC hdc = GetDC(window); // device context

    Input input = {};

    // game loop
    while (running) {
        // Input
        for (int i = 0; i < 4; i++) {
            input.buttons[i].changed = false;
        }

        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
            switch (message.message) {
                case WM_LBUTTONUP:
                case WM_LBUTTONDOWN:
                case WM_KEYUP:
                // TODO: the key press action cannot be correctly detected, but a left mouse click can
                case WM_KEYDOWN: {
                    u32 vk_code = message.wParam;
                    bool is_down = ((message.lParam & (1 << 31)) == 0); // if key is pressed down

                    switch (vk_code) {
                        case VK_F1:
                        case VK_UP:
                        case VK_LBUTTON: {
                            input.buttons[BUTTON_UP].is_down = is_down;
                            input.buttons[BUTTON_UP].changed = true;
                        } break;
                    }
                } break;
                default: {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
            
        }

        // simulate
        // simulate_game(&input);
        // TODO: replace the following lines and put all game logic in simulate_game function
        clear_screen(0xda536e);
        // draw another rectangle when the UP key is pressed on keyboard
        if (input.buttons[BUTTON_UP].is_down) {
            draw_rectangle(0, 0, 300, 400, 0xbce2e8);
        }

        draw_rectangle(50, -50, 100, 200, 0xf4b3c2);

        // render
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
}