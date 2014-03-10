#ifndef _IMAGE
#define _IMAGE

void libereimage(void**);
unsigned int ** alloue_image_int(int nl, int nc) ;
unsigned char ** alloue_image_char(int nl, int nc) ;
unsigned char** getrouge(unsigned char**, unsigned int**, int , int );
unsigned char** getvert(unsigned char**, unsigned int**, int , int );
unsigned char** getbleu(unsigned char**, unsigned int**, int , int );
void setrouge(unsigned char**, unsigned int**, int , int );
void setvert(unsigned char**, unsigned int**, int , int );
void setbleu(unsigned char**, unsigned int**, int , int );

#define ROUGE(v) (((v)&0x00FF0000)>>16)
#define VERT(v) (((v)&0x0000FF00)>>8)
#define BLEU(v) (((v)&0x000000FF)>>0)

/*
#define SETROUGE(v32,v8) ((v32)=(v32)|(0x0000FF00&((v8)<<24)))
#define SETVERT(v32,v8) ((v32)=(v32)|(0x00FF0000&((v8)<<16)))
#define SETBLEU(v32,v8) ((v32)=(v32)|(0xFF000000&((v8)<<8)))
*/
#define SETROUGE(v32,v8) ((v32)=(v32)|((v8)<<16))
#define SETVERT(v32,v8)  ((v32)=(v32)|((v8)<<8))
#define SETBLEU(v32,v8) ((v32)=(v32)|((v8)<<0))

#endif
