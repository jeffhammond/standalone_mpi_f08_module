// SPDX-License-Identifier: MIT

#include <string.h>
#include <mpi.h>
#include "ISO_Fortran_binding.h"
#include "convert_handles.h"
#include "convert_constants.h"

void C_MPI_Info_create(int * info_f, int * ierror)
{
    MPI_Info info = MPI_INFO_NULL;
    *ierror = MPI_Info_create(&info);
    *info_f = MPI_Info_c2f(info);
    C_MPI_RC_FIX(*ierror);
}

void C_MPI_Info_delete(int * info_f, char * key, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    *ierror = MPI_Info_delete(info, key);
    C_MPI_RC_FIX(*ierror);
}

#ifdef HAVE_CFI
void CFI_MPI_Info_delete(int * info_f, CFI_cdesc_t * key_d, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    char * key = key_d -> base_addr;
    *ierror = MPI_Info_delete(info, key);
    C_MPI_RC_FIX(*ierror);
}
#endif

void C_MPI_Info_dup(int * info_f, int * newinfo_f, int * ierror)
{
    MPI_Info newinfo = MPI_INFO_NULL;
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    *ierror = MPI_Info_dup(info,&newinfo);
    *newinfo_f = MPI_Info_c2f(newinfo);
    C_MPI_RC_FIX(*ierror);
}

void C_MPI_Info_free(int * info_f, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    *ierror = MPI_Info_free(&info);
    *info_f = MPI_Info_c2f(info);
    C_MPI_RC_FIX(*ierror);
}

void C_MPI_Info_get_nkeys(int * info_f, int * nkeys_f, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    *ierror = MPI_Info_get_nkeys(info, nkeys_f);
    C_MPI_RC_FIX(*ierror);
}

void C_MPI_Info_get_nthkey(int * info_f, int * n, char * key, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    *ierror = MPI_Info_get_nthkey(info, *n, key);
    C_MPI_RC_FIX(*ierror);
}

#ifdef HAVE_CFI
void CFI_MPI_Info_get_nthkey(int * info_f, int * n, CFI_cdesc_t * key_d, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    char * key = key_d -> base_addr;
    *ierror = MPI_Info_get_nthkey(info, *n, key);
    C_MPI_RC_FIX(*ierror);
}
#endif

void C_MPI_Info_get_string(int * info_f, char * key, int * buflen, char * val, int * flag, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    memset(val,0,*buflen);
#if (MPI_VERSION >= 4)
    // In C, buflen includes the required space for the null terminator.
    *ierror = MPI_Info_get_string(info, key, buflen, val, flag);
#else
    // The length returned in C does not include the end-of-string character.
    *ierror = MPI_Info_get(info, key, *buflen, val, flag);
    if (*ierror == MPI_SUCCESS) {
        *ierror = MPI_Info_get_valuelen(info, key, buflen, flag);
        (*buflen)++;
    }
#endif
    C_MPI_RC_FIX(*ierror);
}

#ifdef HAVE_CFI
void CFI_MPI_Info_get_string(int * info_f, CFI_cdesc_t * key_d, int * buflen, CFI_cdesc_t * val_d, int * flag, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    char * key = key_d -> base_addr;
    char * val = val_d -> base_addr;
    memset(val,0,*buflen);
#if (MPI_VERSION >= 4)
    // In C, buflen includes the required space for the null terminator.
    *ierror = MPI_Info_get_string(info, key, buflen, val, flag);
#else
    // The length returned in C does not include the end-of-string character.
    *ierror = MPI_Info_get(info, key, *buflen, val, flag);
    if (*ierror == MPI_SUCCESS) {
        *ierror = MPI_Info_get_valuelen(info, key, buflen, flag);
        (*buflen)++;
    }
#endif
    C_MPI_RC_FIX(*ierror);
}
#endif

void C_MPI_Info_set(int * info_f, char * key, char * val, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    *ierror = MPI_Info_set(info, key, val);
    C_MPI_RC_FIX(*ierror);
}

#ifdef HAVE_CFI
void CFI_MPI_Info_set(int * info_f, CFI_cdesc_t * key_d, CFI_cdesc_t * val_d, int * ierror)
{
    MPI_Info info = C_MPI_INFO_F2C(*info_f);
    char * key = key_d -> base_addr;
    char * val = val_d -> base_addr;
    *ierror = MPI_Info_set(info, key, val);
    C_MPI_RC_FIX(*ierror);
}
#endif
