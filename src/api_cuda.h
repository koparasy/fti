/**
 *  @file   api_cuda.h
 *  @author Max M. Baird(maxbaird.gy@gmail.com)
 *  @date   May, 2018
 *  @brief  Header file for functions that add CUDA support to FTI.
 */

#ifndef _API_CUDA_H
#define _API_CUDA_H

#include <cuda_runtime_api.h>
#include "interface.h"

#define CUDA_ERROR_CHECK(fun)                                                           \
do {                                                                                    \
    cudaError_t err = fun;                                                              \
    char str[FTI_BUFS];                                                                 \
    sprintf(str, "Cuda error %d %s:: %s", __LINE__, __func__, cudaGetErrorString(err)); \
    if(err != cudaSuccess)                                                              \
    {                                                                                   \
      FTI_Print(str, FTI_EROR);                                                         \
      return FTI_NSCS;                                                                  \
    }                                                                                   \
} while(0)

typedef enum FTIT_ptrtype {
    FTIT_PTRTYPE_CPU = 0,
    FTIT_PTRTYPE_GPU
} FTIT_ptrtype;

/** @typedef    FTIT_ptrinfo
 *  @brief      Information of a data pointer.
 *
 *  This type describes necessary information of a data pointer.
 */
typedef struct FTIT_ptrinfo {
    FTIT_ptrtype    type;               /**< Type of this data pointer      */
    int             deviceID;            /**< ID of the GPU that this pointer belongs to */
} FTIT_ptrinfo;

int FTI_get_pointer_info(const void *ptr, FTIT_ptrinfo *ptrInfo);
int FTI_copy_from_device(void *dst, const void *src, size_t count, FTIT_ptrinfo *ptrInfo, FTIT_execution *exec);
int FTI_copy_to_device(void *dst, const void *src, size_t count, FTIT_ptrinfo *ptrInfo, FTIT_execution *exec);

#endif