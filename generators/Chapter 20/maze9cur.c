// this is a maze that solves itself with no loops - only one true path to anywhere. 
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<curses.h>

#define LENGTH 71  /* must be odd and no bigger than 81 */
#define WIDTH  23  /* must be odd and no bigger than 25 */
#define TRUE 1
#define FALSE 0
char maze[LENGTH][WIDTH];
char ans;
int free_space;
int loc_x;
int loc_y;
int available_path = TRUE;
int win = FALSE;
void display(void);
void setup(void);
void test_for_free_o(void);
void change_next_z(void);
void test_for_next_z(void);
void join_new_z(void);
void clear_up_maze(void);
void place_you(void);
void place_exit(void);
void move_you(void);
void check_for_win(void);
void solve_maze(void);
void put_more_spaces_in(void);
void solve_mult_maze(void);

int main(void)
{
time_t t;
srand((unsigned) time(&t));
initscr();
start_color();
init_pair(7,COLOR_BLACK,COLOR_BLACK);
bkgd(COLOR_PAIR(7));
refresh(); 
init_pair(1,COLOR_BLUE,COLOR_RED);
init_pair(2,COLOR_GREEN,COLOR_YELLOW);
init_pair(3,COLOR_MAGENTA,COLOR_BLUE);
init_pair(4,COLOR_MAGENTA,COLOR_GREEN);
init_pair(5,COLOR_RED,COLOR_YELLOW);
init_pair(6,COLOR_GREEN,COLOR_BLUE);
setup();
clear();
attrset(COLOR_PAIR(1));
refresh();

do
{
test_for_next_z();
if (available_path == TRUE)
do
{
change_next_z();
test_for_next_z();
display();
refresh();
}while (available_path == TRUE);
test_for_free_o();
if (free_space == TRUE)
join_new_z();
test_for_free_o();
display();
refresh();
}while(free_space == TRUE);
clear_up_maze();
display();
clear();
//put_more_spaces_in();
place_you();
place_exit();
display();
refresh();
clear();
do
{
move_you();
check_for_win();
}while (win == FALSE );
napms(40);
clear();
getch();
endwin();
return(0);	
}

void solve_mult_maze(void)
{
int x,y,i,j;
int count;
int goal_attained = 0;
int direction;
int done;
do
{
//solve_maze();
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
if (maze[i][j] == 'E')
maze[i][j] = ' ';
place_you();
display();
refresh();
napms(20);
maze[2][2] = 'E';
x = 2; y = 2;
do{
do{
done = 0;
direction = rand()%(4);
if (direction == 0)
{
if (maze[x-1][y] == ' ')
{
--x;
done = 1;
}
}
else if (direction == 1)
{
if (maze[x][y-1] == ' ')
{
--y;
done  = 1;
}
}
else if (direction == 2)
{
if (maze[x+1][y] == ' ')
{
++x;
done = 1;
}
}
else if (direction == 3)
{
if (maze[x][y+1] == ' ')
{
++y;
done = 1;
}
}
}while (done == 0);
count = 0;
if (maze[x-1][y] == 'X')                 
++count;
if (maze[x+1][y] == 'X')
++count;
if (maze[x][y+1] == 'X')
++count;
if (maze[x][y-1] == 'X')
++count;
if (count > 2)
maze[x][y] = 'X';
else maze[x][y] = 'E';
display();
refresh();
napms(20); 
}while (maze[x][y] == 'E' && !(x == LENGTH-3 && y == WIDTH-4)
&& !(x == LENGTH-4 && y == WIDTH-3)  );
if ( (x == LENGTH-3 && y == WIDTH-4) || (x == LENGTH-4 &&
y == WIDTH -3))
goal_attained = 1;
}while(goal_attained == 0);
}
void put_more_spaces_in(void)
{
int i;
int x,y;
for (i = 0; i < 1000; ++i)
{
x = rand()%(LENGTH-4)+2;
y = rand()%(WIDTH-4)+2;
if (x%2 == 0 && y%2 == 1)
maze[x][y] = ' ';
display();
refresh();
napms(20);
}
}
void solve_maze(void)
{
int local_counter;
int global_counter;
int i,j;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
if (maze[i][j] == 'E')
maze[i][j] = ' ';
place_you();
do
{
global_counter = 0;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
{
local_counter = 0;
if (maze[i][j] == ' ')
{
if (maze[i+1][j] == 'X')
++local_counter;
if (maze[i - 1][j] == 'X')
++local_counter;
if (maze[i][j + 1] == 'X')
++local_counter;
if (maze[i][j - 1] == 'X')
++local_counter;
if (local_counter > 2)
{
maze[i][j] = 'X';
display();
}
if (local_counter > 2) global_counter = local_counter;
}/* end of if */
}/* end of for */
}while(global_counter > 2);
}
void check_for_win(void)
{
if (maze[LENGTH-4][WIDTH-3] == 'E' || maze[LENGTH-3][WIDTH-4] == 'E')
win = TRUE;
}
void place_you(void)
{
loc_x = 2;
loc_y = 2;
maze[loc_x][loc_y] = 'E';
}
void place_exit(void)
{
maze[LENGTH-3][WIDTH-3] = 'D';
}
void move_you(void)
{
solve_mult_maze();
display();
refresh();
napms(20);
}
void clear_up_maze(void)
{
int i,j;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
if (maze[i][j] == 'Z') maze[i][j] = ' ';
}
void join_new_z(void)
{
int x,y;
int found;
do
{
x = rand()%(LENGTH);
y = rand()%(WIDTH);
found = 0;
if (maze[x][y] == 'o')
{
if (maze[x-2][y] == 'Z')
{
maze[x-1][y] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
else if  (maze[x+2][y] == 'Z')
{
maze[x+1][y] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
else if (maze[x][y-2] == 'Z')
{
maze[x][y-1] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
else if (maze[x][y+2] == 'Z')
{
maze[x][y+1] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
}
}while(found == FALSE);
}
void test_for_next_z(void)
{
available_path =  FALSE;
if ( maze[loc_x - 2][loc_y] == 'o' ||
maze[loc_x + 2][loc_y] == 'o' ||
maze[loc_x][loc_y-2] == 'o' ||
maze[loc_x][loc_y+2] == 'o')
available_path = TRUE;
}
void change_next_z(void)
{
int x,y;
int direction;
int temp_loc_x;
int temp_loc_y;
do
{
direction = rand()%(4);
temp_loc_x = loc_x;
temp_loc_y = loc_y;
if (direction == 0)
temp_loc_x = loc_x - 2;
else if (direction == 1)
temp_loc_x = loc_x + 2;
else if (direction == 2)
temp_loc_y = loc_y - 2;
else if (direction == 3)
temp_loc_y = loc_y + 2;
}while (maze[temp_loc_x][temp_loc_y] != 'o');
if (direction == 0)
{
maze[loc_x-1][loc_y] = 'Z';
maze[temp_loc_x][loc_y] = 'Z';
}
else if (direction == 1)
{
maze[loc_x+1][loc_y] = 'Z';
maze[temp_loc_x][loc_y] = 'Z';
}
else if (direction == 2)
{
maze[loc_x][loc_y - 1] = 'Z';
maze[loc_x][temp_loc_y] = 'Z';
}
else if (direction == 3)
{
maze[loc_x][loc_y + 1] = 'Z';
maze[loc_x][temp_loc_y] = 'Z';
}
for (x = -1; x < 2; ++x)
for (y = -1; y < 2; ++y)
if (maze[loc_x + x][loc_y + y] != 'Z')
maze[loc_x + x][loc_y + y]  =  'X';
loc_x = temp_loc_x;
loc_y = temp_loc_y;
}
void test_for_free_o(void)
{
int i,j;
free_space = FALSE;
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
if (maze[i][j] == 'o')
free_space = TRUE;
}
void setup(void)
{
int x;
int i;
int j;
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
{
if (j%2==1||i%2==1)
maze[i][j] = '.';
else maze[i][j] = 'o';
}
for (x = 0; x < LENGTH; ++x)
{
maze[x][0] = 'X';
maze[x][1] = 'X';
}
for (x = 0; x < LENGTH; ++x)
{
maze[x][WIDTH - 1] = 'X';
maze[x][WIDTH - 2] = 'X';
}
for (x = 0; x < WIDTH; ++x)
{
maze[0][x] = 'X';
maze[1][x] = 'X';
}
for (x = 0; x < WIDTH; ++x)
{
maze[LENGTH - 1][x] = 'X';
maze[LENGTH - 2][x] = 'X';
}
loc_x = 2; loc_y = 2;
maze[loc_x][loc_y] = 'Z';
}
void display(void)
{
int i;
int j;
move(0,0);         
for (j = 0; j < WIDTH;++j)
{
for (i = 0; i < LENGTH; ++i)
{
if (maze[i][j] == 'E' || maze[i][j] == 'D')
attrset(COLOR_PAIR(1));
if (maze[i][j] == '.')
attrset(COLOR_PAIR(1));
if (maze[i][j] == 'X')
attrset(COLOR_PAIR(4));
if (maze[i][j] == 'o')
attrset(COLOR_PAIR(3));
if (maze[i][j] == 'Z')
attrset(COLOR_PAIR(5));
if (maze[i][j] == ' ')
attrset(COLOR_PAIR(6));
printw("%c",maze[i][j]);
}
printw("\n");
}
refresh();  
napms(30);
} 
