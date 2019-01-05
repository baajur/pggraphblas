#include "pggraphblas.h"
PG_MODULE_MAGIC;

static void
context_callback_matrix_free(void* m) {
  pgGrB_Matrix *mat = (pgGrB_Matrix *) m;
  GrB_Matrix_free(&mat->A);
}

Datum
matrix_in(PG_FUNCTION_ARGS)
{
  GrB_Info info;
  Datum arr;
  pgGrB_Matrix *retval;
  ArrayType *vals;
  FunctionCallInfoData locfcinfo;
  MemoryContextCallback *ctxcb;
  int ndim, *dims;

  Oid valsType;
  int16 valsTypeWidth;
  bool valsTypeByValue;
  char valsTypeAlignmentCode;
  Datum *valsContent;
  int valsLength;
  bool *valsNullFlags;

  GrB_Index *row_indices, *col_indices;
  int32_t *matrix_values;

  valsType = ObjectIdGetDatum(INT2OID);

  /* /\* A comment from the pg source... */
  /*  * */
  /*  * Normally one would call array_recv() using DirectFunctionCall3, but */
  /*  * that does not work since array_recv wants to cache some data using */
  /*  * fcinfo->flinfo->fn_extra.  So we need to pass it our own flinfo */
  /*  * parameter. */
  /*  *\/ */

  /* /\* arr = DirectFunctionCall3(array_in, *\/ */
  /* /\*                           PG_GETARG_DATUM(0), *\/ */
  /* /\*                           ObjectIdGetDatum(INT2OID), *\/ */
  /* /\*                           Int32GetDatum(-1)); *\/ */

  /* InitFunctionCallInfoData(locfcinfo, */
  /*                          fcinfo->flinfo, */
  /*                          3, */
  /*                          InvalidOid, */
  /*                          NULL, */
  /*                          NULL); */

  /* locfcinfo.arg[0] = PG_GETARG_DATUM(0); */
  /* locfcinfo.arg[1] = ObjectIdGetDatum(INT2OID); */
  /* locfcinfo.arg[2] = Int32GetDatum(-1); */
  /* locfcinfo.argnull[0] = false; */
  /* locfcinfo.argnull[1] = false; */
  /* locfcinfo.argnull[2] = false; */

  /* arr = array_in(&locfcinfo); */

  /* Assert(!locfcinfo.isnull); */

  /* vals = DatumGetArrayTypeP(arr); */

  /* if (ARR_HASNULL(vals)) { */
  /*   ereport(ERROR, (errmsg("Array may not contain NULLs"))); */
  /* } */

  /* ndim = ARR_NDIM(vals); */
  /* if (ndim != 2) { */
  /*   ereport(ERROR, (errmsg("Two-dimesional arrays are required"))); */
  /* } */

  /* dims = ARR_DIMS(vals); */

  /* if (dims[0] != 3) { */
  /*   ereport(ERROR, (errmsg("First dimension must contain 3 arrays"))); */
  /* } */

  /* valsLength = dims[1]; */

  /* get_typlenbyvalalign(valsType, */
  /*                      &valsTypeWidth, */
  /*                      &valsTypeByValue, */
  /*                      &valsTypeAlignmentCode); */

  /* // Extract the array contents (as Datum objects). */
  /* deconstruct_array(vals, */
  /*                   valsType, */
  /*                   valsTypeWidth, */
  /*                   valsTypeByValue, */
  /*                   valsTypeAlignmentCode, */
  /*                   &valsContent, */
  /*                   &valsNullFlags, */
  /*                   &valsLength); */

  /* row_indices = (GrB_Index*) palloc(sizeof(GrB_Index) * valsLength); */
  /* col_indices = (GrB_Index*) palloc(sizeof(GrB_Index) * valsLength); */
  /* matrix_values = (int32_t*) palloc(sizeof(int32_t) * valsLength); */

  /* for (int i = 0; i < valsLength; i++) { */

  /* } */

  retval = (pgGrB_Matrix*) palloc(sizeof(pgGrB_Matrix));

  /*Register context callback to free matrix */

  /* ctxcb = (MemoryContextCallback*) palloc(sizeof(MemoryContextCallback)); */
  /* ctxcb->func = context_callback_matrix_free; */
  /* ctxcb->arg = retval; */
  /* MemoryContextRegisterResetCallback(CurrentMemoryContext, ctxcb); */

  //  GRB_CHECK(GrB_Matrix_new(&retval->A, GrB_INT32, 0, 0));

  PG_RETURN_POINTER(retval);
}

Datum
matrix_out(PG_FUNCTION_ARGS)
{
  pgGrB_Matrix *mat = (pgGrB_Matrix *) PG_GETARG_POINTER(0);
  char *result;

  result = psprintf("{}", 1, 2);
  PG_RETURN_CSTRING(result);
}

void
_PG_init(void)
{
  GrB_Info info;
  info = GrB_init (GrB_BLOCKING);
  if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))
    {
      elog(ERROR, "%s", GrB_error());
      return;
    }
}
