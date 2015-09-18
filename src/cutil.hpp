/* Copyright © 2013 Paulo Roberto Urio */

#ifndef CUTIL_H_
#define CUTIL_H_

#include <cstdio>
#include <cstdlib>

#include <cuda.h>
#include <curand.h>
#include <cusparse.h>

#define cudaSafeCall(func) _cudaSafeCall(func, __FILE__, __LINE__)

extern inline void _cudaSafeCall(const cudaError_t ret, const char *file,
                                 const int line) {
  if (ret != cudaSuccess) {
    fprintf(stderr, "cudaSafeCall() failed at %s:%i: %s (err=%d)\n", file, line,
            cudaGetErrorString(ret), ret);
    cudaDeviceReset();
    exit(EXIT_FAILURE);
  }
}

#define cudaCheckError() _cudaCheckError(__FILE__, __LINE__)

extern inline void _cudaCheckError(const char *file, const int line) {
#ifndef NDEBUG
  cudaDeviceSynchronize();
#endif
  cudaError_t ret = cudaPeekAtLastError();
  if (ret != cudaSuccess) {
    fprintf(stderr, "cudaCheckError() failed at %s:%i: %s\n", file, line,
            cudaGetErrorString(cudaGetLastError()));
#ifndef NDEBUG
    switch (ret) {
    case cudaErrorMissingConfiguration:
      fprintf(stderr, "Error type: cudaErrorMissingConfiguration\n");
      fprintf(stderr, "Missing configuration error.\n");
      break;
    case cudaErrorMemoryAllocation:
      fprintf(stderr, "Error type: cudaErrorMemoryAllocation\n");
      fprintf(stderr, "Memory allocation error.\n");
      break;
    case cudaErrorInitializationError:
      fprintf(stderr, "Error type: cudaErrorInitializationError\n");
      fprintf(stderr, "Initialization error.\n");
      break;
    case cudaErrorLaunchFailure:
      fprintf(stderr, "Error type: cudaErrorLaunchFailure\n");
      fprintf(stderr, "Launch failure.\n");
      break;
    case cudaErrorPriorLaunchFailure:
      fprintf(stderr, "Error type: cudaErrorPriorLaunchFailure\n");
      fprintf(stderr, "Prior launch failure.\n");
      break;
    case cudaErrorLaunchTimeout:
      fprintf(stderr, "Error type: cudaErrorLaunchTimeout\n");
      fprintf(stderr, "Launch timeout error.\n");
      break;
    case cudaErrorLaunchOutOfResources:
      fprintf(stderr, "Error type: cudaErrorLaunchOutOfResources\n");
      fprintf(stderr, "Launch out of resources error.\n");
      break;
    case cudaErrorInvalidDeviceFunction:
      fprintf(stderr, "Error type: cudaErrorInvalidDeviceFunction\n");
      fprintf(stderr, "Invalid device function.\n");
      break;
    case cudaErrorInvalidConfiguration:
      fprintf(stderr, "Error type: cudaErrorInvalidConfiguration\n");
      fprintf(stderr, "Invalid configuration.\n");
      break;
    case cudaErrorInvalidDevice:
      fprintf(stderr, "Error type: cudaErrorInvalidDevice\n");
      fprintf(stderr, "Invalid device.\n");
      break;
    case cudaErrorInvalidValue:
      fprintf(stderr, "Error type: cudaErrorInvalidValue\n");
      fprintf(stderr, "Invalid value.\n");
      break;
    case cudaErrorInvalidPitchValue:
      fprintf(stderr, "Error type: cudaErrorInvalidPitchValue\n");
      fprintf(stderr, "Invalid pitch value.\n");
      break;
    case cudaErrorInvalidSymbol:
      fprintf(stderr, "Error type: cudaErrorInvalidSymbol\n");
      fprintf(stderr, "Invalid symbol.\n");
      break;
    case cudaErrorMapBufferObjectFailed:
      fprintf(stderr, "Error type: cudaErrorMapBufferObjectFailed\n");
      fprintf(stderr, "Map buffer object failed.\n");
      break;
    case cudaErrorUnmapBufferObjectFailed:
      fprintf(stderr, "Error type: cudaErrorUnmapBufferObjectFailed\n");
      fprintf(stderr, "Unmap buffer object failed.\n");
      break;
    case cudaErrorInvalidHostPointer:
      fprintf(stderr, "Error type: cudaErrorInvalidHostPointer\n");
      fprintf(stderr, "Invalid host pointer.\n");
      break;
    case cudaErrorInvalidDevicePointer:
      fprintf(stderr, "Error type: cudaErrorInvalidDevicePointer\n");
      fprintf(stderr, "Invalid device pointer.\n");
      break;
    case cudaErrorInvalidTexture:
      fprintf(stderr, "Error type: cudaErrorInvalidTexture\n");
      fprintf(stderr, "Invalid device pointer.\n");
      break;
    case cudaErrorInvalidTextureBinding:
      fprintf(stderr, "Error type: cudaErrorInvalidTextureBinding\n");
      fprintf(stderr, "Invalid texture binding.\n");
      break;
    case cudaErrorInvalidChannelDescriptor:
      fprintf(stderr, "Error type: cudaErrorInvalidChannelDescriptor\n");
      fprintf(stderr, "Invalid channel descriptor.\n");
      break;
    case cudaErrorInvalidMemcpyDirection:
      fprintf(stderr, "Error type: cudaErrorInvalidMemcpyDirection\n");
      fprintf(stderr, "Invalid memcpy direction.\n");
      break;
    case cudaErrorAddressOfConstant:
      fprintf(stderr, "Error type: cudaErrorAddressOfConstant\n");
      fprintf(stderr, "Address of constant error.\n");
      break;
    case cudaErrorTextureFetchFailed:
      fprintf(stderr, "Error type: cudaErrorTextureFetchFailed\n");
      fprintf(stderr, "Texture fetch failed.\n");
      break;
    case cudaErrorTextureNotBound:
      fprintf(stderr, "Error type: cudaErrorTextureNotBound\n");
      fprintf(stderr, "Texture not bound error.\n");
      break;
    case cudaErrorSynchronizationError:
      fprintf(stderr, "Error type: cudaErrorSynchronizationError\n");
      fprintf(stderr, "Synchronization error.\n");
      break;
    case cudaErrorInvalidFilterSetting:
      fprintf(stderr, "Error type: cudaErrorInvalidFilterSetting\n");
      fprintf(stderr, "Invalid filter setting.\n");
      break;
    case cudaErrorInvalidNormSetting:
      fprintf(stderr, "Error type: cudaErrorInvalidNormSetting\n");
      fprintf(stderr, "Invalid norm setting.\n");
      break;
    case cudaErrorCudartUnloading:
      fprintf(stderr, "Error type: cudaErrorCudartUnloading\n");
      fprintf(stderr, "CUDA runtime unloading.\n");
      break;
    case cudaErrorUnknown:
      fprintf(stderr, "Error type: cudaErrorUnknown\n");
      fprintf(stderr, "Unknown error condition.\n");
      break;
    case cudaErrorNotYetImplemented:
      fprintf(stderr, "Error type: cudaErrorNotYetImplemented\n");
      fprintf(stderr, "Function not yet implemented.\n");
      break;
    case cudaErrorMemoryValueTooLarge:
      fprintf(stderr, "Error type: cudaErrorMemoryValueTooLarge\n");
      fprintf(stderr, "Memory value too large.\n");
      break;
    case cudaErrorInvalidResourceHandle:
      fprintf(stderr, "Error type: cudaErrorInvalidResourceHandle\n");
      fprintf(stderr, "Invalid resource handle.\n");
      break;
    case cudaErrorNotReady:
      fprintf(stderr, "Error type: cudaErrorNotReady\n");
      fprintf(stderr, "Not ready error.\n");
      break;
    case cudaErrorInsufficientDriver:
      fprintf(stderr, "Error type: cudaErrorInsufficientDriver\n");
      fprintf(stderr, "CUDA runtime is newer than driver.\n");
      break;
    case cudaErrorSetOnActiveProcess:
      fprintf(stderr, "Error type: cudaErrorSetOnActiveProcess\n");
      fprintf(stderr, "Set on active process error.\n");
      break;
    case cudaErrorNoDevice:
      fprintf(stderr, "Error type: cudaErrorNoDevice\n");
      fprintf(stderr, "No available CUDA device.\n");
      break;
    }
#endif
    cudaDeviceReset();
    exit(EXIT_FAILURE);
  }
}

#define curandSafeCall(func) _curandSafeCall(func, __FILE__, __LINE__)

extern inline curandStatus_t _curandSafeCall(const curandStatus_t ret,
                                             const char *file, const int line) {
#ifndef NDEBUG
  cudaDeviceSynchronize();
#endif
  if (ret != CURAND_STATUS_SUCCESS) {
    fprintf(stderr, "curandSafeCall() failed at %s:%i: (err=%d)\n", file, line,
            ret);
#ifndef NDEBUG
    switch (ret) {
    case CURAND_STATUS_VERSION_MISMATCH:
      fprintf(stderr, "Error type: CURAND_STATUS_VERSION_MISMATCH\n");
      fprintf(stderr, "Header file and linked library version do not match.\n");
      break;
    case CURAND_STATUS_NOT_INITIALIZED:
      fprintf(stderr, "Error type: CURAND_STATUS_NOT_INITIALIZED\n");
      fprintf(stderr, "Generator not initialized.\n");
      break;
    case CURAND_STATUS_ALLOCATION_FAILED:
      fprintf(stderr, "Error type: CURAND_STATUS_ALLOCATION_FAILED\n");
      fprintf(stderr, "Memory allocation failed.\n");
      break;
    case CURAND_STATUS_TYPE_ERROR:
      fprintf(stderr, "Error type: CURAND_STATUS_TYPE_ERROR\n");
      fprintf(stderr, "Generator is wrong type.\n");
      break;
    case CURAND_STATUS_OUT_OF_RANGE:
      fprintf(stderr, "Error type: CURAND_STATUS_OUT_OF_RANGE\n");
      fprintf(stderr, "Argument out of range.\n");
      break;
    case CURAND_STATUS_LENGTH_NOT_MULTIPLE:
      fprintf(stderr, "Error type: CURAND_STATUS_LENGTH_NOT_MULTIPLE\n");
      fprintf(stderr, "Length requested is not a multple of dimension.\n");
      break;
    case CURAND_STATUS_DOUBLE_PRECISION_REQUIRED:
      fprintf(stderr, "Error type: CURAND_STATUS_DOUBLE_PRECISION_REQUIRED\n");
      fprintf(stderr, "GPU does not have double precision required by "
                      "MRG32k3a.\n");
      break;
    case CURAND_STATUS_LAUNCH_FAILURE:
      fprintf(stderr, "Error type: CURAND_STATUS_LAUNCH_FAILURE\n");
      fprintf(stderr, "Kernel launch failure.\n");
      break;
    case CURAND_STATUS_PREEXISTING_FAILURE:
      fprintf(stderr, "Error type: CURAND_STATUS_PREEXISTING_FAILURE\n");
      fprintf(stderr, "Preexisting failure on library entry.\n");
      break;
    case CURAND_STATUS_INITIALIZATION_FAILED:
      fprintf(stderr, "Error type: CURAND_STATUS_INITIALIZATION_FAILED\n");
      fprintf(stderr, "Initialization of CUDA failed.\n");
      break;
    case CURAND_STATUS_ARCH_MISMATCH:
      fprintf(stderr, "Error type: CURAND_STATUS_ARCH_MISMATCH\n");
      fprintf(stderr, "Architecture mismatch, GPU does not support requested"
                      " feature.\n");
      break;
    case CURAND_STATUS_INTERNAL_ERROR:
      fprintf(stderr, "Error type: CURAND_STATUS_INTERNAL_ERROR\n");
      fprintf(stderr, "Internal library error.\n");
      break;
    default:
      fprintf(stderr, "No description is associated to this error.\n");
      break;
    }
#endif
    cudaDeviceReset();
    exit(EXIT_FAILURE);
  }
  return ret;
}

#define cusparseSafeCall(func) _cusparseSafeCall(func, __FILE__, __LINE__)

extern inline cusparseStatus_t
_cusparseSafeCall(cusparseStatus_t ret, const char *file, const int line) {
  if (ret != CUSPARSE_STATUS_SUCCESS) {
#ifndef NDEBUG
  cudaDeviceSynchronize();
#endif
    fprintf(stderr, "cusparseSafeCall() failed at%s:%i: (err=%d)\n", file, line,
            ret);
#ifndef NDEBUG
    switch (ret) {
    case CUSPARSE_STATUS_NOT_INITIALIZED:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_NOT_INITIALIZED\n");
      fprintf(stderr, "The cuSPARSE library was not initialized.\n");
      break;
    case CUSPARSE_STATUS_ALLOC_FAILED:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_ALLOC_FAILED\n");
      fprintf(stderr, "Resource allocation failed inside the library.\n");
      break;
    case CUSPARSE_STATUS_INVALID_VALUE:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_INVALID_VALUE\n");
      fprintf(stderr, "An unsupported value or parameter was passed.\n");
      break;
    case CUSPARSE_STATUS_ARCH_MISMATCH:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_ARCH_MISMATCH\n");
      fprintf(stderr,
              "The function requires a feature absent from the device"
              " architecture. Compile and run the application on a device with"
              " appropriate compute capability.\n");
      break;
    case CUSPARSE_STATUS_MAPPING_ERROR:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_MAPPING_ERROR\n");
      fprintf(stderr, "An access to GPU memory space failed.\n");
      break;
    case CUSPARSE_STATUS_EXECUTION_FAILED:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_EXECUTION_FAILED\n");
      fprintf(stderr, "Kernel launch failure on the GPU.\n");
      break;
    case CUSPARSE_STATUS_INTERNAL_ERROR:
      fprintf(stderr, "Error type: CUSPARSE_STATUS_INTERNAL_ERROR\n");
      fprintf(stderr, "An internal cuSPARSE operation failed. This error is "
                      "usually caused by a cudaMemcpyAsync() failure.\n");
      break;
    case CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED:
      fprintf(stderr,
              "Error type: CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED\n");
      fprintf(stderr, "The matrix type is not supported by this function."
                      "Check whether the matrix description is valid.\n");
      break;
    default:
      fprintf(stderr, "No description is associated to this error.\n");
      break;
    }
#endif
    cudaDeviceReset();
    exit(EXIT_FAILURE);
  }
  return ret;
}

#endif // CUTIL_H_
