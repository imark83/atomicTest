  // OPEN CL INITIALIZE
	cl_int errorCode;
	char infoString[500];

		/* PLATFORM INITIALIZE AND PLATFORM INFO */
		if ((errorCode = clGetPlatformIDs(1, platform, NULL)) != CL_SUCCESS) {
			fprintf (stderr, "Error getting Platform ID. Error code = %i\n", errorCode);
			return 0;
		}
		fprintf (stderr, "PLATFORM INFO:\n");

		clGetPlatformInfo (platform[0], CL_PLATFORM_PROFILE, 500, infoString, NULL);
		fprintf (stderr, "\tPlatform profile    = %s\n", infoString);

		clGetPlatformInfo (platform[0], CL_PLATFORM_VERSION, 500, infoString, NULL);
		fprintf (stderr, "\tPlatform version    = %s\n", infoString);

		clGetPlatformInfo (platform[0], CL_PLATFORM_NAME, 500, infoString, NULL);
		fprintf (stderr, "\tPlatform name       = %s\n", infoString);

		clGetPlatformInfo (platform[0], CL_PLATFORM_VENDOR, 500, infoString, NULL);
		fprintf (stderr, "\tPlatform vendor     = %s\n", infoString);
#ifndef DEVICE_GPU
		if ((errorCode = clGetDeviceIDs(platform[0], CL_DEVICE_TYPE_CPU, 1, &device, NULL)) != CL_SUCCESS) {
			fprintf (stderr, "Error getting Device ID. Error code = %i\n", errorCode);
			return 0;
		}
#else
		if ((errorCode = clGetDeviceIDs(platform[0], CL_DEVICE_TYPE_GPU, 1, &device, NULL)) != CL_SUCCESS) {
			fprintf (stderr, "Error getting Device ID. Error code = %i\n", errorCode);
			return 0;
		}
#endif

		fprintf (stderr, "DEVICE INFO:\n");

		clGetDeviceInfo (device, CL_DEVICE_NAME, 500, infoString, NULL);
		fprintf (stderr, "\tDevice name:        %s\n", infoString);

		clGetDeviceInfo (device, CL_DEVICE_ADDRESS_BITS, 500, infoString, NULL);
		fprintf (stderr, "\tDevice default address bits = %u\n", *((cl_uint *) infoString));

		clGetDeviceInfo (device, CL_DEVICE_AVAILABLE, 500, infoString, NULL);
		fprintf (stderr, "\tDevice available            = ");
			if (infoString[0]) fprintf (stderr, "TRUE\n");
			else fprintf (stderr, "FALSE\n");

		clGetDeviceInfo (device, CL_DEVICE_GLOBAL_MEM_SIZE, 500, infoString, NULL);
		fprintf (stderr, "\tDevice global mem size (MB) = %lu\n", (*((cl_ulong *) infoString) / 1024 / 1024));

		clGetDeviceInfo (device, CL_DEVICE_LOCAL_MEM_SIZE, 500, infoString, NULL);
		fprintf (stderr, "\tDevice local mem size (KB)  = %lu\n", (*((cl_ulong *) infoString) / 1024));

		clGetDeviceInfo (device, CL_DEVICE_LOCAL_MEM_TYPE, 500, infoString, NULL);
		fprintf (stderr, "\tDevice local mem type       = ");
			if (*((unsigned int *) infoString) == CL_LOCAL) fprintf (stderr, "LOCAL\n");
			if (*((unsigned int *) infoString) == CL_GLOBAL) fprintf (stderr, "GLOBAL\n");

		clGetDeviceInfo (device, CL_DEVICE_MAX_CLOCK_FREQUENCY, 500, infoString, NULL);
		fprintf (stderr, "\tDevice clock freq (MHz)     = %lu\n", *((cl_ulong *) infoString));

		clGetDeviceInfo (device, CL_DEVICE_MAX_COMPUTE_UNITS, 500, infoString, NULL);
		fprintf (stderr, "\tDevice compute units        = %lu\n", *((cl_ulong *) infoString));

		clGetDeviceInfo (device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 500, infoString, NULL);
		fprintf (stderr, "\tDevice compute max sizes    = %zi, %zi, %zi\n", *((size_t *) infoString),
					*((size_t *) infoString+1), *((size_t *) infoString+2));

		clGetDeviceInfo (device, CL_DEVICE_MAX_WORK_GROUP_SIZE, 500, infoString, NULL);
		fprintf (stderr, "\tDevice compute max sizes    = %zi\n", *((size_t *) infoString));

	/* CONTEXT CREATION */
	context = clCreateContext (NULL, 1, &device, NULL, NULL, &errorCode);
	if (errorCode != CL_SUCCESS) {
		fprintf (stderr, "Error creating Context. Error code = %i\n", errorCode);
		return 0;
	}


	/* QUEUE CREATION */
#ifdef DEVICE_GPU

	queue = clCreateCommandQueue (context, device, CL_QUEUE_PROFILING_ENABLE, &errorCode);
	if (errorCode != CL_SUCCESS) {
		fprintf (stderr, "Error creating queue. Error code = %i\n", errorCode);
		return 0;
	}
#else
  cl_queue_properties queue_properties[] =
        {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
	queue = clCreateCommandQueueWithProperties (context, device, queue_properties, &errorCode);
	if (errorCode != CL_SUCCESS) {
		fprintf (stderr, "Error creating queue. Error code = %i\n", errorCode);
		return 0;
	}
#endif
