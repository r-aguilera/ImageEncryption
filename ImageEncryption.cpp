#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void addNoise(Mat&, const bool);
Vec3b newBGR(Vec3b&, const bool);

enum Mode {ENCRYPT = true, DECRYPT = false};

int main()
{
	Mat image;
	String path;	//String path = "../../media/Squirrel_PNG.png";
	while (image.empty()) {
		cout << "Enter the path and name of the image (relative or absolute):" << endl;
		getline(cin, path);
		// If path is not absolute, make it relative to media directory
		if(path[1] != ':')
			path = "../../media/" + path;
		image = imread(path, IMREAD_COLOR);
		if (image.empty()) {
			cout << "No image was found. Enter path again? (Y/N)" << endl;
			char key = getchar();
			// Consume Enter press
			if(key !='\n')
				getchar();
			// Exit the program if N is pressed
			if (toupper(key) == 'N')
				return 0;
		}
	}
	cout << "Enter password (must be an unsigned integer):" << endl;
	int password = 0;
	scanf("%d", &password);
	if (getchar() != '\n') {};
	srand (password);
	cout << "Encrypt or decript image? (E/D):" << endl;
	char key = getchar();
	// Consume Enter press
	if (key != '\n')
		getchar();
	bool mode = (toupper(key) != 'D') ? ENCRYPT : DECRYPT;
	// Perform the encryption/decryption
	addNoise(image, mode);
	// Overwrite the image
	imwrite(path, image);
	cout << (mode ? "Encryption" : "Decryption") << " successful. Press any key to exit this program." << endl;
	getchar();
	return 0;
}

void addNoise(Mat& image, const bool isEncrypting) {
	for (int i = 0; i < image.cols; ++i) {
		for (int j = 0; j < image.rows; ++j) {
			Vec3b BGR = image.at<Vec3b>(Point(i,j));
			newBGR(BGR, isEncrypting);
			image.at<Vec3b>(Point(i, j)) = BGR; 
		}
	}
}

Vec3b newBGR(Vec3b& BGR, const bool isEncrypting) {
	for (int k = 0; k < 3; ++k) {
		int op = isEncrypting ? 1 : -1;
		int value = BGR(k) + op * (rand() % 256) % 256;
		BGR(k) = value;
	}
	return BGR;
}