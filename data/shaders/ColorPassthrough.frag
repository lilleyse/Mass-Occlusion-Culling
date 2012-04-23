#version 420 core

layout (location = 0, index = 0) out vec4 fragColor;
layout(location = 0) in vec4 interpColor;

//layout(early_fragment_tests) in;

layout(binding = 0, offset = 0) uniform atomic_uint nodeCounter;
layout(binding = 1, r32ui) coherent uniform uimage2D headsArray;
layout(binding = 2, rgba32ui) uniform uimageBuffer globalsData;

void main()
{

	//fragColor = interpColor;

	float transparency = .5;
	ivec2 screenCoords = ivec2(gl_FragCoord.xy);
	float depth = gl_FragCoord.z;
	
	uint node = atomicCounterIncrement(nodeCounter) + 1;
	uint prevHeadIndex = imageAtomicExchange(headsArray, screenCoords, node); 
	
	uvec4 globalData;
	globalData.x = prevHeadIndex;
	globalData.y = floatBitsToUint(depth);
	globalData.z = packUnorm2x16(interpColor.xy*transparency);
	globalData.w = packUnorm2x16(interpColor.zw*transparency);
	imageStore(globalsData, int(node), globalData);
	discard;
}
