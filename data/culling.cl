__kernel void pass_along(__global const float4* source, __global float4* destination, int iNumElements)
{
    // get index into global data array
    int iGID = get_global_id(0);

    // bound check (equivalent to the limit on a 'for' loop for standard/serial C code
    if (iGID >= iNumElements)
    {   
        return; 
    }
    
    // add the vector elements
	int index = iGID;// + get_global_offset(0);
    destination[index] = source[index];
}

