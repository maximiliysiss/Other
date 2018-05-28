#include "DataBase.h"
#include "resource.h"


// Обработчики для окон
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_AddElement(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_FindEl(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_FindElResult(HWND, UINT, WPARAM, LPARAM);

// Открыть файл
void OpenFileDB(HWND hwnd);
// Сохранить файл
void SaveFileDB(HWND hwnd);
// Создать окно поиска
void StartFind(HWND hwnd);
// Вывести в окно результаты поиска
void StartOutResultFind(HWND hwnd);
// Вывести окно добавления
void AddToHwndList(HWND hList);

char* ClassName = "CUDB";
char* AppName = "DataBase's system of control";

// Ключ поиска
char key[80] = "\0";

// Выбранный индекс
int Index_Choose = -1;

// БД
DataBase * database = NULL;
// Вектор полученных результатов
std::vector<Student> res_search;

// Определения ID разных элементов окна
const UINT IDC_LIST_CHILD = 101;
const UINT IDC_LISTVIEW = 11;
const UINT IDC_BUTTON_DEL = 13;
const UINT IDC_BUTTON_ADD = 14;
const UINT IDC_BUTTON_SEARCH = 15;
const UINT IDC_BUTTON_DOWNLOAD = 16;
const UINT IDC_BUTTON_SAVING = 17;
const UINT IDC_WINDOW_CHILD = 32;
const UINT IDC_BUTTON_CHILD = 31;
const UINT IDC_EDIT_CHILD_ONE = 33;
const UINT IDC_EDIT_CHILD_TWO = 34;
const UINT IDC_EDIT_CHILD_THR = 35;
const UINT IDC_EDIT_CHILD_FOR = 36;
const UINT IDC_EDIT_CHILD_FIV = 37;

// ID приложения
HINSTANCE hInst;

// Окна добалвения, поиска и вывод результатов
HWND hWndAdd, hWndFind, hWndResultFind;

// Главный лист (таблица)
HWND hListView_Main;

// Проверка массива на число
bool isDigit(char * input)
{
	while (*input != '\0')
		if (!isdigit(*(input++)))
			return false;
	return true;
}

// Добавление колонки
void AddColumn(HWND hListView)
{
	std::string columns[] = { "ID","FIO","Age","Average Balls","University" };
	int sizeX[COUNT_COLUMNS] = { IDCOLUMN,NAMECOLUMN,AGECOLUMN,AVRBALLCOLUMN,UNIVERCOLUMN };
	LVCOLUMN lvc; // Колонка
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_CENTER;
	for (int i = 0; i < COUNT_COLUMNS; i++)
	{
		lvc.cx = sizeX[i]; // Ширина колонки
		lvc.pszText = (LPSTR)columns[i].c_str(); // Текст в колонке
		ListView_InsertColumn(hListView, i, &lvc);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmd, int nCmd) // Главная функция
{
	HWND hWnd;
	hInst = hInstance;
	srand((UINT)time(NULL)); // Для рандомных переменных seed
	MSG msg; // Обработчик сообщение
	WNDCLASS wnd; // Класс окна
	wnd.style = CS_VREDRAW | CS_HREDRAW; // Дальше настройка класса окна
	wnd.cbClsExtra = wnd.cbWndExtra = 0;
	wnd.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wnd.hInstance = hInstance;
	wnd.hIcon = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = ClassName;
	RegisterClass(&wnd); // Регистрация класса окна
	// Создание окна
	hWnd = CreateWindow(ClassName, AppName, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		WIDTHLIST, HEIGHTWND, 0, NULL, hInstance, 0);
	// Создание таблицы
	hListView_Main = CreateWindow(WC_LISTVIEW, "",
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS, 0, 0, WIDTHLIST, HEIGHTLIST_MAIN,
		hWnd, (HMENU)IDC_LISTVIEW, hInstance, NULL);
	// Добавление стилей
	ListView_SetExtendedListViewStyleEx(hListView_Main, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	AddColumn(hListView_Main);
	ShowWindow(hWnd, SW_SHOW); // Показать окно
	UpdateWindow(hWnd); // Обновить
	while (GetMessage(&msg, 0, 0, 0)) // Запуск обработчик сообщений
	{
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

void CreateAddWnd(HWND hwnd) // Создать окно добавления
{
	WNDCLASS w; // Класс окна
	memset(&w, 0, sizeof(WNDCLASS));
	w.lpfnWndProc = WndProc_AddElement;
	w.hInstance = hInst;
	w.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	w.lpszClassName = "ChildWClass";
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&w); // Регистрация класса
	// Создание окна
	hWndAdd = CreateWindowEx(0, "ChildWClass", "Add to DB",
		WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		300, 300, hwnd, NULL, hInst, NULL);
	// Определение для EDIT Box
	UINT IDCs[5]{ IDC_EDIT_CHILD_ONE , IDC_EDIT_CHILD_TWO , IDC_EDIT_CHILD_THR,IDC_EDIT_CHILD_FOR,IDC_EDIT_CHILD_FIV };
	int maxLimit[5]{ 40,3,3,40,4 };
	for (int i = 0; i < 5; i++)
	{
		// Создание EDIT боксов
		HWND Edit_name = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
			10 + 130 * (i / 3), 30 + (i % 3) * 50, 100, 25, hWndAdd, (HMENU)IDCs[i], GetModuleHandle(NULL), NULL);
		SendMessage(Edit_name, EM_SETLIMITTEXT, maxLimit[i], NULL); // Установка лимитов для ввода
	}
	// Создание кнопки
	HWND hButtonActive = CreateWindow("BUTTON", "Add to DataBase Active", WS_CHILD | WS_VISIBLE, 20, 180, 200, 50, hWndAdd,
		(HMENU)IDC_BUTTON_CHILD, GetModuleHandle(NULL), NULL);
	ShowWindow(hWndAdd, SW_NORMAL);
	UpdateWindow(hWndAdd);
}

LRESULT CALLBACK WndProc_AddElement(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) // Обработчик для окна добавления
{
	HDC hdc; // Создание контекста
	PAINTSTRUCT ps; // Структура для рисования
	switch (msg)
	{
	case WM_PAINT: // Рисование
	{
		std::string texts[5]{ "Student Name","Age","Count Marks","University","ID" }; // Определение подписей
		hdc = BeginPaint(hwnd, &ps); // Начало рисовки
		for (int i = 0; i < 5; i++)
		{
			RECT rc{ 10 + 130 * (i / 3),10 + 50 * (i % 3),120 + 140 * (i / 3),30 + 60 * (i % 3) };
			DrawText(hdc, texts[i].c_str(), (int)texts[i].length(), &rc, NULL); // Рисовка надписей по координатам
		}
		EndPaint(hwnd, &ps); // Конец рисовки
	}
	case WM_COMMAND: // Обработка нажатия кнопок
	{
		switch (wParam)
		{
		case IDC_BUTTON_CHILD: // Нажата кнопка
			char name[50] = "\0";
			char university[50] = "\0";
			char age[5] = "\0";
			char id[10] = "\0";
			char countMarks[5] = "\0";
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHILD_ONE), name, sizeof(name)); // Получение из EDIT текста
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHILD_THR), countMarks, sizeof(countMarks));
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHILD_TWO), age, sizeof(age));
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHILD_FIV), id, sizeof(id));
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHILD_FOR), university, sizeof(university));
			if (!isDigit(age) || !isDigit(countMarks) || !isDigit(id)) // Если EDIT не цифра (для некоторых)
			{
				MessageBox(0, "You enter chars in field for numbers", "Error", MB_OK);
				return 0;
			}
			// Если EDITы непусты
			if (!(name[0] == '\0' || university[0] == '\0' || id[0] == '\0' || age[0] == '\0' || countMarks[0] == '\0'))
			{
				if (database == NULL) // Если бд пуста
					database = new DataBase("", true, true); // Создать бд в фоне (InScreen)
				Student to_list(std::stoi(std::string(id)), std::stoi(std::string(age)), std::string(name),
					std::stoi(std::string(countMarks)), std::string(university)); // Студент на добавление
				for (int i = 0; i < ListView_GetItemCount(hListView_Main); i++)
				{
					LV_ITEM itemInfo = { 0 }; // Создание ITem
					char info[20];
					itemInfo.iItem = i;
					itemInfo.mask = LVIF_TEXT;
					itemInfo.cchTextMax = 20;
					itemInfo.iSubItem = 0;
					itemInfo.pszText = info;
					ListView_GetItem(hListView_Main, &itemInfo);
					if (std::string(info) == std::to_string(to_list.GetID())) // Проверка на повторение в бд
					{
						MessageBox(0, "It's have yet", "Error", MB_OK);
						return 0;
					}
				}
				database->AddRecord(to_list); // Добавить в бд студента
				database->AddToHWNDLIST(to_list, hListView_Main); // Добавить студента в таблицу
				SendMessage(hwnd, WM_CLOSE, 0, 0); // Закрыть окно
			}
			else
				MessageBox(0, "Enter data", "Error", MB_OK); // Какое-то из EDIT пусто
			break;
		}
	}
	break;
	case WM_CLOSE:// Закрытие
		DestroyWindow(hwnd);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

Student GetStudentFromList(int index)// Получить студента из таблицы по индексу для будущего сравнения (в сравнении средний балл не учитывается)
{
	if (index < 0 || index >= ListView_GetItemCount(hListView_Main)) // Если индекс вышел за пределы
		return Student(0, 0, "Empty", 0, "Empty");
	LV_ITEM itemInfo = { 0 }; // Создание ITEM
	char info[5][100];
	itemInfo.iItem = index;
	itemInfo.mask = LVIF_TEXT;
	itemInfo.cchTextMax = 100;
	for (int i = 0; i < 5; i++)
	{
		itemInfo.iSubItem = i;
		itemInfo.pszText = info[i];
		ListView_GetItem(hListView_Main, &itemInfo); // Получение инфы из ITEM
	}
	ListView_DeleteItem(hListView_Main, index);
	// Создание и возврат студента
	return Student(std::stoi(std::string(info[0])), std::stoi(std::string(info[2])), std::string(info[1]), 10, std::string(info[4]));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) // Главный обработчик
{
	switch (msg)
	{
	case WM_CREATE: // СОздание 
	{
		UINT IDCs[5]{ IDC_BUTTON_ADD ,IDC_BUTTON_DEL ,IDC_BUTTON_DOWNLOAD ,IDC_BUTTON_SEARCH ,IDC_BUTTON_SAVING }; // Определение Айди для кнопок
		WORD RESs[5]{ IDB_ADD ,IDB_DEL ,IDB_DOWNLOAD ,IDB_SEARCH ,IDB_SAVING }; // Определение для кнопок изображений
		for (int i = 0; i < 5; i++)
		{
			// Создание кнопки
			HWND hButton = CreateWindow("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_BITMAP, 10 + i*(66), 350, 60, 60,
				hwnd, (HMENU)IDCs[i], GetModuleHandle(NULL), NULL);
			SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(NULL),
				MAKEINTRESOURCE(RESs[i]))); // Задание изображения на кнопку
		}
		break;
	}
	case WM_NOTIFY: // Обработка реакций
		LPNMHDR lpnmHdr;
		lpnmHdr = (LPNMHDR)lParam; // Получение информации о том, на кого среагировало
		if ((lpnmHdr->idFrom == IDC_LISTVIEW) && (lpnmHdr->code == NM_CLICK)) // Если нажатие левой клавишей и айди главного листа
		{
			LPNMLISTVIEW pnmLV = (LPNMLISTVIEW)lParam; // Получение полной информации
			Index_Choose = pnmLV->iItem; // Получение индекса
		}
		break;
	case WM_COMMAND: // Обработка кнопок
		switch (wParam)
		{
		case IDC_BUTTON_ADD: // Добавление 
			CreateAddWnd(hwnd);
			break;
		case IDC_BUTTON_DOWNLOAD: // Загрузка
			OpenFileDB(hwnd);
			break;
		case IDC_BUTTON_DEL: // Удалвение
			if (Index_Choose != -1) // Если индекс выбран
			{
				Student del_st = GetStudentFromList(Index_Choose); // Получаем студента по индексу
				if (del_st.GetFIO() == "Empty") // Если пуст, то игнорируем
					break;
				database->DeleteRecord(del_st); // Удаляем
			}
			break;
		case IDC_BUTTON_SEARCH: // Поиск
			StartFind(hwnd);
			break;
		case IDC_BUTTON_SAVING: // Сохранение
			SaveFileDB(hwnd);
			break;
		case ID_WORKWITHDB_NEWDATABASE: // Кнопка в меню
			SetWindowText(hwnd, AppName); // Установить заголовок главного окна
			delete database; // Удаление связи с текущей бд
			database = NULL;
			ListView_DeleteAllItems(hListView_Main); // Очистка главной таблицы
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

std::string GetName(char* file) // Получить имя файла из полного пути
{
	char * res = std::find(file, file + 259, '\0');
	while (*res != '\\')
		res--;
	return std::string(++res);
}

void OpenFileDB(HWND hwnd) // Открыть файл
{
	OPENFILENAME ofn = { 0 }; // Определение для получения информации о выборе пользователя
	char szFile[260]; // Хранение пути
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile; // Подключение к хранению
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "fileDB\0*.fileDB\0"; // Маска
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetOpenFileName(&ofn)) // Проверка на удачное открытие и выбор, а не отмену
		return;
	std::string new_name = std::string(AppName) + " [" + GetName(ofn.lpstrFile) + "]"; //  Создание нового имени для приложения
	SetWindowText(hwnd, (LPSTR)new_name.c_str()); // Установка нового имени
	if (database && std::string(ofn.lpstrFile) == database->GetFilePath()) // Если путь совпал с тем, что же открыта
	{
		MessageBox(NULL, "This file open yet", "Error", MB_OK);
		return;
	}
	int result = MessageBox(NULL, "Download to RAM?", "Place of saving", MB_YESNO); // Загрузить в ОЗУ?
	if (database != NULL) // БД создана - закрыть
		delete database;
	ListView_DeleteAllItems(hListView_Main); // Очищение таблицы
	switch (result)
	{
	case IDYES:
		database = new DataBase(std::string(ofn.lpstrFile), true); // Бд в ОЗУ
		break;
	case IDNO:
		database = new  DataBase(std::string(ofn.lpstrFile), false); // Бд из Файла
		break;
	}
	database->LoadToListViewFromRAM(hListView_Main); // Вывод в таблицу
}

void SaveFileDB(HWND hwnd) // Сохранение
{
	if (database == NULL) // Пустая - пропуск
		return;
	OPENFILENAME ofn; // Определение для получение резульатов выбора
	char szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "fileDB\0*.fileDB\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetSaveFileName(&ofn)) // Удачный выбор?
		return;
	std::string new_name = std::string(AppName) + " [" + GetName(ofn.lpstrFile) + ".fileDB]"; // Изменение имени
	SetWindowText(hwnd, (LPSTR)new_name.c_str());
	database->SavingDB(std::string(ofn.lpstrFile)); // Сохранение
}

void StartFind(HWND hwnd) // Создание окна поиска
{
	WNDCLASS w; // Регистрация класса
	memset(&w, 0, sizeof(WNDCLASS));
	w.lpfnWndProc = WndProc_FindEl;
	w.hInstance = hInst;
	w.hbrBackground = (HBRUSH)(WHITE_BRUSH); // Задание Фона
	w.lpszClassName = "FindClass";
	w.hCursor = LoadCursor(NULL, IDC_ARROW); // Задание курсора
	RegisterClass(&w); // Регистрация
	// Создание окна
	hWndFind = CreateWindowEx(0, "FindClass", "Find in DB",
		WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		300, 100, hwnd, NULL, hInst, NULL);
	// Создание поля ввода
	HWND hEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL, 0, 5, 300, 20, hWndFind,
		(HMENU)IDC_EDIT_CHILD_ONE, hInst, NULL);
	// Создание кнопки
	HWND hButton = CreateWindow("BUTTON", "Start Find", WS_VISIBLE | WS_CHILD, 5, 30, 100, 20, hWndFind, (HMENU)IDC_BUTTON_CHILD, hInst, NULL);
	ShowWindow(hWndFind, SW_NORMAL);
	UpdateWindow(hWndFind);
}

LRESULT CALLBACK WndProc_FindEl(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) // Обработчик для окна поиска
{
	switch (msg)
	{
	case WM_COMMAND://Нажатие клавиш
		switch (wParam)
		{
		case IDC_BUTTON_CHILD:
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHILD_ONE), key, sizeof(key)); // ПОлучение ключа поиска
			if (key[0] != '\0' && database != NULL) // Если ключ пуст и бд не пуста
			{
				StartOutResultFind(GetParent(hwnd)); // Запустить окно вывод рузльтатов
				SendMessage(hwnd, WM_CLOSE, 0, 0); // Закрыть текущее окно
			}
			else
				if (database == NULL) // Если база пуста
					MessageBox(0, "Choose DB", "Error", 0);
				else // Если ввода не было
					MessageBox(0, "Enter smth", "Error", MB_OK);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void StartOutResultFind(HWND hwnd) // Окно вывода результатов поиска
{
	res_search = database->FindEl(std::string(key)); // Получение результатов поиска
	if (res_search.size() < 1) // Если пуст результат, то и вывода не надо
	{
		MessageBox(0, "Not found anything", "404", 0);
		return;
	}
	WNDCLASS w; // Класс окна
	memset(&w, 0, sizeof(WNDCLASS));
	w.lpfnWndProc = WndProc_FindElResult;
	w.hInstance = hInst;
	w.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	w.lpszClassName = "FindRes";
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&w); // Регитсрация
	// Создание окна
	hWndResultFind = CreateWindowEx(0, "FindRes", "Result",
		WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		WIDTHLIST, 300, hwnd, NULL, hInst, NULL);
	// Создание таблицы
	HWND hListChd = CreateWindow(WC_LISTVIEW, "",
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EX_FULLROWSELECT |
		LVS_EDITLABELS,
		0, 0, WIDTHLIST, 300,
		hWndResultFind, (HMENU)IDC_LIST_CHILD, hInst, NULL);
	ListView_SetExtendedListViewStyleEx(hListChd, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	AddColumn(hListChd);
	AddToHwndList(hListChd); // Добалвние информации в лист
	ShowWindow(hWndResultFind, SW_NORMAL);
	UpdateWindow(hWndFind);
}

void SaveLikeDB() // Сохранение ДБ из результатов
{
	OPENFILENAME ofn; // Определение для хранения резов выбора пользователя
	char szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "fileDB\0*.fileDB\0"; // Маска
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetSaveFileName(&ofn))
		return;
	// Запись в файл
	std::fstream file_save(std::string(ofn.lpstrFile) + ".fileDB", std::ios_base::binary | std::ios_base::out);
	for (UINT i = 0; i < res_search.size(); i++)
		file_save.write((char*)&res_search[i], sizeof(Student));
	file_save.close();
}

void AddToHwndList(HWND hList) // Добавление в лист
{
	LVITEM lvi; // Создание элемента таблицы
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
	lvi.state = 0;
	lvi.stateMask = 0;
	for (UINT i = 0; i < res_search.size(); i++)
	{
		lvi.iItem = i;
		lvi.iSubItem = 0;
		int res = ListView_InsertItem(hList, &lvi);
		ListView_SetItemText(hList, res, 0, res_search[i].GetIDChar()); // Передача определенных полей в таблицу
		ListView_SetItemText(hList, res, 1, res_search[i].GetFIOChar());
		ListView_SetItemText(hList, res, 2, res_search[i].GetAgeChar());
		ListView_SetItemText(hList, res, 3, res_search[i].GetAverBallChar());
		ListView_SetItemText(hList, res, 4, res_search[i].GetUniversityChar());
	}
}

LRESULT CALLBACK WndProc_FindElResult(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) // Обработчик для результатов поиска
{
	switch (msg)
	{
	case WM_CLOSE: // Закрытие
	{
		int result = MessageBox(0, "Save it like BD", "Saving", MB_YESNO); // Сохранить результаты поиска как бд
		switch (result)
		{
		case IDYES:
			SaveLikeDB();
			break;
		}
		res_search.clear(); // Очистка
		DestroyWindow(hwnd);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}