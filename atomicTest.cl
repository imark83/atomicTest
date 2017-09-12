#pragma cl_khr_global_int32_base_atomics : enable

__kernel void atomicTest (
      __global volatile int *lock,
      __global int *rop,
      __global int *counter
      ) {
  int i;

  barrier (CLK_LOCAL_MEM_FENCE);
  // START CRITICAL BLOCK
  for (i=0; i<get_local_size(0); ++i) if (get_local_id(0) == i){
    while(atomic_xchg (lock, 1));
    // printf ("thread %zi (local %zi) blocks to add %i at pos %i\n",
        // get_global_id(0), get_local_id(0), towrite[i], *counter);
    rop[*counter] = get_global_id(0);
    ++(*counter);
    atomic_xchg (lock, 0);
  }

  // END CRITICAL BLOCK

  // printf ("Hello from thread %zi/%zi  group id %zi/%zi\n",
  //     get_global_id(0), get_global_size(0),
  //     get_local_id(0), get_local_size(0));

  return;
}
