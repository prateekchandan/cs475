#include "transformer.hpp"
#include "Imageloader.hpp"

void transformer::LoadGLTextures() {	
	
	
	// Load Texture
	Image *image[5];
	
	// allocate space for texture
	image[0] = (Image *) malloc(sizeof(Image));
	image[1] = (Image *) malloc(sizeof(Image));
	image[2] = (Image *) malloc(sizeof(Image));
	image[3] = (Image *) malloc(sizeof(Image));
	image[4] = (Image *) malloc(sizeof(Image));
	if (image[0] == NULL || image[2]==NULL || image[3]==NULL || image[4]==NULL || image[1]==NULL) {
	printf("Error allocating space for image");
	exit(0);
	}
	
	char a[5][100];
	strcpy(a[0],"./img/logo.bmp");
	strcpy(a[1],"./img/metal.bmp");
	strcpy(a[2],"./img/face.bmp");
	strcpy(a[3],"./img/skin.bmp");
	strcpy(a[4],"./img/flap.bmp");

	
	Imageloader img_loader;
	for (int i = 0; i < 4; i++)
	{
		if (!img_loader.ImageLoad(a[i], image[i])) {
			exit(1);
		} 
	}
	
	for (int i = 0; i < 4; i++)
	{
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);   // 2d texture (x and y size)
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image[i]->sizeX, image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->data);
	}
	
	glEnable(GL_TEXTURE_2D);
};

