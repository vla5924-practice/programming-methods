#include <stdio.h>
#include <math.h>

void main() {
	double x1, y1, r1, x2, y2, r2, l;
	printf("Enter center coordinates of circle #1 (with a space between): ");
	scanf("%lf %lf", &x1, &y1);
	printf("Enter radius of circle #1: ");
	scanf("%lf", &r1);
	printf("\nEnter center coordinates of circle #2 (with a space between): ");
	scanf("%lf %lf", &x2, &y2);
	printf("Enter radius of circle #2: ");
	scanf("%lf", &r2);
	printf("\nSummary: circle #1 has center in (%lf, %lf) and radius %lf, circle #2 has center in (%lf, %lf) and radius %lf.\n", x1, y1, r1, x2, y2, r2);

	if ((r1 <= 0) || (r2 <= 0)) {
		printf("At least one [radius] parameter is incorrect: you must enter a float number exceeding 0. Start again, please.\n");
		return;
	}

	if ((x1 == x2) && (y1 == y2) && (r1 == r2)) {
		printf("Circles match (radiuses and center coordinates are equal).\n");
		return;
	}

	l = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	if (l > r1 + r2) {
		printf("Circles does not intersect (no common points).\n");
		return;
	}

	if (l == r1 + r2) {
		printf("Circles concern outside (1 common point).\n");
		return;
	}

	if ((l == r1 - r2) || (l == r2 - r1)) {
		printf("Circles concern inside (1 common point).\n");
		return;
	}

	if ((l < r1 - r2) || (l < r2 - r1)) {
		printf("Circle is inside another one (no common points).\n");
		return;
	}

	printf("Circles intersect (2 common points).\n");
	return;
}