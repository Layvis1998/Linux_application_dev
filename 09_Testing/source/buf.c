#include "buf.h"
	
static void *buf_grow1(void *v, size_t esize, ptrdiff_t n)
{
  struct buf *p;
  size_t max = (size_t)-1 - sizeof(struct buf);
  if (v)
  {
    p = buf_ptr(v);
	if ((n > 0) && (p->capacity + n > max / esize))
	  goto whoops;
	
		p = realloc(p, sizeof(struct buf) + esize * (p->capacity + n));
		if (!p)
		  goto whoops;

		p->capacity = p->capacity + n;
		if (p->size > p->capacity)
		  p->size = p->capacity;		
  }

  else
  {
	if ((size_t)n > max / esize)
	  goto whoops;
	p = malloc(sizeof(struct buf) + esize * n);
	if (!p) 
	  goto whoops;
	p->capacity = n;
	p->size = 0;
  }
  return p->buffer;
	
  whoops:
  
  BUF_ABORT;
  return 0;
}