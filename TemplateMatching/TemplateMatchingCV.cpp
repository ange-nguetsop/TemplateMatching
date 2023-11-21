// TemplateMatchingCV.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include <Windows.h>
#include<vector>
#include "stdafx.h"
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

using namespace cv;
using namespace std;

/*
// Seuil de distance pour considérer que deux correspondances sont distinctes
const double DISTANCE_THRESHOLD = 30;

bool arePointsTooClose(const cv::Point& pt1, const cv::Point& pt2) {
	return cv::norm(pt1 - pt2) < DISTANCE_THRESHOLD;
}

int main()
{
	// Charger l'image d'entrée et le modèle (template)
	cv::Mat image1 = cv::imread("C:/Repositories/Opencv/TemplateMatching/TemplateOpencv-master/TemplateOpencv/TestPhoto.png", cv::IMREAD_COLOR);
	cv::Mat templ1 = cv::imread("C:/Repositories/Opencv/TemplateMatching/TemplateOpencv-master/TemplateOpencv/tem2.png", cv::IMREAD_COLOR);

	if (image1.empty() || templ1.empty())
	{
		std::cerr << "Impossible de charger l'image ou le modèle." << std::endl;
		return -1;
	}
	cv::Mat image,src,src_t;
	cv::Mat templ;

	cvtColor(image1, src, COLOR_BGR2GRAY);
	cvtColor(templ1, src_t, COLOR_BGR2GRAY);

   // cv::GaussianBlur(src, src, cv::Size(5, 5), 0, 0);
	cv::GaussianBlur(src_t, src_t, cv::Size(3, 3), 0, 0);

	cv::equalizeHist(src, image);
	cv::equalizeHist(src_t, templ);

	// Créer une image résultante pour stocker les correspondances trouvées
	cv::Mat result;
	int result_cols = image.cols -templ.cols + 1;
	int result_rows = image.rows -templ.rows + 1;
	result.create(result_rows, result_cols, CV_32FC1);

	// Effectuer le template matching
	cv::matchTemplate(image, templ, result, cv::TM_CCOEFF_NORMED);

	double threshold = 0.59;
	std::vector<cv::Point> locations;
	cv::findNonZero(result > threshold, locations);

	std::vector<cv::Point> filteredLocations;
	for (const cv::Point& location : locations) {
		bool tooClose = false;
		for (const cv::Point& filteredLocation : filteredLocations) {
			if (arePointsTooClose(location, filteredLocation)) {
				tooClose = true;
				break;
			}
		}
		if (!tooClose) {
			filteredLocations.push_back(location);
		}
	}

	// Marquer les correspondances trouvées dans l'image d'entrée
	for (const cv::Point& location : filteredLocations) {
		cv::rectangle(image1, location, cv::Point(location.x + templ.cols, location.y + templ.rows), cv::Scalar(255, 0, 0), 3);
	}

	// Afficher l'image avec les correspondances détectées
	imshow("image_window", image1);
	//imwrite("Cross.png", image1);
	//imshow("result_window", result);
	cv::waitKey(0);
	cv::destroyAllWindows();
}
*/
int main()
{

	// Charger l'image d'entrée
	cv::Mat image = cv::imread("Test.jpg", cv::IMREAD_COLOR);
	cv::Mat result;
	double minVal, maxVal;
	Point minLoc, maxLoc;
	cv::Point matchLoc;
	int fontFace = cv::FONT_HERSHEY_SIMPLEX; // Le type de police
	double fontScale = 0.5; // Échelle de la police
	cv::Scalar couleurTexte(0, 0, 0); // Couleur du texte (rouge dans cet exemple)
	int epaisseurLigne = 2; // Épaisseur de la ligne du texte
	if (image.empty())
	{
		std::cerr << "Impossible de charger l'image d'entrée." << std::endl;
		return -1;
	}

	// Dossier contenant les images de modèles (templates)
	std::string dossier_modeles = "C:/Repositories/Opencv/TemplateMatchingCV/TemplateMatchingCV/Template";

	// Vérifiez que le dossier existe
	if (!std::filesystem::is_directory(dossier_modeles))
	{
		std::cerr << "Le dossier de modèles n'existe pas." << std::endl;
		return -1;
	}

	// Initialisez un vecteur pour stocker les images de modèles
	std::vector<cv::Mat> templates;

	// Utilisez une boucle pour parcourir les fichiers dans le dossier
	for (const auto& entry : std::filesystem::directory_iterator(dossier_modeles))
	{
		// Vérifiez que le fichier est une image (vous pouvez ajouter d'autres vérifications si nécessaire)
		if (entry.is_regular_file() && entry.path().extension() == ".jpg")
		{
			// Chargez l'image du modèle et ajoutez-la au vecteur
			cv::Mat templateImage = cv::imread(entry.path().string(), cv::IMREAD_COLOR);
			if (!templateImage.empty())
			{
				templates.push_back(templateImage);
			}
			else
			{
				std::cerr << "Impossible de charger l'image du modèle : " << entry.path() << std::endl;
			}
		}
	}
	int i = 0, num1cent = 0, num2Cent = 0, num5Cent = 0, num10Cent = 0, num20Cent = 0, num50Cent = 0, num1Euro = 0, num2Euro = 0;
	for (const cv::Mat& templateImage : templates)
	{

		// Effectuez le template matching comme indiqué précédemment      
		int result_cols = image.cols - templateImage.cols + 1;
		int result_rows = image.rows - templateImage.rows + 1;
		result.create(result_rows, result_cols, CV_32FC1);
		cv::matchTemplate(image, templateImage, result, cv::TM_CCOEFF_NORMED);

		//Normalisez la carte de correspondance, trouvez les correspondances, marquez-les, etc.
		cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

		// Trouvez la position de la meilleure correspondance
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
		matchLoc = maxLoc;

		// Ajoutez un texte au-dessus du rectangle
		cv::Point pointTexte(matchLoc.x + templateImage.cols / 2, matchLoc.y + templateImage.rows / 2); // Position du texte au coin inférieur droit

		double thresh = 0.98;
		cv::Mat thresholded_result;

		std::string texte = "texte";
		switch (i)
		{
		case 0:
			texte = "10 Cent";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num10Cent = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 1:
			// Le texte que vous souhaitez afficher
			texte = "1 Cent";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num1cent = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 2:
			texte = "1 Euro";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num1Euro = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 3:
			texte = "20 Cent";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num20Cent = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 4:
			texte = "2 Cent";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num2Cent = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 5:
			texte = "2 Euro";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num2Euro = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 6:
			texte = "50 Cent";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num50Cent = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;
		case 7:
			texte = "5 Cent";
			cv::threshold(result, thresholded_result, thresh, 1.0, cv::THRESH_BINARY);
			num5Cent = cv::countNonZero(thresholded_result);
			// Si vous souhaitez afficher les correspondances sur l'image d'entrée
			cv::rectangle(image, matchLoc, cv::Point(matchLoc.x + templateImage.cols, matchLoc.y + templateImage.rows), cv::Scalar(0, 0, 255), 2);
			cv::putText(image, texte, pointTexte, fontFace, fontScale, couleurTexte, epaisseurLigne);
			break;

		}

		i++;
	}

	double total;
	total = ((double)num10Cent * 10 + (double)num1cent * 1 + (double)num20Cent * 20 + (double)num50Cent * 50 + (double)num5Cent * 5 + (double)num2Cent * 2) / 100 + num1Euro + num2Euro * 2;
	std::string texte = "Total: " + std::to_string(total) + " Euro";
	cv::putText(image, texte, cv::Point(image.cols / 2, image.rows / 2), fontFace, fontScale, cv::Scalar(0, 0, 0), epaisseurLigne);
	// Afficher l'image avec les correspondances détectées
	cv::imshow("Result", image);
	cv::imwrite("Result.png", image);
	cv::waitKey(0);

	return 0;
}

