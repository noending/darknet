#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#ifdef __cplusplus
extern "C"
{
#endif
    int readParams();
    int uv2world(int, int, float*, float*);
    int test(int);
#ifdef __cplusplus
}
#endif
#endif // _DISTANCE_H_
