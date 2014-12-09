// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>

#include <Windows.h>
#include <iostream>
using std::ostream;
#include "mymatrix.h"
typedef matrix::MTX<double>  mat ;
typedef matrix::MTX<int> mati;
using std::cout;
using std::endl;
typedef double (*fitfunction)(double *,double *);

// TODO: reference additional headers your program requires here
