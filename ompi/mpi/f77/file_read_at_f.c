/*
 * Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2005 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2006      Cisco Systems, Inc.  All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#include "ompi_config.h"

#include "ompi/mpi/f77/bindings.h"
#include "ompi/mpi/f77/constants.h"
#include "ompi/errhandler/errhandler.h"
#include "ompi/communicator/communicator.h"

#if OMPI_HAVE_WEAK_SYMBOLS && OMPI_PROFILE_LAYER
#pragma weak PMPI_FILE_READ_AT = mpi_file_read_at_f
#pragma weak pmpi_file_read_at = mpi_file_read_at_f
#pragma weak pmpi_file_read_at_ = mpi_file_read_at_f
#pragma weak pmpi_file_read_at__ = mpi_file_read_at_f
#elif OMPI_PROFILE_LAYER
OMPI_GENERATE_F77_BINDINGS (PMPI_FILE_READ_AT,
                           pmpi_file_read_at,
                           pmpi_file_read_at_,
                           pmpi_file_read_at__,
                           pmpi_file_read_at_f,
                           (MPI_Fint *fh, MPI_Offset *offset, char *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *status, MPI_Fint *ierr),
                           (fh, offset, buf, count, datatype, status, ierr) )
#endif

#if OMPI_HAVE_WEAK_SYMBOLS
#pragma weak MPI_FILE_READ_AT = mpi_file_read_at_f
#pragma weak mpi_file_read_at = mpi_file_read_at_f
#pragma weak mpi_file_read_at_ = mpi_file_read_at_f
#pragma weak mpi_file_read_at__ = mpi_file_read_at_f
#endif

#if ! OMPI_HAVE_WEAK_SYMBOLS && ! OMPI_PROFILE_LAYER
OMPI_GENERATE_F77_BINDINGS (MPI_FILE_READ_AT,
                           mpi_file_read_at,
                           mpi_file_read_at_,
                           mpi_file_read_at__,
                           mpi_file_read_at_f,
                           (MPI_Fint *fh, MPI_Offset *offset, char *buf, MPI_Fint *count, MPI_Fint *datatype, MPI_Fint *status, MPI_Fint *ierr),
                           (fh, offset, buf, count, datatype, status, ierr) )
#endif


#if OMPI_PROFILE_LAYER && ! OMPI_HAVE_WEAK_SYMBOLS
#include "ompi/mpi/f77/profile/defines.h"
#endif

void mpi_file_read_at_f(MPI_Fint *fh, MPI_Offset *offset, char *buf, 
			MPI_Fint *count, MPI_Fint *datatype,
			MPI_Fint *status, MPI_Fint *ierr)
{
    MPI_File c_fh = MPI_File_f2c(*fh);
    MPI_Datatype c_type = MPI_Type_f2c(*datatype);
    MPI_Status *c_status;
#if OMPI_SIZEOF_FORTRAN_INTEGER != SIZEOF_INT
    MPI_Status c_status2;
#endif

    /* See if we got MPI_STATUS_IGNORE */

    if (OMPI_IS_FORTRAN_STATUS_IGNORE(status)) {
        c_status = MPI_STATUS_IGNORE;
    } else {

        /* If sizeof(int) == sizeof(INTEGER), then there's no
           translation necessary -- let the underlying functions write
           directly into the Fortran status */

#if OMPI_SIZEOF_FORTRAN_INTEGER == SIZEOF_INT
        c_status = (MPI_Status *) status;
#else
        c_status = &c_status2;
#endif
    }

    *ierr = OMPI_FINT_2_INT(MPI_File_read_at(c_fh, 
					     (MPI_Offset) *offset,
					     buf, 
					     OMPI_FINT_2_INT(*count),
					     c_type, c_status));

#if OMPI_SIZEOF_FORTRAN_INTEGER != SIZEOF_INT
   if (MPI_SUCCESS == OMPI_FINT_2_INT(*ierr) &&
       MPI_STATUS_IGNORE != c_status) {
        MPI_Status_c2f(c_status, status);
    }
#endif
}
