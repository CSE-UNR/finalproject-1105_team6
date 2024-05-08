//Authors: Cory Coker / Jack Jelinek
//Date Due: 5/7/2024
//Purpose: Final Project - To convert a file wiht numbers into an image, and edit the image in multiple ways

#include <stdio.h>

#define MAX_ROWS 12
#define MAX_COLS 21
void loadNewImage(char image[MAX_ROWS][MAX_COLS], int *rows, int *cols);
void displayCurrentImage(char image[MAX_ROWS][MAX_COLS], int rows, int cols);
void editImage(char image[MAX_ROWS][MAX_COLS], int *rows, int *cols);


int main() {
	char image[MAX_ROWS][MAX_COLS];
	int rows = 0, cols = 0;
	int choice;

	do {
	printf("1: Load image\n");
	printf("2: Display image\n");
	printf("3: Edit image\n");
	printf("0: Exit\n");
	printf("\nChoose from one of the options above: ");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
                loadNewImage(image, &rows, &cols);
                break;	
	case 2:
                displayCurrentImage(image, rows, cols);
                break;
	case 3:
                editImage(image, &rows, &cols);
                break;
	case 0:
                printf("Exiting program.\n");
                break;
	default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

char brightnessToChar(int brightness) {
	switch (brightness) {
		case 0: return ' ';
		case 1: return '.';
		case 2: return 'o';
		case 3: return 'O';
		case 4: return '0';
		default: return ' ';
	}
}

int charToBrightness(char character) {
	switch (character) {
		case ' ': return 0;
		case '.': return 1;
		case 'o': return 2;
		case 'O': return 3;
		case '0': return 4;
		default: return 0;
    }
}


void loadNewImage(char image[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
	char filename[100];
	FILE *file;

	printf("Enter the filename of the image: ");
	scanf("%s", filename);

	file = fopen(filename, "r");
		if (file == NULL) {
		printf("Error opening input file.\n");
	return;
	}


	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			int brightness;
			if (fscanf(file, "%1d", &brightness) != 1) {
			printf("Error reading brightness value.\n");
			fclose(file);
		return;
		}
	image[i][j] = brightnessToChar(brightness);
	}
}

	fclose(file);

   
	*rows = MAX_ROWS;
	*cols = MAX_COLS;

	printf("Image successfully loaded!\n");
}

void displayCurrentImage(char image[MAX_ROWS][MAX_COLS], int rows, int cols) {
	printf("Displaying current image:\n");
	for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
		printf("%c", image[i][j]);
 		}
	printf("\n");
	}
}


void dimImage(char image[MAX_ROWS][MAX_COLS], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (image[i][j] == '.')
			image[i][j] = ' ';
			else if (image[i][j] == 'o')
			image[i][j] = '.';
			else if (image[i][j] == 'O')
			image[i][j] = 'o';
			else if (image[i][j] == '0')
			image[i][j] = 'O';
		}		
	}
	displayCurrentImage(image, rows, cols);
	printf("Image dimmed successfully!\n");
}

char choice;
char filename[100];
FILE *file;
void brightenImage(char image[MAX_ROWS][MAX_COLS], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (image[i][j] == ' ')
			image[i][j] = '.';
			else if (image[i][j] == '.')
			image[i][j] = 'o';
			else if (image[i][j] == 'o')
			image[i][j] = 'O';
			else if (image[i][j] == 'O')
			image[i][j] = '0'	
		}
	}
	displayCurrentImage(image, rows, cols);
	printf("Image brightened successfully!\n");
    	
}


void cropImage(char image[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
	int newLeft, newRight, newTop, newBottom;
	printf("The image you want to crop is %d x %d.\n", *rows, *cols);
 	printf("The row and column values start in the upper lefthand corner.\n\n");
	printf("Which column do you want to be the new left side? ");
	scanf("%d", &newLeft);
	printf("\nWhich column do you want to be the new right side? ");
	scanf("%d", &newRight);
	printf("\nWhich row do you want to be the new top? ");
	scanf("%d", &newTop);
	printf("\nWhich row do you want to be the new bottom? ");
	scanf("%d", &newBottom);


	if (newLeft < 1 || newRight > *cols || newTop < 1 || newBottom > *rows ||
		newLeft > newRight || newTop > newBottom) {
		printf("Invalid crop dimensions.\n");
		return;
    }

	int newRows = newBottom - newTop + 1;
	int newCols = newRight - newLeft + 1;
	char croppedImage[newRows][newCols];
	for (int i = 0; i < newRows; i++) {
		for (int j = 0; j < newCols; j++) {
		croppedImage[i][j] = image[newTop - 1 + i][newLeft - 1 + j];
		}
	}
	*rows = newRows;
	*cols = newCols;
	for (int i = 0; i < newRows; i++) {
		for (int j = 0; j < newCols; j++) {
			image[i][j] = croppedImage[i][j];
		}
	}
	printf("Image cropped successfully!\n");
}

void saveImage(char image[MAX_ROWS][MAX_COLS], int rows, int cols) {
	char filename[100];
	printf("What do you want to name the new image file? (include the extension) ");
	scanf("%s", filename);

	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening output file.\n");
		return;
		}


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int brightness = charToBrightness(image[i][j]);
			fprintf(file, "%d", brightness);
			}
		fprintf(file, "\n");
	}

	fclose(file);
	printf("Image successfully saved as %s!\n", filename);
}


void editImage(char image[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
	int choice;
	do {
		printf("\n**EDIT IMAGE**\n");
		printf("1: Dim image\n");
		printf("2: Brighten image\n");
		printf("3: Crop image\n");
		printf("4: Save image\n");
		printf("0: Exit editing\n");
		printf("\nChoose from one of the options above: ");
		scanf("%d", &choice);

	switch (choice) {
	case 1:
		dimImage(image, *rows, *cols);
		break;
	case 2:
		brightenImage(image, *rows, *cols);
		break;
	case 3:
		cropImage(image, rows, cols);
		break;
	case 4:
                saveImage(image, *rows, *cols);
                break;
	case 0:
		printf("Exiting editing mode.\n");
		break;
	default:
		printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 0);
}




