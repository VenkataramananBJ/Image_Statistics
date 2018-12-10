#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

double median (cv::Mat channel);

int main()
{
	//uncomment the below line to use the image as input
	//cv::Mat img = cv::imread("data/lion.jpg");
	cv::Mat img;	

	//Captures video
	cv::VideoCapture input("data/cars.mp4");
	int image_count = 1;

	for(;;){
		if(!input.read(img))
			break;

	//Color to Grayscale conversion
	cv::cvtColor(img,img, cv::COLOR_BGR2GRAY);

	double minc[1],maxc[1],med;

	//Tiling image into 10 tiles in x direction and 5 tiles in y direction
	int tile_width = img.cols/10;
	int tile_height = img.rows/5;

	//Print out general image info
	std::cout<<"width: "<<tile_width<<"\n";
	std::cout<<"height: "<<tile_height<<"\n";
	int tile_count=1;
	
	//Looping through the tiles (50) of each image
	for(int i=0; i<img.rows;i+=tile_height){
		for (int j=0;j<img.cols;j+=tile_width){

	//Establish the region of interest which in our case is a rectangular tile		
	cv::Rect rect(j,i,tile_width,tile_height);
	cv::Mat roi = img(rect);

	//Finds minimum and maximum value pixel element in the tile
	cv::minMaxLoc (roi,minc, maxc);

	//Finds the mean of all the pixels in the tile
	//cv::Scalar m = mean(roi);

	cv::Scalar mean, stddev;

	//Finds mean and Standard Deviation
	cv::meanStdDev(roi,mean,stddev);
	
	//Finds median through a function call to median()
	med = median(roi);
	
	//Printing out the stats for each tile
	std::cout<<"Stats of Tile number: "<<tile_count<<"\n";
	std::cout<<"Mean: "<<mean[0]<<"\n";
	std::cout<<"Standard Deviation: "<<stddev[0]<<"\n";
	//std::cout<<m[0]<<"\n";
	std::cout<<"Minimum value pixel: "<<minc[0]<<"\n";
	std::cout<<"Maximum value pixel: "<<maxc[0]<<"\n";
	std::cout<<"Median: "<<med<<"\n";

	tile_count++;

	//Displays the region of interest
	cv::imshow("img", roi);


	 cv::waitKey(10);
		}
	}
	std::cout<<"Image Count: "<<image_count<<"\n";
	image_count++;
	char c = cv::waitKey(10);
	if (c==27)
		break;

	}

	return 0;
}

 double median( cv::Mat channel )
    {
        double m = (channel.rows*channel.cols) / 2;
        int bin = 0;
        double med = -1.0;

        int histSize = 256;
        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        cv::Mat hist;

	//Calculates histogram of the tile
        cv::calcHist( &channel, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

	//Computes the middle value through counting the histogram bins
        for ( int i = 0; i < histSize && med < 0.0; ++i )
        {
            bin += cvRound( hist.at< float >( i ) );
            if ( bin > m && med < 0.0 )
                med = i;
        }

        return med;
    }
