
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_phelma.h>
/*
#include <SDL_tab.h>
#include <image.h>
*/

int copyim32toSDL(SDL_Surface* f1, unsigned int ** im, int ligne, int col,int x, int y) { int i,j;
  unsigned char *p;
  if (f1->pixels==NULL || f1->w<col || f1->h<ligne || f1->format->BytesPerPixel !=sizeof(**im)) return -1;
  //for (i=0; i<ligne; i++) 
  //	memcpy(f1->pixels+(y+i)*(f1->pitch)+x*4,im[i],4*col); //f1->format->BytesPerPixel*col); 
     for (i=0; i<ligne; i++) for(j=0; j<col; j++) { p=f1->pixels+(y+i)*(f1->pitch)+(x+j)*4;
       *p++=BLEU(im[i][j]);
       *p++=VERT(im[i][j]); 
       *p++=ROUGE(im[i][j]);
       *p++=0;
     }

  return 0;
}  

int afficheim32SDL(SDL_Surface* f1, unsigned int ** im, int ligne, int col, int x, int y) { int ret;
  ret = copyim32toSDL(f1,im,ligne,col,x,y);
  if (ret==0) SDL_Flip(f1);
  return ret;
}

int copyim8toSDL(SDL_Surface* f1, unsigned char ** im, int ligne, int col, int x, int y) {
  if (f1->pixels==NULL || f1->w<col || f1->h<ligne ) return -1;
  else if (f1->format->BytesPerPixel !=sizeof(**im)) {int i,j;
    for (i=0; i<ligne; i++) for(j=0; j<col; j++) *( ((unsigned int*)f1->pixels+(y+i)*(f1->pitch/f1->format->BytesPerPixel)+j+x)) = im[i][j]<<0|im[i][j]<<16 | im[i][j]<<8; 
    return 0;
  }
return -1;
} 

int afficheim8SDL(SDL_Surface* f1, unsigned char ** im, int ligne, int col, int x, int y) { int ret;
  ret = copyim8toSDL(f1,im,ligne,col,x,y);
  if (ret==0) SDL_Flip(f1);
  return ret;
}

int afficheimageSDL(SDL_Surface* f1, void** im, int ligne, int col, int octetparpixel) {
  switch (octetparpixel) {
     case 1 : return afficheim8SDL(f1,(unsigned char**)im,ligne,col,0,0);
     case 4 : return afficheim32SDL(f1,(unsigned int**)im,ligne,col,0,0);
  }
  return -1;
}

unsigned int** SDLtoim32(SDL_Surface* f1) { unsigned int** im=NULL;
  if(f1==NULL) return NULL;
  im=alloue_image_int(f1->h,f1->w);
  if (f1->format->BytesPerPixel == 4 || f1->format->BytesPerPixel == 3) { int i,j; unsigned char* p;
     for (i=0; i<f1->h; i++) for(j=0; j<f1->w; j++) { p=( (unsigned char*)f1->pixels+i*(f1->pitch)+j* f1->format->BytesPerPixel);
       im[i][j]=0x00000000| *(p+f1->format->Rshift/8)<<16 | *(p+f1->format->Gshift/8)<<8 |*(p+f1->format->Bshift/8);
     }
  }
  else {int i,j;
    unsigned char c;
    for (i=0; i<f1->h; i++) for(j=0; j<f1->w; j++) { c=*( (unsigned char*)f1->pixels+i*(f1->pitch)+j);
      im[i][j]=0xFF000000|c<<16|c<<8|c;
    }
  }
  return im;
}

unsigned char ** SDLtoim8(SDL_Surface* f1) { unsigned char** im=NULL;
  if(f1==NULL) return NULL;
  im=alloue_image_char(f1->h,f1->w);
  if (f1->format->BytesPerPixel == sizeof(**im)) { int i;
    for (i=0; i<f1->h; i++) memcpy(im[i],(unsigned char*)f1->pixels+i*(f1->pitch),f1->format->BytesPerPixel*f1->w);
  }
  else
    if (f1->format->BytesPerPixel == 3) {int i,j;
    unsigned char* p;
    for (i=0; i<f1->h; i++) for(j=0; j<f1->w; j++) { p=( (unsigned char*)f1->pixels+i*(f1->pitch)+j*3);
      im[i][j]=((*(p+2))+(*(p+1))+*(p))/3;
    }
  }
  else {int i,j;
    unsigned char * p;
    for (i=0; i<f1->h; i++) for(j=0; j<f1->w; j++) { p=( (unsigned char*)f1->pixels+i*(f1->pitch)+j*4);
      im[i][j]=(*(p+2)+*(p+1)+*(p))/3;
    }
  }
  return im;
}

unsigned char ** lectureimage8(char* fichier, int* pnl, int* pnc) { 
  SDL_Surface* imsdl=NULL;
  imsdl=IMG_Load(fichier);
  if (imsdl==NULL) return NULL;
  else { *pnl=imsdl->h; *pnc=imsdl->w; return SDLtoim8(imsdl); }
}

unsigned int ** lectureimage32(char* fichier, int* pnl, int* pnc) { 
  SDL_Surface* imsdl=NULL;
  imsdl=IMG_Load(fichier);
  if (imsdl==NULL) return NULL;
  else { *pnl=imsdl->h; *pnc=imsdl->w; return SDLtoim32(imsdl); }
}


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

/* #ifdef unix */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define O_BINARY 0
#define IO_LEN	(1<<30)	
/* #endif */

#if defined(THINK_C) || defined(__MWERKS__)
#include <unix.h>
#define IO_LEN	(1<<14)	
#endif

#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

#ifdef sun
extern char *sys_errlist[];
char *strerror(int err)
{
return sys_errlist[err];
}
#endif


#define MAGIC_PGM	"P5\n"
#define MAGIC_PPM	"P6\n"

static int match_key(int fd, char *key)
{
  char buf[80];

  read(fd, buf, strlen(key));
  if( strncmp(buf, key, strlen(key)) != 0 )
    return FALSE;
  else
    return TRUE;
}

static void skip_comment(int fd, char code, char *c)
{
  while( *c == code )
    {
      while( (read(fd, c, 1) == 1 ) && (*c != '\n') ) ;
      read(fd, c, 1);
    }
}

static void read_header_line(int fd, char *buf)
{
  int i;

  i = 1;
  while( (read(fd, &buf[i], 1) == 1 ) && (buf[i] != '\n') && (buf[i] != '\r') && (i<79) )
    i++;
  buf[i] = 0;
}

static int get_pgm_header(int fd, char *magic, int *width, int *height)
{
  char buf[80];

  if( !match_key(fd, magic) )
    return FALSE;
  read(fd, buf, 1);
  skip_comment(fd, '#', buf);
  read_header_line(fd, buf);
  sscanf(buf, "%d %d", width, height);
  read(fd, buf, 1);
  skip_comment(fd, '#', buf);
  read_header_line(fd, buf);
  return TRUE;
}

static int open_read(char *filename)
{
  int fd;

  if( (fd = open(filename, O_BINARY|O_RDONLY)) < 0 )
    fprintf(stderr, "can't reset file `%s': %s\n", filename, strerror(errno));
  return fd;
}

static int open_read_pixmap(char *filename, char *magic, int *width, int *height)
{
  int fd;

  if( (fd = open_read(filename)) < 0)
    return fd;
  if( !get_pgm_header(fd, magic, width, height) )
    {
      fprintf(stderr, "can't read header of %s\n", filename);
      return -1;
    }
  return fd;
}

static unsigned char *alloc_pixmap(long size)
{
  unsigned char *data;

  if( (data = (unsigned char *)malloc(size)) == NULL )
    {
    fprintf(stderr, "malloc error\n");
    return NULL;
    }
  return data;
}

static void load_data(int fd, unsigned char *data, long size)
{
  char *buffer;
  int count;

  buffer = (char *)data;
  while( size > 0 )
    {
    count = IO_LEN;
    if( count > size )
      count = size;
    read(fd, buffer, count);
    buffer += count;
    size -= count;
    }
}

static void load_chunky(int fd, unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int width, int height)
{
  unsigned char *buffer, *buf, *buf_R, *buf_G, *buf_B;
  int count;

  buffer = alloc_pixmap(3L*width);
  buf_R = R_data;
  buf_G = G_data;
  buf_B = B_data;
  for( ; height > 0; height-- )
    {
    load_data(fd, buffer, 3L*width);
    count = width;
    buf = buffer;
    while( count-- > 0 )
      {
      *buf_R++ = *buf++;
      *buf_G++ = *buf++;
      *buf_B++ = *buf++;
      }
    }
  free(buffer);
}

unsigned char *load_pixmap(char *filename, int *width, int *height)
{
  int fd;
  long size;
  unsigned char *data;

  if( (fd = open_read_pixmap(filename, MAGIC_PGM, width, height)) < 0)
    return NULL;
  size = (long)*width * *height;
  data = alloc_pixmap(size);
  if( data != NULL )
    load_data(fd, data, size);
  close(fd);
  return data;
}

int load_RGB_pixmap(char *filename, int *width, int *height, unsigned char**R_data, unsigned char**G_data, unsigned char**B_data)
{
  int fd;
  long size;

  if( (fd = open_read_pixmap(filename, MAGIC_PPM, width, height)) < 0)
    return FALSE;
  size = (long)*width * *height;
  *R_data = alloc_pixmap(size);
  *G_data = alloc_pixmap(size);
  *B_data = alloc_pixmap(size);
  
  if( (*R_data != NULL) && (*G_data != NULL ) && (*B_data != NULL ))
    {
    load_chunky(fd, *R_data, *G_data, *B_data, *width, *height);
    close(fd);
    return TRUE;
    }

  close(fd);
  if( *R_data == NULL )
    return FALSE;
  free(*R_data);
  if( *G_data == NULL )
    return FALSE;
  free(*G_data);
  return FALSE;
}




static void put_header_line(int fd, char *buf)
{
  write(fd, buf, strlen(buf));
}

static void put_header_info(int fd, char *mark, char *filename)
{
  char buf[80];
  time_t now;

/*
  sprintf(buf, "%sTitle: %s\n", mark, filename);
  put_header_line(fd, buf);
  now = time(NULL);
  sprintf(buf, "%sCreationDate: %s", mark, ctime(&now));
  put_header_line(fd, buf);
  sprintf(buf, "%sCreator: pixmap_io, P. Chassignet\n", mark);
  put_header_line(fd, buf);
*/
}

static void put_pgm_header(int fd, char *magic, int width, int height, char *filename)
{
  char buf[80];

  put_header_line(fd, magic);
  put_header_info(fd, "# ", filename);
  sprintf(buf, "%d %d\n255\n", width, height);
  put_header_line(fd, buf);
}

static int open_write(char *filename)
{
  int fd;

  if( (fd = open(filename, O_TRUNC|O_CREAT|O_BINARY|O_RDWR,0644)) < 0 )
/*
  if( (fd = open(filename, O_BINARY|O_CREAT|O_TRUNC|O_RDWR, S_IREAD|S_IWRITE)) < 0 )
*/
    fprintf(stderr, "can't Rewrite file `%s': %s\n", filename, strerror(errno));
  return fd;
}

static void store_data(int fd, unsigned char *data, long size)
{
  char *buffer;
  int count;
  
  buffer = (char *)data;
  while( size > 0 )
    {
    count = IO_LEN;
    if( count > size )
      count = size;
    write(fd, buffer, count);
    buffer += count;
    size -= count;
    }
}

static void store_chunky(int fd, unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int width, int height)
{
  unsigned char *buffer, *buf, *buf_R, *buf_G, *buf_B;
  int count;

  buffer = alloc_pixmap(3L*width);
  buf_R = R_data;
  buf_G = G_data;
  buf_B = B_data;
  for( ; height > 0; height-- )
    {
    count = width;
    buf = buffer;
    while( count-- > 0 )
      {
       *buf++ = *buf_R++;
       *buf++ = *buf_G++;
       *buf++ = *buf_B++;
      }
    store_data(fd, buffer, 3L*width);
    }
  free(buffer);
}

void store_pixmap(char *filename, unsigned char *data, int width, int height)
{
  int fd;
  
  if( (fd = open_write(filename)) < 0 )
    return;
  put_pgm_header(fd, MAGIC_PGM, width, height, filename);
  store_data(fd, data, (long)width*height);
  close(fd);
}

void store_RGB_pixmap(char *filename, unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int width, int height)
{
  int fd;
  
  if( (fd = open_write(filename)) < 0 )
    return;
  put_pgm_header(fd, MAGIC_PPM, width, height, filename);
  store_chunky(fd, R_data, G_data, B_data, width, height);
  close(fd);
}


void ecritureimagepgm(char *name, unsigned char **im, int rows, int cols) {
  store_pixmap(name,*im,cols,rows);
}

void ecritureimageppm(char *name, unsigned int**im, int rows, int cols) {
  int i,j,fd,count;
  unsigned char* buffer,* buf;

  if( (fd = open_write(name)) < 0 )
    return;
  put_pgm_header(fd, MAGIC_PPM, cols, rows, name);
  buf=buffer = alloc_pixmap(3L*cols);
  for(i=0; i<rows; i++)   {buf=buffer;
     for (j=0; j<cols; j++) { 
       *buf++ = ROUGE(im[i][j]);
       *buf++ = VERT(im[i][j]);
       *buf++ = BLEU(im[i][j]);
     }
     store_data(fd, buffer, 3L*cols);
  }
  free(buffer);
}
