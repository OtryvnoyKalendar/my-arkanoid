#include "core.h"
#include <signal.h> // для signal()
#include <termios.h>
#include <sys/ioctl.h>

// макрос CORE_MOUSE определяет будет ли обрабатываться события мыши

// закрытие программы

void ErrorCloseProgram(const char* message) {
	BeforeCloseProgram();
	printf("Ошибка: %s\n", message);
	
	exit(1);
}

void CloseProgram() {
	BeforeCloseProgram();
	
	exit(0);
}

// сигналы

volatile sig_atomic_t signal_status = 0;

void sighandler(int s) {
	signal_status = s;
}

void setSignals() {
	signal(SIGINT, sighandler); // когда нажимаем Ctrl+C
	signal(SIGQUIT, sighandler); // когда нажимаем Ctrl+'\'
	signal(SIGWINCH, sighandler); // когда изменяется размер терминала
	signal(SIGTSTP, sighandler); // когда нажимаем Ctrl+Z
}

void CheckSignals() {
	if (signal_status && signal_status != SIGWINCH)
		CloseProgram();
}


void setBackgroundColor(int BackgroundColor) {
	init_pair(COLOR_BLACK, COLOR_BLACK, BackgroundColor);
	init_pair(COLOR_GREEN, COLOR_GREEN, BackgroundColor);
	init_pair(COLOR_WHITE, COLOR_WHITE, BackgroundColor);
	init_pair(COLOR_RED, COLOR_RED, 	BackgroundColor);
	init_pair(COLOR_CYAN, COLOR_CYAN, 	BackgroundColor);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, BackgroundColor);
	init_pair(COLOR_BLUE, COLOR_BLUE, 	BackgroundColor);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, BackgroundColor);
}

void includeColors() {
	if(has_colors()) {
		start_color();
		setBackgroundColor(COLOR_BLACK);
	}
	else
		ErrorCloseProgram("терминал не поддерживает цвета");
}

// режим ncurses

void OpenNcursesMode() {
	initscr();
	savetty();
	nonl();
	cbreak();
	noecho();
	timeout(0);
	leaveok(stdscr, TRUE);
	#ifdef CORE_MOUSE
	curs_set(1);
	
	keypad(stdscr, TRUE); // mouse events getting reported as KEY_MOUSE
	mousemask(MOUSE_EVENTS_INIT | REPORT_MOUSE_POSITION, NULL);
	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
	
	if(has_mouse() == FALSE)
		ErrorCloseProgram("терминал не поддерживает мышь");
	#else
	curs_set(0);
	#endif
	
	includeColors();
	setSignals();
}

void CloseNcursesMode() {
	clear();
	refresh();
	resetty();
	#ifdef CORE_MOUSE
	printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
	#else
	curs_set(1);
	#endif
	endwin();
}

#ifdef CORE_MOUSE
// Получение координат курсора
void GetMouseState(int* y, int* x, unsigned* flags) {
	if(wgetch(stdscr) == KEY_MOUSE) {
		MEVENT event;
		if(getmouse(&event) == OK) {
			*y = event.y, *x = event.x;
			*flags = event.bstate;
		}
	}
}
#endif

void setConsoleSize(int consoleWidth, int consoleHeight) {
	printf("\e[8;%d;%dt", consoleHeight, consoleWidth);
}

void setConsoleTitle(const char* consoleTitle) {
	printf("\033]2;%s\007", consoleTitle);
}
