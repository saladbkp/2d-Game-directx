//// Ask the compiler to include minimal header files for our program.
//#define WIN32_LEAN_AND_MEAN	// lean_and_mean(theme), lean=no fat, mean=strong/powerful
//#define BUTTONDOWN 
//// pre-processor(process before), must be done before the program.
//// add the library code, to use datatype in it. 
//// windows.h is too fat, so define it with lean_and_mean to get the minimum head file
//#include <Windows.h> 
////	include the Direct3D 9 library
//#include <d3d9.h>
//#include <iostream>
////	include the D3DX9 library
//// can add the lib by using #pragma comment ( lib, "d3dx9.lib") (only in windows version)
//#include <d3dx9.h> 
//#include <math.h>
//#include <dinput.h>
//
//#include "FrameTimer.h"
////	Link dinput8.lib and dxguid.lib
//using namespace std;
////--------------------------------------------------------------------//--------------------------------------------------------------------
//
////	Window handle
//// handle to window(frame of app). why need? because has many window.. point it to NULL, so not random pointing other
//HWND g_hWnd = NULL;
//
////	Window's structure
//// box(container), to store what we want in GameWindow Class(no need open the class, microsft will open to us)
//WNDCLASS wndClass;
//// another box
//MSG msg;
//
//// Direct3D9
//// Make a pointer to our virtual graphic card
//IDirect3DDevice9* d3dDevice;	// name(d3dDevice) depend on us
//
//// Pointer to texture / picture file
//LPDIRECT3DTEXTURE9 bgTexture = NULL;
//LPDIRECT3DTEXTURE9 pointerTexture = NULL;
//LPDIRECT3DTEXTURE9 p4Texture = NULL;
//LPDIRECT3DTEXTURE9 p4NumTexture = NULL;
//LPDIRECT3DTEXTURE9 explosionTexture = NULL;
//// Sprite interface / sprite brush
//LPD3DXSPRITE sprite = NULL;		//LPD3DXSPRITE spriteBrush = NULL;
//LPD3DXFONT font = NULL;
//LPD3DXLINE line = NULL;
//// input
//LPDIRECTINPUT8 dInput;
//LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
//LPDIRECTINPUTDEVICE8  dInputMouseDevice;
//BYTE  diKeys[256];
//DIMOUSESTATE mouseState;
//LONG currentXpos = 0;
//LONG currentYpos = 0;
////	Specify the "	" rectangle.
//RECT spriteRect;
//RECT p4SpriteRect;
//RECT p4NumSpriteRect;
//RECT explosionSpriteRect;
//RECT textRect;
//RECT mouseRect;
////timer
//FrameTimer* gameTimer = new FrameTimer();
//
////--------------------------------------------------------------------
//
//// RGB Variable // 0,0,0 default black
//int red = 0;
//int recordRed = -5;
//int green = 0;
//int recordGreen = -5;
//int blue = 0;
//int recordBlue = -5;
//// WindowSetting
//int screenWidth = GetSystemMetrics(SM_CXSCREEN);
//int screenHeight = GetSystemMetrics(SM_CYSCREEN);
//int width = /*screenWidth*/ 800;// 400; //CW_DEFAULT
//int height = /*screenHeight*/ 600;// 300;
//bool windowed = true;//false;
//int refreshRate = D3DPRESENT_RATE_DEFAULT;
//// SpritePosition	//get mouse position from lectureNote
//int spriteX = 0;
//int spriteY = 0;
//int mouseX = 0;
//int mouseY = 0;
//bool leftButtonPressed = true;
//bool rightButtonPressed = true;
//// Cursor color // 255,255,255 default white
//int mouseRed = 255;
//int mouseRecordR = 5;
//int mouseGreen = 255;
//int mouseRecordG = 5;
//int mouseBlue = 255;
//int mouseRecordB = 5;
//// Background picture
//const char* bg1 = "bg/bg1.png";
//const char* bg2 = "bg/bg2.png";
//const char* bg3 = "bg/bg3.png";
//const char* bg = bg1;
//// Sprite size for cutting
//int spriteTextureWidth = 128;
//int spriteTextureHeight = 128;
//int spriteCol = 4;
//int spriteRow = 4;
//int spriteWidth = spriteTextureWidth / spriteCol;
//int spriteHeight = spriteTextureHeight / spriteRow;
//int frameCount = 0;
//const double pi = 3.14;
//
////Sprite for the space player 1 and 2
//int player1Textureheight = 64;
//int player1TexttureWidth = 64;
//int player1Col = 2;
//int player1Row = 2;
//int player1MaxFrame = 2;
//float player1EnginePower = 1;
//float player1Speed = 8;
//float player1Mass = 20;
//float player1RotationSpeed = 0.05;
//
//
//// sin/cos/tan(x), x is in radians
////int spriteFrameCount = frameCount;
////int explosionFrameCount = frameCount;
////--------------------------------------------------------------------//--------------------------------------------------------------------
//
////check for balance collision
////if (playerPosition.x<0 || playerPosition.x>windowWidth - playerSpriteWidth)
////{
////	player.Velocity.x *= -1;
////}
////
////if (playerPosition.x<0 || playerPosition.x>windowWidth - playerSpriteWidth)
////{
////	player.Velocity.x *= -1;
////}
////	Window Procedure, for event handling
////											/title/	  /details/    /details/
// // callback= when execute call another function. call by os, so parameter will asign by os. 
//LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//
//	switch (message)
//	{
//		//	The message is post when we destroy the window.
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	case WM_MOUSEMOVE:
//	{
//		// Retrieve mouse screen position        
//		int x = (short)LOWORD(lParam);
//		int y = (short)HIWORD(lParam);
//		//int x = GET_X_LPARAM(lParam);
//		//int y = GET_Y_LPARAM(lParam);
//		//Do something with the mouse screen position
//		mouseX = x;
//		mouseY = y;
//		//cout << "\nMx: " << mouseX << " My: " << mouseY << "\nX : " << x << " Y : " << y << endl;
//	}
//	break;
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_ESCAPE:	//ask Google: Virtual Key Code
//			PostQuitMessage(0);
//			break;
//			// Change number sprite
//		case VK_UP:
//			//spriteFrameCount++;
//			//explosionFrameCount++;
//			frameCount++;
//			/*cout << "left: " << p4NumSpriteRect.left << " right : " << p4NumSpriteRect.right << endl;
//			cout << "top : " << p4NumSpriteRect.top << " bottom: " << p4NumSpriteRect.bottom << endl;
//			cout << "Frame: " << spriteFrameCount << endl;*/
//			break;
//		case VK_DOWN:
//			//spriteFrameCount--;
//			//explosionFrameCount--;
//			frameCount--;
//			break;
//			// cursor sprite color
//			// Check the SHIFT key is pressed, change cursor color
//			//case 'R' & VK_SHIFT: 
//		case 'Z':
//			if (mouseRed <= 0 || mouseRed >= 255)
//			{
//				mouseRecordR *= -1;
//			}
//			mouseRed += mouseRecordR;
//			break;
//			//case 'G' & VK_SHIFT:
//		case 'X':
//			if (mouseGreen <= 0 || mouseGreen >= 255)
//			{
//				mouseRecordG *= -1;
//			}
//			mouseGreen += mouseRecordG;
//			break;
//			//case 'B' & VK_SHIFT:
//		case 'C':
//			if (mouseBlue <= 0 || mouseBlue >= 255)
//			{
//				mouseRecordB *= -1;
//			}
//			mouseBlue += mouseRecordB;
//			break;
//		case 'A':
//			bg = bg1;
//			D3DXCreateTextureFromFile(/* Your Direct3D device */d3dDevice, bg, &bgTexture);
//			break;
//		case 'S':
//			bg = bg2;
//			D3DXCreateTextureFromFile(/* Your Direct3D device */d3dDevice, bg, &bgTexture);
//			break;
//		case 'D':
//			bg = bg3;
//			D3DXCreateTextureFromFile(/* Your Direct3D device */d3dDevice, bg, &bgTexture);
//			break;
//			// BG sprite position
//			/*case VK_UP:
//				spriteY -= 5;
//				break;
//			case VK_DOWN:
//				spriteY += 5;
//				break;*/
//		case VK_LEFT:
//			spriteX -= 5;
//			break;
//		case VK_RIGHT:
//			spriteX += 5;
//			break;
//			// Default Bg color
//		case 'R':
//			if (red <= 0 || red >= 255)
//			{
//				recordRed *= -1;
//			}
//			red += recordRed;
//			cout << "R: " << red << "G: " << green << "B: " << blue << endl;
//			break;
//		case 'G':
//			if (green <= 0 || green >= 255)
//			{
//				recordGreen *= -1;
//			}
//			green += recordGreen;
//			cout << "R: " << red << "G: " << green << "B: " << blue << endl;
//			break;
//		case 'B':
//			if (blue <= 0 || blue >= 255)
//			{
//				recordBlue *= -1;
//			}
//			blue += recordBlue;
//			cout << "R: " << red << "G: " << green << "B: " << blue << endl;
//			break;
//			// Window Fullscreen
//		case 'F':
//			if (windowed)
//			{
//				windowed = false;
//				width = screenWidth;
//				height = screenHeight;
//				refreshRate = D3DPRESENT_RATE_DEFAULT;
//				SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP);
//				SetWindowPos(g_hWnd, NULL, NULL, NULL, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
//			}
//			else
//			{
//				windowed = true;
//				width = 400;
//				height = 300;
//				refreshRate = 0;
//				SetWindowLong(g_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
//				SetWindowPos(g_hWnd, NULL, NULL, NULL, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
//			}
//			break;
//			// WS_POPUP				: Window
//			// WS_OVERLAPPEDWINDOW	: Without Window
//			// GWL_STYLE			: Sets a new window style.
//			// SWP_FRAMECHANGED		: Applies new frame styles set using the SetWindowLong function.
//			// SWP_SHOWWINDOW		: Displays the window.
//			// SWP_NOSIZE			: Retains the current size(ignores the cx and cy parameters).
//			// cleanupD3dDevice();
//			// createDirect3D9();
//		}
//
//		//	Default handling for other messages.
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
////	Practical 1 //--------------------------------------------------------------------
//
//void createWindow() {
//
//	/*
//	Step 1
//	Define and Register a Window.
//	*/
//
//	//	Set all members in wndClass to 0.
//	ZeroMemory(&wndClass, sizeof(wndClass));	// & find the address add the size, then make it 0 everywhere(fill 0 in it follow the size), to set the thing don't use to default = 0
//
//	//	Filling wndClass. You are to refer to MSDN for each of the members details.
//	//	These are the fundamental structure members to be specify, in order to create your window.
//	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndClass.hInstance = GetModuleHandle(NULL);	//	GetModuleHandle(NULL);
//	wndClass.lpfnWndProc = WindowProcedure;
//	wndClass.lpszClassName = "My Window"; // lpsz = long pointer zero string
//	wndClass.style = CS_HREDRAW | CS_VREDRAW;
//
//	//	Register the window.
//	RegisterClass(&wndClass); // microsoft create the class and asign the thing we set upside in it. 
//
//	/*
//		Step 2
//		Create the Window.
//	*/
//	//	You are to refer to MSDN for each of the parameters details.
//	//													/title of window/ 
//	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);
//	/* which */
//	ShowWindow(g_hWnd, 1);
//
//	//	Some interesting function to try out.
//	//	ShowCursor(false);
//
//	ZeroMemory(&msg, sizeof(msg));	// delete everything inside by setting zero
//
//	//initialize timer
//	gameTimer->init(144);
//}
//
//bool windowIsRunning() {
//
//	/*
//		Step 3
//		Handling window messages
//		NOTE! There are several ways of writing the message loop.
//		You have to based on which kind of application your are writing.
//	*/
//	//while (msg.message != WM_QUIT)
//	//{
//
//		/*
//			The if- version process one message per one iteration loop
//			The while- version will clear the message queue before dealing with your own code.
//
//			Another function is GetMessage.
//			This function is not suitable for game, because it will block your program until it recieves a message.
//			your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
//			Suitable for event based program, such as bussiness app.
//		*/
//		//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // peek up and asking operating system:"Do you have message to me.". 
//	{
//		//	Receive a quit message
//		if (msg.message == WM_QUIT)
//			return false;
//		//	Translate the message 
//		TranslateMessage(&msg); // no need care
//		//	Send message to your window procedure
//		DispatchMessage(&msg); // send to WindowProcedure
//	}
//
//	/*
//		Write your code here...
//	*///}
//
//	return true;
//}
//
//void cleanupWindow() {
//	//	Free up the memory.
//	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
//}
//
//void cleanupDirectInput() {
//	dInputKeyboardDevice->Unacquire();
//	dInputKeyboardDevice->Release();
//	dInputKeyboardDevice = NULL;
//
//	dInputMouseDevice->Unacquire();
//	dInputMouseDevice->Release();
//	dInputMouseDevice = NULL;
//
//	//	Release DirectInput.
//	dInput->Release();
//	dInput = NULL;
//}
////	Practical 2 //--------------------------------------------------------------------
//
//int createDirect3D9() {
//	//	Define Direct3D 9.
//	// For interface direct3D9, instanceship class to build the object (use pointer to allocate)
//	// Create the object
//	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
//
//	//	Define how the screen presents.
//	// Specify how we want our virtual graphic card to be like
//	// Make a box to store the virtual graphic card properties
//	D3DPRESENT_PARAMETERS d3dPP;
//	// Delete everything in the box
//	ZeroMemory(&d3dPP, sizeof(d3dPP));
//
//	//	Refer to Direct3D 9 documentation for the meaning of the members.
//	// Fill up the box with what we want
//	d3dPP.Windowed = windowed;// true;
//	// graphic card normal got two buffer, one is back for draw one is front for take by monitor, when draw finish will swap to front. To let monitor will get full picture
//	// Discard the front when to swap to back
//	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;	// no need change
//	d3dPP.BackBufferCount = 1;					// One front, one back. Can more than one, depands on developer
//	d3dPP.BackBufferWidth = width;// 300;				// If the size no match with the window size, the OS will make it bruh and skech it. Or maybe if it less than one pixel then the OS will can't draw
//	d3dPP.BackBufferHeight = height;// 400;
//	d3dPP.hDeviceWindow = g_hWnd;				// Pass by create window
//	d3dPP.FullScreen_RefreshRateInHz = refreshRate;
//
//	//	Create a Direct3D 9 device.
//	// Use the Direct3D object, call the behaviour to create the Virtual Graphic Card
//	// Makes virtual device, use the pointer to get the function
//	// In API, it will make the function to get error message. To tell success or not. Will not build the object*
//	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT,					// Because got CPU & GPU. Default normally use the better. Can flip to other graphic if avaliable.(such as game tester)
//		D3DDEVTYPE_HAL,						// D3DDEVTYPE_HAL: Hardware accelelation, no need change. D3DDEVTYPE_REF: Reference, if the hardware can't use because some graphics code bug
//		g_hWnd,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// Never thouch it, no need change
//		&d3dPP,								// Pass in the box
//		&d3dDevice								// Address, to put the thing in this place. build the object* at here
//	);
//
//	//	To Do: Cout out the message to indicate the failure.
//	// If fail, shutdown the program
//	if (FAILED(hr))
//		return 0;
//}
//
//void render() {
//
//	D3DXVECTOR3 position = D3DXVECTOR3(spriteX, spriteY, 0);
//	D3DXVECTOR3 mousePosition = D3DXVECTOR3(mouseX, mouseY, 0);
//	D3DXVECTOR3 p4Position = D3DXVECTOR3(400, 400, 0);
//	D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(200, 200), D3DXVECTOR2(200, 400) };
//	//	To Do:
//	//	Update.
//
//	//	Clear the back buffer. Delete it by D3DCOLOR_XRGB(0, 0, 0) [Black color]
//	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);
//
//	//	Begin the scene
//	// Unlock the back paper for drawing(when the paper not using will lock. So then will not corrupt by other)
//	d3dDevice->BeginScene();
//
//
//
//	//	To Do:
//	//	Drawing.
//	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
//		// call sprite brush begin drawing
//	sprite->Begin(D3DXSPRITE_ALPHABLEND);
//
//	//	Sprite rendering. Study the documentation.
//	// sprite brush daw the picture file for user
//	//sprite->Draw(bgTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
//	//sprite->Draw(bgTexture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
//	sprite->Draw(bgTexture, &spriteRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
//	sprite->Draw(pointerTexture, NULL, NULL, &mousePosition, D3DCOLOR_XRGB(mouseRed, mouseGreen, mouseBlue));
//	sprite->Draw(p4Texture, &p4SpriteRect, NULL, &p4Position, D3DCOLOR_XRGB(255, 255, 255));
//
//	// Draw Sprite Num
//	p4NumSpriteRect.left = frameCount % spriteCol * spriteWidth;
//	p4NumSpriteRect.top = frameCount / spriteCol * spriteHeight;
//	p4NumSpriteRect.right = p4NumSpriteRect.left + spriteWidth;
//	p4NumSpriteRect.bottom = p4NumSpriteRect.top + spriteHeight;
//	sprite->Draw(p4NumTexture, &p4NumSpriteRect, NULL, &p4Position, D3DCOLOR_XRGB(255, 255, 255));
//
//	//sprite explosion
//	explosionSpriteRect.left = frameCount % spriteCol * spriteWidth;
//	explosionSpriteRect.top = frameCount / spriteCol * spriteHeight;
//	explosionSpriteRect.right = explosionSpriteRect.left + spriteWidth;
//	explosionSpriteRect.bottom = explosionSpriteRect.top + spriteHeight;
//	sprite->Draw(explosionTexture, &explosionSpriteRect, NULL, &p4Position, D3DCOLOR_XRGB(255, 255, 255));
//
//	font->DrawText(/* Your D3DXSprite */sprite, "Hello World!", 12, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
//	//font->DrawText(sprite,"",12,&mouseRect,0, D3DCOLOR_XRGB(255, 255, 255));
//
//	/*if (p4NumSpriteRect.left == (0 * (spriteWidth / cutWidth)) && p4NumSpriteRect.top == (0 * (spriteWidth / cutWidth)) &&
//		p4NumSpriteRect.right == (1 * (spriteWidth / cutWidth)) && p4NumSpriteRect.bottom == (1 * (spriteWidth / cutWidth)))
//	{
//		p4NumSpriteRect.left = 1 * (spriteWidth / cutWidth);
//		p4NumSpriteRect.top = 0 * (spriteHeight / cutHeight);
//		p4NumSpriteRect.right = 2 * (spriteWidth / cutWidth);
//		p4NumSpriteRect.bottom = 1 * (spriteHeight / cutHeight);
//	}
//	else if (p4NumSpriteRect.left == (1 * (spriteWidth / cutWidth)) && p4NumSpriteRect.top == (0 * (spriteWidth / cutWidth)) &&
//			 p4NumSpriteRect.right == (2 * (spriteWidth / cutWidth)) && p4NumSpriteRect.bottom == (1 * (spriteWidth / cutWidth)))
//	{
//		p4NumSpriteRect.left = 0 * (spriteWidth / cutWidth);
//		p4NumSpriteRect.top = 0 * (spriteHeight / cutHeight);
//		p4NumSpriteRect.right = 1 * (spriteWidth / cutWidth);
//		p4NumSpriteRect.bottom = 1 * (spriteHeight / cutHeight);
//	}*/
//
//
//
//	//	End sprite drawing
//	// spirte brush, stop drawing
//	sprite->End();
//
//	line->Begin();
//	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
//	line->End();
//
//	//	End the scene
//	// Lock back the back paper
//	d3dDevice->EndScene();
//
//	//	Present the back buffer to screen
//	// Swap
//	d3dDevice->Present(NULL, NULL, NULL, NULL);
//
//
//}
//
//void cleanupD3dDevice() {
//	//	Release the device when exiting.
//	d3dDevice->Release();
//	//	Reset pointer to NULL, a good practice.
//	d3dDevice = NULL;
//}
////	Practical 3 //--------------------------------------------------------------------
//void initialize() {
//
//	// In directX y-axis going down is positive, x-axis going right is positive
//	// right = picture width, bottom = picture high
//	spriteRect.left = 0;
//	spriteRect.top = 0;
//	spriteRect.right = 400;
//	spriteRect.bottom = 300;
//
//	p4SpriteRect.left = 32;
//	p4SpriteRect.top = 32;
//	p4SpriteRect.right = 64;
//	p4SpriteRect.bottom = 64;
//
//	p4NumSpriteRect.left = 0;
//	p4NumSpriteRect.top = 0;
//	p4NumSpriteRect.right = p4NumSpriteRect.left + spriteWidth;
//	p4NumSpriteRect.bottom = p4NumSpriteRect.top + spriteHeight;
//
//	explosionSpriteRect.left = 0;
//	explosionSpriteRect.top = 0;
//	explosionSpriteRect.right = explosionSpriteRect.left + spriteWidth;
//	explosionSpriteRect.bottom = explosionSpriteRect.top + spriteHeight;
//
//	textRect.left = 100;
//	textRect.top = 100;
//	textRect.right = 350;
//	textRect.bottom = 125;
//}
//
//int createSprite() {
//
//	//	Initialization
//
//	//	Create sprite(brush). Study the documentation. 
//	HRESULT hr = D3DXCreateSprite(/* Your Direct3D device */d3dDevice, &sprite);
//
//	//	Create texture. Study the documentation.
//	// Reading the file from HDD and storing it in the GPU(Device)
//	// hr = D3DXCreateTextureFromFile(/* Your Direct3D device */d3dDevice, "Lab03/bg1.png", &texture);
//	hr = D3DXCreateTextureFromFile(/* Your Direct3D device */d3dDevice, "Assets/bg1.png", &bgTexture);
//	hr = D3DXCreateTextureFromFile(/* Your Direct3D device */d3dDevice, "Assets/pointer.png", &pointerTexture);
//	// Extend, to transparent color by ARGB
//	hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */d3dDevice, "Assets/04.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
//		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
//		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 128, 64),
//		NULL, NULL, &p4Texture);
//	hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */d3dDevice, "Assets/numbers.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
//		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
//		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 128, 0),
//		NULL, NULL, &p4NumTexture);
//	hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */d3dDevice, "Assets/explosion.png", D3DX_DEFAULT, D3DX_DEFAULT,
//		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
//		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 128, 0),
//		NULL, NULL, &explosionTexture);
//	hr = D3DXCreateFont(/* Your Direct3D device */d3dDevice, 25, 0, 0, 1, false,
//		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
//		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
//	hr = D3DXCreateLine(/* Your Direct3D device */d3dDevice, &line);
//	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
//	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
//	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
//	//									NULL, NULL, &texture);
//
//	// Check if succed or fail...
//	if (FAILED(hr))
//		return 0;
//
//	initialize();
//}
//
//int createInput() {
//	HRESULT hr;
//	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
//	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
//	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
//	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//	dInputKeyboardDevice->Acquire();
//
//	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
//	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
//	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//	dInputMouseDevice->Acquire();
//
//	if (FAILED(hr))
//		return 0;
//}
//void getInput() {
//	dInputKeyboardDevice->GetDeviceState(256, diKeys);
//	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
//}
//void cleanupSprite() {
//
//	//	Release and clean up everything
//
//	sprite->Release();
//	sprite = NULL;
//
//	bgTexture->Release();
//	bgTexture = NULL;
//	pointerTexture->Release();
//	pointerTexture = NULL;
//
//	font->Release();
//	font = NULL;
//
//	line->Release();
//	line = NULL;
//}
//
//void update(int frames) {
//
//	for (int i = 0;i < frames; i++) {
//		frameCount++;
//	}
//
//
//	if (frameCount > 9)
//	{
//		frameCount = 0;
//	}
//	else if (frameCount < 0)
//	{
//		frameCount = 9;
//	}
//
//	if (diKeys[DIK_UP] & 0x80)
//	{
//		cout << "UP" << std::endl;
//	}
//	if (BUTTONDOWN(mouseState.rgbButtons[0] & 0x80))
//	{
//		//detect either the left button clicked or not
//		if (!leftButtonPressed) {
//			cout << "Click1" << std::endl;
//			leftButtonPressed = true;
//		}
//	}
//	else {
//		leftButtonPressed = false;
//	}
//	//0x80 detecting a button is pressing
//	if (BUTTONDOWN(mouseState.rgbButtons[1] & 0x80))
//	{
//		//detect either the right button clicked or not
//		if (!rightButtonPressed) {
//			cout << "Click2" << std::endl;
//			rightButtonPressed = true;
//		}
//	}
//	else {
//		rightButtonPressed = false;
//	}
//	/*(mouseState.lX != currentXpos || mouseState.lY != currentYpos) {
//		cout << "Mouse Position: X = " << mouseState.lX << ", Y = " << mouseState.lY << std::endl;
//		currentXpos = mouseState.lX;
//		currentYpos = mouseState.lY;
//	}
//	*/
//}
////--------------------------------------------------------------------
//// 
////--------------------------------------------------------------------
////	use int main if you want to have a console to print out message
////int main()
//
////	use WinMain if you don't want the console
//// Windows defination. auto asign the parameters by system.
////				   /unique id,like student id number/
////										/useless to us,store parent id, parent window/
////																 /long pointer string, command line parameters. to allow us to do thing from outside app(in cmd adding). to allow developers to test/demo... debug mode. server mode. else./
////																				  /useless, no need care/
//int /*WINAPI WinM*/ main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
//
//	createWindow();
//
//	createDirect3D9();
//
//	createSprite();
//
//	createInput();
//
//	while (windowIsRunning())
//	{
//		//cout << gameTimer->FrameToUpdate() << endl;
//		getInput();
//		//Physics
//		//Logic
//		update(gameTimer->framesToUpdate());
//		render();
//
//		//Sound
//	}
//
//	cleanupDirectInput();
//
//	cleanupSprite();
//	//if (windowIsRunning(msg))
//	//{
//	//	//Do something
//	//}
//	cleanupD3dDevice();
//
//	cleanupWindow();
//
//
//	return 0;
//}
////--------------------------------------------------------------------