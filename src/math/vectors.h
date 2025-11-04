#ifndef MS_VECTORS_H_
#define MS_VECTORS_H_

#include <stdint.h>

typedef struct t_vec2_ui32
{
	uint32_t	a;
	uint32_t	b;
} t_vec2_ui32;

typedef struct t_vec2_ui64
{
	uint64_t	a;
	uint64_t	b;
} t_vec2_ui64;

typedef struct t_vec3_ui32
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
} t_vec3_ui32;

typedef struct t_vec3_ui64
{
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
} t_vec3_ui64;

typedef struct t_vec4_ui32
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
} t_vec4_ui32;

typedef struct t_vec4_ui64
{
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
	uint32_t	d;
} t_vec4_ui64;

#endif
