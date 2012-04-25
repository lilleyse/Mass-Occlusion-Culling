#version 420 core

/*----------------------------------------------------
	Processes data from the transparency pass.
	
	TODO: Super un-optimized at the moment
-----------------------------------------------------*/

layout (location = 0, index = 0) out vec4 fragColor;

layout(binding = 1, r32ui) readonly uniform uimage2D headsArray;
layout(binding = 2, rgba32ui) readonly uniform uimageBuffer globalsData;

const int limit = 15;

void main()
{

	
	ivec2 screenCoords = ivec2(gl_FragCoord.xy);
	uint linkedListHead = imageLoad(headsArray, screenCoords).r;
	
	if(linkedListHead == 0)
	{
		discard;
	}
	else
	{
		fragColor = vec4(1,0,0,1);
		uvec4 fragData[limit];
		int fragCount = 0;
		
		//store the linked list into fragData
		while(linkedListHead != 0 && fragCount < limit)
		{
			uvec4 data = imageLoad(globalsData, int(linkedListHead));
			fragData[fragCount++] = data;
			linkedListHead = data.x;
		}
	
		//sort fragData from far depth to close depth with bubble sort
		for(int n = fragCount-1; n != 0 ; n--)
		{
			for(int i = 0; i < n; ++i)
			{
				float a = uintBitsToFloat(fragData[i].y);
				float b = uintBitsToFloat(fragData[i+1].y);
				if(a < b)
				{
					uvec4 temp = fragData[i];
					fragData[i] = fragData[i+1];
					fragData[i+1] = temp;
				}
			}
		}
		
		//blend the colors together.
		vec4 outputColor = vec4(0,0,0,0);
		for(int i = 0; i < fragCount; i++)
		{
			uvec4 data = fragData[i];
			vec4 color = vec4(unpackUnorm2x16(data.z), unpackUnorm2x16(data.w));

			outputColor = vec4(mix(outputColor.xyz, color.xyz, color.w), color.w + outputColor.w);
		}
	
		fragColor = outputColor;
	}

	
}