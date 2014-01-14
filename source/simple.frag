#version 150

in vec2 tx;

out vec4 fragColor;

void main()
{	
	
	// get the length of the texture derivatives
	float lambda_s = length(dFdx(tx));
	float lambda_t = length(dFdy(tx));

	// compute the sample level, based on the maximum derivative, and the interpolation factor between ceiled and floored level
	float level_s;    
	float interp_s = modf(-log2(max(lambda_s, lambda_t)), level_s);
	        
	// get the new texture coordinate by scaling the texture coordinate by the floored and ceiled level
	vec2 tx_down = tx * pow(2, level_s);         
	vec2 tx_up = tx * pow(2, level_s + 1);

	// compute the color procedural
	vec2 highlight_down = clamp(cos(tx_down * 0.2) - 0.95, 0,1) * 10;
	vec2 highlight_up = clamp(cos(tx_up * 0.2) - 0.95, 0,1) * 10;
	// this might be faster, but it doesn't fade nicely...
	//float highlight_down = step(0.9, fract(tx_down * 0.04)) * 0.8;
	//float highlight_up = step(0.9, fract(tx_up * 0.04)) * 0.8;

	// lerp between the intensities
	fragColor = vec4(1 - clamp(mix(
		max(highlight_down.x, highlight_down.y), 
		max(highlight_up.x, highlight_up.y), 
		interp_s), 0,1));
}
