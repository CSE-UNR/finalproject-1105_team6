#include <stdio.h>
#include <stdbool.h>

#define maxISIZE 100

void loadImage(char filename[], char image[maxISize][maxISize], int *size);
void displayImage(char image[maxISize][maxISize], int size);
void editImage(char image[maxISize][maxISize], int size);
void cropImage(char image[maxISize][maxISize], int *size);
void dimImage(char image[maxISize][maxISize], int size);
void brightenImage(char image[maxISize][maxISize], int size);
void saveImage(char image[maxISize][maxISize], int size);

int main(){

char image[maxISize][maxISize];
int imageSize = 0;
int choice;
	
do{
	printf("\n**ERINSTAGRAM**\n");
	printf("1: Load image\n");
	printf("2: Display image\n");
	printf("3: Edit image\n");
	printf("0: Exit\n");
	printf("\nChoose from one of the options above: ");
	scanf("%d", &choice);
		
	switch (choice){
        	case 1:
        		loadImage("", image, &imageSize);
	  		break;
		case 2:
        		displayImage(image, imageSize);
        		break;
        	case 3:
			editImage(image, imageSize);
			break;
  		case 0:
 			printf("Exiting the Program.\n");
			break;
		default:
			printf("Not an Option. Please use options 0-3.\n");
		}
	} while (choice != 0);
	
	return 0;
}

