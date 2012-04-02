__kernel void pass_along(__global const float4* source, 
						__global float4* destination, 
						int numInstances,
						int offset,
						__global uint* indirectCommandData,
						int indirectCommandOffset,
						float16 MVP
						)
{
 
    int iGID = get_global_id(0);

	//don't process if this thread's index is greater than the total number of instances
    if (iGID >= numInstances)
    {   
        return; 
    }
    

	float4 translation = source[offset + iGID];

	float4 clipSpace;
	clipSpace.x = dot(MVP.lo.lo, translation);
	clipSpace.y = dot(MVP.lo.hi, translation);
	clipSpace.z = dot(MVP.hi.lo, translation);
	clipSpace.w = dot(MVP.hi.hi, translation);

	if(clipSpace.x < clipSpace.w && clipSpace.x > -clipSpace.w &&
	   clipSpace.y < clipSpace.w && clipSpace.y > -clipSpace.w &&
	   clipSpace.z < clipSpace.w && clipSpace.z > -clipSpace.w
	)
	{
		//increment the primCounter parameter of the indirect command
		uint index = atomic_inc(&indirectCommandData[indirectCommandOffset]);
  
		destination[offset + index] = translation;
	}
	
}

