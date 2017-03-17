
#include <cuda_runtime.h>

#include "cuRDStruct.h"
#include "cuSDStruct.h"

__global__ void odd_even_sort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper);
__global__ void odd_even_sort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper);


