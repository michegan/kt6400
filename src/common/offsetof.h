#ifndef _OFFSET_OF_H_
#define _OFFSET_OF_H_


// ¼ÆËãÆ«ÒÆÁ¿
#define OFFSET_OF(struct_t, member)  ((size_t)(char*)&((struct_t*)0)->member) 


#endif // _OFFSET_OF_H_