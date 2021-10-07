#include <ncurses.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#define DX 3

    
int main(int argc, char** argv)
{
  char* filename = (char*) malloc(strlen(argv[1]));
  strcpy(filename, argv[1]);
  char symb[1];
  uint32_t lines_amount = 0;
  uint32_t file_size = 0;
  printf("%s ", filename);
  
  
  int descriptor = open(filename, O_RDONLY);
  while (read(descriptor, symb, 1))
  { 
    file_size++;
    if (symb[0] == '\n')
    {
      lines_amount++;
    }
    

  }
  close(descriptor);
  
  
  printf (" %d \n", lines_amount);


  descriptor = open(filename, O_RDWR);
  char* file = (char*) malloc(file_size + 1);
  read(descriptor, file, file_size);
  file[file_size] = '\0';
  close(descriptor);
  //printf("%s", file);

  uint32_t p = 0;
  uint32_t position = 0;
  char *line[lines_amount];
  for (uint32_t cur_line = 0; cur_line < lines_amount; cur_line++)
  {
    
    p = 0;
    
    while ( (file[position + p] != '\n') && (file[position + p] != '\0') ) 
    {
      p++;
    }



    line[cur_line] = (char*) malloc(p + 2);
    
    for (uint32_t i = 0; i <= p; i++)
      *(line[cur_line] + i) = file[position + i];
    *(line[cur_line] + p + 1) = '\0';
    
    position += (p + 1);

  }
  

  
  for (uint32_t cur_line = 0; cur_line <= lines_amount; cur_line+=2)
  {
    printf ("%s", line[cur_line] );
  };
  
    
  int c = 0;
  initscr();
  noecho();
  refresh();
  
  WINDOW* win;
  win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
  keypad(win, TRUE);    
  scrollok (win, TRUE);
  box(win, 0, 0); 
  int cur_line = 0;
  move( 0, 0);  
  while((c = wgetch(win)) != 27)
  {
    if (c == 32)
    {
      werase(win);
      cur_line++;
    }
    
    for (int i = 0; i < LINES; i++)
    {
      wprintw(win, "--->(%d)%s", (cur_line + i)% lines_amount, line[(cur_line + i) % lines_amount]);
    }
    box(win, 0, 0); 

 
    wrefresh(win);

  }
  endwin();
  return 0;
}
