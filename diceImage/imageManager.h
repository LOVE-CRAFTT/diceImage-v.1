
#pragma once

#include <numeric>
#include "Image.h"


std::vector<int> imageManager()
{

	GrayscaleImage Input;
	Input.Load("ImagesResized 180x90/McrftFace.png");
	/*fprintf(stderr, "width: %d", Input.GetWidth());
	fprintf(stderr, "height: %d", Input.GetHeight());*/
	std::vector <int> avgSegment;
	std::vector <int> finalSegValues;


	int inputWidth = Input.GetWidth();
	int inputHeight = Input.GetHeight();

	//inputSegments are the closest whole number which can cause reading pixels that are off the screen
	//No workaround that I know of since the image width and height may or maynot be cleanly divisible by 12 or 6 respectively
	int segmentSizeX = ((double)inputWidth / 18) + 0.5;
	int segmentSizeY = ((double)inputHeight / 9) + 0.5;
	std::vector<int> segmentArray;



	for (int pixelY = 0; pixelY < inputHeight; pixelY += segmentSizeY)
	{
		
		for (int pixelX = 0; pixelX < inputWidth; pixelX += segmentSizeX)
		{


			//get all the values in a single segment
			for (int segmentY = pixelY; segmentY < (segmentSizeY + pixelY); segmentY++)
			{
				for (int segmentX = pixelX; segmentX < (segmentSizeX + pixelX); segmentX++)
				{
					if ( (segmentX >= inputWidth) || (segmentY >= inputHeight)){}
					else
					{
						segmentArray.push_back(Input(segmentX, segmentY));
					}
					
				}
			}

			//Average over values in the segment and push to avgSegment
			double sum = std::accumulate(segmentArray.begin(), segmentArray.end(), 0.0);
			double average = sum / segmentArray.size();
			int roundAvg = average + 0.5;
			avgSegment.push_back(roundAvg);
			//

			//clear the segmentArray for next run
			segmentArray.clear();
			//

			
		}
	}

	//Normalize to values of 1 - 6
	int maxElement = *std::max_element(avgSegment.begin(), avgSegment.end());
	int minElement = *std::min_element(avgSegment.begin(), avgSegment.end());
	int range = maxElement - minElement;
	int normalized;
	for (int i = 0; i < avgSegment.size(); i++)
	{
		double num = (double)((avgSegment[i] - minElement));
		normalized = 5 * ( (num / range)) + 1 + 0.5;

		finalSegValues.push_back(normalized);
	}
	

	//Testing values are correct
	if (0)
	{
		std::cout << "Segment values are: " <<  std::endl;
		for (int i = 0; i < (avgSegment.size()); i++)
		{
			std::cout << avgSegment[i] << ", ";
		}
		std::cout << std::endl;
		std::cout << "Size is: " << avgSegment.size() << std::endl;
		std::cout << "Max element is: " << maxElement << std::endl;
		std::cout << "Min element is: " << minElement << std::endl;
		std::cout << "Range element is: " << range << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "Segment values normalized are: " << std::endl;
		for (int i = 0; i < (finalSegValues.size()); i++)
		{
			std::cout << finalSegValues[i] << ", ";
		}
		std::cout << std::endl;
		std::cout << "Size is: " << finalSegValues.size() << std::endl;

	}

	return finalSegValues;
	
}
