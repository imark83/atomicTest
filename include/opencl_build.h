
	// PROGRAM CREATION
  for (i=0; i<nProgram; ++i) {
  	program[i] = clCreateProgramWithSource (context, 1, source[i], NULL, &errorCode);
  	if (errorCode != CL_SUCCESS) {
  		fprintf (stderr, "Error creating Program. Error code = %i\n", errorCode);
  		return 0;
  	}
    // PROGRAM BUILD AND BUILD LOG FILE
    if ((errorCode = clBuildProgram (program[i], 1, &device, "-I. -cl-opt-disable", NULL, NULL)) != CL_SUCCESS) {
      fprintf (stderr, "Error building Program. Error code = %i\n", errorCode);

      size_t logSize;
      clGetProgramBuildInfo (program[i], device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
      char *buildLog = (char*) malloc (logSize * sizeof (char));
      clGetProgramBuildInfo (program[i], device, CL_PROGRAM_BUILD_LOG, logSize, buildLog, NULL);
      fprintf (stderr, "BUILD LOG:\n%s\n", buildLog);

      return 0;
    }
    #ifdef BUILD_LOG
    	size_t logSize;
    	clGetProgramBuildInfo (program[i], device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    	char *buildLog = (char*) malloc (logSize * sizeof (char));
    	clGetProgramBuildInfo (program[i], device, CL_PROGRAM_BUILD_LOG, logSize, buildLog, NULL);
    	fprintf (stderr, "BUILD LOG:\n%s\n", buildLog);
    	// return 0;
    #endif

  }


  for (i=0; i<nProgram; ++i) {
  	// KERNEL BUILD AND KERNEL INFO
  	kernel[i] = clCreateKernel (program[i], kernelName[i], &errorCode);
  	if (errorCode != CL_SUCCESS) {
  		fprintf (stderr, "Error creating Kernel. Error code = %i\n", errorCode);
  		return 0;
  	}

  	// clGetKernelWorkGroupInfo (kernel, device,
    //       CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof (size_t),
    //       infoString, NULL);
  	// fprintf (stderr, "\nWarp size = %zi\n", *((size_t*) infoString));
  }
