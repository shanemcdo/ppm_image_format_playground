#include<stdio.h>
#include<math.h>

#define MIN(a, b) ({\
	typeof(a) _a = (a);\
	typeof(b) _b = (b);\
	a < b ? a : b;\
})

double distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// https://www.youtube.com/watch?v=xNX9H_ZkfNE
// https://netpbm.sourceforge.net/doc/ppm.html
int main(void) {
	const char* output_path = "output.ppm";
	FILE* file = fopen(output_path, "wb");
	const int scale = 60;
	const int width = 16 * scale;
	const int height = 9 * scale;
	const int max_color_val = 255;
	const int radius = MIN(width, height) / 2;
	const int center_x = width / 2;
	const int center_y = height / 2;
	// Magic nubmer
	fprintf(file, "P6\n");
	// width & height
	fprintf(file, "%d %d\n", width, height);
	// Max color value
	fprintf(file, "%d\n", max_color_val);

	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int red = (1.0 * y) / height * max_color_val;
			int green = (1.0 * x) / width * max_color_val;
			int blue = 0;
			int dist = distance(center_x, center_y, x, y);
			if(dist <= radius) {
				red = max_color_val - red;
				green = max_color_val - green;
			}
			// rgb: if maxcolorval > 255 then 2 bytes are needed per color value
			fprintf(file, "%c%c%c", red, green, blue);
		}
	}

	fclose(file);
	printf("Generated to \"%s\"\n", output_path);
	return 0;
}
