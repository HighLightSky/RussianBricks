//
// Created by weizh on 2025/9/26.
//
#define GAME_FRAME_WIDTH 18  // 左边框宽度
#define GAME_FRAME_HEIGHT 25 // 左边框高度
#define GAME_INFO_FRAME_WIDTH 15  // 右边框宽度
#define GAME_INFO_FRAME_HEIGHT 25  // 右边框高度

#define TYPE_COUNT 7  // 7种方块
// 消分规则
#define ONE_SCORE 10
#define TWO_SCORE 30
#define THREE_SCORE 60
#define FOUR_SCORE 100

#define CHANGE_SPEED_PER_SCORE 1000  // 每1000分加速度

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

const int bricks[7][4][4][4] = {
    { // I型方块 (0)
        { // 形态 0 (水平)
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1 (垂直)
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0}
        },
        { // 形态 2 (水平，另一种表示，通常同形态0)
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0}
        },
        { // 形态 3 (垂直，另一种表示，通常同形态1)
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        }
    },
    { // J型方块 (1)
        { // 形态 0
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        { // 形态 2
            {0,0,0,0},
            {1,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        { // 形态 3
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
        }
    },
    { // L型方块 (2)
        { // 形态 0
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        { // 形态 2
            {0,0,0,0},
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        { // 形态 3
            {1,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    { // O型方块 (3)
        { // 形态 0 (所有形态都一样)
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 2
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 3
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },
    { // S型方块 (4)
        { // 形态 0
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        { // 形态 2 (同形态0，但位置可能不同)
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        { // 形态 3
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    { // T型方块 (5)
        { // 形态 0
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        { // 形态 2
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        { // 形态 3
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    { // Z型方块 (6)
        { // 形态 0
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        { // 形态 1
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        { // 形态 2
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        { // 形态 3
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        }
    }
};

//即将到来的形状
typedef struct tagNextBrick {
    int type;
    int shape;
    int row;  // 行，用数组表示是前面的数字
    int col;  // 列，用数组表示是后面的数字
} NextBrick;

typedef struct tagChess {
    int chessBoard[GAME_FRAME_HEIGHT][GAME_FRAME_WIDTH];  // 棋盘的状态
    // int (*p)[TYPE_COUNT][4][4][4]; // 当前方块种类
    int type;
    int shape;
    int row;  // 行，用数组表示是前面的数字
    int col;  // 列，用数组表示是后面的数字
    int left;  // 离4*4方格左侧距离
    int right; // 离4*4方格右侧距离
    int top;  // 离4*4方格上方距离
    int bottom;  // 离4*4方格底部距离
} Chess;

// 统一坐标系统
// 使用 [row][col] 作为主要坐标系统
// 控制台坐标(x,y)对应下来，x是col，y是row
// 获取方块的信息，实际方块到4*4格子边距

HANDLE g_hOut;
HANDLE g_hIn;
int score;
BOOL gameover = FALSE;
Chess chess;
NextBrick next;
BOOL isDown = FALSE;

// 生成随机整数
int Getrand(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 设置控制台窗口大小
BOOL SetConsoleSize(int width, int height) {
    // 1. 设置屏幕缓冲区大小
    COORD bufferSize = { (SHORT)width, (SHORT)height };
    if (!SetConsoleScreenBufferSize(g_hOut, bufferSize)) {
        return FALSE; // 设置缓冲区失败
    }

    // 2. 设置窗口大小
    SMALL_RECT windowRect = {
        0,              // 左上角X坐标
        0,              // 左上角Y坐标
        (SHORT)(width - 1),  // 右下角X坐标
        (SHORT)(height - 1)  // 右下角Y坐标
    };

    if (!SetConsoleWindowInfo(g_hOut, TRUE, &windowRect)) {
        // 如果设置窗口失败，尝试调整缓冲区大小
        COORD maxSize = GetLargestConsoleWindowSize(g_hOut);
        if (width > maxSize.X) width = maxSize.X;
        if (height > maxSize.Y) height = maxSize.Y;

        bufferSize.X = (SHORT)width;
        bufferSize.Y = (SHORT)height;
        SetConsoleScreenBufferSize(g_hOut, bufferSize);

        windowRect.Right = (SHORT)(width - 1);
        windowRect.Bottom = (SHORT)(height - 1);
        return SetConsoleWindowInfo(g_hOut, TRUE, &windowRect);
    }

    return TRUE;
}

// 定位光标位置
void GotoXY(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 获取当前光标位置
COORD GetCurrentCursorPosition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return csbi.dwCursorPosition;
    } else {
        // 如果获取失败，返回默认位置 (0,0)
        COORD invalid = {0, 0};
        return invalid;
    }
}

// 画边框
void DrawFrame(int init_x, int init_y, int width, int height) {
    int i;
    GotoXY(init_x, init_y);
    printf("·");
    // 上边线
    for (i=0; i<width; i++) {
        printf("-");
    }
    printf("·");
    // 左右边线
    for (i=init_x; i<=(init_y+height); i++) {
        GotoXY(init_x, i+1);
        printf("|");
        GotoXY(init_x+(width+1), i+1);
        printf("|");
    }
    GotoXY(init_x, init_y+height+1);
    printf("·");
    for (i=0; i<width; i++) {
        printf("-");
    }
    printf("·");
    return;
}

void printScore(int s) {
    GotoXY(GAME_FRAME_WIDTH+14, 16);
    printf("%d", s);
}

void printSpeed(int s) {
    GotoXY(GAME_FRAME_WIDTH+14, 16);
    printf("%d", s);
}

// 右侧信息窗口信息输出
void GameInfoOutput() {
    int i;
    GotoXY(GAME_FRAME_WIDTH+6, 2);
    printf("Next:");
    GotoXY(GAME_FRAME_WIDTH+6, 10);
    for (i=0; i<GAME_INFO_FRAME_WIDTH; i++) {
        printf("-");
    }
    GotoXY(GAME_FRAME_WIDTH+6, 13);
    printf("Speed:");
    GotoXY(GAME_FRAME_WIDTH+6, 16);
    printf("Score:");
    GotoXY(GAME_FRAME_WIDTH+6, 22);
    printf("Gamer:");
    GotoXY(GAME_FRAME_WIDTH+12, 22);
    printf("Admin");
}

// 显示下一个方块
void printNextBrick() {
    int i, j, row;
    row = 1;
    GotoXY(GAME_FRAME_WIDTH+11, 3);
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            if (bricks[next.type][next.shape][i][j]==1) {
                printf("■");
            }else printf(" ");
        }
        GotoXY(GAME_FRAME_WIDTH+11, 3+row);
        row++;
    }
}

// 写入棋盘
void setBoard(int state) {  // state=0 空 1 有方块
    int i, j;
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            if (bricks[chess.type][chess.shape][i][j]==1) {
                chess.chessBoard[chess.row+i][chess.col+j] = state;
            }
        }
    }
}


void clearBrick() {
    int i, j, row;
    GotoXY(chess.col, chess.row);
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            if (bricks[chess.type][chess.shape][i][j]==1) {
                printf(" ");
            }
        }
        GotoXY(chess.col, chess.row+i+1);
    }
}


// 找到方块最左侧的离方块边界的位置
int getLeft() {
    for (int i=0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            if (bricks[chess.type][chess.shape][j][i]!=0) {
                return i;
            }
        }
    }
}

int getRight() {
    for (int i=0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            if (bricks[chess.type][chess.shape][j][3-i]!=0) {
                return i;
            }
        }
    }
}

int getTop() {
    for (int i=0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            if (bricks[chess.type][chess.shape][i][j]!=0) {
                return i;
            }
        }
    }
}

int getBottom() {
    for (int i=0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            if (bricks[chess.type][chess.shape][3-i][j]!=0) {
                return i;
            }
        }
    }
}

// 创建新的下一块方块
void createNext() {
    next.col = Getrand(1, GAME_FRAME_WIDTH-4);
    next.row = 1;
    next.type = Getrand(0, TYPE_COUNT-1);
    next.shape = Getrand(0, 3);
}

// 创建新方块
void createBrick() {
    // 初始化当前方块
    chess.col = next.col;
    chess.row = 1;
    chess.type = next.type;
    chess.shape = next.shape;

    chess.left = getLeft();
    chess.right = getRight();
    chess.top = getTop();
    chess.bottom = getBottom();

    // 初始化下落状态，此时开始下落
    isDown = TRUE;
}

// 检测是否会碰撞
BOOL checkCollision(int new_row, int new_col) {
    BOOL is_col = FALSE;
    // 检测时不能被本身干扰，首先需要清除自己

    // 检测超出边界
    if (new_col < 0 || new_col > GAME_FRAME_WIDTH - 4) is_col = TRUE;
    if (new_row < 0 || new_row > GAME_FRAME_HEIGHT - 4 + chess.bottom) is_col = TRUE;

    // 检测下边，从下往上，从左往右依次判断
    for (int row=3; row>0; row--) {
        for (int col=0; col<4; col++) {
            if (bricks[chess.type][chess.shape][row][col]==1 && chess.chessBoard[new_row+row][new_col+col]==1) {
                is_col = TRUE;
                return is_col;
            }
        }
    }

    // 检测左边，从上往下，从左往右
    for (int col=0; col<4; col++) {
        for (int row=0; row<4; row++) {
            if (bricks[chess.type][chess.shape][row][col]==1 && chess.chessBoard[new_row+row][new_col+col]==1) {
                is_col = TRUE;
                return is_col;
            }
        }
    }

    // 检测右边，从上往下，从右往左
    for (int col=3; col>=0; col--) {
        for (int row=0; row<4; row++) {
            if (bricks[chess.type][chess.shape][row][col]==1 && chess.chessBoard[new_row+row][new_col+col]==1) {
                is_col = TRUE;
                return is_col;
            }
        }
    }
    return is_col;
}

// 根据棋盘打印到游戏主界面
void printToMain() {
    for (int row=0; row<GAME_FRAME_HEIGHT; row++) {
        GotoXY(1, 1+row);
        for (int col=0; col<GAME_FRAME_WIDTH; col++) {
            if (chess.chessBoard[row][col]==1) {
                printf("■");
            }else {
                printf(" ");
            }
        }
    }
}


// 测试用：打印棋盘
void printChessBoard() {
    int row = 1;
    int init_x = GAME_FRAME_WIDTH+GAME_INFO_FRAME_WIDTH+10;
    GotoXY(init_x, row);
    for (int i=0; i<GAME_FRAME_HEIGHT; i++) {
        for (int j=0; j<GAME_FRAME_WIDTH; j++) {
            printf("%d", chess.chessBoard[i][j]);
        }
        row++;
        GotoXY(init_x, row);
    }
}

// 测试用，打印测试数据
void printHelp(char *s) {
    GotoXY(1, GAME_FRAME_HEIGHT+2);
    printf(s);
}

// 如果一排全都满了，消去这一排
void clearRow() {
    for (int row=GAME_FRAME_HEIGHT-1; row>=0; row--) {
        BOOL clear = TRUE;
        for (int col=1; col<GAME_FRAME_WIDTH-1; col++) {
            if (chess.chessBoard[row][col]==0) {
                clear = FALSE;
                break;
            }
        }

        if (clear) {
            printHelp("                         ");
            printHelp("CLEAR ROW!");
            for (int new_row=row; new_row>=0; new_row--) {
                if (new_row==0) {
                    for (int new_col=0; new_col<GAME_FRAME_WIDTH; new_col++) {
                        chess.chessBoard[new_row][new_col] = 0;
                    }
                }else {
                    for (int new_col=0; new_col<GAME_FRAME_WIDTH; new_col++) {
                        chess.chessBoard[new_row][new_col] = chess.chessBoard[new_row-1][new_col];
                    }
                }
            }
        }
    }
}

void brickDown() {
    setBoard(0);
    if (!checkCollision(chess.row+1, chess.col)) {
        chess.row++;
    }else {
        isDown = FALSE;
        // 固定方块
        setBoard(1);
        clearRow();  // 每次到底都检测是否可以清除方块
        return;
    }
    setBoard(1);
    printChessBoard();
    printToMain();
}
void changeType() {
    setBoard(0);
    chess.shape = chess.shape+1>3 ? 1:chess.shape+1;
}

void brickDownToBottom() {
    for (int i=1; i<GAME_FRAME_HEIGHT; i++) {
        setBoard(0);
        if (!checkCollision(chess.row+1, chess.col)) {
            chess.row++;
            continue;
        }else {
            isDown = FALSE;
            // 固定方块
            setBoard(1);
            printHelp("DOWN!");
            setBoard(1);
            printChessBoard();
            printToMain();
            return;
        }
    }
}

void brickLeft() {
    setBoard(0);
    if (!checkCollision(chess.row, chess.col-1)) {
        chess.col--;
    }else {
        return;
    }
    setBoard(1);
    printChessBoard();
    printToMain();
}

void brickRight() {
    setBoard(0);
    if (!checkCollision(chess.row, chess.col+1)) {
        chess.col++;
    }else {
        return;
    }
    setBoard(1);
    printChessBoard();
    printToMain();
}

// 在游戏主循环中
DWORD cNumRead;  // 实际读取的输入记录数
INPUT_RECORD irInBuf[128];  // 输入事件缓冲区

void Gaming() {
    while (!gameover) { // 游戏主循环
        // 初始化操作
        createBrick();
        createNext();
        setBoard(1);
        printNextBrick();
        printChessBoard();
        printToMain();

        DWORD dwPreviousTime = GetTickCount(); // 记录当前时间戳
        int fallInterval = 500; // 下落间隔500毫秒

        while (isDown == TRUE) {
            DWORD dwCurrentTime = GetTickCount();

            // 1. 非阻塞地检查输入
            DWORD cNumRead;
            INPUT_RECORD irInBuf[128];
            if (GetNumberOfConsoleInputEvents(g_hIn, &cNumRead) && cNumRead > 0) {
                if (ReadConsoleInput(g_hIn, irInBuf, 128, &cNumRead)) {
                    for (DWORD i = 0; i < cNumRead; i++) {
                        if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                            // 处理按键，例如改变方向、加速下落等
                            switch (irInBuf[i].Event.KeyEvent.wVirtualKeyCode) {
                                case VK_LEFT:
                                    printHelp("                   ");
                                    printHelp("LEFT");
                                    brickLeft();
                                    break;
                                case VK_RIGHT:
                                    printHelp("                   ");
                                    printHelp("RIGHT");
                                    brickRight();
                                    break;
                                case VK_SPACE:
                                    printHelp("                   ");
                                    printHelp("SPACE");
                                    brickDownToBottom();
                                    break;
                                case VK_DOWN:
                                    printHelp("                   ");
                                    printHelp("RETURN");
                                    changeType();
                                    break;
                            }
                        }
                    }
                }
            }
            // 2. 正常的游戏逻辑（方块下落，碰撞检测等）,检查是否到达下落时间，而非单纯Sleep
            if (dwCurrentTime - dwPreviousTime >= fallInterval) {
                brickDown(); // 执行一次下落
                dwPreviousTime = dwCurrentTime; // 重置计时器
            }


            // 3. 给予极短的休息，避免CPU占用率100%
            Sleep(10); // 例如，每次循环休眠50毫秒
        }
    }
}


int main() {
    // 初始化随机数种子
    srand(time(NULL));

    system("color 3f");
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_hIn = GetStdHandle(STD_INPUT_HANDLE);

    // 这里还差一个隐藏光标
    SetConsoleSize(GAME_FRAME_WIDTH+GAME_INFO_FRAME_WIDTH+4, GAME_FRAME_HEIGHT);
    // 画左边格子
    DrawFrame(0, 0, GAME_FRAME_WIDTH, GAME_FRAME_HEIGHT);
    // 画右边格子
    // DrawFrame(GAME_FRAME_WIDTH+4, 0, GAME_INFO_FRAME_WIDTH, GAME_INFO_FRAME_HEIGHT);
    SetConsoleTitle("俄罗斯方块");
    GameInfoOutput();

    int timestar, i, j;
    gameover = FALSE;
    // 初始化棋盘 没有任何方块 需要和实际输出相对应
    for (int row=0; row<GAME_FRAME_HEIGHT; row++) {
        for (int col=0; col<GAME_FRAME_WIDTH; col++) {
            chess.chessBoard[row][col] = 0;
        }
    }

        // 初始化分数和速度
    printScore(100);
    printSpeed(1000);
    createNext();  // 初始化第一个一个方块
    // 游戏主循环，获取用户输入
    Gaming();

    getchar();
}