#include "ccv.h"

int main(int argc, char** argv)
{
	assert(argc == 2);
	ccv_enable_default_cache();
	ccv_dense_matrix_t* object = 0;
	ccv_read(argv[1], &object, CCV_IO_GRAY | CCV_IO_ANY_FILE);
	ccv_sift_param_t params = {
		.noctaves = 3,
		.nlevels = 6,
		.up2x = 1,
		.edge_threshold = 10,
		.norm_threshold = 0,
		.peak_threshold = 0,
	};
	ccv_array_t* obj_keypoints = 0;
	ccv_dense_matrix_t* obj_desc = 0;
	ccv_sift(object, &obj_keypoints, &obj_desc, 0, params);
	int i, k;
	for (i = 0; i < obj_keypoints->rnum; i++)
	{
		float* odesc = obj_desc->data.f32 + i * 128;
		for (k = 0; k < 128; k++)
		{
			printf("%f ", odesc[k]);
		}
		printf("\n");
	}
	ccv_array_free(obj_keypoints);
	ccv_matrix_free(obj_desc);
	ccv_matrix_free(object);
	ccv_disable_cache();
	return 0;
}

