#include <windows.h>

// Nome da classe da janela
const char g_szClassName[] = "ClassedaJanela";

// Função de callback para processar mensagens da janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        // Mensagem de fechar a janela
        case WM_CLOSE:
            DestroyWindow(hwnd); // Destroi a janela
        break;

        // Mensagem de destruir a janela
        case WM_DESTROY:
            PostQuitMessage(0); // Posta mensagem para encerrar o programa
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam); // Processa outras mensagens padrão
    }
    return 0;
}

// Função principal do programa Windows (WinMain)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{   
    
    WNDCLASSEX wc; // Estrutura que define as características da janela
    HWND hwnd; // Identificador da janela
    MSG Msg; // Estrutura que contém mensagens do sistema

    // Preenche a estrutura WNDCLASSEX
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc; // Define a função de callback para mensagens da janela
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance; // Instância do programa
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // Ícone padrão
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Cursor padrão
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // Cor de fundo da janela
    wc.lpszMenuName  = NULL; // Menu da janela (não há menu neste caso)
    wc.lpszClassName = g_szClassName; // Nome da classe da janela
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // Ícone pequeno

    // Registra a classe da janela
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK); // Exibe mensagem de erro se falhar ao registrar a classe
        return 0;
    }

    // Cria a janela
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "LIG4", //Nome da janela
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 900, //Tamanho da janela
        NULL, NULL, hInstance, NULL);

    // Verifica se a criação da janela foi bem-sucedida
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK); // Exibe mensagem de erro se falhar ao criar a janela
        return 0;
    }

    // Mostra a janela na tela
    ShowWindow(hwnd, nCmdShow);

    // Atualiza a janela
    UpdateWindow(hwnd);

    // Passo 3: O loop de mensagens
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg); // Traduz mensagens virtuais de teclado
        DispatchMessage(&Msg); // Envia a mensagem para a função de callback da janela
    }

    // Retorna o código de saída da mensagem
    return Msg.wParam;
}
