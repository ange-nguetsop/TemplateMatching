# Coin Summation Using Template Matching

## Project Overview
This project aims to deepen knowledge in the domain of template matching through a practical application: identifying and summing the value of coins in an image. The project illustrates the challenges and solutions encountered in applying template matching techniques in image processing.


## Results
The project successfully demonstrates the use of template matching in identifying and summing the value of coins in an image. It highlights the importance of appropriate template selection and image preprocessing in achieving accurate results.

### Original Image
![Processed Image with Identified Coins](https://github.com/ange-nguetsop/TemplateMatching/blob/main/TemplateMatching/Test3.png)
![Processed Image with Identified Coins](https://github.com/ange-nguetsop/TemplateMatching/blob/main/TemplateMatching/Test.png)

### Processed Image
![Processed Image with Identified Coins](https://github.com/ange-nguetsop/TemplateMatching/blob/main/TemplateMatching/Result.png)
![Processed Image with Identified Coins](https://github.com/ange-nguetsop/TemplateMatching/blob/main/TemplateMatching/Cross.png)

## Process Flow
1. **Image Preprocessing**: Initial steps involve preprocessing the image to enhance the template matching effectiveness. Key preprocessing step includes:
   - Blurring the image to reduce noise.

2. **Template Matching Challenges**:
   - Initial attempts were made using templates not sourced from the original image, which resulted in minimal or false matches.

3. **Solution - Extracting Templates from Original Image**:
   - The most effective strategy was to extract the templates directly from the original image. This significantly improved the matching accuracy.

4. **Successful Coin Identification**:
   - With the extracted templates, the template matching process was successful, allowing for accurate identification of coins in the image.

5. **Summation of Total Value**:
   - The final step involved summing up the total value of all identified coins.

## Challenges in Initial Template Matching

During the initial phase of the project, the template matching process faced significant challenges:

1. **Differences in Detail and Lighting**: The template matching algorithm compares pixel to pixel. However, even minor differences in edge definition or brightness levels between the template and the target image led to unsuccessful matches. This was a crucial limitation, as the templates initially used had either more defined contours or varied in brightness compared to the original image.

2. **Attempts to Overcome the Challenges**:
    - **Grayscale Conversion**: Converting the image to grayscale was one of the strategies employed to simplify the image processing. However, this alone was not sufficient to align the brightness and contrast of the template with the target.
    - **Histogram Equalization**: Applying histogram equalization aimed to enhance image contrast. Yet, it did not effectively address the differences in lighting conditions and texture details between the template and the target, resulting in continued mismatches.

3. **Conclusion**: These challenges led to the realization that template matching is highly sensitive to the environment and works best under ideal conditions where the template and target are closely matched in details and lighting. This project's experience underscores the importance of using templates that are very closely aligned with the target image in terms of all visual aspects.

## Technologies Used
- Template Matching Algorithms
- Image Processing Techniques
- 
### Template Example

![Example of a Template Used](https://github.com/ange-nguetsop/TemplateMatching/blob/main/Template/10cent.jpg)

## Conclusion
This project not only deepened the understanding of template matching but also provided practical insights into its application in a real-world scenario. The successful identification and summation of coins from an image using template matching techniques are a testament to the power of this method in image processing.
