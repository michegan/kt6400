#ifndef _OFFSET_OF_H_
#define _OFFSET_OF_H_


// ����ƫ����
#define OFFSET_OF(struct_t, member)  ((size_t)(char*)&((struct_t*)0)->member) 


#endif // _OFFSET_OF_H_