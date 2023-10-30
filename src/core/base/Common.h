#pragma once

#define 	UNUSUED_PARAM(x) 				((void)(x))
#define 	UNUSUED_2PARAMS(x1,x2) 			((void)(x1),(void)(x2))
#define 	UNUSUED_3PARAMS(x1,x2,x3) 		((void)(x1),(void)(x2),(void)(x3))
#define 	UNUSUED_4PARAMS(x1,x2,x3,x4)	((void)(x1),(void)(x2),(void)(x3),(void)(x4))

#define ARRAY_SIZE(s) (sizeof(s)/sizeof(s[0]))
